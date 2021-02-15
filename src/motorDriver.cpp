#include "motorDriver.h"

/// L298P methods

void L298P::Move(motorDirection direction)
{
    m_direction = direction;
    m_isMoving = true;
    digitalWrite(m_directionPIN, direction == Forward ? HIGH : LOW);
    analogWrite(m_speedPIN , m_speedRatio);   // Use speed ration directly as the abs for this driver is 0-100
}

void L298P::Stop()
{
    analogWrite(m_speedPIN , minSpeedRatio);   // Use speed ration directly as the abs for this driver is 0-100
    m_isMoving = false;
}


/// L298N methods

void L298N::begin()
{
    motorDriver::begin();
    pinMode(m_invDirectionPIN, OUTPUT);
}

void L298N::Move(motorDirection direction)
{
    m_direction = direction;
    m_isMoving = true;
    digitalWrite(m_directionPIN, direction == Forward ? HIGH : LOW);
    digitalWrite(m_invDirectionPIN, direction == Forward ? LOW : HIGH);
    int absSpeed = SpeedRatioToAbsolute(m_speedRatio);
    Serial.println(absSpeed);
    analogWrite(m_speedPIN,absSpeed);
}

void L298N::Stop()
{
    digitalWrite(m_directionPIN, LOW);
    digitalWrite(m_invDirectionPIN, LOW);
    m_isMoving = false;
}

