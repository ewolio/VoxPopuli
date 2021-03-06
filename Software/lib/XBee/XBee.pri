### LOCATIONS ###
XBee = $$PWD
SRC = $$XBee/src

### BUILD OPTIONS ###
DEFINES +=XBEE_DEVICE_ENABLE_ATMODE # XBEE_SERIAL_VERBOSE

### SOURCES ###
INCLUDEPATH += $$XBee/include
SOURCES +=  $$SRC/xbee/xbee_device.c\
            $$SRC/xbee/xbee_firmware.c\
            $$SRC/xbee/xbee_xmodem.c\
            $$SRC/xbee/xbee_atcmd.c\
            $$SRC/xbee/xbee_atmode.c\
            $$SRC/wpan/wpan_types.c

SOURCES += $$files($$SRC/util/*.c)

### Platform Specific ###
unix {
SOURCES += $$files($$SRC/posix/*.c)
DEFINES += POSIX
}
win32 {
SOURCES += $$files($$SRC/win32/*.c)
DEFINES += _WIN32 WIN32
}
