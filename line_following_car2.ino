void motor(char pin, char pwmpin, char state, int val)
{
  pinMode(pin, OUTPUT);

  if (state == 1)
  {
    analogWrite(pwmpin, val);
    digitalWrite(pin, 1);
  }
  else if (state == 2)
  {
    analogWrite(pwmpin, val);
    digitalWrite(pin, 0);
  }
  else if (state == 0)
  {
    analogWrite(pwmpin, 0);
    digitalWrite(pin, 0);
  }
}

void runfoward(int i)   //前进
{
  motor(4, 5, 1, i);
  motor(7, 6, 1, i-30);
}
void runback(int j)    //后退
{
  motor(4, 5, 2, j);
  motor(7, 6, 2, j);
}
void turnL(int m)     //左转
{
  motor(4, 5, 1, m);
  motor(7, 6, 0, 0);
}
void turnR(int n)      //右转
{
  motor(4, 5, 0, 0);
  motor(7, 6, 1, n);
}
void stop()            //停止
{
  motor(4, 5, 0, 0);
  motor(7, 6, 0, 0);
}
void setup()
{
  pinMode(13, INPUT); //定义右边传感器,
  pinMode(12, INPUT); //定义中间传感器,
  pinMode(11, INPUT); //定义左边传感器,
  Serial.begin(9600);
}
void loop()
{
  char num1, num2, num3;

  num1 = digitalRead(11);
  num2 = digitalRead(12);
  num3 = digitalRead(13);

  if ((num1 == 0) && num2 && num3) {
    turnL(120);          //往左
    delay(2);
    while (1) {
      num2 = digitalRead(12);   //循环判断中间传感器
      if (num2 == 1) {
        turnL(120);                     
        delay(2);
      }
      else
        break;                      
    }                                       
  }

  else if (num2 && num1 && (num3 == 0)) {
    turnR(120);
    delay(2);
    while (1)
    {
      num2 = digitalRead(12);
      if (num2 == 1) {
        turnR(120);
        delay(2);
      }
      else
        break;
    }
  }
  else {
    runfoward(120);
    delay(2);
  }
}
