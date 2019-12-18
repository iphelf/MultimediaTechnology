QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bitmap/adjustbc.cpp \
    src/bitmap/bitmap.cpp \
    src/bitmap/modegrayscale.cpp \
    src/main.cpp \
    src/menu/menu.cpp

HEADERS += \
    src/bitmap/adjustbc.h \
    src/bitmap/convertor.h \
    src/console.h \
    src/bitmap/bitmap.h \
    src/bitmap/modegrayscale.h \
    src/menu/menu.h

FORMS += \
    src/bitmap/adjustbc.ui \
    src/bitmap/bitmap.ui \
    src/bitmap/modegrayscale.ui \
    src/menu/menu.ui

INCLUDEPATH += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\install\include
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_core412.dll
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_highgui412.dll
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_imgcodecs412.dll
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_imgproc412.dll
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_features2d412.dll
LIBS += D:\Programs\OpenCV\opencv-4.1.2-built-Qt\bin\libopencv_calib3d412.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
