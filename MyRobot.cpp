#include "WPILib.h"

//MOTOR CAN IDs
const int FRONT_LEFT_MOTOR_ID = 1;
const int FRONT_RIGHT_MOTOR_ID = 2;
const int LIFT_MOTOR_ID = 3;
const int THROW_MOTOR_ID = 4;

const int LIFT_UP_BUTTON_ID = 5;
const int LIFT_DOWN_BUTTON_ID = 3;
const float LIFT_SPEED = .8;
const int THROW_BUTTON_ID = 1;
const int DETHROW_BUTTON_ID = 2;
const float THROW_SPEED = .7;


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
    //Relay *liftRelay;

public:
	HerbertBot()
	{

        //Initialize the joysticks.
        leftStick = new Joystick(1);
        rightStick = new Joystick(2);
        thirdStick = new Joystick(3);
        //Initialize the motors
        leftMotor = new Jaguar(FRONT_LEFT_MOTOR_ID);
        rightMotor = new Jaguar(FRONT_RIGHT_MOTOR_ID);
        liftMotor = new Jaguar(LIFT_MOTOR_ID);
        throwMotor = new Jaguar(THROW_MOTOR_ID);
       // liftRelay = new Relay(LIFT_MOTOR_ID);
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
            //set the motor speeds.
            setLeft(leftSpeed);
            setRight(rightSpeed);
            if(thirdStick->GetRawButton(LIFT_UP_BUTTON_ID))
            {
            	setLift(LIFT_SPEED);
            	//liftRelay->Set(Relay::kForward);
            }
            else if(thirdStick->GetRawButton(LIFT_DOWN_BUTTON_ID))
            {
            	setLift(LIFT_SPEED *-1);
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
    
};

START_ROBOT_CLASS(HerbertBot);

