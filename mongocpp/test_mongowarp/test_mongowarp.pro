QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
#       ../lib/hex/hex.cpp \
#       ../lib/cjsonobject/CJsonObject.cpp \
#       ../lib/cjsonobject/cJSON.cpp \



#HEADERS += \
#       ../lib/hex/hex.h \
#       ../lib/cjsonobject/CJsonObject.hpp \
#       ../lib/cjsonobject/cJSON.h \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



unix:!macx: LIBS += -L$$PWD/../mongodb_driver/cxx/usr/lib64/ -lmongocxx

INCLUDEPATH += $$PWD/../mongodb_driver/cxx/usr/include/mongocxx/v_noabi/mongocxx
DEPENDPATH += $$PWD/../mongodb_driver/cxx/usr/include/mongocxx/v_noabi/mongocxx



unix:!macx: LIBS += -L$$PWD/../mongodb_driver/cxx/usr/lib64/ -lbsoncxx

INCLUDEPATH += $$PWD/../mongodb_driver/cxx/usr/include/bsoncxx/v_noabi/bsoncxx
DEPENDPATH += $$PWD/../mongodb_driver/cxx/usr/include/bsoncxx/v_noabi/bsoncxx


unix:!macx: LIBS += -L$$PWD/../mongodb_driver/bs_cxx_driver_bin/lib/ -lbs_cxx_driver

INCLUDEPATH += $$PWD/../mongodb_driver/bs_cxx_driver_bin/include
DEPENDPATH += $$PWD/../mongodb_driver/bs_cxx_driver_bin/include

unix {

QMAKE_POST_LINK += cp $$PWD/../mongodb_driver/cxx/usr/lib64/*so* $$OUT_PWD && cp $$PWD/../mongodb_driver/bs_cxx_driver_bin/lib/*so* $$OUT_PWD

}



