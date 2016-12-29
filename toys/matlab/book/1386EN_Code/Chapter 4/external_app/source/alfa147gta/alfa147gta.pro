QT += core gui widgets printsupport
TARGET = alfa147gta
TEMPLATE = app
SOURCES += main.cpp\
        alfa147gta.cpp \
    qcustomplot.cpp
HEADERS  += alfa147gta.h \
    qcustomplot.h \
    spline.hpp
FORMS    += alfa147gta.ui

# Boost libraries: you need the headers.
# Linux: it's trivial to install the package.
# Windows: I downloaded the libraries and extracted them to c:\boost_1_54_0
INCLUDEPATH += "C:\\boost_1_54_0"