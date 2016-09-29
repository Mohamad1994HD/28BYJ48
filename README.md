# 28BYJ48
:smile: Library to interface 28BYJ48 stepper motor &amp; make it easier to control :smile:

## This library shall provide easy way to interact with 28BYJ48 Stepper motor

### It provides the user with two modes or actually two types of controlling the motor

#### 1. Blocking Mode(sync): 
        In this mode the motor will lock the microcontroller to perform the whole 
        process of rotating the motor to a specific angle before going to the
        next command in the program.
        
####Example:
```c++
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

```
 in the above example the motor will perform the whole angle rotation before going to the next step
 
#### 2. Non-Blocking Mode (async): 
        In this mode the motor will NOT lock the microcontroller to perform the whole 
        process of rotating the motor. However, it will increment one step at a time
        depending on the timing implemented in the loop function, so arduino can do
        other things while motor is rotating 
        
####Example:

```c++
#include "Arduino.h"
#include <28BYJ48.h>

NonBlockingMotor motor(6, 7, 8, 9);


long f1(long x){
   return x*motor.steps_per_rev/360;
}

void on_reached(long steps){
  Serial.println(steps);
}

void setup(){
  Serial.begin(9600);

  motor.init();
  motor.set_time_between_pulses(2000); // recommended
  // set the function that will convert degrees to
  // steps (OPTIONAL)
  // you can just provide steps
  motor.set_conversion_function(f1);
  motor.set_on_destination_reached(on_reached);
  int angle = 180 ;
  motor.set_destination(angle); // destination angle
  // Set the direction CW: clockwise CCW:anti-clockwise
  motor.status = CW;
}




void loop(){
  motor.update(); // commit rotation
}
```

the update function will take care of rotating the motor one step at a time.

###Usage:
```c++
//Constructors: 
// Blocking
BlockingMotor motor(6, 7, 8, 9);
// Non-blocking
NonBlockingMotor motor(6, 7, 8, 9);

//functions
// Functions for Both Blocking/Non-Blocking modes

void init(); // initialize the motor object
void set_time_between_pulses; // set time delays between each pulse (Microseconds): 2000 is recommended
void set_conversion_function; // Optional: if you dont want to pass steps (512, 1024) and you want to use angles
                              // so you can provide your own conversion function between angles & steps to implement your own 
                              // accuracy conversion

// Functions specific for Blocking mode
void rotate_by(int); // rotate to a given step or angle ( if you have provided the conversion function so it will rotate to the angle)
                     // otherwise to the step

// Functions specific for Non Blockign mode
void set_on_destination_reached(void (*f)(long)); // a callback function setter so whenever the motor reach the destination 
                                                  // the callback will fire up to make a descision
void set_destination(long); // set destination astep (angle: if conversion function is provided in the initializing process)
void update(); // updating the current status of the motor
```


 
