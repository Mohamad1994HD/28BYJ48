// #include "Arduino.h"
// #include <28BYJ48.h>
//
// NonBlockingMotor motor(6, 7, 8, 9);
//
//
// long f1(long x){
//    return x*motor.steps_per_rev/360;
// }
//
// void on_reached(long steps){
//   Serial.println(steps);
// }
//
// void setup(){
//   Serial.begin(9600);
//
//   motor.init();
//   motor.set_time_between_pulses(2000); // recommended
//   // set the function that will convert degrees to
//   // steps (OPTIONAL)
//   // you can just provide steps
//   motor.set_conversion_function(f1);
//   motor.set_on_destination_reached(on_reached);
//   int angle = 180 ;
//   motor.set_destination(angle); // destination angle
//   // Set the direction CW: clockwise CCW:anti-clockwise
//   motor.status = CW;
// }
//
//
//
//
// void loop(){
//   motor.update(); // commit rotation
// }
