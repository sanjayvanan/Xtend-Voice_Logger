/********************************************************************************
** Form generated from reading UI file 'audioplayerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIOPLAYERDIALOG_H
#define UI_AUDIOPLAYERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AudioPlayerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *currentTimeLabel;
    QSlider *positionSlider;
    QLabel *totalTimeLabel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QLabel *volumeLabel;
    QSlider *volumeSlider;

    void setupUi(QDialog *AudioPlayerDialog)
    {
        if (AudioPlayerDialog->objectName().isEmpty())
            AudioPlayerDialog->setObjectName("AudioPlayerDialog");
        AudioPlayerDialog->resize(400, 200);
        verticalLayout = new QVBoxLayout(AudioPlayerDialog);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(AudioPlayerDialog);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        currentTimeLabel = new QLabel(AudioPlayerDialog);
        currentTimeLabel->setObjectName("currentTimeLabel");

        horizontalLayout->addWidget(currentTimeLabel);

        positionSlider = new QSlider(AudioPlayerDialog);
        positionSlider->setObjectName("positionSlider");
        positionSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(positionSlider);

        totalTimeLabel = new QLabel(AudioPlayerDialog);
        totalTimeLabel->setObjectName("totalTimeLabel");

        horizontalLayout->addWidget(totalTimeLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        playButton = new QPushButton(AudioPlayerDialog);
        playButton->setObjectName("playButton");

        horizontalLayout_2->addWidget(playButton);

        pauseButton = new QPushButton(AudioPlayerDialog);
        pauseButton->setObjectName("pauseButton");

        horizontalLayout_2->addWidget(pauseButton);

        stopButton = new QPushButton(AudioPlayerDialog);
        stopButton->setObjectName("stopButton");

        horizontalLayout_2->addWidget(stopButton);

        volumeLabel = new QLabel(AudioPlayerDialog);
        volumeLabel->setObjectName("volumeLabel");

        horizontalLayout_2->addWidget(volumeLabel);

        volumeSlider = new QSlider(AudioPlayerDialog);
        volumeSlider->setObjectName("volumeSlider");
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(100);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(volumeSlider);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(AudioPlayerDialog);

        QMetaObject::connectSlotsByName(AudioPlayerDialog);
    } // setupUi

    void retranslateUi(QDialog *AudioPlayerDialog)
    {
        AudioPlayerDialog->setWindowTitle(QCoreApplication::translate("AudioPlayerDialog", "Audio Player", nullptr));
        titleLabel->setText(QCoreApplication::translate("AudioPlayerDialog", "Now Playing:", nullptr));
        currentTimeLabel->setText(QCoreApplication::translate("AudioPlayerDialog", "00:00", nullptr));
        totalTimeLabel->setText(QCoreApplication::translate("AudioPlayerDialog", "00:00", nullptr));
        playButton->setText(QCoreApplication::translate("AudioPlayerDialog", "Play", nullptr));
        pauseButton->setText(QCoreApplication::translate("AudioPlayerDialog", "Pause", nullptr));
        stopButton->setText(QCoreApplication::translate("AudioPlayerDialog", "Stop", nullptr));
        volumeLabel->setText(QCoreApplication::translate("AudioPlayerDialog", "Volume:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioPlayerDialog: public Ui_AudioPlayerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIOPLAYERDIALOG_H
