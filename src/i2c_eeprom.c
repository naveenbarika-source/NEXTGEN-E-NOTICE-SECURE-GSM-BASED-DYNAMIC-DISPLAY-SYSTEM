//i2c_eeprom.c

#include "i2c.h"

#include "delay.h"


void EEPROM_Write(u8 slaveAddr,

	                        u16 wBufStartAddr,

                          u8 *p,

                          u8 nBytes) 
{ 

  u8 i; 

	//issue start condition

  i2c_start();	 

  //slaveAddr + w,& take ack 

  i2c_write(slaveAddr<<1);     

  //wBufStartAddr,& take ack 

  i2c_write(wBufStartAddr>>8);
  i2c_write(wBufStartAddr);   

  for(i=0;i<nBytes;i++) 

  { 

    //wDATA,& take ack 

   i2c_write(p[i]);              

  }
   
  i2c_write('$');

  //issue stop condition

  i2c_stop(); 

  //delay for internal write-cycle in eeprom

    delay_ms(10); 

}			  


void EEPROM_Reed(u8 slaveAddr,

	                      u16 rBufStartAddr,

                        u8 *p,

                        u8 nBytes) 

{ 

   u8 i; 

   //issue start condition

   i2c_start();	 

   //slaveAddr + w,&take ack 

   i2c_write(slaveAddr<<1); 

	 //rBufStartAddr,&take ack 
   i2c_write(rBufStartAddr>>8);

   i2c_write(rBufStartAddr); 

   //issue repeated start condition

   i2c_restart();	 

   //slaveAddr + r,&take ack

   i2c_write(slaveAddr<<1|1);

   for(i=0;i<nBytes;i++) 

   { 

     //read (n-1) bytes,for each,provide mack

     p[i]=i2c_mack();
	 if(p[i]=='$')
	       break;	 

   }

   //read nth(last) byte,& provide nack	 
	  p[i]='\0';

      i2c_nack(); 
   
   //issue stop condition

   i2c_stop(); 

}
void i2c_eeprom_bytewrite(u8 slaveAddr,
                                u8 wBufAddr,
                          u8 dat)
{
    //issue i2c start 
    i2c_start();
    //slaveAddr + w,& take ack 
    i2c_write(slaveAddr<<1);
    //wBuffAddr,ack 
	i2c_write(wBufAddr>>8);
    i2c_write(wBufAddr);
    //dat,ack 
    i2c_write(dat);
    //issue i2c stop     
    i2c_stop();
    //write cycle delay 
    delay_ms(10);
}
u8 i2c_eeprom_randomread(u8 slaveAddr,
                         u8 rBufAddr)
{
    u8 dat;
    //start condition 
    i2c_start();
    //slaveAddr + w , &take ack 
    i2c_write(slaveAddr<<1);
    //rBufAddr , &take ack
	i2c_write(rBufAddr>>8);
	 
    i2c_write(rBufAddr);
    //restart     
    i2c_restart();
    //slaveAddr + r, &take ack 
    i2c_write(slaveAddr<<1|1);
          //read byte & provide nack
    dat=i2c_nack();
    //stop condition 
    i2c_stop();
    return dat;
}

