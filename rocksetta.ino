
//Web PI 

// By Jeremy Ellis


//PUT YOUR VARIABLES HERE


bool myPiControl = false;   // You may want this to be true so that the 
                            // PI Loop controls an actuator at startup
bool isPI = false;                            


void setup(){
    
    if (PLATFORM_ID == 31){isPI = true; }
    
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
   int myComma = myCode.indexOf(",");
   int myOpenBracket = myCode.indexOf("(");
    
   // Particle.publish("READ VALUE", String(myCharLocation), 60, PRIVATE);  
    String  myActivity = myCode.substring(0, myOpenBracket);     // take characters until cutoff
    

    String pinNumberString = myCode.substring(myOpenBracket+1, myComma);   // for PI 2 digit GPIO numbers
    
    
    
    
    String myOptional = myCode.substring(myComma + 1);   //grabs the numbers after the equal sign   
   // if (pinNumber< 0 || pinNumber >7) return -1; 
   // if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
   
    myOptional = myOptional.replace(");", "");  // get rid of the ); at the end
   
   
    Particle.publish(myActivity, String(pinNumberString + ", "+myOptional), 60, PRIVATE);  
    
    int pinNumber = pinNumberString.toInt();
    
        // try  string.replace(" ", "");
        
        
     int mySetWrite = 0;       
    
    if (isPI){   // Raspberry PI pin numbers
    
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
    
    } else{   // photon  pin numbers
        
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
        
        
        
        
    }
    
     
    
    //Following sets the 7 and on characters to integers
    
    // try string.charAt(n)
    //string.indexOf(val)

    
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
    
    
    // myCode parsing complete
    

    String myPinStr = String(pinNumber, DEC);
    String mySetStr = String(mySetWrite, DEC);
    
    if ( isPI ){
       Particle.publish("PI", String(myActivity + ", " + pinNumberString + " GPIO Pin = " + myPinStr + " set to " + mySetStr ), 60, PRIVATE);  
    } else {
       Particle.publish("Photon", String(myActivity + ", " + pinNumberString + " Pin = " + myPinStr + " set to " + mySetStr ), 60, PRIVATE);  
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
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
    
  
    if ( isPI ){
    
    //if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "DIGITALREAD"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            Particle.publish("READ VALUE", String(digitalRead(pinNumber)), 60, PRIVATE);  
            return digitalRead(pinNumber);
        }
        
        
         if (myActivity == "DIGITALWRITE"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }           
        
   } else
   
   {
       if (pinNumber < 10){
           if (myActivity == "DIGITALREAD"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            Particle.publish("Digital Read Value", String(digitalRead(pinNumber)), 60, PRIVATE);  
            return digitalRead(pinNumber);
        }
        
   
        
         if (myActivity == "DIGITALWRITE"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }         
       
       } else {  // only photon has analog read pin numbers over 10
       
        if (myActivity == "ANALOGREAD"){    //Analog read     values 0-4095   
                                      // strangely analogRead does not need pinMode() set
            Particle.publish("Analog read value", String(analogRead(pinNumber)), 60, PRIVATE);  
            return analogRead(pinNumber);
        }
         
           
       }
   }
    
    
    


        
        
        
       
        
    if ( isPI ){   // PWM 0-255 on the PI only on certain pins 13, 16, 18, 19 
     if (pinNumber == 13 || pinNumber == 16 || pinNumber == 18 || pinNumber == 19 ){
        
        if (myActivity == "ANALOGWRITE"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }        
      }
    } else {   // PWM 0-255 on Photon only on these pins:  D0, D1, (A4 or D2), (A5 or D3), WKP=A7, RX, TX
        
       if (pinNumber == 0 || pinNumber == 1 || pinNumber == 2 || pinNumber == 3    || pinNumber == 14  || pinNumber == 15  || pinNumber == 17   || pinNumber == 18  || pinNumber == 19   ){
        if (myActivity == "ANALOGWRITE"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        } 
       }    
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

















