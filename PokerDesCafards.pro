TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Card.cpp \
        GameController.cpp \
        GameModel.cpp \
        GameView.cpp \
        Player.cpp \
        PlayerController.cpp \
        PlayerView.cpp \
        main.cpp

HEADERS += \
    Card.h \
    GameController.h \
    GameModel.h \
    GameView.h \
    Player.h \
    PlayerController.h \
    PlayerView.h
