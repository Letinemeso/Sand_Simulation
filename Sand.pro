TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BMP_Image.cpp \
        Image_Manager.cpp \
        Sand_Simulation.cpp \
        Utility.cpp \
        main.cpp

HEADERS += \
    BMP_Image.h \
    Image_Manager.h \
    Sand_Simulation.h \
    Utility.h
