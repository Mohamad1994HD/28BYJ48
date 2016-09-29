#include "28BYJ48.h"

BaseMotor::BaseMotor(uint8_t p1, uint8_t p2,
             uint8_t p3, uint8_t p4):pin1(p1),pin2(p2),pin3(p3),pin4(p4){}

void BaseMotor::init(){
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  status = STOP;
}

void BaseMotor::set_time_between_pulses(int t){
  if (t < 0){
    t*=-1;
  }
  time_between_pulses = t;
}


void BaseMotor::set_rotation_status(rotation_status st){
    status = st;
}

void BaseMotor::out(int digit){
  digitalWrite(pin1, bitRead(lookup[digit], 0));
  digitalWrite(pin2, bitRead(lookup[digit], 1));
  digitalWrite(pin3, bitRead(lookup[digit], 2));
  digitalWrite(pin4, bitRead(lookup[digit], 3));
}


void BaseMotor::set_conversion_function(calc_function cf){
  conv_function = cf;
}
/////////////////////////////////////////////////
// BLOCKING MOTOR MODE
////////////////////////////////////////////////
BlockingMotor::BlockingMotor(uint8_t p1, uint8_t p2,
                             uint8_t p3,uint8_t p4):
                             BaseMotor(p1,p2,p3,p4){
                             }


void BlockingMotor::rotate_by(long val){
  int steps;
  // if conversion functioin provieded convert accordingly
  // else just assign the number of steps
  conv_function != NULL ? steps=conv_function(val): steps=val;
  // rotate
  step(steps);
}
// //blocking
void BlockingMotor::step(int num_of_steps){
  int steps = 0;

  if (status == STOP){
    return;
  }
  // check provided direction
  if(status == CW){
    while(true){
      for (int i=7; i>=0; i--){
        out(i);
        delayMicroseconds(time_between_pulses);
      }
      steps++;
      if (steps >= num_of_steps){
        status = STOP;
        break;
      }
    }
  }else{
    while(true){
      for (int i=0; i<8; i++){
        out(i);
        delayMicroseconds(time_between_pulses);
        }
      steps++;
      if (steps >= num_of_steps){
        status = STOP;
        break;
        }
    }
  }
}
//
// void Motor::rotate(int degrees){
//   if (status == STOP){
//     return;
//   }
//   // convert degrees to steps
//   int num_of_steps=map(degrees, 0, 360, 0, 512);
//   // check provided direction
//   if(status == CW){
//     while(true){
//       for (int i=7; i>=0; i--){
//         out(i);
//         delayMicroseconds(time_between_pulses);
//       }
//       steps++;
//       if (steps >= num_of_steps){
//         steps=0;
//         status = STOP;
//         break;
//       }
//     }
//   }else{
//     while(true){
//     for (int i=0; i<8; i++){
//       out(i);
//       delayMicroseconds(time_between_pulses);
//       }
//     steps++;
//     if (steps >= num_of_steps){
//       steps=0;
//       status = STOP;
//       break;
//       }
//     }
//   }
// }
//
// //Non-blocking
// void Motor::rotate_by(int degrees){
//   if(!goal_set){
//     goal_set = true;
//     to_angle = degrees;
//     to_steps = map(to_angle, 0, 360, 0, 512);
//   }
// }
//
// void Motor::rotate_by_steps(int steps){
//     if(!goal_set){
//       goal_set = true;
//       to_steps = steps;
//     }
// }
//
// void Motor::commit(){
//   if(!goal_set){
//     return ;
//   }
//   if(status == STOP){
//     return ;
//   }
//
//   if (micros() - t >= time_between_pulses){
//     if (status == CW){
//       for(int i=7; i>=0; i--){
//         out(i);
//       }
//     }else{
//       for(int i=0; i<8; i++){
//         out(i);
//       }
//     }
//     steps++;
//     if(steps == to_steps){
//       status = STOP;
//       steps = 0;
//       return;
//     }
//   }
// }
//
//
