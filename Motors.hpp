#ifndef MOTORS_HPP
#define MOTORS_HPP

#define SERVO_1_LIMIT_TOP 140
#define SERVO_1_LIMIT_BOTTOM 75
#define SERVO_2_LIMIT_TOP 170
#define SERVO_2_LIMIT_BOTTOM 0
#define SERVO_3_LIMIT_TOP 170
#define SERVO_3_LIMIT_BOTTOM 0
#define SERVO_4_LIMIT_TOP 130
#define SERVO_4_LIMIT_BOTTOM 5

void toZero();
void run1(int x, int step);
void run2(int x, int step);
void run3(int x, int step);
void run4(int x, int step);
void TornStepper(int x);

int zeroServo1 = 75;
int zeroServo2 = 50;
int zeroServo3 = 50;
int zeroServo4 = 50;

#endif // MOTORS_HPP