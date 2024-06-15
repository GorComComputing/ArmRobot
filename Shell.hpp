#ifndef SHELL_HPP
#define SHELL_HPP

#define RL_BUFSIZE 20 // Размер буфера ввода
#define TOK_BUFSIZE 64  // Размер буфера с указателями на токены
#define TOK_DELIM " \t\r\n\a" // Разделители для токенизации

#define MAX_LINE 10  // Максимальное количество строчек в программе
#define MAX_LENGTH 20 // Максимальная длина строчки программы
#define MAX_SIZE MAX_LINE * MAX_LENGTH

//int cmd_led(char **args);
int cmd_servo1(char **args);
int cmd_servo2(char **args);
int cmd_servo3(char **args);
int cmd_servo4(char **args);
int cmd_help(char **args);
int cmd_home(char **args);
int cmd_zero(char **args);
int cmd_wait(char **args);
int cmd_list(char **args);
int cmd_print(char **args);
int cmd_new(char **args);
int cmd_input(char **args);
int cmd_run(char **args);

void shell();

// Массив имен встроенных команд
char *cmd_str[] = {
	//"led",           // Включение светодиода
  "servo1",        // Вращение серво мотора
  "servo2",        // Вращение серво мотора
  "servo3",        // Вращение серво мотора
  "servo4",        // Вращение серво мотора
	"help",			     // Справка
	"zero", 		     // Задать позицию нуля
  "home", 		     // Перейти в позицию нуля
  "wait", 		     // Ожидание
	"list",          // Вывод на экран программы
	"print",         // PRINT
	"new",           // Очищает программу
	"input",         // Ввести переменную  
	"run"            // Запуск выполнения программы
};

// Массив указателей на функции встроенных команд
int (*cmd_func[]) (char **) = {
	//cmd_led,
  cmd_servo1,
  cmd_servo2,
  cmd_servo3,
  cmd_servo4,
	cmd_help,
	cmd_zero,
  cmd_home,
  cmd_wait,
	cmd_list,
	cmd_print,
	cmd_new,
	cmd_input,
	cmd_run    
};

#endif // SHELL_HPP