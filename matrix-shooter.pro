#-------------------------------------------------
#
# Project created by QtCreator 2019-03-20T11:13:50
#
#-------------------------------------------------

!versionAtLeast(QT_VERSION, 5.12): error("Use at least Qt version 5.12! No gamepad and networkdatagram support before it :(")

QT       += core gui network gamepad widgets multimedia

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

CONFIG += c++14

HEADERS += \
    src/asteroid.h \
    src/bar.h \
    src/mainwindow.h \
    src/matrixscene.h \
    src/missile.h \
    src/player.h \
    src/powerup.h \
    src/collidingitem.h \
    src/config.h \
    src/wreck.h \
    src/border.h \
    src/laser.hpp \
    src/hitindicator.h

SOURCES += \
    src/asteroid.cpp \
    src/bar.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/matrixscene.cpp \
    src/missile.cpp \
    src/player.cpp \
    src/powerup.cpp \
    src/collidingitem.cpp \
    src/config.cpp \
    src/wreck.cpp \
    src/border.cpp \
    src/laser.cpp \
    src/hitindicator.cpp

FORMS += \
    src/mainwindow.ui

INCLUDEPATH += $$PWD/lib/emu

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/emu/mueb/release/ -lmueb
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/emu/mueb/debug/ -lmueb
else:unix: LIBS += -L$$PWD/lib/emu/mueb/ -lmueb

INCLUDEPATH += $$PWD/lib/emu/mueb
DEPENDPATH += $$PWD/lib/emu/mueb

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/emu/mueb/release/libmueb.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/emu/mueb/debug/libmueb.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/lib/emu/mueb/release/mueb.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/lib/emu/mueb/debug/mueb.lib
else:unix: PRE_TARGETDEPS += $$PWD/lib/emu/mueb/libmueb.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/SFML/build/lib/ -lsfml-audio- -lsfml-system-
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/SFML/build/lib/ -lsfml-audio-d -lsfml-system-d
else:unix: LIBS += -lsfml-audio -lsfml-system

INCLUDEPATH += $$PWD/lib/SFML/include
DEPENDPATH += $$PWD/lib/SFML/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/gainput/build/lib/ -lgainput-
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/gainput/build/lib/ -lgainput-d
else:unix: LIBS += -L$$PWD/lib/gainput/build/lib/ -lgainput

INCLUDEPATH += $$PWD/lib/gainput/lib/include
DEPENDPATH += $$PWD/lib/gainput/lib/include
