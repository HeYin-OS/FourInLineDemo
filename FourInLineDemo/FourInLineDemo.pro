QT       += core gui multimedia
RC_ICONS += main.ico

VERSION = 1.0.8.0

RC_LANG = 0x0004

QMAKE_TARGET_COMPANY = HeYinOS D.P.S.
QMAKE_TARGET_PRODUCT = Four in line v1080
QMAKE_TARGET_DESCRIPTION = 首先将4个棋子连在一起的人获胜！
QMAKE_TARGET_COPYRIGHT = Copyright(C) 2019-2022 HeYinOS D.P.S.

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 RESOURCES_BIG

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    resultdialog.cpp \
    startwindow.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    resultdialog.h \
    startwindow.h

FORMS += \
    dialog.ui \
    mainwindow.ui \
    resultdialog.ui \
    startwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    highdpi.qrc \
    res/res.qrc
