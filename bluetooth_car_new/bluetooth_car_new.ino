//www.elegoo.com
//2016.09.12

//int receiverpin = 12;
int LED = 13;
volatile int state = LOW;
char getstr;
int in1 = 9;
int in2 = 8; // digital
int in3 = 7; // digital
int in4 = 6;
int ENA = 10;
int ENB = 5;
int ABS = 135;
float vr;
float vl;
unsigned long time;

void simple_drive(int vr, int vl) {

  if (vr < 0)
    analogWrite(in1, 255 - abs(vr) /* map(fabs(vel), 0, 100, 255, 0)*/);
  else
    analogWrite(in1, abs(vr) /* map(fabs(vel), 0, 100, 255, 0)*/);
  digitalWrite(in2, vr >= 0 ? LOW : HIGH);

  // left
  if (vl > 0)
    analogWrite(in4, 255 - abs(vl) /* map(fabs(vel), 0, 100, 255, 0)*/);
  else
    analogWrite(in4, abs(vl) /* map(fabs(vel), 0, 100, 255, 0)*/);
  digitalWrite(in3, vl > 0 ? HIGH : LOW);
}

void drive(int omega, int vel) {
  vr = (vel + omega) / 2;
  vl = vel - vr;
  // right
  analogWrite(in2, vr /*map(fabs(vel), 0, 100, 0, 255)*/);
  digitalWrite(in1, vel >= 0 ? LOW : HIGH);

  // left
  analogWrite(in3, vl /* map(fabs(vel), 0, 100, 255, 0)*/);
  digitalWrite(in4, vel > 0 ? HIGH : LOW);
}

void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("STOP!");  
}

void setup()
{
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  //_mStop();

  //simple_drive(100, 100);
  //while(true);
}
void loop()
{
  /*
    getstr=Serial.read();
    if(getstr=='f')
    {
    _mForward();
    }
    else if(getstr=='b')
    {
    _mBack();
    delay(200);
    }
    else if(getstr=='l')
    {
    _mleft();
    delay(200);
    }
    else if(getstr=='r')
    {
    _mright();
    delay(200);
    }
    else if(getstr=='s')
    {
    _mStop();
    }
    else if(getstr=='A')
    {
    stateChange();
    } */
  if (Serial.available() > 0) {
    int v2 = Serial.parseInt();
    int v1 = Serial.parseInt();
    int vr = v1;
    int vl = v2;
    simple_drive(vr, vl);
    Serial.println(String(vr) + ' ' + vl);
//    Serial.println(vl);
    //analogWrite(in2, abs(vr));
    //digitalWrite(in1, vr >= 0 ? LOW : HIGH);

    delay(10);
    while (Serial.available() > 0)
      Serial.read();
//    Serial.print("Time: ");
//    time = millis();
//    Serial.println(time);
  }
}

