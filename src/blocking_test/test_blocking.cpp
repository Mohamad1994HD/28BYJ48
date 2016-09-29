#include "Arduino.h"
#include <28BYJ48.h>

BlockingMotor motor(6, 7, 8, 9);


long f1(long x){
   return x*motor.steps_per_rev/360;
}

void setup(){
  Serial.begin(9600);

  motor.init();
  motor.set_time_between_pulses(2000); // recommended
  // set conversion function to convert
  // given argument (degrees) into steps
  motor.set_conversion_function(f1);

}




void loop(){
  motor.status = CW;
  motor.rotate_by(90);
  delay(1000);
  //
  motor.status = CCW;
  motor.rotate_by(90);
  delay(1000);
  //
  motor.status = CW;
  motor.rotate_by(180);
  delay(1000);
  //
  motor.status =CCW;
  motor.rotate_by(180);
  delay(1000);
  //

}
