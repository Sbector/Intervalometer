#include <JeeLib.h>

int outPin = 13;
int pulseWidth = 0;
int state;
int intervalo = 3;
int disparos;
ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup()

{

  pinMode(outPin, OUTPUT);
  Serial.begin(9600);

}

void SendPulse(int pulseWidth)
{
  int reps = pulseWidth / 23.6;

  for (int i = 0; i <= reps; i++)
  {
    digitalWrite(outPin, HIGH);
    delayMicroseconds(11);
    digitalWrite(outPin, LOW);
    delayMicroseconds(5);
  }

}

void SendSequence()
{

  for (int i = 0; i < 2; i++)
  {
    SendPulse(2000);
    delay(27);
    delayMicroseconds(800);
    SendPulse(500);
    delayMicroseconds(1500);
    SendPulse(500);
    delayMicroseconds(3500);
    SendPulse(500);
    if (i < 1)
    {
      delay(63);
    }
  }
}


void loop() {

  Serial.println("Intervalo deseado(milisegundos)");
  while (Serial.available() == 0) { }
  intervalo = Serial.parseInt();
  Serial.print("\n Intervalo: ");
  Serial.print(intervalo);
  Serial.println(" ms\n\n");

  Serial.println("Disparos a realizar");
  while (Serial.available() == 0) { }
  disparos = Serial.parseInt();
  Serial.print("\n ");
  Serial.print(disparos);
  Serial.println(" disparos\n\n");


  for (int val = 1; val <= disparos; val ++) {
    Serial.print("disparo - ");
    Serial.println(val);
    SendSequence ();
    //delay(intervalo);
    Sleepy::loseSomeTime(intervalo);
    
  }
  Serial.print("\n");
}
