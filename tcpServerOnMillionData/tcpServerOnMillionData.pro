QT += core network
QT -= gui

TARGET = tcpServerOnMillionData
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    TCPServer.cpp

HEADERS += \
    TCPServer.h

