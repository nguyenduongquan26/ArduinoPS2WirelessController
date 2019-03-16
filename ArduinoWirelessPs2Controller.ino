#include <PS2X_lib.h>
#include <Servo.h>
#define PS2_DAT        13  
#define PS2_CMD        7  
#define PS2_SEL        8  
#define PS2_CLK        12  
#define pressures   false
#define rumble      false
#define in1 6
#define in2 2
#define in3 4
#define in4 5
PS2X ps2x;
Servo servo1;

int pos1=10;
int error = 0;
byte type = 0;
byte vibrate = 0;
int temp1;
int temp2;
int temp3;
int temp4;
int temp33;
int temp44;

void setup(){
pinMode(6,OUTPUT);
pinMode(2,OUTPUT); 
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
servo1.attach(3);
servo1.write(10);
ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  Serial.begin(57600);
  
  delay(300);  
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

 void loop() {
  if(error == 1) //skip loop if no controller found
    return; 
  
  if(type == 2){ //Guitar Hero Controller
    ps2x.read_gamepad();          //read controller 
   
  
    
   

  }
  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");        
    

    if(ps2x.Button(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if(ps2x.Button(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if(ps2x.Button(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just released");     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }     
  }
  delay(50);  
  temp1 = 0 ;
  temp2 = 0 ;
  temp3 = 0 ;
  temp4 = 0 ;
  if(error == 1){ 
    return; 
  }
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
  if(ps2x.Button(PSB_R2)) {
    delay(80);
    if(ps2x.Button(PSB_R2)){
  pos1+=30 ;
        servo1.write(pos1);
        delay(600);
        servo1.write(10);
        delay(600);
    }
}

    if(ps2x.Button(PSB_CROSS)==HIGH)
{  
  if(ps2x.Analog(PSS_LY) > 128)
      {
temp1= (ps2x.Analog(PSS_LY)-128) * 2 ;
      }
  else if (ps2x.Analog(PSS_LY) < 128)
      {
    
temp2 = abs(ps2x.Analog(PSS_LY)- 128) * 2 ;
        if (temp2 > 255 )
        temp2 = 255;
 
      }
      else
      {
       temp2 = 0;
      
      }
  if(ps2x.Analog(PSS_RX) > 128)
      {
   
 temp3= (ps2x.Analog(PSS_RX)-128 ) * 2 ;

      }
  else if (ps2x.Analog(PSS_RX) < 128)
      {
 
       temp4 = abs(ps2x.Analog(PSS_RX) -128 ) * 2 ;
        if (temp4 > 255 )
        temp4 = 255;
    
      }
      else
      {
       temp4 = 0;
       
      }

 }
 else
 {
  if(ps2x.Analog(PSS_LY) > 128)
      {
temp1= (ps2x.Analog(PSS_LY)-128)  ;
      }
  else if (ps2x.Analog(PSS_LY) < 128)
      {
    
temp2 = abs(ps2x.Analog(PSS_LY)- 128)  ;
        if (temp2 > 255 )
        temp2 = 255;
 
      }
      else
      {
       temp2 = 0;
      
      }
  if(ps2x.Analog(PSS_RX) > 128)
      {
   
 temp3= (ps2x.Analog(PSS_RX)-128 )  ;

      }
  else if (ps2x.Analog(PSS_RX) < 128)
      {
 
       temp4 = abs(ps2x.Analog(PSS_RX) -128 ) ;
        if (temp4 > 255 )
        temp4 = 255;
    
      }
      else
      {
       temp4 = 0;
       
      }
 }
 
if( (temp2 > 0) && temp3 == 0 && temp4 == 0 )
  {
       digitalWrite(in1,temp2);
       digitalWrite(in2,0);
       digitalWrite(in3,temp2);
       digitalWrite(in4,0);
  }
else 
 {
      if( (temp1 > 0) && temp3 == 0 && temp4 == 0 )
        {
             digitalWrite(in1,0);
             digitalWrite(in2,temp1);
             digitalWrite(in3,0);
             digitalWrite(in4,temp1);
        }
      else
        {
             if ( (temp2 > 0) && temp4 > 0 )
                {
                    temp44 = ( temp2 - temp4 );
                    if (temp44 <0 ) 
                       {
                         temp44 = 0; 
                       } 
                    digitalWrite(in1,temp44 );
                    digitalWrite(in2,0);
                    digitalWrite(in3,temp2);
                    digitalWrite(in4,0);
                }
               else
               {
                 if ( (temp2 > 0) && temp3 >  0 )
                   {
                          temp33 = ( temp2 - temp3 );
                          if (temp33 <0 ) 
                             {
                               temp33 = 0; 
                             } 
                          digitalWrite(in1,temp2 );
                          digitalWrite(in2,0);
                          digitalWrite(in3,temp33);
                          digitalWrite(in4,0); 
                   }
                   else
                   {
                           if ( (temp1 > 0) && temp4 > 0 )
                {
                    temp44 = ( temp1 - temp4 );
                    if (temp44 <0 ) 
                       {
                         temp44 = 0; 
                       } 
                    digitalWrite(in1,0 );
                    digitalWrite(in2,temp44);
                    digitalWrite(in3,0);
                    digitalWrite(in4,temp1);
                }
               else
               {
                 if ( (temp1 > 0) && temp3 >  0 )
                   {
                          temp33 = ( temp1 - temp3 );
                          if (temp33 <0 ) 
                             {
                               temp33 = 0; 
                             } 
                          digitalWrite(in1,0 );
                          digitalWrite(in2,temp33);
                          digitalWrite(in3,0);
                          digitalWrite(in4,temp1);   
                   }
                  
                 }
                   
         } 
 }
 
}



 }
 
  }


