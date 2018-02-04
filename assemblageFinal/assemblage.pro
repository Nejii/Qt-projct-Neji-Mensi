#-------------------------------------------------
#
# Project created by QtCreator 2018-01-27T17:14:33
#
#-------------------------------------------------

QT       += core gui xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = assemblage
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
INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc


SOURCES += \
        main.cpp \
        mymainwindow.cpp \
    TableD.cpp \
    mainwindow.cpp \
    descripteur.cpp \
    dialog.cpp \
    otherwindow.cpp

HEADERS += \
        mymainwindow.h \
    TableD.h \
    mainwindow.h \
    descripteur.h \
    dialog.h \
    otherwindow.h

FORMS += \
        mymainwindow.ui \
    mainwindow.ui \
    dialog.ui \
    otherwindow.ui
