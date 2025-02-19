// ===================================================================================
// User Configurations for CH552G USB MacroPad Plus
// ===================================================================================

#pragma once

// Pin definitions
// enum{P10, P11, P12, P13, P14, P15, P16, P17, P30, P31, P32, P33, P34, P35, P36, P37};
// enum{P10, P11, P12, P13, P14, P15, P16, P17, P30, P31, P32, P33, P34, P35, P36, P37};
#define PIN_NEO             P36         // P16 pin connected to NeoPixel
#define PIN_KEY1            P17         // P17 pin connected to key 1
#define PIN_KEY2            P16         // P31 pin connected to key 2 11?
#define PIN_KEY3            P30         // P30 pin connected to key 3
#define PIN_KEY4            P15         // P15 pin connected to key 4
#define PIN_KEY5            P34         // P34 pin connected to rotary encoder A 36?
#define PIN_KEY6            P11         // P11 pin connected to rotary encoder switch 31?
#define KNOB_CW             P14         // P14 pin connected to key 5
#define KNOB                P32         // P32 pin connected to key 6
#define KNOB_BOTAO          P33         // P33 pin connected to rotary encoder B 32?




// NeoPixel configuration
#define NEO_COUNT           18          // number of pixels in the string
#define NEO_GRB                         // type of pixel: NEO_GRB or NEO_RGB

// USB device descriptor
#define USB_VENDOR_ID       0x1189      // VID
#define USB_PRODUCT_ID      0x8890      // PID
#define USB_DEVICE_VERSION  0x0100      // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    150         // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'w','a','g','i','m','i','n','a','t','o','r'
#define PRODUCT_STR         'M','a','c','r','o','P','a','d'
#define SERIAL_STR          'C','H','5','5','2','x','H','I','D'
#define INTERFACE_STR       'H','I','D','-','K','e','y','b','o','a','r','d'
