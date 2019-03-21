/*ESC calibration sketch; author: ELECTRONOOBS */
#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 1000
#define MOTOR_PIN_F_L 3
#define MOTOR_PIN_F_R 10
#define MOTOR_PIN_B_R 9
#define MOTOR_PIN_B_L 11
int DELAY = 1000;

Servo motor_f_l;
Servo motor_f_r;
Servo motor_b_r;
Servo motor_b_l;

void setup() {
  Serial.begin(9600);
  Serial.println("Don't forget to subscribe!");
  Serial.println("ELECTRONOOBS ESC calibration...");
  Serial.println(" ");
  delay(1500);
  Serial.println("Program begin...");
  delay(1000);
  Serial.println("This program will start the ESC.");

  motor_f_l.attach(MOTOR_PIN_F_L);
  motor_f_r.attach(MOTOR_PIN_F_R);
  motor_b_r.attach(MOTOR_PIN_B_R);
  motor_b_l.attach(MOTOR_PIN_B_L);

  Serial.print("Now writing maximum output: (");Serial.print(MAX_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  motor_f_l.writeMicroseconds(MAX_SIGNAL);
  motor_f_r.writeMicroseconds(MAX_SIGNAL);
  motor_b_r.writeMicroseconds(MAX_SIGNAL);
  motor_b_l.writeMicroseconds(MAX_SIGNAL);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("\n");
  Serial.println("\n");
  Serial.print("Sending minimum output: (");Serial.print(MIN_SIGNAL);Serial.print(" us in this case)");Serial.print("\n");
  motor_f_l.writeMicroseconds(MIN_SIGNAL);
  motor_f_r.writeMicroseconds(MIN_SIGNAL);
  motor_b_r.writeMicroseconds(MIN_SIGNAL);
  motor_b_l.writeMicroseconds(MIN_SIGNAL);
  Serial.println("The ESC is calibrated");
  Serial.println("----");
  Serial.println("Now, type a values between 1000 and 2000 and press enter");
  Serial.println("and the motor will start rotating.");
  Serial.println("Send 1000 to stop the motor and 2000 for full throttle");

}

void loop() {
   
  if (Serial.available() > 0)
  {
    int DELAY = Serial.parseInt();
    if (DELAY > 999)
    {
      
      motor_f_l.writeMicroseconds(DELAY);
      motor_f_r.writeMicroseconds(DELAY);
      motor_b_r.writeMicroseconds(DELAY);
      motor_b_l.writeMicroseconds(DELAY);
      float SPEED = (DELAY-1000)/10;
      Serial.print("\n");
      Serial.println("Motor speed:"); Serial.print("  "); Serial.print(SPEED); Serial.print("%"); 
    }     
  }
}
