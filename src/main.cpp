#include "ultraSonic.h"
#include "Vehicle.h"
//#include <Arduino.h>  Included at both headers
#include <IRremote.h>

enum vehicleMode
{
	IRControl,
	LineFollow
};

vehicleMode mode = vehicleMode::IRControl;
motorDirection direction    = motorDirection::Forward;
const int Buzzer            = 12;
const int IRR               = 7;
const int lineRight         = 11;
const int lineCenter        = 9;
const int lineLeft          = 8;
const int forwardDistLimit  = 60;

const int IR_star           = 0x16;
const int IR_hash           = 0xD;
const int IR_up             = 0x18 ;
const int IR_down           = 0x52;
const int IR_right          = 0x5A;
const int IR_left           = 0x8;

const int IRAllowMaxCycles  = 30000;

bool bContIRpress = false;
uint32_t  nCylesAllowContIR = IRAllowMaxCycles;     

L298N rightMotor(5, 3, 10);
L298N leftMotor(2, 4, 6);
Vehicle vehicle(&rightMotor, &leftMotor);

ultraSonic uSonic(A0, A1);

IRrecv irrecv(IRR);
decode_results results;

void StopWithSound()
{
    if(vehicle.isMoving())
    {
        vehicle.Stop();
        digitalWrite(Buzzer, HIGH);
        delay(500);
        digitalWrite(Buzzer, LOW);
    }
}

byte getLineSensorState()
{
    // returns 0 to 8 according to the truth table of the 3 pins of the line follower
    byte byRet = digitalRead(lineLeft);
    byRet = byRet << 1;
    byRet = byRet | digitalRead(lineCenter);
    byRet = byRet << 1;
    byRet = byRet | digitalRead(lineRight);

    return byRet;
}
void setup() {
    pinMode(Buzzer, OUTPUT);

    pinMode(lineRight, INPUT);
    pinMode(lineCenter, INPUT);
    pinMode(lineLeft, INPUT);

    Serial.begin(9600);
    vehicle.begin();
    uSonic.begin();
    irrecv.enableIRIn();
    irrecv.blink13(true);
}

void loop() {
    if (irrecv.decode())
    {
        nCylesAllowContIR=IRAllowMaxCycles;
        uint16_t command = irrecv.decodedIRData.command;
        if(command==0 && bContIRpress)
            command = irrecv.lastDecodedCommand;

        switch (command)
        {
        case IR_star:
            mode = vehicleMode::IRControl;
            vehicle.setSpeedRatio(100);
            break;
        
        case IR_hash:
            mode = vehicleMode::LineFollow;
            vehicle.setSpeedRatio(40);
            break;
        
        case IR_up:
            if(mode==vehicleMode::IRControl)
            {
                if(uSonic.getAheadDistance()<forwardDistLimit)
                    StopWithSound();
                else    
                    vehicle.Move();
            }
            break;
        
        case IR_down:
            if(mode==vehicleMode::IRControl)
                vehicle.Move(motorDirection::Backword);
            break;
        
        case IR_right:
            if(mode==vehicleMode::IRControl)
                vehicle.TurnRight();
            break;
        
        case IR_left:
            if(mode==vehicleMode::IRControl)
                vehicle.TurnLeft();
            break;

        default:
            if(mode==vehicleMode::IRControl)
                vehicle.Stop();
            break;
        }
        bContIRpress = true;
        irrecv.resume();
    }
    else
    {
        if(mode==vehicleMode::IRControl)
        {
            nCylesAllowContIR--;
            if(nCylesAllowContIR==0)
            {
                nCylesAllowContIR=IRAllowMaxCycles;
                bContIRpress = false;
                if(mode==vehicleMode::IRControl)
                    vehicle.Stop();
            }
        }
        else
        {
            byte byLineSensorState = getLineSensorState();
            Serial.println(byLineSensorState);
            switch (byLineSensorState)
            {
                case 0:
                case 5:
                    vehicle.Move();
                    break;

                case 2:
                case 4:
                case 6:
                    vehicle.TurnRight();
                break;
            
                case 1:
                case 3:
                    vehicle.TurnLeft();
                    break;
                
                default:
                    StopWithSound();
                    break;
            }           
        }
    }
}
