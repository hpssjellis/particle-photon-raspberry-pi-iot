//PUT YOUR VARIABLES HERE



void setup(){
    
    Spark.function("my-main", myMain);  
    
    //PUT YOUR SETUP CODE HERE. Note: Only three more functions allowed!
    // test everything using the return int from a function!
      
  
    //RGB.control(true);
    //RGB.color(0, 255, 255);  //cyan
    RGB.brightness(1);    // 1=very low light, 255 = max


}

void loop(){
    
    //PUT YOUR LOOP CODE HERE

}

int myMain(String myCode) {
    
    myCode.toUpperCase();           // set argument to uppercase--remove for better security
    
    // used send instead of write since I needed it to be 4 characters long.
    

    // d7:send:1 or d7:send:high or d7:send:on    to turn on D7
    // d7:send:0   or d7:send:low  or d7:send:off to tuurn off D7
    // d5:read    read D5

    // a0:send:0     turn A0 off
    // a0:send:255   turn A0 maximum
  
     
    // Block sets pinNumber for digital 0-7 or analog 10-17 from the number
    int mySetWrite = 0;
    String pinNumber2 = myCode.substring(0,1);   // for PI 2 digit GPIO numbers
   // if (pinNumber< 0 || pinNumber >7) return -1; 
   // if (myCode.startsWith("A")){pinNumber = pinNumber+10;}  //+10 is for analog numbers
    
    
    if (pinNumber2 == "D0"){pinNumber2 = "4";} // Photon to PI
    if (pinNumber2 == "D1"){pinNumber2 = "17";} // Photon to PI
    if (pinNumber2 == "D2"){pinNumber2 = "27";} // Photon to PI
    if (pinNumber2 == "D3"){pinNumber2 = "22";} // Photon to PI
    if (pinNumber2 == "D4"){pinNumber2 = "5";} //  Photon to PI
    if (pinNumber2 == "D5"){pinNumber2 = "4";} //  Photon to PI
    if (pinNumber2 == "D6"){pinNumber2 = "13";} // PWM   Photon to PI
    if (pinNumber2 == "D7"){pinNumber2 = "19";} // PWM   Photon to PI
    if (pinNumber2 == "A0"){pinNumber2 = "18";} // PWM   Photon to PI
    if (pinNumber2 == "A1"){pinNumber2 = "23";} // Photon to PI
    if (pinNumber2 == "A2"){pinNumber2 = "24";} // Photon to PI
    if (pinNumber2 == "A3"){pinNumber2 = "25";} // Photon to PI
    if (pinNumber2 == "A4"){pinNumber2 = "12";} // Photon to PI
    if (pinNumber2 == "A5"){pinNumber2 = "16";} // PWM    Photon to PI
    if (pinNumber2 == "A6"){pinNumber2 = "20";} // Photon to PI
    if (pinNumber2 == "A7"){pinNumber2 = "21";} // Photon to PI
    
    int pinNumber = pinNumber2.toInt();
    
  
    String  myActivity = myCode.substring(3,7);     // take 4 characters starting at the 3rd.
     
    
    //Following sets the 7 and on characters to integers
    String myOptional = myCode.substring(8);      
    if(myOptional == "HIGH") {mySetWrite = 1;}
        else if(myOptional == "LOW") {mySetWrite = 0; }
            else if(myOptional == "ON") {mySetWrite = 1;}
                else if(myOptional == "OFF") {mySetWrite = 0; }
                   else {mySetWrite = myOptional.toInt();  }  // sets  write value
    
    
    // myCode parsing complete
    
    
    
    
    // PUT YOUR OWN IF STATEMENT HERE
    // USE CODE 99:MINE:30
    if (myActivity == "MINE"){ 
          
          
          // Your I2C special code or other code
          
     return mySetWrite;     
    }
    
    
    
    
    
    
    
    
    
    
    //if (pinNumber < 9) {   // digital pins activated
   
        if (myActivity == "READ"){    //digital read
            pinMode(pinNumber, INPUT_PULLDOWN);
            return digitalRead(pinNumber);
        }
        
        if (myActivity == "SEND"){    //digital write
            pinMode(pinNumber, OUTPUT);
            digitalWrite(pinNumber, mySetWrite);
            return mySetWrite;
        }        
        
        
   // }  else {      // analog pins activated
    
    
    
    // NO ANALOG READ USE I2C INSTEAD ?????:???
     //   if (myActivity == "READ"){    //Analog read
          //  pinMode(pinNumber, INPUT_PULLUP); // stangely not needed on the photon
       //     return analogRead(pinNumber);
     //   }
        
        
        
        
        
        // PWM only on certain pins 13, 16, 18, 19
    if (pinNumber == 13 || pinNumber == 16 || pinNumber == 18 || pinNumber == 19 ){
        
        
        if (myActivity == "SEND"){    //Analog Write
            pinMode(pinNumber, OUTPUT);
            analogWrite(pinNumber,  mySetWrite);
            return mySetWrite;
        }        
      }
    
}


