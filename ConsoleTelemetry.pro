QT += core network
QT -= gui

CONFIG += c++11

TARGET = ConsoleTelemetry
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    ctcpserver.cpp

HEADERS += \
    ctcpserver.h
