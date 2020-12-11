QT     += core gui widgets multimedia

CONFIG += c++17

TARGET = MyTetris

TRANSLATIONS += tetris_ru.ts

SOURCES += \
    controller.cpp \
    figure.cpp \
    figureview.cpp \
    main.cpp \
    mainwindow.cpp \
    scenemodel.cpp \
    sceneview.cpp

HEADERS += \
    controller.h \
    figure.h \
    figureview.h \
    mainwindow.h \
    scenemodel.h \
    sceneview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resurses.qrc
