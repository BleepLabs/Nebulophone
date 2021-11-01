/*

 NEBULOPHONE code v11 by Dr. Bleep
 
This code has not changed much since it was released mid 2011. It's very gnarly and amature and kinda embarrassing now but it did the thing!
It was my first big Arduino project and I coundn't have done it without these resources:

DDS:
 http://mouro.info/signal-generator-using-arduino-and-dds/
 http://interface.khm.de/index.php/lab/experiments/arduino-dds-sinewave-generator/
 http://www.analog.com/library/analogdialogue/archives/38-08/dds.html

Setting up timers.
 http://www.cs.mun.ca/~rod/Winter2007/4723/notes/timer0/timer0.html
 http://arcfn.com/2009/07/secrets-of-arduino-pwm.html
 http://blog.wingedvictorydesign.com/2009/05/29/generate-real-time-audio-on-the-arduino-using-pulse-code-modulation/2/

Also good to know:
 http://billgrundmann.wordpress.com/2009/03/03/to-use-or-not-use-writedigital/

BUT
My DIY noise guides and classes on using the Teensy to make synths are a better place to start these days. 
https://github.com/BleepLabs/Bleep-wiki/wiki
https://github.com/BleepLabs/dadageek-April-21/wiki

 */
#include <avr/pgmspace.h>
//#include <MemoryFree.h>

unsigned long chromatic[] = {

  2750, 2914, 3087, 3270, 3465, 3671, 3889, 4120, 4365, 4625, 4900, 5191, 5500, 5827, 6174, 6541, 6930, 7342, 7778,
  8241, 8731, 9250, 9800, 10383, 11000, 11654, 12347, 13081, 13859, 14683, 15556, 16481, 17461, 18500, 19600,
  20765, 22000, 23308, 24694, 26163, 27718, 29367, 31113, 32963, 34923, 36999, 39200, 41531, 44000, 46616, 49388,
  52325, 55437, 58733, 62225, 65926, 69846, 73999, 78399, 83061, 88000, 93233, 98777, 104650, 110873, 117466,
  124451, 131851, 139691, 147998, 156798, 166122, 176000, 186466, 197553, 209300, 221746, 234932, 248902, 263702,
  279383, 295996, 313596, 332244, 352000, 372931, 395107, 418601

};
int scale[] = {
  0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26, 28, 29, 31, 33, 35, 36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60, 62, 64
};


unsigned long counter, cprev1, cprev2;
unsigned long freq, freq2, keyfreq;

byte n = 1;
int keypress, kh, prevkh2, prevkeypress2;
int prevn;
int prevkeypress, prevattackmode;
int keyr1, keyr0, keyra, keyrw, keyrw2;
int waveselect, subwaveselect, prevwavepot;
int r, r2;
int i = 1;
long prev;
long prev4;

int irin;
int irout;
long irtempo;
int ir = 0;
long previrtempo = 1;
long previr = 0;
int arpselect;
byte count = 0;
int a = 0;
int key = 1;
int d;
int s;
int lforate;
int lforateC;
int lfo = 0;
int l = 0;
int j = 10;
int r3;
byte dronemode = 3;
byte dronemodebutton, prevdronemodebutton;
int irtempomod;
int irswitch;
int arprate = 10;
int arprateF;
int arprateL;
int keyoffset = 0;

byte scan = 1;
byte shiftbutton;
byte prevshiftbutton;
int shift = 0;
int maxrelease = 250;
int maxbrightness = 84;
int keym;
int prevarprateF;
int glide = 3;
byte keyp;
byte keyc;
int remember[2];
int h = 0;
long frequencyout;
long frequencyp;
long g;
long  f;
int gliderate;
long prev9;
int k;
int glidebutton;
int prevglidebutton;
int c = 1;
int b;
int maxwaveindex = 15;
int temp;
int release, releasem, releaseb;
int releaselength;
int ampholder = 1;
int previrin;
static int oscc, oscx, oscy, oscz, oscb, oscxb;
float amp = 1;
int wavepot, arppot, lfopot;
int himap, lowmap, lowf, hif, himap2, lowmap2;
int pwmPin = 3;
int ampm, ampb, read0, read1;
int arpcount, arp;
volatile unsigned long accumulator = 0;
volatile unsigned long accumulator2 = 0;
volatile unsigned long accumulator3 = 0;
volatile unsigned long accumulator4 = 0;
volatile unsigned long accumulator5 = 0;
volatile unsigned long increment = 0;
volatile unsigned long increment2 = 0;
volatile unsigned long increment3 = 0;
volatile unsigned long increment4 = 0;
volatile unsigned long increment5 = 0;
volatile unsigned long increment6 = 0;
volatile unsigned long increment7 = 0;


long prev8;
int incrementb = 0;
unsigned long holder4;
unsigned long holder3;
unsigned long holder2;
unsigned long holder;
int offx;
byte index = 0;
byte index2 = 0;
byte index3 = 0;
byte index4 = 0;
byte indexb = 0;
byte index5 = 0;
long frequency, frequencyc, frequency2, frequency2c, frequencyouta, frequencycs, frequencyps, temppot;
int rint, indexi;
int noise = 0;
int wrc, cnw, apot, waveB, waveoff;
float bpotf;
int drone;
int acc = 8;
int oscmode = 1;
int ircount;
//long tempobank[4];
int aread, oscsel;
int oscswitch = 1;
uint16_t osc, oscj, uosc, wr, wr2, rosc, bswitch;
int xpot;
int up = 1;
int tempermentbutton, shiftcount;
int temperment = 1;
int offsetpot = 5;
int keypot = 0;
int keypotm = 0;
int tunemode = 0;
int attackmode;
int attacklength;
int upa = 1, upb = 1, upc = 1;
int toplatcha = 0;
int attackon = 0;
unsigned long prev2, prev3;
int keydown, counta, prevkeydown;
//long tune;
int maxarp = 306;
unsigned long frequencya, frequencyw, frequencyw2;
int attackp;
long attacka, attackw, wavemod;
long gstep;
unsigned int lfsr = 1;
unsigned int lfsr2 = 1;
unsigned bitholder, bitholder2;
volatile byte icnt1, icnt2, ms, noisecount;
int keysb, keysd, keypressb, keypressd, prevkeypressb, prevkeypressd, prevkh;
int scount;
int gauge, spd;
long sprev;
int restbutton = 1,      recordbutton = 1, prevrestbutton,      prevrecordbutton ;
int record, rcount = 1, recordlatch, prevrcount, resta = 0;
int recordbank[32] = {2, 63, 5, 63, 10, 63, 5, 63, 1, 63, 63, 63, 10, 63, 63, 63};
int rplace, rest = 0, rstop = 8, prevrecord;
byte bhold;
volatile long whatok, whatno;
int i1, i2, i3, i4, tria;
byte b1, b2, b3, b4;
int epot, dswitch, noisekey, rarp;
long fpot, bpot, gpot, recordinput;
long thecount;
const  char  waveTable[] PROGMEM =


{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255,

  1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
  61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
  114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156,
  157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
  200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242,
  243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,

  1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31,
  33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65,
  67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99,
  101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 129, 131, 133,
  135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167,
  169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201,
  203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235,
  237, 239, 241, 243, 245, 247, 249, 251, 253, 255, 254, 252, 250, 248, 246, 244, 242,
  240, 238, 236, 234, 232, 230, 228, 226, 224, 222, 220, 218, 216, 214, 212, 210, 208,
  206, 204, 202, 200, 198, 196, 194, 192, 190, 188, 186, 184, 182, 180, 178, 176, 174,
  172, 170, 168, 166, 164, 162, 160, 158, 156, 154, 152, 150, 148, 146, 144, 142,
  140, 138, 136, 134, 132, 130, 128, 126, 124, 122, 120, 118, 116, 114, 112, 110, 108,
  106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 86, 84, 82, 80, 78, 76, 74, 72, 70, 68, 66,
  64, 62, 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22,
  20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 0,



};

void setup(void)

{

  //Serial.begin(9600);
  pinMode(1, INPUT);
  pinMode(0, INPUT);

  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(12, INPUT);
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT); // IR out
  pinMode(11, OUTPUT); // LFO LED out

  digitalWrite(1, HIGH);
  digitalWrite(0, HIGH);

  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);

  randomSeed(analogRead(5));


  if (digitalRead(14) == LOW) {
    oscswitch = 2;
  }
  else oscswitch = 1;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


  sbi (TIMSK2, TOIE2);

  sbi (TCCR2B, CS20);
  cbi (TCCR2B, CS21);
  cbi (TCCR2B, CS22);

  cbi (TCCR2A, COM2A0);  // clear Compare Match
  sbi (TCCR2A, COM2A1);
  sbi (TCCR2A, COM2B1);

  sbi (TCCR2A, WGM20);  // Mode 1  / Phase Correct PWM
  cbi (TCCR2A, WGM21);
  cbi (TCCR2B, WGM22);

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ISR(TIMER2_OVF_vect)
{ 



  if (oscswitch ==1){   //STANDARD MODE



    if (oscsel==1){  //single wave
     OCR2B =((osc)*release)>>8;
      accumulator += increment; 
      index=(accumulator >> 24);  
releaseb=0;
      accumulator2 += increment2; 
      index2 =(accumulator2 >> 24);  



      osc = pgm_read_byte(&waveTable[index+waveselect]);
      //osc = (((pgm_read_byte(&waveTable[(index2)+64])))/2);
    }
    if (oscsel==2){ // double wave selectable
    OCR2B =((osc)*release)>>8;

      accumulator += increment; 
      index=(accumulator >> 24);  

      accumulator2 += increment2; 
      index2 =(accumulator2 >> 24);  


      osc = (((pgm_read_byte(&waveTable[index+waveselect]))/4)+((pgm_read_byte(&waveTable[(index2)+subwaveselect])))/2);
    }

    if (oscsel==4){ // double wave
    OCR2B =((osc)*release)>>8;

      accumulator += increment; 
      index=(accumulator >> 24);  

      accumulator2 += increment2; 
      index2 =(accumulator2 >> 24);  


      osc = (((pgm_read_byte(&waveTable[index+waveselect]))/2)+((pgm_read_byte(&waveTable[(index2)])))/2);
    }
    if (oscsel==6){ // double wave


      OCR2B =(((osc)-releaseb)*release)>>5;
      accumulator += increment; 
      index=(accumulator >> 24);  




      osc = (pgm_read_byte(&waveTable[index+waveselect]))-tria;
    }


       if (oscsel==3){ //|?\/|/|/\/|/\?|?|?|?\/??|??||?\/\/\//\/ white noise
    OCR2B =((osc)*release)>>8;
      osc=lfsr>>8;
      //  nkey=(major[remember[0]+2])+ keyoffset+offsetpot+keypotm;
      if (freq!=0){
        icnt1++;
        if(icnt1==(remember[1]<<2)-3) {
          bitholder  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
          lfsr =  (lfsr >> 1) | (bitholder << 15);
          icnt1=0;
        }

        
        }
        if (freq==0){
          osc=0;
      }



    }
  }

  if (oscswitch==2){ //drone death 40XX


    if (dronemode==0){ //METAL MACHINE
      releaselength=40;
      accumulator += increment>>1; 
      index=(accumulator >> 24);  

      accumulator2 += increment2>>2; 
      index2 =(accumulator2 >> 24);  
      accumulator3 += bpot;

      index3 = (accumulator3) >> 8;
      if(dswitch == 1)
      {
        uosc =((pgm_read_byte(&waveTable[index3+waveoff])))-(((pgm_read_byte( &waveTable[index+waveoff]))*release)>>8);
      }
      if(dswitch == 0)
      {
        uosc =((pgm_read_byte(&waveTable[index3+waveoff])))^(((pgm_read_byte( &waveTable[index+waveoff]))*release)>>8);
      }
    }
    if (dronemode==1){ //detunestep


      uosc = (osc*release)>>8; 
      releaselength=40;

      accumulator5 += increment5; 
      index5=(accumulator5 >> 24);  

      accumulator += increment; 
      index =(accumulator >> 24);  

      if(dswitch == 1)
      {
        osc = (((pgm_read_byte(&waveTable[index5+waveselect])))-((pgm_read_byte(&waveTable[(index+waveselect)]))));
      }
      if(dswitch == 0)
      {
        osc = (((pgm_read_byte(&waveTable[index5+waveselect])))*((pgm_read_byte(&waveTable[(index+waveselect)]))))>>8;
      }





    }

    if (dronemode==2){ //ALL GLORY TO THE NEBULO-TOAD
      releaselength=40;
      accumulator += increment>>1; 
      index=(accumulator >> 24);  

      accumulator2 += increment2>>2; 
      index2 =(accumulator2 >> 24);  
      accumulator3 += bpot;

      b1++;
      b2+=2;
      b3+=3;
      b4+=epot;

      osc =(((pgm_read_byte(&waveTable[waveoff+index^b2^b3])))+(pgm_read_byte( &waveTable[waveoff+index2^b1^b4])));
      uosc = (osc*release)>>8; 

    }

    if (dronemode==3){


      // You broke my master system
      accumulator += increment6; 
      index=(accumulator >> 24);  

      accumulator2 += increment7; 
      index2=(accumulator2 >> 24);  

      if(icnt1++ == (bpot)) {
        bitholder  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
        lfsr =  (lfsr >> 1) | (bitholder << 15);
        icnt1=0;
      }


      if ((i2+=4)>(lfsr*bitholder)+1){
        i2=0;
      }
      if ((i3+=6)>(lfsr*2+1)){
        i3=0;
      }
      if ((i4+=32)>((lfsr*16)+1)){
        i4=0;
      }


      if(dswitch == 1) 
      {
        if ((i2+=4)>(lfsr*bitholder)+1){
          i2=0;
        }
        if ((i3+=6)>(lfsr*2+1)){
          i3=0;
        }
        if ((i4+=32)>((lfsr*16)+1)){
          i4=0;
        }
        uosc =(((pgm_read_byte(&waveTable[waveoff+index])))-(pgm_read_byte( &waveTable[waveoff+index2])));
      }
      if(dswitch == 0)

      {
        if ((i2+=2)>(lfsr)+1){
          i2=0;
        }
        if ((i3+=2)>(lfsr*2+1)){
          i3=0;
        }
        if ((i4+=16)>((lfsr*2)+1)){
          i4=0;
        }

        uosc =(((pgm_read_byte(&waveTable[waveoff+index])))-(pgm_read_byte( &waveTable[waveoff+index2])));
      }

    }


    if (dronemode>=4){

      dronemode=0;
    }
    OCR2B = uosc;

  }
}


void DDS() //////////////////////////////////////////////////////////////////////////////////////////////////////////FREQUENCY 1 
{
  releasem=release;

  if (resta==0){
      freq=frequencyouta;
    freq2=freq*3;
      if (oscsel==2){
    freq=frequencyouta;
    freq2=freq/3;
  }
  if (oscsel==4){
    freq=frequencyouta;
    freq2=freq*2;
  }
  else{
    freq=frequencyouta;
    freq2=freq/3;
  }

  
  //  noisekey=(remember[1]<<2)-3;
  }
  if (resta==1){
    freq=0;
    freq2=0;
   //noisekey=1;
  }
  if (oscswitch==1){
    increment=(pow(2,32)*freq)/(3137660);
    increment2=pow(2,32)*freq2/ (3133000);

    // increment3=pow(2,32)*freq/ (3137660);
  }
  if (oscswitch==2){
    increment=(pow(2,32)*freq)/(3137660);
    increment2=pow(2,32)*freq2/ (3133000);

    increment5=(pow(2,30)*(freq))/ (3137660+fpot);

    increment4=pow(2,32)*(freq)/ (3137660);
    increment6=pow(2,32)*(freq+i2)/ (3137660);
    increment7=pow(2,32)*(freq+i4-i3)/ (3137660);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(){

DDS(  );
CONTROLS ();
KEYS ();
GLIDE();
SHIFT();
WAVESELECT();

ARP();
LFO();
RECORD();

}

////////////////////////////////////////////////////////////////// ARP

void ARP(){

  if (arppot <5){
    //  remember[0] = key;
    remember[1] = key;
    count=0;  
    //a=0;

  }
  if (arppot >=5 && arppot<170)  {

    arprateL = map(arppot, 5, 170, maxarp, 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 5, 170, 4, 1);
    arprateF = constrain(arprateL, 1 , 4);  

    if (count==0){
      remember[0] = key;
      remember[1] = key +0;
      toplatcha=0;
    }
    else if (count==1){
      remember[0] = key;
      remember[1] = key +2;
      toplatcha=0;
    }
    else if (count>=2){ 
      count=0;
    }

  }


  if (arppot >=170 && arppot<340)  {

    arprateL = map(arppot, 170, 340, maxarp , 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 170, 340, 1, 4);
    arprateF = constrain(arprateF, 1 , 4);  


    if (count==0)      {
      remember[0] = key;
      remember[1] = key +0;

    }
    else if (count==1)      {
      remember[0] = key;
      remember[1] = key -1;

    }
    else if (count==2)      {        
      remember[0] = key;
      remember[1] = key -2; 

    }
    else if (count>=3)      {        
      count=0;

    }
  }



  if (arppot >=340 && arppot<510)  {

    arprateL = map(arppot, 340, 510, maxarp , 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 340, 510,  1, 4);
    arprateF = constrain(arprateF, 1 , 4);  

    if (count<8)
    {
      remember[0] = key;
      remember[1] = key +count;

    }
    else if (count>=8)
    {
      // a=0; 
      count=0;
    }
  }

  if (arppot >=510 && arppot<680)  {


    arprateL = map(arppot, 510, 680, maxarp , 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 510, 680,  1, 4);
    arprateF = constrain(arprateF, 1 , 4);  

    if (count<8)
    {
      remember[0] = key;
      remember[1] = key+8 -count;

    }
    else if (count>=8)
    {
      // a=0; 
      count=0;
    }
  }
  if (arppot >=680 && arppot<850)  {
    
    
    
    recordlatch=0;
    resta=0;
    rest=0;
    arprateL = map(arppot, 680, 850,  maxarp , 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 680, 850,  1, 4);
    arprateF = constrain(arprateF, 1 , 4);  


    if (count==0)
    {    

      remember[0] = key;
      remember[1] = key+rarp;

    }
    else if (count==1)
    { 
       rarp=  random(-8,12);
       
      remember[0] = key;
      remember[1] = key +0;

    }
    else if (count>=2)
    {
      count=0;
    }

  }

  if (arppot >=850 && arppot<1020) {
    recordlatch=0;
    rplace=0;
    rcount=0;
    record=0;

    record=0;
    arprateL = map(arppot, 850, 1020,  maxarp , 1);
    arprateL = constrain(arprateL, 1 , maxarp);  
    arprateF = map(arppot, 850, 1020,  1, 4);
    arprateF = constrain(arprateF, 1 , 4);  

    if (count<rstop)
    {

      if (recordbank[count]==63){
        
        resta=1;
        remember[0] = key;
        remember[1] = key;
      }

      if (recordbank[count]!=63){
        resta=0;
        remember[0] = key;
        remember[1] = key+recordbank[count];
      }

    }

    if (count>=rstop)
    {
      count=0;
    }


  }

  if (arppot >=1020){

   // count=0;
   // arprateL=0;
   // arprateF=0;
    recordlatch=1;
    digitalWrite(13, LOW);  
    //arprateL=0;
    //arprateF=0;
    resta=0;

  }

  if (prevarprateF != arprateF){
    previrtempo=0;
  }

  prevarprateF = arprateF;


}




void IR(){
   ////////////////////////////////////////////////////////////////// IR
  // All of the Andromeda Space Rocker Kits can communicate via IR. The Nebulophone can sync it's arpeggiator to a multiple
  // of the IR clock rate. This is done but simply reading the analog input conected to the detector and measuring the time
  // between peaks. There are some sync issuse to work, though. I believe the rate is read correctly but sometimes the arp
  // speed can lag.

 // if (tunemode!=1){
    if (irswitch == 0){

      irin = (analogRead(2));

      if (irin > 5 && previrin <=5){

        irtempo = millis() - previrtempo; 
        previrtempo = millis();
        ir=1;

        //      irsub();
      }

      else {
        ir=0;   
      }

      previrin=irin; 
      arprate = irtempo / arprateF;

    }



    else if (irswitch == 1){
      arprate = arprateL;

    }



    if (millis() - prev8 >= arprate ) {
      prev8 = millis();

    //  r3 = (lfsr2>>12)-8;

      count++;   
PORTB |= _BV(5);

    }
    
    else {
    PORTB &= ~_BV(5);
    
    }
  }

void KEYS(){
  
// the order of the pins from lowest note is 15,16,18,2,4,6,11,12,13,14
  j++;//
  if (j>63){
    //dfreqc=(analogRead(4))*8;         
    //dfreqf=(analogRead(5)/8); 
  }

  keysb = (PINB & B00010111);
  keysd= (PIND &   B11110101);

  switch (keysb){
  case B10101:
    kh=1;
    keypress=1;
    keypressb=1;
    break;

  case B10011:
    kh=2;   
    keypress=1;   
    keypressb=1;
    break;

  case B111:
    kh=3;   
    keypress=1;   
    keypressb=1;
    break;

  case B10110:
    kh=10;   
    keypress=1;   
    keypressb=1;
    break;

  default: 
    keypressb=0;   
    break;
  }

  switch (keysd){
  case B11110100:
    kh=4;
    keypress=1;
    keypressd=1;
    break;

  case B11110001:
    kh=5;   
    keypress=1;   
    keypressd=1;
    break;

  case B11100101:
    kh=6;   
    keypress=1;   
    keypressd=1;
    break;

  case B11010101:
    kh=7;   
    keypress=1;   
    keypressd=1;
    break;

  case B10110101:
    kh=8;   
    keypress=1; 
    keypressd=1;  
    break;

  case B1110101:
    kh=9;   
    keypress=1; 
    keypressd=1;      
    break;

  default: 

    keypressd=0;  
    break;
  }

  key = kh;

  if (keypressd==0 && keypressb==0)
  {
    keypress=0;
  }

  if (kh != prevkh || keypress!=prevkeypress){

    if (keypress == 1) {
      count=0;
      remember[0] = prevkh;
      release=255;
              releaseb=255;
      remember[1] = key;
      keydown =1;
      scan=0;
    }   

    prevkh = kh;
    prevkeypress=keypress;
    prevkeydown=keydown;
  }

  if (keypress == 0) {

    keydown =0;
    if (millis() - prev > releaselength ) {       
      prev = millis();
      if (releaselength<20){
                releaseb-=4;
        if (release > 5){
          release-=(((release))*.3);
        }

        if (release <= 10){
                  releaseb-=4;
          release =0;
          ampholder=1;
        }
      }
      if (releaselength>=20){
        releaseb-=4;
        if (release > 5){
          release-=(((release))*.02);
        }

        if (release <= 10){
          release =0;
          ampholder=1;
        }
      }




    }

  }

  
}

void LFO(){
  
 ////////////////////////////////////////////////////////////////// LFO
  // The LFO outputs analog levels through the PWM in a more traditional way but since it's using
  // pin 11 with is also on Timer 1, it will sound much better since the LED won't actually be 
  // blinking at 500 Hz.
  // Only one pot is used to control mode as well as rate. Inside each mode a differnt output
  // is performed based on lforateC.
  
maxbrightness=64;
  if (tunemode!=1){
    
    if (lfopot <202){
      lforate = map(lfopot, 0, 202, 0 , maxbrightness);
      lforateC = constrain(lforate, 0,maxbrightness);
      analogWrite(11, lforateC);
    }

    else if (lfopot >=202 && lfopot <404){

      lforate = map(lfopot, 202, 404, 96 , 1);
      lforateC = constrain(lforate, 1 , 96);

      if (millis() - prev4 > lforateC ) {
        prev4 = millis();    

        lfo+=2;
        lfo+=(lfo/4);
        analogWrite(11, lfo);

        if (lfo>=maxbrightness){
          lfo=0;  
        }
      }

    }

    else if (lfopot >=404 && lfopot <606){

      lforate = map(lfopot, 404, 606, 64 , 1);
      lforateC = constrain(lforate, 1 , 64);

      if (lfo<=5){
        up=1;  
      }
      if (lfo>=maxbrightness){
        up=0;  
      }

      if (millis() - prev4 > lforateC ) {
        prev4 = millis();    

        if (up==1){
          lfo+=4;
          lfo+=(lfo/4);
        }
        if (up==0){
          lfo-=4;
          lfo-=(lfo/4);
        }         


        analogWrite(11, lfo);


      }

    }

    else if (lfopot >=606 && lfopot <808){
      lforate = map(lfopot, 606, 808, 255 , 1);
      lforateC = constrain(lforate, 1 , 255);

      if (millis() - prev4 > lforateC ) {
        prev4 = millis();    

        if (lfo==0){
          analogWrite(11, 0);
          lfo=1;
        }

        else if (lfo>=1){
          analogWrite(11, maxbrightness);
          lfo=0;
        }
      }
    }

    else if (lfopot >=808&& lfopot<1010){

      lforate = map(lfopot, 808, 1010, 255 , 1);
      lforateC = constrain(lforate, 1 , 255);

      if (millis() - prev4 > lforateC ) {
        prev4 = millis();    
r2 = (lfsr2>>8);
        analogWrite(11, r2);

      }

    }
    else if (lfopot>=1010 && lfopot<1020){

      if (millis() - prev4 > arprate/3 ) {
        prev4 = millis();    

        if (lfo==0){
          analogWrite(11, 0);
          lfo=1;
        }

        else if (lfo>=1){
          analogWrite(11, maxbrightness);
          lfo=0;
        }
      }

    }
    else if (lfopot>=1020){

      if (millis() - prev4 > arprate/2 ) {
        prev4 = millis();    

        if (lfo==0){
          analogWrite(11, 0);
          lfo=1;
        }

        else if (lfo>=1){
          analogWrite(11, maxbrightness);
          lfo=0;
        }
      }

    }
  }
  else{
  }

}

void SHIFT(){
  
  if (shiftcount<=600){
    if (shiftbutton != prevshiftbutton){
      if (shiftbutton == HIGH) {
        shift++;
        shiftcount=0;
      }     

      else{
        shiftcount=0;
      }
      prevshiftbutton = shiftbutton;
    }

    offx=12;
    if( shift == 0){
      keyoffset=(0);
    }

    if( shift > 3){
      shift=0;
    }
    if( shift > 0 ){
      keyoffset=(offx*shift);


    } 




 
  }
  
    if (shiftbutton == LOW) {
      shiftcount++;

    }    
    
  if (shiftcount>600){
    analogWrite(11, maxbrightness);
    digitalWrite(13, LOW);  
    tunemode=1;
    if (shiftbutton != prevshiftbutton){
      if (shiftbutton == LOW) {

        tunemode=0;
        shiftcount=0;
      }
    }
    prevshiftbutton = shiftbutton;
  }


}


void CONTROLS(){ 
   
  if (oscswitch==1){
    IR();
    if (tunemode!=1 && recordlatch!=1){    //standard
      
   glidebutton = digitalRead(1);
    //   glidebutton = 1;
      shiftbutton = digitalRead(14);
      irswitch = digitalRead(15);
      wavepot=(analogRead(3))>>6;
      lfopot= (analogRead(4));
    // apot = (analogRead(5))<<4; arppot = 1;
     arppot = (analogRead(5));
    }
    
    if (tunemode==1){
      tempermentbutton = digitalRead(1);
      shiftbutton = digitalRead(14);
      wavepot=(analogRead(3));
      offsetpot=0;
      // offsetpot=(((analogRead(5))>> 7)-2)*12;
      keypot= (analogRead(4));
      // apot = (analogRead(5))/32; arppot = 1;
      arppot = 0;

      if (keypot<=4)
      {
        temperment=0;
      }

      if (keypot>4 && keypot<512)
      {
        temperment=1;
        keypotm=map(keypot,4,512,-11,11);
      }
      if (keypot>=512)
      { 
        temperment=2;
        keypotm=map(keypot,512,1020,-11,11);
      }
 

    }
    
    if (recordlatch==1){
       arppot = (analogRead(5));
      restbutton = digitalRead(1);
      recordbutton = digitalRead(14);
      irswitch = digitalRead(15);
      wavepot=(analogRead(3))>>6;
      lfopot= (analogRead(4));
    }
    
  }
  if (oscswitch==2){

    if (uosc>200){
      digitalWrite(13, HIGH);  
    }
    if (uosc<=200){
      digitalWrite(13, LOW);  
    }

    shiftbutton = digitalRead(14);

    irswitch = 0;
    dswitch=digitalRead(15);
    wavepot=127;
    waveoff=(analogRead(3))+128;
    lfopot = (analogRead(4));
    arppot = 1;
    bpot = (analogRead(5));
       epot = bpot >> 5;
       fpot= (bpot<<12)-4194304;
       gpot= bpot*4;
    dronemodebutton= digitalRead(1);
    if (dronemodebutton != prevdronemodebutton){
      if (dronemodebutton == HIGH) {
        dronemode++;
      }     

      else{

      }
      prevdronemodebutton = dronemodebutton;
    }
  }
}

void GLIDE(){
   /////////////////////////////////////////////////////////////////////////////////// glide

  if (glidebutton != prevglidebutton){
    if (glidebutton == HIGH) {
      glide++;
            analogWrite(11, 255);
    }     

    else{

    }
    prevglidebutton = glidebutton;
  }
  
  
if (temperment==1){
keyr1=(scale[remember[1]+5])+ keyoffset+offsetpot+keypotm;
keyr0=(scale[remember[0]+5])+ keyoffset+offsetpot+keypotm;

}
if (temperment==2){
keyr1=(scale[remember[1]+3])+ keyoffset+offsetpot+keypotm;
keyr0=(scale[remember[0]+3])+ keyoffset+offsetpot+keypotm;

}
if (temperment==0){
keyr1=(remember[1])+ keyoffset+12+offsetpot+keypotm;
keyr0=(remember[0])+ keyoffset+12+offsetpot+keypotm;

}

  frequencyc=chromatic[keyr1];
  frequencyp=chromatic[keyr0];


  if (gliderate>0){
    frequencyout = frequencyp+g;
    f= frequencyc-frequencyp;
    gstep=(f/16);


    if (f>0){

      if (millis() - prev9 > gliderate ) {
        prev9 = millis();    
        g+=(gstep);

      }


      if (g>=f){

        remember[0]=remember[1];
        g=0;
      }
    }

    if (f<0){


      if (millis() - prev9 > gliderate ) {
        prev9 = millis();    
        g-=(gstep)*-1;
      }


      if (g<=f){

        remember[0]=remember[1];
        g=0;
      }

    }

  }








  if (gliderate==0){
    frequencyout= frequencyc;

  }

  if (glide ==0){
    gliderate=0;

  }
  else if (glide ==1){
    gliderate=2;

  }
  else if (glide==2){
    gliderate=6;

  }
  else if( glide == 3)
  {
    gliderate=12;
  }
  else if( glide >= 4)
  {
    glide=0;
  }}


  void RECORD(){
  

 if (recordbutton != prevrecordbutton){

      if (recordbutton == HIGH) {
        rcount++;
 rplace=0;
      }     

      else{

      }
      prevrecordbutton = recordbutton;
          prevrcount=rcount;
    }
  



    if( rcount == 0){
      record=0 ;
     // rstop=rplace;
    }

    if( rcount == 1){
      record=1;
     
    }

    if( rcount > 1){
      // record=0 ;
      rcount=0;

    }

if (restbutton != prevrestbutton){
   if (restbutton == HIGH) {
   recordbank[rplace]=63;
        rplace++;
                rstop=rplace; 
       digitalWrite(13, HIGH);  rest=1;
   }     
   
   
   prevrestbutton = restbutton;
   }
   else{
   rest=0;
   }
//if (recordlatch==0){record=0;rcount=0;}
 if (rplace>=32){
   digitalWrite(13, LOW);
 record=0;
 rplace=0;
 } 
  if (record==1){
    digitalWrite(13, HIGH);
    
if (rplace<32){
delay(10);
    if (kh != prevkh2 || keypress!=prevkeypress2){
      if (keydown==1){
        recordbank[rplace]=key;
        rplace++;
        rstop=rplace; 
      }

           else{
      }
      prevkh2= kh;
      prevkeypress2=keypress;

    }
}


  }
  prevrecord=record;
}
 /*   
if (prevrecord!=record){
  if (record==1){
    rplace=0;
//  recordbank[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
}}


 if (recordbutton==0){
 //rcount++;
 }
 
 if (rcount>40 && recordlatch==1){
 record=1;
 rcount=0;
 }
 
 */
/*
  if (recordlatch==0){
    record=0;
    rcount=0;
  }
  if (recordlatch==1){
    if (recordbutton != prevrecordbutton){
      if (recordbutton == HIGH) {
        rcount++;

      }     

      else{

      }
      prevrecordbutton = recordbutton;
    }

    if( rcount == 0){
      record=0 ;
      rstop=rplace;
    }

    if( rcount == 1){
      record=1;
      if (      prevrcount!=rcount){
        rplace=0;
      }
    }

    if( rcount >= 2){
      // record=0 ;
      rcount=0;

    }
    prevrcount=rcount;
  }


  
 if (restbutton != prevrestbutton){
   if (restbutton == HIGH) {
   rest=1;
   
   }     
   
   else{
   
   }
   prevrestbutton = restbutton;
   }
   */

void WAVESELECT(){
  
  ////////////////////////////////////////////////////////////////// Wave select  /////////////////////////////////////////////////////
  //////////// Wave select
  //Just like the LFO pot except the variable inside each mode controls release.
if (attackmode!=prevattackmode || wavepot != prevwavepot){ cprev2=0;attacka=0;attackw=0;}


  if (attackmode==0){
    frequencyouta=frequencyout;

  }

  if (attackmode==2){
    //  wavemod=0;
    attacka=0;            
    if (millis() - cprev2 > attacklength ) {       
      cprev2 = millis();

      counta++;
    }

    if (counta==0){
      frequencyouta=frequencyout; 
      toplatcha=0;
    }
    else if (counta==1){
      frequencyouta=0; 
      toplatcha=0;
    }
    else if (counta>=2){ 
      counta=0;
    }

  }
  if (attackmode==3){    // do the wiggle
  


    frequencyouta=frequencyout+attackw;

    if (attackw>=frequencyc/12){
      //attackw=frequencyw;
      upa=0;
    }

    if (attackw<=(frequencyc/-12)){
      //attackw=frequencyw2;
      upa=1;
    }


  if (millis() - cprev2 > attacklength ) {       
      cprev2 = millis();

      if (upa==1){
        attackw+=(frequencyc/24);  
        // wavemod+=4; 

      }
      if (upa==0){
        attackw-=(frequencyc/24);  
        //  wavemod-=4;    

      }   

    }

  }
  
  if (attackmode==4){    
  


    frequencyouta=frequencyout;

    if (tria>=255){
      //attackw=frequencyw;
      upa=0;
    }

    if (tria<=0){
      //attackw=frequencyw2;
      upa=1;
    }


  if (millis() - cprev2 > attacklength ) {       
      cprev2 = millis();

      if (upa==1){
        tria+=4;  
        // wavemod+=4; 

      }
      if (upa==0){
        tria-=4;  
        //  wavemod-=4;    

      }   

    }

  }
//if (wavepot != prevwavepot){frequencyouta=0;}
  if (wavepot ==0){

    releaselength = 5;
    // pulse +  oct down pulse
    waveselect=0;
    subwaveselect=32;
    oscsel=2;
    attackmode=0;

  }

  if (wavepot ==1){

    releaselength = 40;
    // pulse +  oct down pulse
    waveselect=0;
    subwaveselect=32;
    oscsel=2;
    attackmode=0;
  }

  if (wavepot ==2){

    releaselength = 5;
    // tri +  oct down squ
    waveselect=319;
    subwaveselect=319;
    oscsel=4;
    attackmode=0;

  }

  if (wavepot ==3){

    releaselength = 40;
    // tri +  oct down squ
    waveselect=319;
    subwaveselect=319;
    oscsel=4;
    attackmode=0;

  }
  if (wavepot ==4){
   attacklength = 6;

    releaselength=30;

    // Wiggle
    waveselect=64;
    oscsel=2;
    attackmode=3;

  }
  if (wavepot ==5){
   attacklength = 24;

    releaselength=35;

    // Wiggle 
    waveselect=64;
    oscsel=2;
    attackmode=3;

  }
  if (wavepot ==6){
   attacklength = 24;
    releaselength = 15;
    // gate
    waveselect=64;
    subwaveselect=64;
    oscsel=2;
    attackmode=2;

  }
  if (wavepot ==7){
   attacklength = 48;
    releaselength = 15;
    // gate
    waveselect=64;
    subwaveselect=64;
    oscsel=2;
    attackmode=2;
  }
  
if (wavepot ==8){
    // PEWPEW
           attacklength = 64;
   releaselength = 16;
    waveselect=575;
    noise=0;
    oscsel=6;
attackmode=4;
  }
   if (wavepot ==9){
    // PEWPEW
       attacklength = 64;
   releaselength = 50;
    waveselect=575;
    noise=0;
    oscsel=6;
attackmode=4;

  }
   if (wavepot ==10){
    // ramp

   releaselength = 2;
    waveselect=0;
    noise=0;
    oscsel=1;

  }
   if (wavepot ==11){
    // ramp
   releaselength = 25;
    waveselect=0;
    noise=0;
    oscsel=1;

  }
    if (wavepot ==12){
    // tri
   releaselength = 5;
    waveselect=575;
    oscsel=1;
        attackmode=0;

  }
    if (wavepot ==13){
    // tri
   releaselength = 25;
    waveselect=575;
    oscsel=1;
        attackmode=0;

  }
     if (wavepot ==14){
    // noise
   releaselength = 1;
    oscsel=3;

  }   
  if (wavepot ==15){
    // noise
   releaselength = 25;
    oscsel=3;

  }
  

prevwavepot=wavepot;
prevattackmode=attackmode;}
