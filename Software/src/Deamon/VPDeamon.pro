TEMPLATE = app

### CONFIG ###
QT += core network
QT -= gui

debug{
	#DEFINES += XBEE_SERIAL_VERBOSE
}

CONFIG += c++11, console
CONFIG -= app_bundle

TARGET = VPDeamon

##############################
###      LOCATIONS         ###
##############################
VPD = $$PWD
SRC = $$VPD/..
ROOT = $$SRC/..
LIB = $$ROOT/lib




##############################
###        SOURCES         ###
##############################
SOURCES += VPDeamon.cpp \
    telnet/telnetserver.cpp \
    telnet/telnetsocket.cpp \
    xbee/xbeeinterface.cpp \
    model/model.cpp \
    model/networkmodel.cpp\
    $$SRC/lib/misc.cpp \
    xbee/xbeeremote.cpp \
    model/eventmodel.cpp \
    model/virtualnetwork.cpp \
    model/eventtrigger.cpp \
    model/patch.cpp \
    model/eventprototype.cpp \
    model/midiinterface.cpp \
    model/oscinterface.cpp

HEADERS += \
    telnet/telnetserver.h \
    telnet/telnetsocket.h \
    xbee/xbeeinterface.h \
    model/model.h \
    model/networkmodel.h\
    $$SRC/lib/singleton.h\
    $$SRC/lib/misc.h \
    xbee/xbeeremote.h \
    model/eventmodel.h \
    model/virtualnetwork.h \
    model/eventtrigger.h \
    model/patch.h \
    model/eventprototype.h \
    model/oscinterface.h \
    model/midiinterface.h

INCLUDEPATH += $$SRC/lib

RESOURCES += \
    ressources.qrc


##############################
###      LIBRAIRIES        ###
##############################


# telnet, Rt Midi
win32{
	INCLUDEPATH += $$LIB/libtelnet $$LIB/RtMidi
	SOURCES += $$LIB/libtelnet/libtelnet.c $$LIB/RtMidi/RtMidi.cpp
}
unix{
	LIBS += -ltelnet -lrtmidi -lX11 -lXtst
	DEFINES += X11_SUPPORT
}

#XBee
include($$LIB/XBee/XBee.pri)

#OSC
include($$LIB/oscpack/osc.pri)
