
#ifndef _MOTORCONTROLLER_h
#define _MOTORCONTROLLER_h

#include "Arduino.h"

const int maxSpeedRatio = 100;
const int minSpeedRatio = 0;

enum motorDirection
{
	Forward = HIGH,
	Backword = LOW
};

class motorDriver
{
public:
	motorDriver(int DirectionPIN, int speedPIN=-1) // if speedPIN=-1, usually speed pin then is set (with a jumper or so) to HIGH always
		: m_speedPIN{ speedPIN },  m_directionPIN{ DirectionPIN }{}

	virtual ~motorDriver() {}

    virtual void begin()
    {
        pinMode(m_speedPIN, OUTPUT);
        pinMode(m_directionPIN, OUTPUT);
    }

	virtual void setSpeedRatio(int speedRatio)
	{
        if(m_speedPIN!=-1)
            m_speedRatio = speedRatio;
	}

	virtual int getSpeedRatio()
	{
		return m_speedRatio;
	}

	virtual int getAbsoluteSpeed()
    {
        return SpeedRatioToAbsolute(m_speedRatio);
    }

	virtual motorDirection getDirection()
	{
        return m_direction;
	}

	virtual int SpeedRatioToAbsolute(int speedRatio)
	{
		double dSpeed = (speedRatio * m_maxABSspeed) / maxSpeedRatio;
		return dSpeed;
	}

	virtual int SpeedActualToRatio(int speed)
	{
		double dSpeed = (speed / m_maxABSspeed) * maxSpeedRatio;
		return dSpeed;
	}

    virtual bool isMoving()
    {
        return m_isMoving;
    }

    virtual void Move(motorDirection direction = motorDirection::Forward) = 0;
    virtual void Stop() = 0;

protected:
	int m_speedPIN;
	int m_directionPIN;
    int m_speedRatio = maxSpeedRatio;
    int m_maxABSspeed = 100;
    motorDirection m_direction = motorDirection::Forward;
    bool m_isMoving = false;
};

class L298P : public motorDriver
{
public:
	L298P(int DirectionPIN, int speedPIN)
		: motorDriver(DirectionPIN, speedPIN)
    {
        m_maxABSspeed = 100;
    }

	virtual ~L298P() {}

    virtual void Move(motorDirection direction = motorDirection::Forward);
    virtual void Stop();
};

class L298N : public motorDriver
{
public:
	L298N(int DirectionPIN, int invDirectionPIN, int speedPIN=-1)
		: motorDriver(DirectionPIN, speedPIN), m_invDirectionPIN{ invDirectionPIN }
    {
        m_maxABSspeed = 255;
    }

	virtual ~L298N() {}

    virtual void begin();
    virtual void Move(motorDirection direction = motorDirection::Forward);
    virtual void Stop();


private:
	int m_invDirectionPIN;
};
#endif

