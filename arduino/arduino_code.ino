#include <AccelStepper.h>

// Motor 1
#define STEP1 6
#define DIR1 7

// Motor 2
#define STEP2 11
#define DIR2 12

AccelStepper stepper1(AccelStepper::DRIVER, STEP1, DIR1);
AccelStepper stepper2(AccelStepper::DRIVER, STEP2, DIR2);

String input = "";

void setup()
{
    Serial.begin(115200);

    stepper1.setMaxSpeed(200);
    stepper1.setAcceleration(200);

    stepper2.setMaxSpeed(200);
    stepper2.setAcceleration(200);

    stepper1.moveTo(0);
    stepper2.moveTo(0);

    Serial.println("Ready.");
    Serial.println("Commands:");
    Serial.println("M1 <pos>");
    Serial.println("M2 <pos>");
    Serial.println("BOTH <pos1> <pos2>");
    Serial.println("HOME");
}

void handleCommand(String cmd)
{
    cmd.trim();

    if (cmd.startsWith("M1 "))
    {
        long pos = cmd.substring(3).toInt();
        stepper1.moveTo(pos);
        Serial.print("Motor 1 target set to: ");
        Serial.println(pos);
    }
    else if (cmd.startsWith("M2 "))
    {
        long pos = cmd.substring(3).toInt();
        stepper2.moveTo(pos);
        Serial.print("Motor 2 target set to: ");
        Serial.println(pos);
    }
    else
    {
        Serial.print("Unknown command: ");
        Serial.println(cmd);
    }
}

void loop()
{
    stepper1.run();
    stepper2.run();

    while (Serial.available() > 0)
    {
        char c = Serial.read();

        if (c == '\n')
        {
            handleCommand(input);
            input = "";
        }
        else if (c != '\r')
        {
            input += c;
        }
    }
}