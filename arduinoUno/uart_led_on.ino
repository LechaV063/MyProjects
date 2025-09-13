/*
При нажатии на кнопку, подключённую к
Ардуино, она отправляет на STM32
поочерёдно символ 'A' (по которому 
STM32 включает светодиод) или 'a'
(выключить светодиод). 
STM32 передаёт на Ардуино символы 'B'
или 'b' соответственно.
*/

// pins for the LEDs:
const int LED = 4;        // D4 - светодиод
const int Button = 2;     // D2 - кнопка
const int debounce = 90;  // величина антидребезговой задержки мс
int prevLedState = 0;     // предыдущее значение светодиода
int prevButtonState = 0;  // предыдущее значение конпки
volatile int clicked = 0; // флаг нажатия кнопки

void setup() {
  pinMode(Button, INPUT_PULLUP);              // подтяжка на входе кнопки
  attachInterrupt(0, buttonClicked, FALLING); // для D2 назначена функция обработки прерывания buttonClicked по нажатию
  pinMode(LED, OUTPUT);                       // 
  digitalWrite(LED, LOW);                     // начальное значение светодиода - LOW
  Serial.begin(115200);                       // 
  }

void loop() 
{
  if (clicked && (prevButtonState == digitalRead(Button))) 
    {
      if (prevLedState){
          prevLedState = 0;
          // для отладки антидребезговой паузы
          // digitalWrite(LED, LOW);
          Serial.println('a');    // отправляем на stm символ 'a'
        } else {
          prevLedState = 1;
          // для отладки антидребезговой паузы
          // digitalWrite(LED, HIGH);
          Serial.println('A');    // отправляем на stm символ 'A'
        }
      clicked = 0;
    }
  if(Serial.available())
    {
      char c = Serial.read();
      if (c == 'b') {
          digitalWrite(LED, LOW); // ВЫКЛ при получении от stm символа 'b'
      } else if (c == 'B') {
          digitalWrite(LED, HIGH);// ВКЛ при получении от stm символа 'B'
      }
    }
    prevButtonState = digitalRead(Button); // обновляем предыдущее значение кнопки
    delay(debounce);                       // антидребезговая задержка
}

void buttonClicked() {
  clicked = 1;
}
