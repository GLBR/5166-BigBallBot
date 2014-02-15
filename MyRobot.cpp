#include "WPILib.h"

//MOTOR CAN IDs
const int FRONT_LEFT_MOTOR_ID = 1;
const int FRONT_RIGHT_MOTOR_ID = 2;
const int LIFT_MOTOR_ID = 3;
const int THROW_MOTOR_ID = 5;
const int ELEVATOR_MOTOR_ID = 4;

const int TICKS_FORWARD =600;

const int LIFT_UP_BUTTON_ID = 5;
const int LIFT_DOWN_BUTTON_ID = 3;
const float LIFT_SPEED = .9;
const float LIFT_DOWN_SPEED = -.15;
const int THROW_BUTTON_ID = 1;
const int DETHROW_BUTTON_ID = 2;
const float THROW_SPEED = .1;
const int ELEVATOR_UP_BUTTON_ID = 9;
const int ELEVATOR_DOWN_BUTTON_ID = 11;
const float ELEVATOR_SPEED = .35;
		


class HerbertBot : public IterativeRobot

{
    //Joysticks (only 2 of them)
    Joystick *leftStick, *rightStick;
    Joystick *thirdStick;
    //Jaguars
    Jaguar *leftMotor;
    Jaguar *rightMotor;
    Jaguar *liftMotor;
    Jaguar *throwMotor;
    Jaguar *elevatorMotor;
    //Relay *liftRelay;
    int counter;   

public:
	HerbertBot()
	{

		counter = 0;
        //Initialize the joysticks.
        leftStick = new Joystick(1);
        rightStick = new Joystick(2);
        thirdStick = new Joystick(3);
        //Initialize the motors
        leftMotor = new Jaguar(FRONT_LEFT_MOTOR_ID);
        rightMotor = new Jaguar(FRONT_RIGHT_MOTOR_ID);
        liftMotor = new Jaguar(LIFT_MOTOR_ID);
        throwMotor = new Jaguar(THROW_MOTOR_ID);
        elevatorMotor = new Jaguar(ELEVATOR_MOTOR_ID);
       // liftRelay = new Relay(LIFT_MOTOR_ID);
	}
	
	void AutonomousPeriodic()
	{
		counter++;
		if(counter<TICKS_FORWARD);
		{
            //driving forward
			leftMotor->Set(1);
			rightMotor->Set(1);
		}
		if(counter>TICKS_FORWARD);
		{
		    //stop driving forward
			leftMotor->Set(0);
			rightMotor->Set(0);
		}
	}
    
    void TeleopPeriodic()
    {
            //declare some holder variables
            float leftSpeed, rightSpeed; 
            float liftSpeed;
            //get the speeds from the joystics
            leftSpeed = leftStick->GetY();
            rightSpeed = rightStick->GetY();
            liftSpeed = thirdStick->GetY();
            //set the motor speeds.;
            setLeft(leftSpeed);
            setRight(rightSpeed);
            if(thirdStick->GetRawButton(LIFT_UP_BUTTON_ID))
            {
            	setLift(LIFT_SPEED);
            	//liftRelay->Set(Relay::kForward);
            }
           else if(thirdStick->GetRawButton(LIFT_DOWN_BUTTON_ID))
            {
            	setLift(LIFT_DOWN_SPEED);
            	//liftRelay->Set(Relay::kReverse);
            }
            else
            {
            	setLift(0);
            	//liftRelay->Set(Relay::kOff);
            }
            if(thirdStick->GetRawButton(THROW_BUTTON_ID))
            {
            	setThrowingArm(THROW_SPEED);
            }
            else if(thirdStick->GetRawButton(DETHROW_BUTTON_ID))
            {
            	setThrowingArm(THROW_SPEED *-1);
            }
            else
            {
            	setThrowingArm(0);
            }
            if(thirdStick->GetRawButton(ELEVATOR_UP_BUTTON_ID))
            {
            	printf("Elevator::up\n");
              	setElevator(ELEVATOR_SPEED *-1);

            }
            else if(thirdStick->GetRawButton(ELEVATOR_DOWN_BUTTON_ID))
            {
            	printf("Elevator::down\n");
                setElevator(ELEVATOR_SPEED);

            }
            else
            {
                setElevator(0);
            }
            
    }

    void setLeft(float speed)
    {
            leftMotor -> Set(speed *-1);
            
    }
    
    void setRight(float speed)
    {
            rightMotor -> Set(speed);
    }
    
    void setLift(float speed)
    {
    	    liftMotor -> Set(speed);
    }
    
    void setThrowingArm(float speed)
    {
            throwMotor -> Set(speed);
            
    }
    void setElevator(float speed)
    {
            elevatorMotor -> Set(speed);
            
    }
    
};

START_ROBOT_CLASS(HerbertBot);

