// 9/1/25 notes
// everything works - use this copy to
//adjust volumes, times, intervals

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define D10 13   //radio receiver #2 functions
#define D11 12  
#define D12  9

#define D0  8 //radio receiver #1 functions
#define D1  7
#define D2  5

#define T2 4  // transmitter functions
#define T1 3    
#define T0 2

int i =0;
//RX1
int vx =0; // digital read D0
int vy=0; // digital read D1
int vz=0; //digital read D2

int VX=0;  //detected value of DO
int VY=0;
int VZ=0;

//RX2
int vx2 =0; // digital read D10
int vy2=0; // digital read D11
int vz2=0; //digital read D12

int VX2=0;  //detected value of D1O
int VY2=0;
int VZ2=0;

int b = 1;   //for counting the RX1 001 loop
int q = 1;   //for counting the RX1 100 loop, new 8/26/25

int u = 1; // for counting the RX2 001 loop
           //RX2 has no loop for 100 detect, single result
int w = 1; //for counting the RX2 010 loop
int s = 1;  //for counting the RX2 011 loop
int p = 1;  //for countng the RX2 101 loop
int r = 1;  //for counting the RX2 110 loop
int c = 1;   //for counting the RX2 111 loop


//_____________________________________ transmitter control one digit
void transmit(int VX, int VY, int VZ) {
for (i=0; i<10; i++) {
if (VX==HIGH) {
digitalWrite(T0, LOW);
delay(50);
digitalWrite(T0, HIGH);
delay(400);  
}
if(VY==HIGH) {
digitalWrite(T1, LOW);
delay(50);
digitalWrite(T1, HIGH);
delay(400);  
}
if(VZ==HIGH) {
digitalWrite(T2, LOW);
delay(50);
digitalWrite(T2, HIGH);
delay(400);
}    //_______________________________end of transmitter control one digit
}    // xmit time= 10*(.05+.40)sec = 4.5 seconds
}

//_____________________________________ transmitter control two digits
void xmit2(int VX, int VY, int VZ) {
for (i=0; i<5; i++) {
if (VX==HIGH) {
digitalWrite(T0, LOW);
delay(50);
digitalWrite(T0, HIGH);
delay(400);  
}
if(VY==HIGH) {
digitalWrite(T1, LOW);
delay(50);
digitalWrite(T1, HIGH);
delay(400);  
}
if(VZ==HIGH) {
digitalWrite(T2, LOW);
delay(50);
digitalWrite(T2, HIGH);
delay(400);
}
}    //________________________end of transmitter control two digits
}    //   xmit time= 5*2*(.05+.40)sec = 4.5 seconds


//_____________________________________ transmitter control three digits
void xmit3(int VX, int VY, int VZ) {
for (i=0; i<3; i++) {
if (VX==HIGH) {
digitalWrite(T0, LOW);
delay(50);
digitalWrite(T0, HIGH);
delay(450);  
}
if(VY==HIGH) {
digitalWrite(T1, LOW);
delay(50);
digitalWrite(T1, HIGH);
delay(450);  
}
if(VZ==HIGH) {
digitalWrite(T2, LOW);
delay(50);
digitalWrite(T2, HIGH);
delay(450);
}
}    //  xmit time= 3*3*(.05+.45)sec = 4.5 seconds
}    //___________end of transmitter control three digits






void setup()   //_____________________________________________________
{
pinMode(D2, INPUT);  //radio 
pinMode(D1, INPUT);
pinMode(D0, INPUT);

pinMode(D12, INPUT);  //radio 
pinMode(D11, INPUT);
pinMode(D10, INPUT);

pinMode(T2, OUTPUT);
pinMode(T1, OUTPUT);
pinMode(T0, OUTPUT);

digitalWrite(T0, HIGH);
digitalWrite(T1, HIGH);
digitalWrite(T2, HIGH);

mySoftwareSerial.begin(9600);
Serial.begin(115200);

Serial.println();
Serial.println(F(" Pepper #1"));
Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
Serial.println(F("Unable to begin:"));
Serial.println(F("1.Please recheck the connection!"));
Serial.println(F("2.Please insert the SD card!"));
while(true);
 }
 delay(1000);
Serial.println(F("DFPlayer Mini online."));
delay(2000);
myDFPlayer.volume(20);  //_____________________________Set volume value. 

myDFPlayer.playMp3Folder(5);  //___Did you say something
delay(6000);
myDFPlayer.pause();

delay(500);

myDFPlayer.playMp3Folder(21);  // Are we going...dog dream again?
delay(4000);
myDFPlayer.pause();
}





void loop()    //___________________________________________________________
{
digitalWrite(T0, HIGH);
digitalWrite(T1, HIGH);
digitalWrite(T2, HIGH);

Serial.println();
Serial.print(" start Pepper");
Serial.println();


//____________________________________________________  RX1 RF signal detector 
// reset signal detect, samples and saves any HIGH states
VX=LOW;
VY=LOW;
VZ=LOW;

for (i=0; i<100; i++) {    //from 300 on 8/7/25 
vx= digitalRead(D0);
vy=digitalRead(D1);
vz= digitalRead(D2);

delay(10);

if (vx==HIGH)  { VX=HIGH;  }
if (vy==HIGH)  { VY=HIGH;  }
if (vz==HIGH)  { VZ=HIGH;  }
}  //_______________________________________________________ end of RF signal detect part 1

//_____________________________________________________ extend detect time if any signal is detected
// 8/7/25 from 1 sec to 3 sec
if (VX==HIGH||VY==HIGH||VZ==HIGH)  {
for (i=0; i<300; i++) {   

vx= digitalRead(D0);
vy=digitalRead(D1);
vz= digitalRead(D2);

delay(10);

if (vx==HIGH)  { VX=HIGH;  }
if (vy==HIGH)  { VY=HIGH;  }
if (vz==HIGH)  { VZ=HIGH;  }
}  //_______________________________ end of RX1 RF signal detect part 2
}






if(VZ==LOW&&VY==LOW&&VX==HIGH) {   //___________RX1 0 0 1 code detect
if (b>2) {b=1;}

if(b==1){
myDFPlayer.playMp3Folder(22);  //did somebody let the Chordettes out?
delay(4000);
myDFPlayer.pause();

myDFPlayer.playMp3Folder(100);  //_____________ Pepper
delay(103000); 
myDFPlayer.pause();
delay(500); 

VZ=LOW; VY=LOW; VX=HIGH;
transmit(VX,VY,VZ);
VZ=LOW; VY=LOW; VX=HIGH;
}

if(b==2){
myDFPlayer.playMp3Folder(84);  //never on sunday
delay(42000);
myDFPlayer.pause();

delay(500); 

VZ=LOW; VY=LOW; VX=HIGH;
transmit(VX,VY,VZ);
VZ=LOW; VY=LOW; VX=HIGH;
}
//to here 8/30/25__________________________________________________________________ 

b=b+1;
Serial.println();
Serial.print(b);
Serial.println();
}
// _________________________________________end of RX1 001 code detect



if(VZ==HIGH&&VY==LOW&&VX==LOW) {   //______________RX1  1 0 0 code detect
if (q>2) {q=1;}

if(q==1){
myDFPlayer.playMp3Folder(82);  //lay down your arms
delay(24000);
myDFPlayer.pause();

delay(500);

VZ=HIGH; VY=LOW; VX=LOW;
transmit(VX,VY,VZ);
VZ=HIGH; VY=LOW; VX=LOW;
}

if(q==2){
myDFPlayer.playMp3Folder(36);  //alien is impersonating the Chordettes
delay(4000);
myDFPlayer.pause();

delay(500); 

VZ=HIGH; VY=LOW; VX=LOW;
transmit(VX,VY,VZ);
VZ=HIGH; VY=LOW; VX=LOW;
}

q=q+1;
}
Serial.println();
Serial.print("test1");
Serial.println();







//____________________________________________________  RX2 RF signal detector 
// reset signal detect, samples and saves any HIGH states
VX2=LOW;
VY2=LOW;
VZ2=LOW;

for (i=0; i<100; i++) {    //from 300 on 8/7/25 
vx2= digitalRead(D10);
vy2=digitalRead(D11);
vz2= digitalRead(D12);

delay(10);

if (vx2==HIGH)  { VX2=HIGH;  }
if (vy2==HIGH)  { VY2=HIGH;  }
if (vz2==HIGH)  { VZ2=HIGH;  }
}  //_________________________________ end of RX2 RF signal detect part 1

Serial.println();
Serial.print("test2");
Serial.println();

//_____________________________________________________ extend detect time if any signal is detected
if (VX2==HIGH||VY2==HIGH||VZ2==HIGH)  {
for (i=0; i<300; i++) {   

vx2= digitalRead(D10);
vy2=digitalRead(D11);
vz2= digitalRead(D12);

delay(10);

if (vx2==HIGH)  { VX2=HIGH;  }
if (vy2==HIGH)  { VY2=HIGH;  }
if (vz2==HIGH)  { VZ2=HIGH;  }
} 
}


Serial.println();
Serial.print("test");
Serial.println();

if(VZ2==LOW&&VY2==LOW&&VX2==HIGH) {   //___________RX2 0 0 1 code detect

if (u>2) {u=1;}
if(u==1){
myDFPlayer.playMp3Folder(34);  //don't forget to pepper your remarks
delay(5000);
myDFPlayer.pause();

VZ=LOW; VY=HIGH; VX=LOW;
transmit(VX,VY,VZ);
VZ=LOW; VY=LOW; VX=HIGH;
}

if(u==2){
myDFPlayer.playMp3Folder(35);  //she got peppered with questions
delay(3000);
myDFPlayer.pause();

delay(300);
myDFPlayer.playMp3Folder(48);  // she gave salty answers
delay(3600);
myDFPlayer.pause();

delay(500); 

VZ=LOW; VY=HIGH; VX=LOW;
transmit(VX,VY,VZ);
VZ=LOW; VY=LOW; VX=HIGH;
}

u=u+1;
Serial.println();
Serial.print(u);
Serial.println();
}


//___________________________________RX2 1 0 0 code detect
if(VZ2==HIGH&&VY2==LOW&&VX2==LOW) {   

myDFPlayer.playMp3Folder(100); // Pepper by Butthole Surfers
delay(103000);  
myDFPlayer.pause();
delay(1000);

Serial.println();
Serial.print("RX2 100 detect");
Serial.println();

VZ=HIGH; VY=LOW; VX=HIGH;
transmit(VX,VY,VZ);
VZ=HIGH; VY=LOW; VX=LOW;
}




if(VZ2==LOW&&VY2==HIGH&&VX2==LOW) {   //___________ 0 1 0 code detect

if (w>2) {w=1;}
if(w==1) {
myDFPlayer.playMp3Folder(34); //Don't forget to pepper
delay(5000);
myDFPlayer.pause();

VZ=LOW; VY=HIGH; VX=HIGH;
transmit(VX,VY,VZ);
VZ=LOW; VY=HIGH; VX=LOW;
}

if(w==2) {
myDFPlayer.playMp3Folder(47);//here's Black Pepper by Micropop
delay(4500);
myDFPlayer.pause();

myDFPlayer.playMp3Folder(88);//Black Pepper by Micropop
delay(31000);
myDFPlayer.pause();

VZ=LOW; VY=HIGH; VX=HIGH;
transmit(VX,VY,VZ);
VZ=LOW; VY=HIGH; VX=LOW;
}

Serial.println();     //monitor "w" loop
Serial.print(w);
Serial.print(" w");
Serial.println();

w= w+1;
}



if(VZ2==HIGH&&VY2==LOW&&VX2==HIGH) {   // 1 0 1 code detect   "p" loop

if (p>2) {p=1;}
if(p==1) {
myDFPlayer.playMp3Folder(50); //Here's Stone Love by Pepper 
delay(4000);
myDFPlayer.pause();

myDFPlayer.playMp3Folder(91); //Stone Love by Pepper
delay(110000);
myDFPlayer.pause();

delay(300);

VZ=HIGH; VY=HIGH; VX=LOW;
transmit(VX,VY,VZ);
VZ=HIGH; VY=LOW; VX=HIGH;
}

if(p==2) {
myDFPlayer.playMp3Folder(100); //Pepper by Butthole Surfers
delay(40000);
myDFPlayer.pause();

myDFPlayer.playMp3Folder(19); //That's Pepper by Butthole Surfers
delay(4000);
myDFPlayer.pause();

VZ=HIGH; VY=HIGH; VX=LOW;
transmit(VX,VY,VZ);
VZ=HIGH; VY=LOW; VX=HIGH;
}

Serial.println();     //monitor "p" loop
Serial.print(p);
Serial.print(" p");
Serial.println();

p= p+1;
}


if(VZ2==LOW&&VY2==HIGH&&VX2==HIGH) {   //      0 1 1 code detect "s" loop

if (s>2) {s=1;}
if(s==1) {
myDFPlayer.playMp3Folder(86); // Beverly Hills
delay(195000);
myDFPlayer.pause();
}
if(s==2) {
myDFPlayer.playMp3Folder(85); //  Ghost Riders in the Sky
delay(195000);
myDFPlayer.pause();
}

Serial.println();     //monitor "s" loop
Serial.print(s);
Serial.print(" s");
Serial.println();

s= s+1;
}



if(VZ2==HIGH&&VY2==HIGH&&VX2==LOW) {   //___________ 1 1 0 code detect "r" loop

if (r>2) {r=1;}
if(r==1) {
myDFPlayer.playMp3Folder(35); //She got peppered with questions
delay(4000);
myDFPlayer.pause();

myDFPlayer.playMp3Folder(48); //She gave salty answers
delay(4000);
myDFPlayer.pause();
}

if(r==2) {
myDFPlayer.playMp3Folder(34); //Don't forget to pepper your
delay(6000);
myDFPlayer.pause();
}

Serial.println();     //monitor "r" loop
Serial.print(r);
Serial.print(" r");
Serial.println();

r= r+1;

VZ=HIGH; VY=HIGH; VX=HIGH;
xmit3(VX,VY,VZ);
VZ=HIGH; VY=HIGH; VX=LOW;
}

if(VZ2==HIGH&&VY2==HIGH&&VX2==HIGH) {   //___ 1 1 1 code detect "c" loop

if (c>2) {c=1;}
if(c==1) {
myDFPlayer.playMp3Folder(27); //the life you lead
delay(4000);
myDFPlayer.pause();
}

if(c==2) {
myDFPlayer.playMp3Folder(33); //  Ghost Riders in the sky
delay(195000);
myDFPlayer.pause();
}

c= c+1;

}

}

