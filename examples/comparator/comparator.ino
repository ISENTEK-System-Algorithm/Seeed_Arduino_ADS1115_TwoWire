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
    while(!ads.begin(ADS1115_GND_ADDRESS)){
        Serial.print("ads1115 init failed!!!");
        delay(1000);
    }
    ads.setOperateMode(ADS1115_OS_SINGLE);   
    ads.setOperateStaus(ADS1115_MODE_CONTIN);
    ads.setPGAGain(ADS1115_PGA_6_144); //MAX 6.144V 
    ads.setSampleRate(ADS1115_DR_860); //860 SPS
    ads.setCompaMode(ADS1115_COMP_MODE_WINDOW); 
    //Set Comparator mode to window mode
    ads.setCompaPolarity(ADS1115_COMP_POL_ACTVHIGH); 
    //The ALERT pin keeping high when the ADC value beyond a threshold upper or lower value.
    ads.setCompaLatching(ADS1115_COMP_LAT_LATCH);
    //latching when the ADC value beyond a threshold upper or lower value. 
    ads.setCompaQueue(ADS1115_COMP_QUE_1CONV);
    //comparing after 1 Conversion. 
    ads.setLowThreshold(0x0050);
    //set low threshold value to 0x0050(0x0000 ~ 0x7fff)
    ads.setHighThreshold(0x4e20);
    //set high threshold value to 0x4e20(0x0000 ~ 0x7fff)
}
void loop(void)
{   
    int16_t adc0;
    adc0 = ads.getConversionResults(channel0); //P = AIN0, N = GND
    Serial.print("AIN0: "); Serial.println(adc0);
    Serial.println(" ");    
    delay(1000);
}