
TEMPLATE = app
TARGET = visitor
DESTDIR = .
CONFIG += console
QT -= gui

SOURCES += main.cpp

HEADERS += h/main.hpp

include(../../QtArg/qtarg.pri)
