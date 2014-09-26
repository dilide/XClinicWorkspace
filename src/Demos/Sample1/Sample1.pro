TARGET = Sample1
TEMPLATE = app

release:DESTDIR = "../../../bin"
debug:DESTDIR = "../../../debug"

CONFIG += qt debug_and_release
CONFIG(debug,debug|release) {
	CONFIG += console
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
	CONFIG -= console
}

QT += core \
    gui
	
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

PRECOMPILED_HEADER = StdAfx.h


HEADERS += StdAfx.h MainWindow.h

SOURCES += main.cpp MainWindow.cpp 

INCLUDEPATH += "../../../include/"
INCLUDEPATH += "../../xe/"

release:LIBS += -L"../../../bin"
debug:LIBS += -L"../../../debug"

LIBS += -lXEngine