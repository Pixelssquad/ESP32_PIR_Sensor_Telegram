# ESP32_PIR_Sensor_Telegram
ENG <br> 
Pir sensor with telegram messages support<br> 
You can verify that the bot is online and working by writing anything in the chat, the bot responds by replicating what you write<br> 
File Test01_HCSR505.ino test the sensor (no bot telegram)<br> 
File PIR_Alarm_Telegram.ino Main program<br> 
<br> <br> 

ITA<br> 
ESP32 con sensore PIR che avvisa via telegram quando rileva movimento<br> 
Puoi verificare che il bot sia online e funzionante scrivendo qualsiasi cosa in chat, il bot risponde replicando quello che scrivi<br> 
File Test01_HCSR505.ino test funzionamento del sensore (no bot telegram)<br> 
File PIR_Alarm_Telegram.ino programma principale<br> 
<br> <br> 

![IMG20240922124649](https://github.com/user-attachments/assets/666500fe-64ab-4f56-8b60-c0e9b6c537aa)
![1](https://github.com/user-attachments/assets/88d3b67b-f001-4526-ac62-2ba6793924bc)
![Pir_sensor_telegram_bb1](https://github.com/user-attachments/assets/24f03255-75aa-403d-a894-70fb4d896c73)

Added a relay connected to pin 2, is the shared pin with the onboard led
Aggiunto relé al pin 2, è quello condiviso con il led sulla scheda (nel mio caso)
![IMG20240924131833](https://github.com/user-attachments/assets/0e6dbebc-41f4-4d0d-86ba-488589503b8e)

Ideas From:
https://randomnerdtutorials.com/telegram-esp8266-nodemcu-motion-detection-arduino/
https://gist.github.com/nafiesl/4ad622f344cd1dc3bb1ecbe468ff9f8a
https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
