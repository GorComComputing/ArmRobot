# Промышленный робот манипулятор на ESP32

![img/ArmRobot.jpg](img/ArmRobot.jpg)


В основе промышленного робота лежит микроконтроллер ESP32.
Робот подключается по Wi-Fi к локальной сети.  

Звенья робота напечатаны на 3D-принтере.  
Робот состоит из:
- 4-х сервомоторов SG90;
- шагового двигателя 28BYJ-48 (для поворота платформы);
- инфракрасного датчика пульта управления.


Wi-Fi модуль может работать в режимах:
- точки доступа (AP);
- станции (STA).

В режиме точки доступа (AP) устройство имеет следующий адрес:
- ip-адрес: 192.168.1.1
- шлюз: 192.168.1.1
- маска сети: 255.255.255.0

Web-сервер работает на порту 80.

```
// SSID и пароль хранятся во внешнем файле secret.ino в переменных:
// for AP 
const char* ssid_AP = "********";  
const char* password_AP = "********";
// for STA
const char* ssid = "********";  
const char* password = "********";
```

```
# Для автоматческого добавление на GitHub
$ python make.py git "Комментарий"

# Токен GitHub хранится во внешнем файле secret.py в переменной:
# tokenGit = "********"
```

- Написан на языке C++ Arduino

Статус проекта: Разрабатывается.


Copyright (c) 2024 Evgeny Goryachev  
Gor.Com 