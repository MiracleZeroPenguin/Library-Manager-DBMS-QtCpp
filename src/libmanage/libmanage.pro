#-------------------------------------------------
#
# Project created by QtCreator 2020-04-07T22:48:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libmanage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        addcard.cpp \
        borrowbook.cpp \
        const.cpp \
        createuser.cpp \
        deletecard.cpp \
        deleteuser.cpp \
        filebookinsert.cpp \
        getdatabase.cpp \
        login.cpp \
        main.cpp \
        mainwindow.cpp \
        mylineedit.cpp \
        returnbook.cpp \
        searchbook.cpp \
        searchcard.cpp \
        searchuser.cpp \
        showrecord.cpp \
        singlebookinsert.cpp \
        updatecard.cpp

HEADERS += \
        addcard.h \
        borrowbook.h \
        const.h \
        createuser.h \
        deletecard.h \
        deleteuser.h \
        filebookinsert.h \
        getdatabase.h \
        login.h \
        mainwindow.h \
        mylineedit.h \
        returnbook.h \
        searchbook.h \
        searchcard.h \
        searchuser.h \
        showrecord.h \
        singlebookinsert.h \
        updatecard.h

FORMS += \
        addcard.ui \
        borrowbook.ui \
        createuser.ui \
        deletecard.ui \
        deleteuser.ui \
        filebookinsert.ui \
        getdatabase.ui \
        login.ui \
        mainwindow.ui \
        returnbook.ui \
        searchbook.ui \
        searchcard.ui \
        searchuser.ui \
        showrecord.ui \
        singlebookinsert.ui \
        updatecard.ui

QT += sql

INCLUDEPATH += D:\mysql-8.0.19-winx64\mysql-8.0.19-winx64\include


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
