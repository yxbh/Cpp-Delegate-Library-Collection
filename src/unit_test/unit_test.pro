TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

SOURCES += \
    TEST_FastFunc.cpp \
    test_main.cpp \
    TEST_raw.cpp \
    test_sample.cpp \
    TEST_SRDelegate.cpp

HEADERS += \
    test_sample.hpp \
    catch.hpp

#
# Build ouput
#
BUILDDIRWIN32DBG = ../../build/Win32-Debug
BUILDDIRWIN32REL = ../../build/Win32-Release
BUILDDIRUNIXDBG  = ../../build/Unix-Debug
BUILDDIRUNIXREL  = ../../build/Unix-Release
CONFIG(debug, debug|release) { # Debug build dirs
    win32:  DESTDIR     = $${BUILDDIRWIN32DBG}/
    win32:  OBJECTS_DIR = $${BUILDDIRWIN32DBG}/obj
    win32:  MOC_DIR     = $${BUILDDIRWIN32DBG}/moc
    win32:  RCC_DIR     = $${BUILDDIRWIN32DBG}/rsc
    win32:  UI_DIR      = $${BUILDDIRWIN32DBG}/ui
    unix:   DESTDIR     = $${BUILDDIRUNIXDBG}/obj
    unix:   OBJECTS_DIR = $${BUILDDIRUNIXDBG}/obj
    unix:   MOC_DIR     = $${BUILDDIRUNIXDBG}/moc
    unix:   RCC_DIR     = $${BUILDDIRUNIXDBG}/rsc
    unix:   UI_DIR      = $${BUILDDIRUNIXDBG}/ui
} else { # Release build dirs
    win32:  DESTDIR     = $${BUILDDIRWIN32REL}/
    win32:  OBJECTS_DIR = $${BUILDDIRWIN32REL}/obj
    win32:  MOC_DIR     = $${BUILDDIRWIN32REL}/moc
    win32:  RCC_DIR     = $${BUILDDIRWIN32REL}/rsc
    win32:  UI_DIR      = $${BUILDDIRWIN32REL}/ui
    unix:   DESTDIR     = $${BUILDDIRUNIXREL}/
    unix:   OBJECTS_DIR = $${BUILDDIRUNIXREL}/obj
    unix:   MOC_DIR     = $${BUILDDIRUNIXREL}/moc
    unix:   RCC_DIR     = $${BUILDDIRUNIXREL}/rsc
    unix:   UI_DIR      = $${BUILDDIRUNIXREL}/ui
}
#

#
# Library include paths
#
INCLUDEPATH += \
    ../ \                           # delegate libraries
#
