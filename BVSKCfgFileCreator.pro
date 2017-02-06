QT += core
QT -= gui

CONFIG += c++11

TARGET = BVSKCfgFileCreator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    parser.cpp \
    angle.cpp \
    cl_algorithms.cpp

HEADERS += \
    parser.h \
    angle.h \
    cl_algorithms.h \
    io_structs.h
