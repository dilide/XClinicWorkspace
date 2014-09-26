TARGET = XEngine
TEMPLATE = lib
DEFINES += XE_LIBRARY

release:DESTDIR = "../../bin"
debug:DESTDIR = "../../debug"

CONFIG -= flat
CONFIG += debug_and_release
CONFIG(debug,debug|release) {
	CONFIG += console
} else {
	DEFINES += QT_NO_DEBUG_OUTPUT
	CONFIG -= console
}

# PRECOMPILED_HEADER = ../../include/common.h

HEADERS += Dicom/DicomReader.h \
		Image\ImageBase.h Image\ImageData.h

SOURCES += Dicom/DicomReader.cpp \
		Image\ImageBase.cpp Image\ImageData.cpp

INCLUDEPATH += "../../include/"
INCLUDEPATH += "E:/Projects/Common/opencv/build/include/"
INCLUDEPATH += "C:/Program Files/DCMTK/include/"

win32{
	!contains(QMAKE_TARGET.arch, x86_64) {
		message("x86 build")
		LIBS += -L"E:/Projects/Common/opencv/build/x86/vc12/staticlib/"
	} else {
		message("x86_64 build")
		LIBS += -L"E:/Projects/Common/opencv/build/x64/vc12/staticlib/"
		LIBS += -L"C:/Program Files/DCMTK/lib/"
	}
}

LIBS += -lfreeglut -lglew32 -lofstd -ldcmimage -ldcmdata -loflog -ldcmimgle

QMAKE_CXXFLAGS += -openmp
# QMAKE_LFLAGS +=  -openmp