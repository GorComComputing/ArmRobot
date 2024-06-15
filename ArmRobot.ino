// Arm Robot ESP32

#include "timer.hpp"
#include "Motors.hpp"
#include "WiFiAP.hpp"
#include "SD.hpp"

// For watchdog reset
#include <esp_task_wdt.h>

// SD Card
//#include <Arduino.h>
//#include "FS.h"
//#include "SD.h"
//#include "SPI.h"

// Wi-Fi ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
// for AP
extern const char* ssid_AP;  
extern const char* password_AP;  
IPAddress local_ip_AP(192,168,1,1);      // Настройки IP адреса
IPAddress gateway_AP(192,168,1,1);
IPAddress subnet_AP(255,255,255,0);

// for SDA
extern const char* ssid;  
extern const char* password;
byte tries = 10;                         // Попыткок подключения к точке доступа 
bool is_CONNECTED = false;

AsyncWebServer server(80);

const char* PARAM_CMD = "cmd";
String postCmd = "";

// IR remote control
#include <IRremote.hpp>
#define RECV_PIN 25
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

// LED
//#define LED_TEST 2
//bool is_LED_TEST = false;

// ISR Servo
/*#define USE_ESP32_TIMER_NO 3
#define MIN_MICROS      800  //544
#define MAX_MICROS      2450
#include "ESP32_ISR_Servo.h"
int servoIndex1  = -1;
int servoIndex2  = -1;
int servoIndex3  = -1;
int servoIndex4  = -1;*/

// Servo
#include <ESP32Servo.h>
#define SERVO_1 32
#define SERVO_2 33
#define SERVO_3 26
#define SERVO_4 27
Servo servo_1;
Servo servo_2;
Servo servo_3;
Servo servo_4;
int position_1 = 0;
int position_2 = 0;
int position_3 = 0;
int position_4 = 0;
int speed_1 = 0;
int speed_2 = 0;
int speed_3 = 0;
int speed_4 = 0;

// Stepper
#include <Stepper.h>
const int stepsPerRevolution = 2048;
#define STEPPER_IN1 0
#define STEPPER_IN2 4
#define STEPPER_IN3 16
#define STEPPER_IN4 17
Stepper myStepper(stepsPerRevolution, STEPPER_IN1, STEPPER_IN3, STEPPER_IN2, STEPPER_IN4);
int zeroStepper = 0;

// Shell
#include "Shell.hpp"
int running = 0;          // Указатель на строчку, которая сейчас выполняется
char *line;               // Указатель на строку ввода
char **args;              // Указатель на указатель на аргументы
int vars[26];             // Переменные (a-z)
char program[MAX_SIZE];   // Указатель на буфер исходника программы


void setup() {
  // LED
  //pinMode(LED_BUILTIN, OUTPUT);

  // Servo 1
  pinMode(SERVO_1, OUTPUT);             
  servo_1.attach(SERVO_1);             
  position_1 = 75;
  servo_1.write(position_1);
  delay(1000);

  // Servo 2
  pinMode(SERVO_2, OUTPUT);               
  servo_2.attach(SERVO_2);              
  position_2 = 50;
  servo_2.write(position_2);
  delay(1000);

  // Servo 3
  pinMode(SERVO_3, OUTPUT);               
  servo_3.attach(SERVO_3);              
  position_3 = 50;
  servo_3.write(position_3);
  delay(1000);

  // Servo 4
  pinMode(SERVO_4, OUTPUT);               
  servo_4.attach(SERVO_4);              
  position_4 = 50;
  servo_4.write(position_4);
  delay(1000);

  // Stepper
  myStepper.setSpeed(5);    // set the speed at 5 rpm

  // Serial
  Serial.begin(9600);
  while (!Serial);          // Ждем пока Serial будет готов
  Serial.println("Arm Robot v.1.0 (c) 2024 Gor.Com");

  // Timer for motors
/*  Motor_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(Motor_timer, &onTimer, true);
  timerAlarmWrite(Motor_timer, 1000000, true);
  timerAlarmEnable(Motor_timer);*/

  //ISR Servo
/*	ESP32_ISR_Servos.useTimer(USE_ESP32_TIMER_NO);
  servoIndex1 = ESP32_ISR_Servos.setupServo(SERVO_1, MIN_MICROS, MAX_MICROS);
	servoIndex2 = ESP32_ISR_Servos.setupServo(SERVO_2, MIN_MICROS, MAX_MICROS);
  servoIndex3 = ESP32_ISR_Servos.setupServo(SERVO_3, MIN_MICROS, MAX_MICROS);
	servoIndex4 = ESP32_ISR_Servos.setupServo(SERVO_4, MIN_MICROS, MAX_MICROS);
  if (servoIndex1 != -1)
		Serial.println(F("Setup Servo1 OK"));
	else
		Serial.println(F("Setup Servo1 failed"));
	if (servoIndex2 != -1)
		Serial.println(F("Setup Servo2 OK"));
	else
		Serial.println(F("Setup Servo2 failed"));
  if (servoIndex3 != -1)
		Serial.println(F("Setup Servo3 OK"));
	else
		Serial.println(F("Setup Servo3 failed"));
	if (servoIndex4 != -1)
		Serial.println(F("Setup Servo4 OK"));
	else
		Serial.println(F("Setup Servo4 failed"));
  toZero();*/

  // IR remote control
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);    // IR Control Enable

  // SD Card
  //initSDCard();

  //  Wi-Fi AP and STA
  WiFi.mode(WIFI_AP_STA);

  //  Wi-Fi AP
  WiFi.softAP(ssid_AP, password_AP);
  WiFi.softAPConfig(local_ip_AP, gateway_AP, subnet_AP);
  delay(100);

  // Configures static IP address
//  if (!WiFi.config(local_ip, gateway, subnet, primaryDNS, secondaryDNS)) {
//    Serial.println("STA Failed to configure");
//  }
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (--tries && WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    is_CONNECTED = false;
    Serial.println("Non Connecting to WiFi..");
  } else {
    is_CONNECTED = true;
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected OK");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

  /*server.on("/hello_server", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello AsyncWebServer!");
  });*/

  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", index_html, processor);
  });*/

  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {
    String respond = "";
    if(request->hasParam(PARAM_CMD, true)) {
      postCmd = request->getParam(PARAM_CMD, true)->value();
      Serial.println(postCmd);
      args = split_line((char*)postCmd.c_str());         // Извлекает аргументы
      execute(args, (char*)postCmd.c_str());             // Исполняем команду

      request->send(200, "text/plain", respond);
    }

    request->send(200);
  });

  server.onNotFound(notFound);

  /*server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/www/index.html", "text/html");
  });*/

  //server.serveStatic("/", SD, "/www/");

  server.begin();
  Serial.println("Web server started OK");
  }

  // Запускаем интерпретатор
  start_bas();
  Serial.print(">");        // Печатает приглашение ввода команды
}


void loop() {
    if (IrReceiver.decode()) {
    // 0xBB44FF00 - Left
    // 0xBF40FF00 - OK
    // 0xBC43FF00 - Right
    // 0xE916FF00 - 1
    // 0xE619FF00 - 2
    // 0xF20DFF00 - 3
    // 0xF30CFF00 - 4
    // 0xE718FF00 - 5
    // 0xA15EFF00 - 6
    // 0xF708FF00 - 7
    // 0xE31CFF00 - 8
    // 0xA55AFF00 - 9
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
    if (IrReceiver.decodedIRData.decodedRawData == 0){
      IrReceiver.decodedIRData.decodedRawData = key_value;
    }
    
    switch(IrReceiver.decodedIRData.decodedRawData){
      case 0xBB44FF00:
        //do_beep(A_BUZZER);
        TornStepper(30);
        break;

      case 0xBF40FF00:
        Serial.println("OK");
        //do_beep(A_BUZZER);
        program1();
        Serial.println("Program 1 DONE");
        program2();
        Serial.println("Program 2 DONE");
        program3();
        Serial.println("Program 3 DONE");
        break;

      case 0xBC43FF00:
        //do_beep(A_BUZZER);
        TornStepper(-30);
        break;

      case 0xE916FF00:
        Serial.println("1");
        //do_beep(A_BUZZER);
        run1(position_1 + 5, 1);
        break;

      case 0xE619FF00:
        Serial.println("2");
        //do_beep(A_BUZZER);
        run2(position_2 + 5, 1);
        break;

      case 0xF20DFF00:
        Serial.println("3");
        //do_beep(A_BUZZER);
        run3(position_3 + 5, 1);
        break;

      case 0xF30CFF00:
        Serial.println("4");
        //do_beep(A_BUZZER);
        run1(position_1 - 5, 1);
        break;

      case 0xE718FF00:
        Serial.println("5");
        //do_beep(A_BUZZER);
        run2(position_2 - 5, 1);
        break;

      case 0xA15EFF00:
        Serial.println("6");
        //do_beep(A_BUZZER);
        run3(position_3 - 5, 1);
        break;

      case 0xF708FF00:
        Serial.println("7");
        //do_beep(A_BUZZER);
        run4(position_4 + 5, 1);
        break;

      case 0xE31CFF00:
        Serial.println("8");
        //do_beep(A_BUZZER);
        run4(position_4 - 5, 1);
        break;

      case 0xA55AFF00:          // Zero position
        Serial.println("9");
        //do_beep(A_BUZZER);
        toZero();
        break;
    }
    key_value = IrReceiver.decodedIRData.decodedRawData;
    //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
    //IrReceiver.printIRSendUsage(&Serial); // Print the statement required to send this data
    IrReceiver.resume(); // Enable receiving of the next value
    delay(150);
  }

  // Shell
  shell();
}






