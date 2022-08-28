const int photoTransistorPin = 2;
const int buttonPin = 4;
const int motorPin = 8; //initialize led variable
const int turnValue3m = 22;
const int turnValue6m = 44;
const int turnValue9m = 66; //not used yet
const int turnValue12m = 88;
const int turnValue15m = 110;

int photoTransistorState = 0;
int lastTransistorState;
int buttonState;
bool printIntro = false; //for button press

int screenDisplayM = 3; 

int turnCount = turnValue3m; //number of turns before motor stops. Default is 3m


int counter = 1; //offset first increment

// Rotary Encoder code
#define CLK 5
#define DT 6
#define SW 7

int counterRotary = 1; // 1 = 3 meters
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
//---------

//screen code
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//--------


void setup() {
  Serial.begin(9600); //setting the baud (speed) to 9600
  pinMode(photoTransistorState, INPUT);
  pinMode(motorPin, OUTPUT);           //set pin 8
  pinMode(buttonPin, INPUT);
  
//display: initialize with the I2C addr 0x3D (for the 128x64)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.display();
  delay(1000);
  // Clear the buffer.
  display.clearDisplay();


//Rotary encoder
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);
  Serial.println(lastStateCLK);//temp
  //--------
  
}

void loop() {

//----------------------------------
  
  while (printIntro == false){ //waits until button is presssed
    
    WriteToDisplay();
    
    while (digitalRead(SW) == HIGH) { //wait until button is pressed
    //Serial.println("Press button to begin.");
    printIntro = true;

    

    //rotary encoder
    
         // Read the current state of CLK
        currentStateCLK = digitalRead(CLK);
      
        // If last and current state of CLK are different, then pulse occurred
        // React to only 1 state change to avoid double count
        if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      
          // If the DT state is different than the CLK state then
          // the encoder is rotating CCW so decrement
          if (digitalRead(DT) != currentStateCLK) {
            counterRotary ++;
            currentDir ="CW";
          } else {
            // Encoder is rotating CW so increment
            counterRotary --;
            currentDir ="CCW";            
          }
      
          //Serial.print("Direction: ");
          //Serial.print(currentDir);
          //Serial.print(" Counter: ");
          //Serial.println(counterRotary);
          Serial.print("Press button to start. Metres: ");
          Serial.println(screenDisplayM);
          CheckTurnValue(); //limit values and assign display values
          WriteToDisplay();


          //limit turn rotation
          if (counterRotary < 1){
           counterRotary = 1;
          }
          if (counterRotary > 5){
           counterRotary = 5;
          }
          
        }
      
        // Remember last CLK state
        lastStateCLK = currentStateCLK;
      
        // Read the button state
        int btnState = digitalRead(SW);
      
        //If we detect LOW signal, button is pressed
        if (btnState == LOW) {
          //if 50ms have passed since last LOW pulse, it means that the
          //button has been pressed, released and pressed again
          if (millis() - lastButtonPress > 50) {
            Serial.println("Button pressed!");
          }
      
          // Remember last button press event
          lastButtonPress = millis();
        }
      
        // Put in a slight delay to help debounce the reading
        delay(1);
        
        

    
    }
    //delay(50);

    
    
          
  }
//---------------------------------------

  //Phototransistor Read :
  photoTransistorState = digitalRead(photoTransistorPin);
  
  
  
  
  
  if (photoTransistorState == 0 && lastTransistorState == 1){ //turn reading code
    counter ++;
    //delay(100); 
    Serial.println(counter); //print to serial
    lastTransistorState = 0;
  }
  
  

  lastTransistorState = photoTransistorState;

//----------------------------------pop
  
  if (counter < turnCount) { 
  digitalWrite(motorPin, HIGH); //turn motor
  
  }

  else {
    digitalWrite(motorPin, LOW);
    counter = 1;
    printIntro = false; //send back to button press loop
  }
  
//---------------------------------------

}


//refresh display function
void WriteToDisplay(){
// deal with display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(" JEFA Winding Machine");
    display.println("    Press to start.");
    display.setTextSize(1);
    display.print("     ");
    if (screenDisplayM == 3||screenDisplayM == 6||screenDisplayM == 9){
      display.print(" ");
    }
    display.setTextSize(2);
    display.print(screenDisplayM);
    display.setTextSize(1);
    display.println("");
    display.print(" <        metres   >");
    display.display();
}

void CheckTurnValue(){
  if (counterRotary == 1){
         turnCount = turnValue3m;
         screenDisplayM = 3;
        }
        
        if (counterRotary == 2){
         turnCount = turnValue6m;
         screenDisplayM = 6;
        }
        
        if (counterRotary == 3){
         turnCount = turnValue9m;
         screenDisplayM = 9;
        }
        if (counterRotary == 4){
         turnCount = turnValue12m;
         screenDisplayM = 12;
        }
        if (counterRotary == 5){
         turnCount = turnValue15m;
         screenDisplayM = 15;
        }
}
