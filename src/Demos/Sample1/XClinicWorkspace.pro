TARGET = XClinicWorkspace
TEMPLATE = app
DESTDIR = "../bin"

CONFIG += qt debug_and_release
CONFIG(debug,debug|release) {
	CONFIG += console
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
	CONFIG -= console
}

QT += core \
    gui
	

PRECOMPILED_HEADER = StdAfx.h


HEADERS += StdAfx.h MainWindow.h

SOURCES += main.cpp MainWindow.cpp 