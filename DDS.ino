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



