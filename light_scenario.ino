#include <WS2812.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 2
#define outputPin 9  // Digital output pin (default: 7)
#define LEDCount 5   // Number of LEDs to drive (default: 9)

WS2812 LED(LEDCount); 
cRGB value;

byte intensity;
byte sign;

void setup() {
	LED.setOutput(outputPin); // Digital Pin 7
	LED.setColorOrderRGB();  // Uncomment for RGB color order

	intensity = 0;
	sign = 1;

  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
}

void morning_light() {
  for (int b=0; b<255; b++) {
    value.b = b*0.5; 
    value.g = b*0.5;
    value.r = b*0.5;
    
    for (int i=0; i<5; i++) {
      LED.set_crgb_at(i, value);
    }

    LED.sync();
    //delay (100);
  } 

  value.b = 174*0.5; 
  value.g = 242*0.5;
  value.r = 255*0.5;
  for (int i=0; i<5; i++) {
    LED.set_crgb_at(i, value);
  }
  LED.sync();
 // delay (1000);
}

void day_light() {
  value.b = 174*0.5; 
  value.g = 196*0.5;
  value.r = 255*0.5;
  for (int i=0; i<5; i++) {
    LED.set_crgb_at(i, value);
  }
  LED.sync();
  //delay (1000);
}

void evening_light() {
  value.b = 174*0.2; 
  value.g = 196*0.2;
  value.r = 255*0.2;
  for (int i=0; i<5; i++) {
    LED.set_crgb_at(i, value);
  }
  LED.sync();
  //delay (1000);
}

void night_light() {
  value.b = 174*0.1; 
  value.g = 196*0.1;
  value.r = 255*0.1;
  for (int i=0; i<5; i++) {
    LED.set_crgb_at(i, value);
  }
  LED.sync();
  //delay (1000);
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume(); 
    int command = IrReceiver.decodedIRData.command;

    if (command == 0) {
      morning_light();
    }
    else if (command == 3) {
      day_light();
    }

    else if (command == 1) {
      evening_light();
    }

    else if (command == 9) {
      night_light();
    }
    Serial.println(command);
  }
  
  //elay(100);
}


// morning 0
// day 3
// evening 1
// night 9
