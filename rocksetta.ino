
//Web PI 

// By Jeremy Ellis


//PUT YOUR VARIABLES HERE


bool myPiControl = false;   // You may want this to be true so that the 
                            // PI Loop controls an actuator at startup
bool isPI = false;  
String myDevice = "Photon";   // default is the Photon


void setup(){
    
    if (PLATFORM_ID == 31){
        isPI = true; 
         myDevice = "Raspberry Pi";
        }
    
    Spark.function("my-main", myMain);  
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
      
  
    //RGB.control(true);
    //RGB.color(0, 255, 255);  //cyan
    RGB.brightness(1);    // 1=very low light, 255 = max
    
    


}

void loop(){
    
    //PUT YOUR GENERIC LOOP CODE HERE
    
    if ( myPiControl ){
    
    //PUT YOUR SPECIAL LOOP CODE HERE 
    
       // delete the following two lines when operational 
       Particle.publish("Special Loop", "Active", 60, PRIVATE);  
       delay(5000);
    
    }

}

int myMain(String myCode) {
    
    myCode.toUpperCase();           // set argument to uppercase
    

    
    //digitalWrite(D7,HIGH);
    
    //myActivity -- pinNumber -- myOptional
    
    
    
   // int pinNumber = pinNumber2.toInt();
   int myComma = myCode.indexOf(",");   // find the comma
   if (myComma == -1) {myComma = myCode.indexOf(")");} //if no comma use end brackets
   
   int myOpenBracket = myCode.indexOf("(");
    
    String  myActivity = myCode.substring(0, myOpenBracket);     // grab characters until bracket
    

    String pinNumberString = myCode.substring(myOpenBracket+1, myComma);   // for PI 2 digit GPIO numbers
    
    
    
    
    String myOptional = myCode.substring(myComma + 1);   //grabs the numbers after the equal sign   
   // if (pinNumber< 0 || pinNumber >7) return -1; 
   // if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
   
    myOptional = myOptional.replace(");", "");  // get rid of the ); at the end
   
   
   // Particle.publish(myActivity, String(pinNumberString + ", "+myOptional), 60, PRIVATE);  
    
    int pinNumber = pinNumberString.toInt();
    
    pinNumberString = pinNumberString.replace(" ", "");  // ditch spaces
    
        // try  string.replace(" ", "");
        
        
     int mySetWrite = 0;       
     
     
       
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
      
     
     
     
     
     
#if (PLATFORM_ID == 31) 
  // only compile following Raspberry PI stuff
  
  
  
  
    
    if (pinNumberString == "D0"){pinNumber = 4;}    
    if (pinNumberString == "D1"){pinNumber = 17;}    
    if (pinNumberString == "D2"){pinNumber = 27;}    
    if (pinNumberString == "D3"){pinNumber = 22;}    
    if (pinNumberString == "D4"){pinNumber = 5;}     
    if (pinNumberString == "D5"){pinNumber = 4;}     
    if (pinNumberString == "D6"){pinNumber = 13;}    // PWM   
    if (pinNumberString == "D7"){pinNumber = 19;}    // PWM   
    if (pinNumberString == "A0"){pinNumber = 18;}    // PWM   
    if (pinNumberString == "A1"){pinNumber = 23;}    
    if (pinNumberString == "A2"){pinNumber = 24;}    
    if (pinNumberString == "A3"){pinNumber = 25;}    
    if (pinNumberString == "A4"){pinNumber = 12;}    
    if (pinNumberString == "A5"){pinNumber = 16;}    // PWM    
    if (pinNumberString == "A6"){pinNumber = 20;}    
    if (pinNumberString == "A7"){pinNumber = 21;}    
    
    
  //  String myPinStr = String(pinNumber, DEC);
  //  String mySetStr = String(mySetWrite, DEC);
    

  //  Particle.publish("PI", String(myActivity + ", " + pinNumberString + " GPIO Pin = " + myPinStr + " set to " + mySetStr ), 60, PRIVATE);  



#else 
  // only compile following Photon Stuff

    if (pinNumberString == "D0"){pinNumber = 0;}     // PWM
    if (pinNumberString == "D1"){pinNumber = 1;}     // PWM
    if (pinNumberString == "D2"){pinNumber = 2;}     // PWM if not A4
    if (pinNumberString == "D3"){pinNumber = 3;}     // PWM if not A5
    if (pinNumberString == "D4"){pinNumber = 4;}    
    if (pinNumberString == "D5"){pinNumber = 5;}     
    if (pinNumberString == "D6"){pinNumber = 6;}    
    if (pinNumberString == "D7"){pinNumber = 7;}    
    if (pinNumberString == "A0"){pinNumber = 10;}    
    if (pinNumberString == "A1"){pinNumber = 11;}   
    if (pinNumberString == "A2"){pinNumber = 12;}    
    if (pinNumberString == "A3"){pinNumber = 13;}    
    if (pinNumberString == "A4"){pinNumber = 14;}      // PWM if not D2
    if (pinNumberString == "A5"){pinNumber = 15;}      // PWM if Not D3
    if (pinNumberString == "A6"){pinNumber = 16;}   
    if (pinNumberString == "A7"){pinNumber = 17;}      // PWM
    if (pinNumberString == "RX"){pinNumber = 18;}      // PWM // PWM
    if (pinNumberString == "TX"){pinNumber = 19;}      // PWM
   // if (pinNumberString == "BT"){pinNumber = 20;}    // BTN pin is 20 ??    
   
  //  String myPinStr = String(pinNumber, DEC);
  //  String mySetStr = String(mySetWrite, DEC);
    
  //  Particle.publish("Photon", String(myActivity + ", " + pinNumberString + " Pin = " + myPinStr + " set to " + mySetStr ), 60, PRIVATE);  
  
  // Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
  // String(pinNumber, DEC) + " set to " + String(mySetWrite, DEC) ), 60, PRIVATE);  
    
     

#endif
     
     
     
   
    
    // PUT YOUR OWN IF STATEMENT HERE
    // USE CODE 99:MINE:30
    if (myActivity == "MINE"){ 
          
          
          // Your special code here
          
     return mySetWrite;     
    }
    
    
   
     
    if (myActivity == "WHOAMI"){   // which microprocessor
        if ( isPI ){ 
            mySetWrite = 31;   //raspberry PI
        } else {
            mySetWrite = 6;  // Photon 
          }
          
     return mySetWrite;     
    }     
    
  
    
    if (myActivity == "LOOP"){   //xx:loop:1  sets loop to be on
        if (mySetWrite == 0) {myPiControl = false; }  
        if (mySetWrite == 1) {myPiControl = true; }  
          
          // Your special code here
          
     return mySetWrite;     
    }   
    
    
    
    
    
    
  
#if (PLATFORM_ID == 31) 
  // only compile following Raspberry PI stuff
   
        if (myActivity == "DIGITALREAD"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
           // Particle.publish("READ VALUE", String(digitalRead(pinNumber)), 60, PRIVATE);  
            mySetWrite = digitalRead(pinNumber);
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
            return mySetWrite;  
        }
        
        
         if (myActivity == "DIGITALWRITE"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
            return mySetWrite;
        }   
        
        
        // PWM 0-255 on the PI only on certain pins 13, 16, 18, 19 
    if (pinNumber == 13 || pinNumber == 16 || pinNumber == 18 || pinNumber == 19 ){
        
        if (myActivity == "ANALOGWRITE"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
            return mySetWrite;
        }        
      }

#else 
  // only compile following Photon Stuff
       if (pinNumber < 10){
           if (myActivity == "DIGITALREAD"){    //digital read
              pinMode(pinNumber, INPUT_PULLDOWN);
              // Particle.publish("Digital Read Value", String(digitalRead(pinNumber)), 60, PRIVATE);  
              mySetWrite = digitalRead(pinNumber);
              Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
              String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
              return mySetWrite;  
        }
        
   
        
         if (myActivity == "DIGITALWRITE"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
            return mySetWrite;
        }         
       
       } else {  // only photon has analog read pin numbers over 10
       
        if (myActivity == "ANALOGREAD"){    //Analog read     values 0-4095   
                                      // strangely analogRead does not need pinMode() set
           // Particle.publish("Analog read value", String(analogRead(pinNumber)), 60, PRIVATE);  
           // return analogRead(pinNumber);
            mySetWrite = analogRead(pinNumber);  
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  

            return mySetWrite;  
        }
         
         
       // PWM 0-255 on Photon only on these pins:  D0, D1, (A4 or D2), (A5 or D3), WKP=A7, RX, TX
        
       if (pinNumber == 0 || pinNumber == 1 || pinNumber == 2 || pinNumber == 3    || pinNumber == 14  || pinNumber == 15  || pinNumber == 17   || pinNumber == 18  || pinNumber == 19   ){
        if (myActivity == "ANALOGWRITE"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);            
            Particle.publish(myDevice, String(myActivity + ", " + pinNumberString + " Pin = " + 
            String(pinNumber, DEC) + " returning = " + String(mySetWrite, DEC) ), 60, PRIVATE);  
            return mySetWrite;
        } 
       }    
         
           
       }
       
#endif  
    
    
 
    
}

















