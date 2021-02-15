// Vehicle.h

#ifndef _VEHICLE_h
#define _VEHICLE_h

#include "Arduino.h"
#include "motorDriver.h"

class Vehicle
{
public:
	Vehicle(motorDriver* rightMotor, motorDriver* leftMotor)
		: m_pRightMotor{ rightMotor }, m_pLeftMotor{ leftMotor } {}

	virtual ~Vehicle() {} // Will not free the motor objects as they are owned by the caller

    virtual void begin(); 
	virtual void Move(motorDirection direction = motorDirection::Forward);
	virtual void Stop();
	virtual void TurnRight();
	virtual void TurnLeft();
	virtual void setSpeedRatio(int speedRatio);
    virtual bool isMoving();

protected:
	motorDriver*    m_pRightMotor;
	motorDriver*    m_pLeftMotor;
    int             m_speedRatio = maxSpeedRatio;
    bool            m_isMoving = false;
};

class FWDVehicle : Vehicle
{
public:
	FWDVehicle(motorDriver* rightMotor, motorDriver* leftMotor, motorDriver* rearRightMotor, motorDriver* rearLeftMotor)
		: Vehicle(rightMotor, leftMotor), m_pRearRightMotor{ rearRightMotor }, m_pRearLeftMotor{ rearLeftMotor } {}
	
	virtual ~FWDVehicle() {} // Will not free the motor objects as they are owned by the caller

    virtual void begin(); 
	virtual void Move(motorDirection direction = motorDirection::Forward);
	virtual void Stop();
	virtual void TurnRight();
	virtual void TurnLeft();
	virtual void setSpeedRatio(int speedRatio);

private:
	motorDriver* m_pRearRightMotor;
	motorDriver* m_pRearLeftMotor;
};

#endif

