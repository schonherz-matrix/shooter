#-------------------------------------------------
#
# Project created by QtCreator 2019-03-20T11:13:50
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = matrix-shooter
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

HEADERS += \
    src/asteroid.h \
    src/bar.h \
    src/mainwindow.h \
    src/matrixscene.h \
    src/player.h

SOURCES += \
    src/player.cpp \
    src/powerup.cpp \
    src/asteroid.cpp \
    src/bar.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/matrixscene.cpp \
    src/player.cpp \
    src/powerup.cpp \
    src/powerup.h
FORMS += \
        src/mainwindow.ui \
    src/mainwindow.ui \
    src/mainwindow.ui \
    src/mainwindow.ui

INCLUDEPATH += $$PWD/matrix-simple

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/matrix-simple/mueb/release/ -lmueb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/matrix-simple/mueb/debug/ -lmueb
else:unix: LIBS += -L$$PWD/matrix-simple/mueb/ -lmueb

INCLUDEPATH += $$PWD/matrix-simple/mueb
DEPENDPATH += $$PWD/matrix-simple/mueb

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/release/libmueb.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/debug/libmueb.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/release/mueb.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/debug/mueb.lib
else:unix: PRE_TARGETDEPS += $$PWD/matrix-simple/mueb/libmueb.a
