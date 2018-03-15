#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T11:26:13
#
#-------------------------------------------------

QT       += core gui xlsx network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TireManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    informationdialog.cpp \
    mainform.cpp \
    configurationform.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    define.h \
    informationdialog.h \
    mainform.h \
    configurationform.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    informationdialog.ui \
    mainform.ui \
    configurationform.ui

RESOURCES += \
    tiremanagement.qrc

win32
{
   RC_FILE = TireManagement.rc
   CONFIG += embed_manifest_exe
   QMAKE_LFLAGS_WINDOWS += /MANIFESTUAC:level=\'requireAdministrator\'
}

TRANSLATIONS += Lang_ko_KR.ts\
                Lang_en_US.ts
