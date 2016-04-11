TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


#CONFIG += console
CONFIG += c++11

SOURCES += main.cpp

HEADERS += \
    FastFunc.hpp \
    FastDelegate.h \
    FastDelegateBind.h \
    SRDelegate.hpp \
    FastDelegatePJ.hpp
