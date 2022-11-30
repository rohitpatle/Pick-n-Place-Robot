#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//BOTTTTT
const byte my_radio_pipe[6] = "00011"; //constant data-type to define radio frequency
RF24 radio(7, 8);                      //(CE, CNF)
int arr[8];                            //integer data-type to store array
int X1;                                //integer data-type to store vaiables
int Y1;
int X2;
int Y2;
int Value;                             //integer data-type to store vaiables
 
//ARMMMMM
int val1;                              //integer data-type to store vaiables
int val2;
int val3;

void setup()
{
  Serial.begin(9600);                   //baud rate for serial monitor
  radio.begin();                        //to start wireless communication
  radio.setDataRate(RF24_250KBPS);      //communication frequency
  radio.openWritingPipe(my_radio_pipe); //setting address where we will send data
  radio.stopListening();                //end of the communication
  Value = 0; 
  Serial.println("SETUP DONE");
}

void loop()
{
  //BOTTTTT
  X1 = map( analogRead(A3),0,1023, 0,255); //mapping value of joystick to speed of motor according to arduino
  Y1 = map( analogRead(A4),0,1023, 0,255);
  X2 = map( analogRead(A6),0,1023, 0,255);
  Y2 = map( analogRead(A7),0,1023, 0,255);
  arr[0]=X1;                               //store this variables in this array
  arr[1]=Y1;
  arr[2]=X2;
  arr[3]=Y2;
                                           //following are the statements to give conditions
  if(X1>135){
    Value = 1;                //forward
  }
  else if(X1<125){
    Value = 2;                //back
  }
  else if(Y2<125){
    Value = 3;                //left
  }
  else if(Y2>135){
    Value = 4;                //right
  }
  else{
    Value = 0;                //stop
  }

  //ARMMMMM
  val1 = map(analogRead(A2), 0, 1023, 180, 60); //mapping value of potentiometer to degree of rotation of servo motors
  val2 = map(analogRead(A1), 0, 1023, 180, 60);
  val3 = map(analogRead(A0), 0, 1023, 180, 60); //reading the value of toggle switch
  arr[4] = val1;                               //store this variables in this array
  arr[5] = val2;
  arr[6] = val3;
  arr[7] = Value;
  
  radio.write(&arr, sizeof(arr));              //we are sending this arrays to the receiver side

  Serial.print(Value);
  Serial.print("\t");
  Serial.print(X1);
  Serial.print("\t");
  Serial.print(Y1);
  Serial.print("\t");
  Serial.print(X2);
  Serial.print("\t");
  Serial.print(Y2);
  Serial.print("\t");
  Serial.print(val1);
  Serial.print("\t");
  Serial.print(val2);
  Serial.print("\t");
  Serial.print(val3);
  Serial.print("\t");
  Serial.println("");
}
