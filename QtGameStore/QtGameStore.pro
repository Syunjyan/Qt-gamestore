QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    gameinfodialog.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    signdialog.cpp \
    usrsetting.cpp

HEADERS += \
    client.h \
    gameinfodialog.h \
    logindialog.h \
    mainwindow.h \
    signdialog.h \
    usrsetting.h

FORMS += \
    gameinfodialog.ui \
    logindialog.ui \
    mainwindow.ui \
    signdialog.ui \
    usrsetting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = logo2.ico

RESOURCES += \
    myicon.qrc
