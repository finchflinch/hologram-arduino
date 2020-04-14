const int TRIG1 = 9;
const int ECHO1 = 10;

const int TRIG2 = 5;
const int ECHO2 = 6;
static int slideNo = 0;
bool sense = false;
void setup() {
  
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  Serial.begin(9600);

}

void loop() {
 
  int data1 = GetUltra(TRIG1, ECHO1);

  if (data1 <= 10)
  {
    if (slideNo == 0)
    {
      slideNo = 1;
  delay(200);
    }
    
    else
    {
      uint32_t period = 5000L;       // 5 seconds
       for( uint32_t tStart = millis();  (millis()-tStart) < period; )
       {
        int data2 = GetUltra(TRIG2, ECHO2);
  delay(20);
        if (data2 <= 10)
        {
          if (slideNo == 1)
          {
            slideNo = 2;
            sense = true;
          }
          else if (slideNo == 2)
          {
            slideNo = 3;
            sense = true;
          }
          else
          {
            slideNo = 1;
            sense = true;
          }

          break;
        }}
       if (sense == false)
       {
          slideNo = 0;

       }
      
     }
  }
  sense = false;
  Serial.flush();
  Serial.write(slideNo);
  delay(100);
}

double GetUltra(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  digitalWrite(trig, HIGH);
  delayMicroseconds(8);
  digitalWrite(trig, LOW);

  double distance = (pulseIn(echo, HIGH))* 343.2 / 20000;
  return distance;
}
