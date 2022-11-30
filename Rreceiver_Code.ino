#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//BOTTTTTT
const byte address[6] = "00011";//constant data-type to receive radio frequency
RF24 radio(8, 7);               //(CE, CNF)
int arr[8];                     //integer data-type to store array
int X1;                         //integer data-type to store vaiables
//int Y1;
//int X2;
int Y2;
int Value;                      //integer data-type to store vaiables
const int IN1 = 14;             //constant data-type to define the pin number of motors
const int IN2 = 15;
const int IN3 = 16;
const int IN4 = 17;
const int ENa = 6;
const int ENb = 5;

//ARMMMMMM
Servo myservo1, myservo2,myservo3;//function for servo library to defines servo motors
int val1;                         //integer data-type to store vaiables
int val2;
int val3;

void setup() 
{
  Serial.begin(9600);               //baud rate for serial monitor
  radio.begin();                    //to start wireless communication
  radio.setDataRate(RF24_250KBPS);  //communication frequency
  radio.openReadingPipe(0,address); //setting address where we will send data
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();           //end of the communication
  Serial.println("SETUP DONE");  
  
  pinMode(IN1,OUTPUT);    //left motor front
  pinMode(IN2,OUTPUT);    //left motor back
  pinMode(IN3,OUTPUT);    //right motor front
  pinMode(IN4,OUTPUT);    //right motor back  
  pinMode(ENa,OUTPUT);    //both left motors
  pinMode(ENb,OUTPUT);    //both right motors
  //pinMode(13, OUTPUT);
  
  myservo1.attach(9);     //defining the pin number where servos are attached
  myservo2.attach(10);
  myservo3.attach(3);
  myservo1.write(180);    //writing the initial positions of servo
  myservo2.write(180);
  myservo3.write(180);
}

void loop()
{
  if (radio.available())          //if we are receiving signals then
  { //Serial.print("connected");
    //digitalWrite(13,HIGH);
    radio.read(&arr, sizeof(arr));//we are receiving this arrays from the transmiter side
    X1=arr[0];                    //take this variable from this array
    //Y1=arr[1];
    //X2=arr[2];
    Y2=arr[3];
    Value = arr[7];               //take this variable from this array
    
    val1=arr[4];                  //take this variable from this array
    val2=arr[5];
    val3=arr[6];
    myservo1.write(val1);         //writing the position of servo according to potentiometer
    myservo2.write(val2);
    myservo3.write(val3);
    //delay(10);
    

    Serial.print(X1);
    Serial.print("\t");
    //Serial.print(Y1);
    //Serial.print("\t");
    //Serial.print(X2);
    //Serial.print("\t");
    Serial.print(Y2);
    Serial.print("\t");
    Serial.print(val1);
    Serial.print("\t");
    Serial.print(val2);
    Serial.print("\t");
    Serial.print(val3);
    Serial.println("");
    
    switch(Value)  //according to the variable received from transmiter it will switch to that case below
    {              //making cases for all the below functions
      case 1:        //forward
        Forward();
      break;
      case 2:        //back
        Back();
      break;
      case 3:        //left 
        Left(); 
      break;
      case 4:        //right
        Right();
      break;
      default:       //stop
        Stop();
      break;
    }
  }
}

void Forward()                //declaring function
{
 X1= map(X1,127,255,0,150);   //mapping value of joystick to speed of motor according to arduino
 digitalWrite(IN1,HIGH);      //motor direction
 digitalWrite(IN3,HIGH);      //motor direction
 analogWrite(ENa,X1);         //motor speed
 analogWrite(ENb,X1);         //motor speed
 Serial.println("Forward");
}


void Back()
{
 X1= map(X1,127,0,0,150);
 digitalWrite(IN2,HIGH);      
 digitalWrite(IN4,HIGH);      
 analogWrite(ENa,X1);         
 analogWrite(ENb,X1);         
 Serial.println("Back");
}

void Left()
{
 Y2= map(Y2,127,0,0,150);
 digitalWrite(IN1,HIGH);      
 analogWrite(ENa,Y2);       
 Serial.println("Left");
}

void Right()
{
 Y2= map(Y2,127,255,0,150);
 digitalWrite(IN3,HIGH);      
 analogWrite(ENb,Y2);         
 Serial.println("Right");
}

void Stop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("Stop");
}
