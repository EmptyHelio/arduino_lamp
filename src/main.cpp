#include <Arduino.h>

//обьявляем светик и кнопку
#define led 11
#define pin_button 12

//Хранение значения кнопки
int buttonState = 0;

//Переменная для таймера
unsigned long last_time;

//переменные для флагов
int value = 0;
int mode = 0;
int n = 0;

void setup() {
  
  pinMode(led, OUTPUT);
  /*
  Инициализируем led(11 пин) как выход
  Кнопку как вход со встроенным подтягивающим резистором
  */
 
  pinMode(pin_button, INPUT_PULLUP);
  
}

void loop() {
//считываем данные с кнопки
buttonState = digitalRead(pin_button);
    /*
    Если нажата кнопка нажата, флаг состояния(value) меняется на 1
    Для переключения режимов, используем переменную regim
    */
    if(buttonState == LOW && value == 0)      
    {                                              
      mode++;
      value = 1;
      
      if(mode > 3) //Если regim больше 3, то сбрасываем все на 0, что бы зациклить
        {
          mode = 0;
        }
    }
    //сброс value
     if(buttonState == HIGH && value == 1)
     {
       value = 0;
     }  

/*-------Выполнение режимов----------*/
/*-------Первый режим--------*/
    if(mode == 1 && n == 0)
    {
      //Запуск таймера
      //Медленное разгорание led
      last_time = millis();
      for(int i = 0; i<=255; i++)
      {
        analogWrite(led, i);
        delay(5);
      }
      //Что бы не было мигание на первом режиме, меняется переменная n
      n++;
    }
    /*
      Проверка. Прошло ли 30 мин после 1 режима. Если прошло, то выключаем led
    
    */
      if((millis() - last_time >(unsigned long) 30 * 60 * 1000) && mode == 1)
      {
        for(int i = 255; i >= 0; i--)
        {
         analogWrite(led, i);
         delay(30);
        }
       mode = 0;
       n = 0;
      }


/*-------Второй режим--------*/
      if(mode == 2 && n == 1)
      {  
        for(int i = 255; i >= 125; i--)
        {
          analogWrite(led, i);
          delay(5);
        }
        n++;
      }
   

      if((millis() - last_time >(unsigned long)30 * 60 * 1000) && mode == 2)
      {
        for(int i = 125; i >= 0; i--)
        {
          analogWrite(led, i);
          delay(30);
        }
        mode = 0;
        n = 0;
      }
      
/*-------Третий режим. Выключение--------*/
      if(mode == 3 && n == 2)
      {  
        for(int i = 125; i >= 0; i--)
        {
          analogWrite(led, i);
          delay(5);
        }
        n = 0;
      }

}






