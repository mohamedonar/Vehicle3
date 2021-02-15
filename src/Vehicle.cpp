// 
// 
// 

#include "Vehicle.h"

void Vehicle::begin()
{
    m_pRightMotor->begin();
    m_pLeftMotor->begin();
}

void Vehicle::Move(motorDirection direction)
{
	m_pRightMotor->Move(direction);
	m_pLeftMotor->Move(direction);
    m_isMoving = true;
}

void Vehicle::Stop()
{
	m_pLeftMotor->Stop();
	m_pRightMotor->Stop();
    m_isMoving = false;
}

void Vehicle::TurnRight()
{
	m_pLeftMotor->Move();
	m_pRightMotor->Stop();
    m_isMoving = true;
}

void Vehicle::TurnLeft()
{
	m_pRightMotor->Move();
	m_pLeftMotor->Stop();
    m_isMoving = true;
}

void Vehicle::setSpeedRatio(int speedRatio)
{
    m_pRightMotor->setSpeedRatio(speedRatio);
    m_pLeftMotor->setSpeedRatio(speedRatio);
}

bool Vehicle::isMoving() 
{ 
    return m_isMoving; 
}

/// FWDVehicle methods

void FWDVehicle::begin()
{
    Vehicle::begin();
    m_pRearRightMotor->begin();
    m_pRearLeftMotor->begin();
}

void FWDVehicle::Move(motorDirection direction)
{
	Vehicle::Move(direction);
	m_pRearRightMotor->Move(direction);
	m_pRearLeftMotor->Move(direction);
}

void FWDVehicle::Stop()
{
	Vehicle::Stop();
	m_pRearRightMotor->Stop();
	m_pRearLeftMotor->Stop();
}

void FWDVehicle::TurnRight()
{
	Vehicle::TurnRight();
	m_pRearLeftMotor->Move(motorDirection::Forward);
	m_pRearRightMotor->Move(motorDirection::Backword);
}

void FWDVehicle::TurnLeft()
{
	Vehicle::TurnLeft();
	m_pRearRightMotor->Move(motorDirection::Forward);
	m_pRearLeftMotor->Move(motorDirection::Backword);
}

void FWDVehicle::setSpeedRatio(int speedRatio)
{
    Vehicle::setSpeedRatio(speedRatio);
    m_pRearRightMotor->setSpeedRatio(speedRatio);
    m_pRearLeftMotor->setSpeedRatio(speedRatio);
}

