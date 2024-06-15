#include "Shell.hpp"
#include "Motors.hpp"


int cmd_home(char **args) {
  toZero(); 
	return 0;
}


int cmd_zero(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL || args[2] == NULL || args[3] == NULL || args[4] == NULL) {
		// Сообщение об ошибке
    Serial.println("Expected argument (1, 2, 3, 4) to \"zero\"");
	} else {
    //String str = args[1];
    zeroServo1 = dec_str_to_number(args[1]);
    zeroServo2 = dec_str_to_number(args[2]);
    zeroServo3 = dec_str_to_number(args[3]);
    zeroServo4 = dec_str_to_number(args[4]);    
    Serial.println("New zero point: ");
    Serial.print(zeroServo1);
    Serial.print(", ");
    Serial.print(zeroServo2);
    Serial.print(", ");
    Serial.print(zeroServo3);
    Serial.print(", ");
    Serial.println(zeroServo4); 
	}
	return 0;
}


int cmd_wait(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial.println("Expected argument (1000) to \"wait\"");
	} else {   
    Serial.print("Waiting: ");
    Serial.print(args[1]);
    delay(dec_str_to_number(args[1]));
    Serial.println(" DONE");
	}
	return 0;
}

/*
// Команда включения светодиода
int cmd_led(char **args) {
	// Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial.println("Expected argument (on/off) to \"led\"");
	} else {
    String str = args[1];    
    if (str == "on") {
      is_LED_TEST = true;  				
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Led ON"); 
	  }
    if (str == "off") {
      is_LED_TEST = false;  				
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Led OFF");      
	  }
	}
	return 1;
}
*/

int cmd_servo1(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (num) to \"servo1\"");
	} else {
    int servo_pos = dec_str_to_number(args[1]);
    if(servo_pos < 75) servo_pos = 75;
    if(servo_pos > 140) servo_pos = 140;
    char msg[20];
    sprintf(msg, "Servo1: %d", servo_pos); 
    Serial.print(msg);
    run1(servo_pos, 1);
	}
	return 0;
}


int cmd_servo2(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (num) to \"servo2\"");
	} else {
    int servo_pos = dec_str_to_number(args[1]);
    if(servo_pos < 0) servo_pos = 0;
    if(servo_pos > 170) servo_pos = 170;
    char msg[20];
    sprintf(msg, "Servo2: %d", servo_pos); 
    Serial.print(msg);
    run2(servo_pos, 1);
	}
	return 0;
}


int cmd_servo3(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (num) to \"servo3\"");
	} else {
    int servo_pos = dec_str_to_number(args[1]);
    if(servo_pos < 0) servo_pos = 0;
    if(servo_pos > 170) servo_pos = 170;
    char msg[20];
    sprintf(msg, "Servo3: %d", servo_pos); 
    Serial.print(msg);
    run3(servo_pos, 1);
	}
	return 0;
}


int cmd_servo4(char **args) {
  // Проверяем, есть ли второй аргумент
	if (args[1] == NULL) {
		// Сообщение об ошибке
    Serial2.println("Expected argument (num) to \"servo4\"");
	} else {
    int servo_pos = dec_str_to_number(args[1]);
    if(servo_pos < 5) servo_pos = 5;
    if(servo_pos > 130) servo_pos = 130;
    char msg[20];
    sprintf(msg, "Servo4: %d", servo_pos); 
    Serial.print(msg);
    run4(servo_pos, 1);
	}
	return 0;
}


// Команда help
int cmd_help(char **args) {
	int i;
  Serial.println("Arm Robot v.1.0 (c) 2024 Gor.Com");
	Serial.println("The following command are built in:");
   
	// Выводим массив имен встроенных команд
	for (i = 0; i < num_builtins(); i++) {
		Serial.println(cmd_str[i]);    
	}
	return 1;
}


// Команда вывода на экран программы
int cmd_list(char **args) {
    // Служебный вывод программы
    for(int i = 0; i < MAX_LINE; i++){
      if(program[i*20] != 0x0D){ 
        Serial.print(i+1);
        Serial.print(" ");       
      }

      for(int j = 0; j < MAX_LENGTH; j++){
        if(program[i*20 + j] != 0x0D){        
          Serial.print(program[i*20 + j]);
        }
      }
      if(program[i*20] != 0x0D){ 
        Serial.println("");
      }        
    }
	return 0;
}


// Команда выполнения программы
int cmd_run(char **args) {
    for(int i = 0; i < MAX_LINE; i++){
      line[0] = 0;
      for(int j = 0; j < MAX_LENGTH; j++){
        if(program[i*20 + j] != 0x0D){
          line[j] = program[i*20 + j];       // Копируем строку из программы для выполнения      
        }
      }
      // execute str
      if(line[0]){
        args = split_line(line);  // Извлекает аргументы
        execute(args, line);      // Исполняем команду  
      }    
        
    }
	return 0;
}


// Команда PRINT
int cmd_print(char **args) {
  if(args[1] == NULL){
    return 0;
  }
  if(args[1][0] == 34){
    for(int i = 1; i < 20; i++){
      if(args[1][i] == 34 || args[1][i] == 0x0D || args[1][i] == 0x20 || args[1][i] == 0){
        if(args[1][i] == 34 && args[1][i+1] != 0x3B){    
          Serial.println(""); 
        }
        break;
      } 
      Serial.print(args[1][i]);  
    }
    
    return 0;
  }

  Serial.println(process_expr());
	return 0;
}


// Команда очистки программы
int cmd_new(char **args) {
  running = 0;
  start_bas();
	return 0;
}


// Команда ввода переменной
int cmd_input(char **args) {
  Serial.print("?");
  while(Serial.available()==0);  //Ожидаем ввода данных
  // Вычисляем адрес по букве
  vars[args[1][0] - 97] = process_expr();//Serial.read();

  // Служебный вывод
  for(int i = 0; i < 26; i++){
    Serial.print(vars[i]);   
  } 
  Serial.println("");  
  
	return 0;
}