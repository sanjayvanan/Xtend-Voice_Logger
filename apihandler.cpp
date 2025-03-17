#include "apihandler.h"
#include <QCryptographicHash>
#include <QUrlQuery>
#include <QDebug>
#include <QRegularExpression>
#include <QJsonArray>

APIHandler::APIHandler(QObject *parent)
    : QObject(parent)
    , networkManager(new QNetworkAccessManager(this))
{
}

QString APIHandler::hashPassword(const QString &password)
{
    QByteArray data = password.toUtf8();
    QByteArray hashData = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    return QString(hashData.toHex());
}

void APIHandler::login(const QString &username, const QString &hashedPassword)
{
    QString urlStr = QString("%1?LoginUser()&USERNAME=%2&PWD=%3")
                        .arg(baseUrl, username, hashedPassword);
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onLoginReply(reply);
    });
}

void APIHandler::logout(const QString &token)
{
    QString urlStr = QString("%1?LogoutUser()&token=%2")
                        .arg(baseUrl, token);
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onLogoutReply(reply);
    });
}

void APIHandler::fetchCallDetails(const QString &token, const QString &callRefId)
{
    QString urlStr = QString("%1?ShowVoiceLogs()&token=%2&method=LISTALL")
                        .arg(baseUrl, token);
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onCallDetailsReply(reply);
    });
}

void APIHandler::fetchCallList(const QString &token, 
                             const QDateTime &fromDate,
                             const QDateTime &toDate,
                             const QString &callerNo,
                             const QString &callType,
                             int pageNumber,
                             int pageSize)
{
    QString urlStr = QString("%1?ShowCallLogs()&token=%2&method=LIST&fromdate=%3&todate=%4&pagenumber=%5&pagesize=%6")
        .arg(baseUrl,
             token,
             fromDate.toString("yyyyMMddhhmmss"),
             toDate.toString("yyyyMMddhhmmss"))
        .arg(pageNumber)
        .arg(pageSize);

    if (!callerNo.isEmpty()) {
        urlStr += "&callerno=" + callerNo;
    }
    if (!callType.isEmpty()) {
        urlStr += "&calltype=" + callType;
    }
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onCallDetailsReply(reply);
    });
}

void APIHandler::fetchLiveCalls(const QString &token)
{
    QString urlStr = QString("%1?ShowLiveCalls()&token=%2&method=ACTIVECALLS")
                        .arg(baseUrl, token);
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onLiveCallsReply(reply);
    });
}

void APIHandler::streamWaveFile(const QString &token, const QString &callRefId, const QString &wavPass)
{
    QString urlStr = QString("%1?streamcallwave()&token=%2&callrefid=%3")
                        .arg(baseUrl, token, callRefId);
    
    if (!wavPass.isEmpty()) {
        urlStr += "&wavpass=" + wavPass;
    }
    
    QNetworkReply *reply = networkManager->get(QNetworkRequest(QUrl(urlStr)));
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onWaveFileReply(reply);
    });
}

void APIHandler::onLoginReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        
        if (jsonObj["status"].toString() == "1") {
            emit loginSuccessful(jsonObj["token"].toString());
        } else {
            emit loginFailed(jsonObj["message"].toString());
        }
    } else {
        emit loginFailed(reply->errorString());
    }
    
    reply->deleteLater();
}

void APIHandler::onLogoutReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        
        if (jsonObj["status"].toString() == "1") {
            emit logoutSuccessful();
        } else {
            emit logoutFailed(jsonObj["message"].toString());
        }
    } else {
        emit logoutFailed(reply->errorString());
    }
    
    reply->deleteLater();
}

void APIHandler::onCallDetailsReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        
        // Clean up the JSON response
        QString jsonStr = QString::fromUtf8(responseData);
        
        // Remove trailing commas before closing brackets
        jsonStr.replace(QRegularExpression(",\\s*]"), "]");
        
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &parseError);
        
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON Parse Error:" << parseError.errorString();
            qDebug() << "Raw response:" << jsonStr;
            
            // Create a valid empty response instead of failing
            QJsonObject emptyResponse;
            emptyResponse["status"] = "1";
            emptyResponse["message"] = "No available data";
            emptyResponse["List"] = QJsonArray();
            emptyResponse["TotalCount"] = "0";
            emit callDetailsReceived(emptyResponse);
            
            reply->deleteLater();
            return;
        }
        
        QJsonObject jsonObj = jsonDoc.object();
        if (jsonObj["status"].toString() == "1") {
            // Check if the List array exists and is not empty
            if (jsonObj.contains("List") && jsonObj["List"].isArray()) {
                emit callDetailsReceived(jsonObj);
            } else {
                // Create a valid response with empty list
                QJsonObject emptyResponse;
                emptyResponse["status"] = "1";
                emptyResponse["message"] = "No available data";
                emptyResponse["List"] = QJsonArray();
                emptyResponse["TotalCount"] = "0";
                emit callDetailsReceived(emptyResponse);
            }
        } else {
            // Check if this is an "Internal Server Error" that might be due to no data
            QString errorMsg = jsonObj["message"].toString("Unknown error");
            if (errorMsg.contains("Internal Server Error")) {
                // Create a valid response with empty list
                QJsonObject emptyResponse;
                emptyResponse["status"] = "1";
                emptyResponse["message"] = "No available data";
                emptyResponse["List"] = QJsonArray();
                emptyResponse["TotalCount"] = "0";
                emit callDetailsReceived(emptyResponse);
            } else {
                // Create a valid response with empty list and the error message
                QJsonObject emptyResponse;
                emptyResponse["status"] = "1";
                emptyResponse["message"] = errorMsg;
                emptyResponse["List"] = QJsonArray();
                emptyResponse["TotalCount"] = "0";
                emit callDetailsReceived(emptyResponse);
            }
        }
    } else {
        // Handle network errors by returning empty data instead of an error
        QJsonObject emptyResponse;
        emptyResponse["status"] = "1";
        emptyResponse["message"] = "No available data";
        emptyResponse["List"] = QJsonArray();
        emptyResponse["TotalCount"] = "0";
        emit callDetailsReceived(emptyResponse);
    }
    
    reply->deleteLater();
}

void APIHandler::onLiveCallsReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject jsonObj = jsonDoc.object();
        
        emit liveCallsReceived(jsonObj);
    } else {
        emit liveCallsFailed(reply->errorString());
    }
    
    reply->deleteLater();
}

void APIHandler::onWaveFileReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray waveData = reply->readAll();
        emit waveFileReceived(waveData);
    } else {
        emit waveFileFailed(reply->errorString());
    }
    
    reply->deleteLater();
}
