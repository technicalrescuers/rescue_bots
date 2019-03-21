#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

//Define widths
int pwm_width_2 = 0;
int pwm_width_3 = 0;
int pwm_width_4 = 0;
int pwm_width_5 = 0;
int pwm_width_6 = 0;
int pwm_width_7 = 0;

Servo PWM2;
Servo PWM3;
Servo PWM4;
Servo PWM5;
Servo PWM6;
Servo PWM7;

/**************************************************/

void setup()
{
  //Set the pins for each PWM signal
  PWM2.attach(2);
  PWM3.attach(4);
  PWM4.attach(5);
  PWM5.attach(6);
  PWM6.attach(7);
  PWM7.attach(8);
}

void loop()
{
  pwm_width_2 = 1700;     //PWM value on digital pin D2
  pwm_width_3 = 1500;     //PWM value on digital pin D3
  pwm_width_4 = 1500;     //PWM value on digital pin D4
  pwm_width_5 = 1500;     //PWM value on digital pin D5
  pwm_width_6 = 1000;     //PWM value on digital pin D6
  pwm_width_7 = 1000;     //PWM value on digital pin D7
  
  
  //Now we write the PWM signal using the servo function
  PWM2.writeMicroseconds(pwm_width_2);
  PWM3.writeMicroseconds(pwm_width_3);
  PWM4.writeMicroseconds(pwm_width_4);
  PWM5.writeMicroseconds(pwm_width_5);
  PWM6.writeMicroseconds(pwm_width_6);
  PWM7.writeMicroseconds(pwm_width_7);     
}//Loop end
/**************************************************/
