#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define HOJA_BT_LOGGING_DEBUG 0

// Device stuff
#define HOJA_DEVICE_ID  0xB001
#define HOJA_FW_VERSION 0x0A01

// RGB Stuff
#define HOJA_RGB_PIN 28
#define HOJA_RGB_COUNT 11
#define HOJA_RGBW_EN 0

// If we do not have native analog triggers
// set this to zero
#define HOJA_ANALOG_TRIGGERS 0

// Sets the analog light trigger level for SP function
#define HOJA_ANALOG_LIGHT 50

// URL that will display to open a config tool
#define HOJA_WEBUSB_URL     "handheldlegend.github.io/hoja_config"
#define HOJA_MANUFACTURER   "HHL"
#define HOJA_PRODUCT        "RetroGlow+"

#define HOJA_CAPABILITY_ANALOG_STICK_L 0
#define HOJA_CAPABILITY_ANALOG_STICK_R 0
#define HOJA_CAPABILITY_ANALOG_TRIGGER_L 0
#define HOJA_CAPABILITY_ANALOG_TRIGGER_R 0

#define HOJA_CAPABILITY_BLUETOOTH 0
#define HOJA_CAPABILITY_BLUETOOTH_OPTIONAL 0
#define HOJA_CAPABILITY_BATTERY 0
#define HOJA_CAPABILITY_RGB 1
#define HOJA_CAPABILITY_GYRO 0

#define HOJA_CAPABILITY_NINTENDO_SERIAL 0
#define HOJA_CAPABILITY_NINTENDO_JOYBUS 0

#define HOJA_CAPABILITY_RUMBLE_ERM 0
#define HOJA_CAPABILITY_RUMBLE_LRA 0

// -1 indicates that the RGB group is unused.
#define HOJA_RGB_GROUP_RS       {-1}
#define HOJA_RGB_GROUP_LS       {-1}
#define HOJA_RGB_GROUP_DPAD     {0, 1, 2, 3}
#define HOJA_RGB_GROUP_MINUS    {4}
#define HOJA_RGB_GROUP_CAPTURE  {-1}
#define HOJA_RGB_GROUP_HOME     {-1}
#define HOJA_RGB_GROUP_PLUS     {5}
#define HOJA_RGB_GROUP_Y        {6}
#define HOJA_RGB_GROUP_X        {8}
#define HOJA_RGB_GROUP_A        {9}
#define HOJA_RGB_GROUP_B        {7}

#define HOJA_RGB_GROUP_L {-1}
#define HOJA_RGB_GROUP_ZR {-1}
#define HOJA_RGB_GROUP_R {-1}
#define HOJA_RGB_GROUP_ZL {-1}
#define HOJA_RGB_GROUP_PLAYER {-1}

#endif
