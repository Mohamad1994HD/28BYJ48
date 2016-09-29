#include "Arduino.h"
#include <28BYJ48.h>

BlockingMotor motor(6, 7, 8, 9);


long calc(long x){
   return x*motor.steps_per_rev/360;
}

void setup(){
  Serial.begin(9600);
  motor.init();
  motor.set_time_between_pulses(2000); // recommended
  auto f1 = [] (long x) ->long{
    return x*motor.steps_per_rev/360;
  };
  auto f2 = [] (long x) -> long{
    return map(x, 0, 360, 0, motor.steps_per_rev);
  };

  motor.set_conversion_function(f2);
}


void loop(){

  motor.set_rotation_status(CW);
  motor.rotate_by(360);
  delay(1000);
  motor.set_rotation_status(CCW);
  motor.rotate_by(180);
  delay(1000);
  // motor.set_rotation_status(CW);
  // motor.rotate_by(360, to_steps);
//  delay(2000);
}
