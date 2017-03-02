

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
    
    myCode.toUpperCase();           // set argument to uppercase--remove for better security
    
    // used send instead of write since I needed it to be 4 characters long.
    

    // d7:write=1 or d7:send:high or d7:send:on    to turn on D7
    // d7:write=0   or d7:send:low  or d7:send:off to tuurn off D7
    // d5:read    read D5

    // a5:PWM=0     turn A5  PWM off
    // a5:PWM=255   turn A5 PWM maximum
  
     
    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number
    int mySetWrite = 0;
    String pinNumberString = myCode.substring(0,2);   // for PI 2 digit GPIO numbers
   // if (pinNumber< 0 || pinNumber >7) return -1; 
   // if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
    
    int pinNumber = pinNumberString.toInt();
        
    
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
    
   // int pinNumber = pinNumber2.toInt();
    
  
    String  myActivity = myCode.substring(3,7);     // take 4 characters starting at the 3rd.
     
    
    //Following sets the 7 and on characters to integers
    
    // try string.charAt(n)
    //string.indexOf(val)
    
    String myOptional = myCode.substring(myCode.indexOf("="));   //grabs the numbers after the equal sign   
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    if (myActivity == "LOOP"){   //xx:loop:1  sets loop to be on
        if (mySetWrite == 0) {myPiControl = false; }  
        if (mySetWrite == 1) {myPiControl = true; }  
          
          // Your special code here
          
     return mySetWrite;     
    }   
    
  
    if ( isPI ){
    
    //if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "READ"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            Particle.publish("READ VALUE", String(digitalRead(pinNumber)), 60, PRIVATE);  
            return digitalRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //digital write
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }       
        
         if (myActivity == "WRIT"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }           
        
   } else
   
   {
       if (pinNumber < 10){
           if (myActivity == "READ"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            Particle.publish("Digital Read Value", String(digitalRead(pinNumber)), 60, PRIVATE);  
            return digitalRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //digital write
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }       
        
         if (myActivity == "WRIT"){    //digital write   D3:writeHIGH  to fit the 5th letter miss the final colon
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }         
       
       } else {  // only photon has analog read pin numbers over 10
       
        if (myActivity == "READ"){    //Analog read     values 0-4095   
                                      // strangely analogRead does not need pinMode() set
            Particle.publish("Analog read value", String(digitalRead(pinNumber)), 60, PRIVATE);  
            return analogRead(pinNumber);
        }
         
           
       }
   }
    
    
    


        
        
        
       
        
    if ( isPI ){   // PWM 0-255 on the PI only on certain pins 13, 16, 18, 19 
     if (pinNumber == 13 || pinNumber == 16 || pinNumber == 18 || pinNumber == 19 ){
        
        if (myActivity == "PWM!"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }        
      }
    } else {   // PWM 0-255 on Photon only on these pins:  D0, D1, (A4 or D2), (A5 or D3), WKP=A7, RX, TX
        
       if (pinNumber == 0 || pinNumber == 1 || pinNumber == 2 || pinNumber == 3    || pinNumber == 14  || pinNumber == 15  || pinNumber == 17   || pinNumber == 18  || pinNumber == 19   ){
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }   
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

















