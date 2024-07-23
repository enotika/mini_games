QT       += core gui
QT += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clickablelabel.cpp \
    figuretetris.cpp \
    findpair.cpp \
    ltetris.cpp \
    lttetris.cpp \
    main.cpp \
    mainwindow.cpp \
    minor.cpp \
    squaretetris.cpp \
    startwindow.cpp \
    stetris.cpp \
    sticktetris.cpp \
    tetris.cpp \
    ttetris.cpp \
    ztetris.cpp

HEADERS += \
    clickablelabel.h \
    figuretetris.h \
    findpair.h \
    ltetris.h \
    lttetris.h \
    mainwindow.h \
    minor.h \
    squaretetris.h \
    startwindow.h \
    stetris.h \
    sticktetris.h \
    tetris.h \
    ttetris.h \
    ztetris.h

FORMS += \
    findpair.ui \
    mainwindow.ui \
    minor.ui \
    startwindow.ui \
    tetris.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
