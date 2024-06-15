#include "Motors.hpp"


// to Zero 
void toZero(){
  Serial.print("Zero position ");
  Serial.print(zeroServo1);
  Serial.print(", ");
  Serial.print(zeroServo2);
  Serial.print(", ");
  Serial.print(zeroServo3);
  Serial.print(", ");
  Serial.println(zeroServo4);

  run1(zeroServo1, 5);
  run2(zeroServo2, 5);
  run3(zeroServo3, 5);
  run4(zeroServo4, 5);
}


// Run 1 motor
void run1(int x, int step){
  if(x > SERVO_1_LIMIT_TOP) x = SERVO_1_LIMIT_TOP;
  if(x < SERVO_1_LIMIT_BOTTOM) x = SERVO_1_LIMIT_BOTTOM;
  if(x > position_1){
    while(position_1 != x){
      position_1 += step;
      if(position_1 > x) position_1 = x;
      servo_1.write(position_1);
      /*ESP32_ISR_Servos.setPosition(servoIndex1, position_1);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_1);
      delay(100);
      esp_task_wdt_reset();
    }
  } 
  if(x < position_1){
    while(position_1 != x){
      position_1 -= step;
      if(position_1 < x) position_1 = x;
      servo_1.write(position_1);
      /*ESP32_ISR_Servos.setPosition(servoIndex1, position_1);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_1);
      delay(100);
      esp_task_wdt_reset();
    }
  }
}


// Run 2 motor
void run2(int x, int step){
  if(x > SERVO_2_LIMIT_TOP) x = SERVO_2_LIMIT_TOP;
  if(x < SERVO_2_LIMIT_BOTTOM) x = SERVO_2_LIMIT_BOTTOM;
  if(x > position_2){
    while(position_2 != x){
      position_2 += step;
      if(position_2 > x) position_2 = x;
      servo_2.write(position_2);
      /*ESP32_ISR_Servos.setPosition(servoIndex2, position_2);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_2);
      delay(100);
      esp_task_wdt_reset();
    }
  } 
  if(x < position_2){
    while(position_2 != x){
      position_2 -= step;
      if(position_2 < x) position_2 = x;
      servo_2.write(position_2);
      /*ESP32_ISR_Servos.setPosition(servoIndex2, position_2);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_2);
      delay(100);
      esp_task_wdt_reset();
    }
  }
}


// Run 3 motor
void run3(int x, int step){
  if(x > SERVO_3_LIMIT_TOP) x = SERVO_3_LIMIT_TOP;
  if(x < SERVO_3_LIMIT_BOTTOM) x = SERVO_3_LIMIT_BOTTOM;
  if(x > position_3){
    while(position_3 != x){
      position_3 += step;
      if(position_3 > x) position_3 = x;
      servo_3.write(position_3);
      /*ESP32_ISR_Servos.setPosition(servoIndex3, position_3);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_3);
      delay(100);
      esp_task_wdt_reset();
    }
  } 
  if(x < position_3){
    while(position_3 != x){
      position_3 -= step;
      if(position_3 < x) position_3 = x;
      servo_3.write(position_3);
      /*ESP32_ISR_Servos.setPosition(servoIndex3, position_3);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_3);
      delay(100);
      esp_task_wdt_reset();
    }
  }
}


// Run 4 motor
void run4(int x, int step){
  if(x > SERVO_4_LIMIT_TOP) x = SERVO_4_LIMIT_TOP;
  if(x < SERVO_4_LIMIT_BOTTOM) x = SERVO_4_LIMIT_BOTTOM;
  if(x > position_4){
    while(position_4 != x){
      position_4 += step;
      if(position_4 > x) position_4 = x;
      servo_4.write(position_4);
      /*ESP32_ISR_Servos.setPosition(servoIndex4, position_4);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_4);
      delay(100);
      esp_task_wdt_reset();
    }
  } 
  if(x < position_4){
    while(position_4 != x){
      position_4 -= step;
      if(position_4 < x) position_4 = x;
      servo_4.write(position_4);
      /*ESP32_ISR_Servos.setPosition(servoIndex4, position_4);
			delay(30);  // waits 30ms for the servo to reach the position*/
      Serial.println(position_4);
      delay(100);
      esp_task_wdt_reset();
    }
  }
}


// Torn Stepper motor
// Left   +x
// Right  -x
void TornStepper(int x){
  myStepper.step(x);
  Serial.print("Torn ");
  Serial.println(x);
  digitalWrite(STEPPER_IN1, LOW);
  digitalWrite(STEPPER_IN2, LOW);
  digitalWrite(STEPPER_IN3, LOW);
  digitalWrite(STEPPER_IN4, LOW);
}
