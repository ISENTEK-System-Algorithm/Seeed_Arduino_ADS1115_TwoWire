#include "ADS1115.h"

#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    ADS1115<SoftwareWire> ads(myWire);//IIC
#else
    #include <Wire.h>
    ADS1115<TwoWire> ads(Wire);//IIC
#endif

void setup(void) 
{
    Serial.begin(115200);
    while(!ads.begin(ADS115_GND_ADDRESS)){
        Serial.print("ads1115 init failed!!!");
        delay(1000);
    }//0x48
    //ads.begin(ADS115_VDD_ADDRESS)
    //ads.begin(ADS115_SDA_ADDRESS)
    //ads.begin(ADS115_SCL_ADDRESS)

    ads.setOperateMode(ADS1115_OS_SINGLE);   
    ads.setOperateStaus(ADS1115_MODE_SINGLE);

    ads.setPGAGain(ADS1115_PGA_6_144); //6.144V 
    // ads.setPGAGain(ADS1115_PGA_4_096); //4.096V
    // ads.setPGAGain(ADS1115_PGA_2_048); //2.048V
    // ads.setPGAGain(ADS1115_PGA_1_024); //1.024V
    // ads.setPGAGain(ADS1115_PGA_0_512); //0.512V 
    // ads.setPGAGain(ADS1115_PGA_0_256); //0.256V
    
    // ads.setSampleRate(ADS1115_DR_8); //8 SPS
    // ads.setSampleRate(ADS1115_DR_16); //16 SPS
    // ads.setSampleRate(ADS1115_DR_32); //32 SPS
    // ads.setSampleRate(ADS1115_DR_64); //64 SPS
    // ads.setSampleRate(ADS1115_DR_128); //128 SPS
    // ads.setSampleRate(ADS1115_DR_250); //250 SPS
    // ads.setSampleRate(ADS1115_DR_475); //475 SPS
    ads.setSampleRate(ADS1115_DR_860); //860 SPS
}
void loop(void) 
{   
    int16_t adc0,adc1,adc2,adc3;
    adc0 = ads.getConversionResults(channel0); //P = AIN0, N = GND
    adc1 = ads.getConversionResults(channel1); //P = AIN1, N = GND
    adc2 = ads.getConversionResults(channel2); //P = AIN2, N = GND
    adc3 = ads.getConversionResults(channel3); //P = AIN3, N = GND
    Serial.print("AIN0: "); Serial.println(adc0);
    Serial.print("AIN1: "); Serial.println(adc1);
    Serial.print("AIN2: "); Serial.println(adc2);
    Serial.print("AIN3: "); Serial.println(adc3);
    Serial.println(" ");    
    delay(1000);
}