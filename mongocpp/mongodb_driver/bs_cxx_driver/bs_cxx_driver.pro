#-------------------------------------------------
#
# Project created by QtCreator 2019-05-06T12:44:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = bs_cxx_driver
TEMPLATE = lib

DEFINES += BS_CXX_DRIVER_LIBRARY



#make install INSTALL_ROOT=$$PWD/../bs_cxx_driver_bin
#INSTALLS       += $$PWD/../bs_cxx_driver_bin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bs_cxx_driver.cpp \
       ../../lib/hex/hex.cpp \
       ../../lib/cjsonobject/CJsonObject.cpp \
       ../../lib/cjsonobject/cJSON.cpp \

HEADERS += \
        bs_cxx_driver.h \
        bs_cxx_driver_global.h \ 
        bs_cxx_driver_export.h \
       ../../lib/hex/hex.h \
       ../../lib/cjsonobject/CJsonObject.hpp \
       ../../lib/cjsonobject/cJSON.h \


DISTFILES += bs_cxx_driver_export.h
DESTDIR = $$PWD/../bs_cxx_driver_bin/lib


unix {
    SrcIncludeFile = $$PWD/bs_cxx_driver_export.h
    OutputIncludeDir = $$PWD/../bs_cxx_driver_bin/include/
    QMAKE_POST_LINK += mkdir $$OutputIncludeDir -p && cp $$SrcIncludeFile $$OutputIncludeDir
#QMAKE_POST_LINK += echo "Hello world"; echo "How are you!"; echo "How old are you!"; pwd; cat /etc/passwd; cp main.cpp main.cpp.bak

    target.path = /usr/lib
    INSTALLS += target
}


#INCLUDEPATH += ../c/usr/include/libbson-1.0/ ../c/usr/include/libmongoc-1.0/
#INCLUDEPATH += $$PWD/../../


INCLUDEPATH += $$PWD/../c/usr/include/libbson-1.0
DEPENDPATH += $$PWD/../c/usr/include/libbson-1.0


#INCLUDEPATH += $$PWD/../c/usr/include/libmongoc-1.0
#DEPENDPATH += $$PWD/../c/usr/include/libmongoc-1.0
#LIBS += -L$$PWD/../c/usr/lib64/ -lbson-1.0 -lmongoc-1.0


INCLUDEPATH += $$PWD/../cxx/usr/include/bsoncxx/v_noabi/
DEPENDPATH += $$PWD/../cxx/usr/include/bsoncxx/v_noabi/

INCLUDEPATH += $$PWD/../cxx/usr/include/mongocxx/v_noabi
DEPENDPATH += $$PWD/../cxx/usr/include/mongocxx/v_noabi

INCLUDEPATH += $$PWD/../../../../../Software/Qt5.9.7/5.9.7/gcc_64/include
DEPENDPATH += $$PWD/../../../../../Software/Qt5.9.7/5.9.7/gcc_64/include
