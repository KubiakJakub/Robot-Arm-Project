#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver(0x40);

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQUENCY 50

void setup()
{
  pwmDriver.begin();
  pwmDriver.setPWMFreq(FREQUENCY); // 50hz is normaly used for servo motors
  Serial.begin(9600);
  Serial.println("Witam");
}

int tempPotVal = 0;
int adcPin[4] = {A0, A1, A2, A3};
int pwmRisingTime = 0;
int pwmFallingTime = 0;

void moveMotor(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, potVal;

  // Read values from potentiometer
  potVal = analogRead(controlIn);

  // Convert to pulse width
  pulse_wide = map(potVal, 0, 1023, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);

  //Control Motor
  pwmDriver.setPWM(motorOut, 0, pulse_width);
}

void loop()
{
  for (int id = 0; id < 4; id++)
  {
    // tempPotVal = analogRead(adcPin[id]);
    // Serial.print("> ");
    // Serial.println(tempPotVal);
    // pwmFallingTime = map(tempPotVal, 113, 842, 102, 512);
    // pwmDriver.setPWM(id, pwmRisingTime, pwmFallingTime);
    moveMotor(id, id);
  }
}