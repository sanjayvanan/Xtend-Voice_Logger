QT       += core gui network multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apihandler.cpp \
    audioplayerdialog.cpp \
    dashboard.cpp \
    livecalls.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    timetimecalls.cpp \
    usermanagement.cpp

HEADERS += \
    apihandler.h \
    audioplayerdialog.h \
    dashboard.h \
    livecalls.h \
    login.h \
    mainwindow.h \
    timetimecalls.h \
    mainwindow.h \
    usermanagement.h

FORMS += \
    audioplayerdialog.ui \
    dashboard.ui \
    livecalls.ui \
    login.ui \
    mainwindow.ui \
    timetimecalls.ui \
    usermanagement.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
