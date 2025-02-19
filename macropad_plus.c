// ===================================================================================
// Project:   MacroPad Plus for CH551, CH552 and CH554
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Firmware example implementation for the MacroPad Plus.
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: 16 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Customize the macro functions in the corresponding section below.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash' immediatly afterwards.
// - To compile the firmware using the Arduino IDE, follow the instructions in the 
//   .ino file.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID device with
//   keyboard, mouse and joystick interface.
// - Press a macro key or turn the knob and see what happens.
// - To enter bootloader hold down rotary encoder switch while connecting the 
//   MacroPad to USB. All NeoPixels will light up white as long as the device is in 
//   bootloader mode (about 10 seconds).


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
//#include <stdio.h>
#include "src/config.h"                     // user configurations
#include "src/system.h"                     // system functions
#include "src/delay.h"                      // delay functions
#include "src/gpio.h"

#include "src/usb_composite.h"              // USB HID composite functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

#pragma disable_warning 110                 // Keep calm, EVELYN!

// ===================================================================================
// Macro Functions which associate Actions with Events (Customize your MacroPad here!)
// ===================================================================================
// The list of available USB HID functions can be found in src/usb_composite.h
// The keys are enumerated the following way:
// +---+---+---+    -----
// | 4 | 5 | 6 |  /CCW  CW\
// +---+---+---+  |   K   |
// | 3 | 2 | 1 |  \       /
// +---+---+---+    -----


#define KBD_sendReport()    HID_sendReport(KBD_report, sizeof(KBD_report))
void asterisco(){
  __xdata uint8_t KBD_report[]   = {1,0,0,0,0,0,0,0};
  int i=0;
  for(i=3; i<8; i++) {
    if(KBD_report[i] == 0) {                    // empty slot?
      KBD_report[1] |= 0x02;                    // add left shift modifier shift para =
      KBD_report[i] = 0x2f;                     // insert key *
      KBD_sendReport();                         // send report

      //KBD_report[1] &= ~0x02;                   // remove shift modifier
      KBD_report[i] = 0;                        // delete key in report
      KBD_sendReport();                         // send report

      return;                                    // and return
    }
  }
}
void igual(){
  __xdata uint8_t KBD_report[]   = {1,0,0,0,0,0,0,0};
  int i=0;
  for(i=3; i<8; i++) {
    if(KBD_report[i] == 0) {                    // empty slot?
      KBD_report[1] |= 0x02;                    // add left shift modifier shift para =
      KBD_report[i] = 0x27;                     // insert key =
      KBD_sendReport();                         // send report

      //KBD_report[1] &= ~0x02;                   // remove shift modifier
      KBD_report[i] = 0;                        // delete key in report
      KBD_sendReport();                         // send report
      KBD_report[1] &= ~0x02;                   // remove shift modifier
      return;                                    // and return
    }
  }
}



// Key 1 example -> mouse wheel up (scroll page)
// ---------------------------------------------

// Define action(s) if key1 was pressed
// +---+---+---+    -----
// |   |   |   |  /       \
// +---+---+---+  |       |
// |   |   | 1 |  \       /
// +---+---+---+    -----
inline void KEY1_PRESSED() {
  KBD_press(KBD_KEY_LEFT_SHIFT);
  DLY_ms(50);
  KBD_print("v cn*");asterisco();KBD_print("(,activate");
  KBD_press(KEY_KP_ENTER);
  KBD_release(KEY_KP_ENTER);  
  DLY_ms(50);
  KBD_release(KBD_KEY_LEFT_SHIFT);

  // DLY_ms(500);

  // KBD_press(KBD_KEY_LEFT_SHIFT);
  // DLY_ms(50);
  KBD_print("v cn*");asterisco();KBD_print("(,rout");igual();KBD_print("all");
  KBD_press(KEY_KP_ENTER);
  KBD_release(KEY_KP_ENTER);  
  DLY_ms(50);
  KBD_release(KBD_KEY_LEFT_SHIFT);
  DLY_ms(50);

  // KBD_press(KBD_KEY_LEFT_SHIFT);
  // KBD_print("ingams refresh cfg");
  // DLY_ms(50);  
  // KBD_press(KBD_KEY_LEFT_SHIFT);igual();
  // KBD_press(KBD_KEY_LEFT_SHIFT);asterisco();
  // KBD_release(KBD_KEY_LEFT_SHIFT);
  //DLY_ms(50);
  // KBD_press('\xAB');
  // KBD_release('\xAB');
  // DLY_ms(50);
  //KBD_press(KBD_KEY_LEFT_SHIFT);
  // KBD_press('\75');
  // KBD_release('\75');
  //KBD_release(KBD_KEY_LEFT_SHIFT);
  //DLY_ms(500);
  KBD_press(KEY_KP_ENTER);
  //DLY_ms(50);
  KBD_release(KEY_KP_ENTER);  
}

// Define action(s) if key1 was released
inline void KEY1_RELEASED() {
  DLY_ms(200);
  KBD_release(KBD_KEY_RIGHT_CTRL);
}
// Define action(s) when key1 is held
inline void KEY1_HOLD() {
  //MOUSE_wheel_down();                                   // turn mouse wheel up
  //DLY_ms(10);                                         // delay
}

// +---+---+---+    -----
// |   |   |   |  /       \
// +---+---+---+  |       |
// |   | 2 |   |  \       /
// +---+---+---+    -----
inline void KEY2_PRESSED() {
  KBD_print("dispstat"); 
  KBD_press(KEY_KP_ENTER);
  KBD_release(KEY_KP_ENTER);    
  //KBD_print("KEY2"); 
  //KBD_press(KBD_KEY_F6);
  //DLY_ms(50);
  //KBD_press(KBD_KEY_LEFT_ALT);                        // press left ALT key

}
// Define action(s) if key2 was released
inline void KEY2_RELEASED() {
  //KBD_release(KBD_KEY_F6);                      // release left ALT key
}
// Define action(s) when key2 is held
inline void KEY2_HOLD() {
  //KBD_type(KBD_KEY_TAB);                              // press and release TAB key
  //DLY_ms(500);                                        // delay
}


// +---+---+---+    -----
// |   |   |   |  /       \
// +---+---+---+  |       |
// | 3 |   |   |  \       /
// +---+---+---+    -----
inline void KEY3_PRESSED() {
  KBD_press(KBD_KEY_LEFT_CTRL);
  KBD_type('v'); 
  DLY_ms(50);
  //KBD_press(KBD_KEY_LEFT_GUI);                        // press left WIN key
  //KBD_press(KBD_KEY_DOWN_ARROW);                      // press DOWN ARROW key
}
inline void KEY3_RELEASED() {
  KBD_release(KBD_KEY_LEFT_CTRL);
  //KBD_release(KBD_KEY_DOWN_ARROW);                    // release DOWN ARROW key
  //KBD_release(KBD_KEY_LEFT_GUI);                      // release left WIN key
}
inline void KEY3_HOLD() {
}


// +---+---+---+    -----
// | 4 |   |   |  /       \
// +---+---+---+  |       |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void KEY4_PRESSED() {
  KBD_press(KBD_KEY_LEFT_CTRL);
  KBD_type('c'); 
  DLY_ms(50);
  // KBD_press(KBD_KEY_LEFT_CTRL);                       // press left CTRL key
  // KBD_press(KBD_KEY_LEFT_ALT);                        // press left ALT key
  // KBD_press(KBD_KEY_DELETE);                          // press DEL key
}
inline void KEY4_RELEASED() {
  KBD_release(KBD_KEY_LEFT_CTRL);
  // KBD_release(KBD_KEY_DELETE);                        // release DEL key
  // KBD_release(KBD_KEY_LEFT_ALT);                      // release left ALT key
  // KBD_release(KBD_KEY_LEFT_CTRL);                     // release left CTRL key
}
inline void KEY4_HOLD() {
}


// +---+---+---+    -----
// |   | 5 |   |  /       \
// +---+---+---+  |       |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void KEY5_PRESSED() {
  //KBD_print("rodar clockwise\n");
  KBD_press(KEY_PAUSE);
  DLY_ms(50);
  KBD_release(KEY_PAUSE);
  DLY_ms(50);  
  // CON_press(CON_VOL_UP);                              // press VOLUME UP key
}
inline void KEY5_RELEASED() {
  // CON_release();                                      // release VOLUME UP KEY
  // KBD_release(KEY_PAUSE);
  // DLY_ms(50);
}
inline void KEY5_HOLD() {
  // CON_release();                                      // release VOLUME UP KEY
  DLY_ms(500);
  KBD_press(KBD_KEY_F6);
  KBD_release(KBD_KEY_F6);
  DLY_ms(500);
}


// +---+---+---+    -----
// |   |   | 6 |  /       \
// +---+---+---+  |       |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void KEY6_PRESSED() {
  KBD_press(KBD_KEY_LEFT_SHIFT);
  KBD_print("ingams refresh cfg");
  DLY_ms(50);  
  KBD_press(KBD_KEY_LEFT_SHIFT);igual();
  KBD_press(KBD_KEY_LEFT_SHIFT);asterisco();
  KBD_release(KBD_KEY_LEFT_SHIFT);
  //DLY_ms(50);
  // KBD_press('\xAB');
  // KBD_release('\xAB');
  // DLY_ms(50);
  //KBD_press(KBD_KEY_LEFT_SHIFT);
  // KBD_press('\75');
  // KBD_release('\75');
  //KBD_release(KBD_KEY_LEFT_SHIFT);
  //DLY_ms(500);
  KBD_press(KEY_KP_ENTER);
  //DLY_ms(50);
  KBD_release(KEY_KP_ENTER);
  //DLY_ms(50);  
  // KBD_press(KBD_KEY_RIGHT_CTRL);
  // DLY_ms(500);
  // CON_press(CON_VOL_MUTE);                            // press VOLUME MUTE key
}
inline void KEY6_RELEASED() {
  //KBD_release(KBD_KEY_RIGHT_CTRL);
  // CON_release();                                      // release VOLUME MUTE key
}
inline void KEY6_HOLD() {
  // KBD_print("automan");
  // DLY_ms(250);
  // KBD_press(KBD_KEY_RIGHT_CTRL);
  // DLY_ms(100);  
  // KBD_release(KBD_KEY_RIGHT_CTRL);
  // DLY_ms(50);  
  // CON_release();                                      // release VOLUME MUTE key
}


// +---+---+---+    -----
// |   |   |   |  /CCW    \
// +---+---+---+  |       |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void GIRAR_KNOB_CCW() {
  KBD_press(KBD_KEY_F7);
  //DLY_ms(500);
  // KBD_press(KBD_KEY_LEFT_CTRL);
  // KBD_type('c'); 
  // DLY_ms(500);

  // KBD_press(KBD_KEY_LEFT_GUI);                        // press left WIN key
  // KBD_type('t');                                      // press and release 'T' key
  // DLY_ms(500);                                        // wait for terminal to open
  // KBD_release(KBD_KEY_LEFT_GUI);                      // release left WIN key
  // KBD_print("sudo shutdown -h now");                  // type shutdown command
  // KBD_type(KBD_KEY_RETURN);                           // press and release RETURN key

}
inline void PARAR_KNOB_CCW() {
  KBD_release(KBD_KEY_F7);
}
inline void MANTER_KNOB_CCW() {
}


// +---+---+---+    -----
// |   |   |   |  /     CW\
// +---+---+---+  |       |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void GIRAR_KNOB_CW() {
  KBD_press(KBD_KEY_F8);
}
inline void PARAR_KNOB_CW() {
  KBD_release(KBD_KEY_F8);
}
inline void MANTER_KNOB_CW() {
  // MOUSE_wheel_down();                                 // turn mouse wheel down
  // DLY_ms(10);                                         // delay
}

// +---+---+---+    -----
// |   |   |   |  /       \
// +---+---+---+  |  knob |
// |   |   |   |  \       /
// +---+---+---+    -----
inline void PREMIR_KNOB() {
  // KBD_press(KBD_KEY_RETURN);
  // DLY_ms(50);
  // KBD_release(KBD_KEY_RETURN);
  // DLY_ms(50);

  KBD_press(KBD_KEY_HOME);
  DLY_ms(50);
  KBD_release(KBD_KEY_HOME);
  DLY_ms(50);

  KBD_print("canzlog");
  DLY_ms(50);
  //KBD_type(KBD_KEY_RIGHT_CTRL);
  KBD_press(KEY_KP_ENTER);
  DLY_ms(50);
  KBD_release(KEY_KP_ENTER);
  // DLY_ms(1000);
  // KBD_press(KEY_KP_ENTER);
  // DLY_ms(50);
  // KBD_release(KEY_KP_ENTER);
  // DLY_ms(50);  
  // KBD_releaseAll();
  // DLY_ms(50);
  // CON_press(CON_VOL_DOWN);                            // press VOLUME DOWN key
}
inline void SOLTAR_KNOB() {
  // DLY_ms(50);
  // KBD_releaseAll();
  // DLY_ms(50);
  //KBD_press(KBD_KEY_HOME);
  // CON_release();                                      // release VOLUME DOWN KEY
}
inline void MANTER_KNOB_PRESSIONADO() {
  // CON_release();                                      // release VOLUME DOWN KEY
}




// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Variables
  __bit key1last    = 0;                          // last state of key 1
  __bit key2last    = 0;                          // last state of key 2
  __bit key3last    = 0;                          // last state of key 3
  __bit key4last    = 0;                          // last state of key 4
  __bit key5last    = 0;                          // last state of key 5
  __bit key6last    = 0;                          // last state of key 6
  __bit keyKNOBlast = 0;                          // state of rotary encoder switch
  __idata uint8_t i;                              // temp variable




  // Setup
   CLK_config();                                   // configure system clock
  DLY_ms(10);                                     // wait for clock to settle
  // Enter bootloader if rotary encoder switch is pressed
  if(!PIN_read(PIN_KEY6)) {                     // encoder switch pressed?
    BOOT_now();                                   // enter bootloader
  }

  // Init USB HID device
  HID_init();                                     // init USB HID device
  DLY_ms(500);                                    // wait for Windows
  WDT_start();                                    // start watchdog timer

  // Loop
  while(1) {

    // Handle key 1
    // ------------
    // +---+---+---+    -----
    // |   |   |   |  /       \
    // +---+---+---+  |       |
    // |   |   | 1 |  \       /
    // +---+---+---+    -----
    if(!PIN_read(PIN_KEY1) != key1last) {         // key state changed?
      key1last = !key1last;                       // update last state flag
      if(key1last) {                              // key was pressed?
        // NEO_writeHue(0, NEO_KEY1, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
        
        KEY1_PRESSED();                           // take proper action
      }
      else {                                      // key was released?
        // NEO_clearPixel(0);                        // light up corresponding NeoPixel
        
        KEY1_RELEASED();                          // take proper action
      }
    }
    else if(key1last) {                           // key still being pressed?
      KEY1_HOLD();                                // take proper action
    }

    // Handle key 2
    // ------------
    // +---+---+---+    -----
    // |   |   |   |  /       \
    // +---+---+---+  |       |
    // |   | 2 |   |  \       /
    // +---+---+---+    -----    
    if(!PIN_read(PIN_KEY2) != key2last) {         // key state changed?
    //if(!PIN_read(PIN_NEO) != key2last) {         // key state changed?
      key2last = !key2last;                       // update last state flag
      if(key2last) {                              // key was pressed?
        //NEO_writeHue(1, NEO_KEY2, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
        //NEO_update();                             // update pixels
        KEY2_PRESSED();                           // take proper action
      }
      else {                                      // key was released?
        // NEO_clearPixel(1);                        // light up corresponding NeoPixel
        
        KEY2_RELEASED();                          // take proper action
      }
    }
    else if(key2last) {                           // key still being pressed?
      KEY2_HOLD();                                // take proper action
    }

    // Handle key 3
    // ------------
    // +---+---+---+    -----
    // |   |   |   |  /       \
    // +---+---+---+  |       |
    // | 3 |   |   |  \       /
    // +---+---+---+    -----        
    if(!PIN_read(PIN_KEY3) != key3last) {         // key state changed?
      key3last = !key3last;                       // update last state flag
      if(key3last) {                              // key was pressed?
        // NEO_writeHue(2, NEO_KEY3, NEO_BRIGHT_KEYS);    // light up corresponding NeoPixel
        
        KEY3_PRESSED();                           // take proper action
      }
      else {                                      // key was released?
        // NEO_clearPixel(2);                        // light up corresponding NeoPixel
        
        KEY3_RELEASED();                          // take proper action
      }
    }
    else if(key3last) {                           // key still being pressed?
      KEY3_HOLD();                                // take proper action
    }

    // Handle key 4
    // ------------
    // +---+---+---+    -----
    // | 4 |   |   |  /       \
    // +---+---+---+  |       |
    // |   |   |   |  \       /
    // +---+---+---+    -----        
    if(!PIN_read(PIN_KEY4) != key4last) {         // key state changed?
      key4last = !key4last;                       // update last state flag
      if(key4last) {                              // key was pressed?
        
        
        KEY4_PRESSED();                           // take proper action
      }
      else {                                      // key was released?
        // NEO_clearPixel(3);                        // light up corresponding NeoPixel
        
        KEY4_RELEASED();                          // take proper action
      }
    }
    else if(key4last) {                           // key still being pressed?
      KEY4_HOLD();                                // take proper action
    }

    // +---+---+---+    -----
    // |   | 5 |   |  /       \
    // +---+---+---+  |       |
    // |   |   |   |  \       /
    // +---+---+---+    -----          
    if(!PIN_read(PIN_KEY5) != key5last) {        
      key5last = !key5last;                    
      if(key5last) {                            
        KEY5_PRESSED();                          
      }
      else {                                      
        KEY5_RELEASED();                         
      }
    }
    else if(key5last) {                          
      //MANTER_KNOB_CW();
      KEY5_HOLD();
    }        

    // +---+---+---+    -----
    // |   |   | 6 |  /       \
    // +---+---+---+  |       |
    // |   |   |   |  \       /
    // +---+---+---+    -----          
    if(!PIN_read(PIN_KEY6) != key6last) {        
      key6last = !key6last;                    
      if(key6last) {                            
        KEY6_PRESSED();                          
      }
      else {                                      
        KEY6_RELEASED();                         
      }
    }
    else if(key6last) {                          
      //MANTER_KNOB_CW();
      KEY6_HOLD();
    }    


    // Acto de girar o knob tanto CW como CCW
    // +---+---+---+    -----
    // |   |   |   |  / <   > \
    // +---+---+---+  |   K   |
    // |   |   |   |  \       /
    // +---+---+---+    -----    
    if(!PIN_read(KNOB)) {                    // encoder turned ?
      if(PIN_read(KNOB_CW)) {                   // clockwise ?
        GIRAR_KNOB_CW();                          // take proper action
        DLY_ms(5);                                // debounce
        PARAR_KNOB_CW();                        // take proper action
      }
      else {                                      // counter-clockwise ?
        GIRAR_KNOB_CCW();                         // take proper action
        DLY_ms(5);                                // debounce
        PARAR_KNOB_CCW();                       // take proper action
      }
      while(!PIN_read(KNOB));                // wait until next detent
    }     

    // Acto de premir o knob
    // +---+---+---+    -----
    // |   |   |   |  /       \
    // +---+---+---+  | KNOB  |
    // |   |   |   |  \       /
    // +---+---+---+    -----          
    if(!PIN_read(KNOB_BOTAO) != keyKNOBlast) {        
      keyKNOBlast = !keyKNOBlast;                    
      if(keyKNOBlast) {                            
        PREMIR_KNOB();                          
      }
      else {                                      
        SOLTAR_KNOB();                         
      }
    }
    else if(keyKNOBlast) {                          
      MANTER_KNOB_PRESSIONADO();
    }        



    DLY_ms(1);                                    // debounce
    WDT_reset();                                  // reset watchdog
  }
}
