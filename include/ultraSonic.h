#ifndef _ULTRASONIC_h
#define _ULTRASONIC_h

#include <Arduino.h>

class ultraSonic
{
private:
    int m_trigPin;
    int m_echoPin;

public:
    ultraSonic(int trigPin, int echoPin)
        : m_trigPin { trigPin }, m_echoPin { echoPin } {}
    ~ultraSonic() {}

    void begin()
    {
        pinMode(m_trigPin, OUTPUT);
        pinMode(m_echoPin, INPUT);
    }

    int getAheadDistance()
    {
        digitalWrite(m_trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(m_trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(m_trigPin, LOW);
        return pulseIn(m_echoPin, HIGH)*0.034 / 2;
    }
};

#endif
