#include "main.h"
#include "math.h"
using namespace std;
using namespace pros;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(6, true);
pros::Motor rightFront(3,false);
pros::Motor leftBack(5, true);
pros::Motor rightBack(18,false);
pros::Motor puncher(9,false);
pros::Motor intake(19,false);
pros::Motor angle(13,true);
pros::Motor lift(20,false);

//pros::ADIGyro gyroA ('e');
//pros::ADIAnalogIn accelX ('g');
//pros::ADIAnalogIn accelY ('h');
//pros::ADIAnalogIn accelZ ('f');
//pros::ADIDigitalIn pLimit ('a');
pros::ADIDigitalIn iLimit('h');
pros::ADIDigitalIn pLimit('a');

bool forwards=true;
float gyroprevA=0;
int iCount=0,pCount=0;
int moveToHigh=0,moveToLow=0;
int velocity=0;

int pullBack=-1800;
int lockYL=100000,lockFlagL,lockWidthL;
int lockXH=-1,lockYH=-1,lockFlagH,lockWidthH;
int lockWidth=18;
bool dont=false;

void printTask(void* param)
{
  while(true)
  {
    pros::lcd::print(1,"%f", rightFront.get_torque());
    //pros::lcd::print(5,"%d", line.get_value());
    pros::delay(200);
  }
}

void driveTask(void* param)
{
  while(true)
  {
    //voltage drive
    double lpower=master.get_analog(ANALOG_LEFT_Y);
    double rpower=master.get_analog(ANALOG_RIGHT_Y);

      rpower = rpower * -12000 / 127;
      lpower = lpower * -12000 / 127;
      rightFront.move_voltage(rpower);//all in mv
      leftFront.move_voltage(lpower);
      rightBack.move_voltage(rpower);
      leftBack.move_voltage(lpower);
      pros::delay(2);
    }
}
bool pIn=false;
bool angleFeed=false;
//int lineInit=0;
void intakeTask(void* param)
{
  while(true)
  {
    if(pLimit.get_value()&&iLimit.get_value())
    {
      intake.move_velocity(0);
      intake.move_velocity(200);
      pros::delay(250);
      intake.move_velocity(0);
      pros::delay(300);
      intake.move_velocity(-200);
      pros::delay(300);
      dont=true;
    }
    else if(!pLimit.get_value())
      dont=false;
    if(dont==true)
    {
      if(master.get_digital(DIGITAL_R2))
        intake.move_velocity(-200);
      else
        intake.move_velocity(0);
    }
    else
    {
      if(master.get_digital(DIGITAL_R1))
        intake.move_velocity(200);
      else if(master.get_digital(DIGITAL_R2))
        intake.move_velocity(-200);
      else if(!angleFeed)
        intake.move_velocity(0);
    }
    pros::delay(2);
  }
}
double final=0;

void boringAngleTask(void* param)
{
  int frontHigh=0,frontMid=350;//0,360--0, 360
  int midHigh=110, midMid=360; //130, 430--100, 400
  int backHigh=40, backMid=280; //90, 400--20, 300
  while(true)
  {
    angleFeed=false;
    //FRONT DOUBLE SHOT-LEFT
    if(master.get_digital(DIGITAL_LEFT))
    {
      angleFeed=true;
      angle.move_absolute(frontHigh,200);
      while (!((angle.get_position()<frontHigh+15)&&(angle.get_position()>frontHigh-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      angle.move_absolute(frontMid,200);
      intake.move_velocity(200);
      while (!((angle.get_position()<frontMid+15)&&(angle.get_position()>frontMid-15)))
        pros::delay(2);

      pros::delay(400);
      puncher.move_relative(-1800,200);
      while(master.get_digital(DIGITAL_LEFT))
        pros::delay(2);
    }
    //FRONT TOP-UP
    if(master.get_digital(DIGITAL_UP))//high front
    {
      angleFeed=true;
      angle.move_absolute(frontHigh,200);
      while (!((angle.get_position()<frontHigh+15)&&(angle.get_position()>frontHigh-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      intake.move_velocity(200);
      pros::delay(400);
      while(master.get_digital(DIGITAL_UP))
        pros::delay(2);
    }

    //FRONT MIDDLE-DOWN
    if(master.get_digital(DIGITAL_DOWN))//middle front
    {
      angleFeed=true;
      angle.move_absolute(frontMid,200);
      while (!((angle.get_position()<frontMid+15)&&(angle.get_position()>frontMid-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      intake.move_velocity(200);
      pros::delay(400);
      while(master.get_digital(DIGITAL_DOWN))
        pros::delay(2);
    }

    //BACK DOUBLE SHOT-A
    if(master.get_digital(DIGITAL_A))
    {
      angleFeed=true;
      angle.move_absolute(backHigh,200);
      while (!((angle.get_position()<backHigh+15)&&(angle.get_position()>backHigh-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      angle.move_absolute(backMid,200);
      intake.move_velocity(200);
      while (!((angle.get_position()<backMid+15)&&(angle.get_position()>backMid-15)))
        pros::delay(2);
      pros::delay(400);
      puncher.move_relative(pullBack,200);
      while(master.get_digital(DIGITAL_A))
        pros::delay(2);
    }

    //
    if(master.get_digital(DIGITAL_X))//high back
    {
      angleFeed=true;
      angle.move_absolute(backHigh,200);
      while (!((angle.get_position()<backHigh+15)&&(angle.get_position()>backHigh-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      intake.move_velocity(200);
      pros::delay(400);
      while(master.get_digital(DIGITAL_X))
        pros::delay(2);
    }
    if(master.get_digital(DIGITAL_B))//middle back
    {
      angleFeed=true;
      angle.move_absolute(backMid,200);
      while (!((angle.get_position()<backMid+15)&&(angle.get_position()>backMid-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      intake.move_velocity(200);
      pros::delay(400);
      while(master.get_digital(DIGITAL_B))
        pros::delay(2);
    }

    if(master.get_digital(DIGITAL_Y))
    {
      angleFeed=true;
      angle.move_absolute(midHigh,200);
      while (!((angle.get_position()<midHigh+15)&&(angle.get_position()>midHigh-15)))
        pros::delay(2);
      puncher.move_relative(pullBack,200);
      pros::delay(250);
      angle.move_absolute(midMid,200);
      intake.move_velocity(200);
      while (!((angle.get_position()<midMid+15)&&(angle.get_position()>midMid-15)))
        pros::delay(2);
      pros::delay(400);
      puncher.move_relative(pullBack,200);
      while(master.get_digital(DIGITAL_Y))
        pros::delay(2);
    }
  }
}
void liftTask(void* param)
{
  while(true)
  {
      if(master.get_digital(DIGITAL_L1))
        lift.move_velocity(-160);
      else if(master.get_digital(DIGITAL_L2))
        lift.move_velocity(160);
      else
      {
        lift.move_velocity(0);
      }
    pros::delay(2);
  }
}
/*void visionTask(void* param)
{
  vision.set_exposure(88);
  vision_object_s_t objects[20];
  vision_object_s_t rtn;
  while(true)
  {
    int c=0;
    rtn= vision.get_by_size(c);
    if(rtn.top_coord<37||rtn.width>40)
    {
      rtn= vision.get_by_size(1);
    }
      lockWidth=rtn.width;

    master.print(0,0,"%d",lockWidth);
    //master.print(1,0,"%d",poten.get_value());
    pros::delay(5);
  }
}*/
void setDriveHold()
{
  leftFront.set_brake_mode(MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightFront.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(MOTOR_BRAKE_HOLD);
  pros::delay(10);
}
void setDriveCoast()
{
  leftFront.set_brake_mode(MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(MOTOR_BRAKE_COAST);
  rightFront.set_brake_mode(MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(MOTOR_BRAKE_COAST);
  pros::delay(10);
}
void opcontrol()
{
  //vision.set_signature(1, &REDFLAG);
  //vision.set_signature(2, &BLUEFLAG);
  //vision.set_signature(3, &GREENFLAG);
  intake.set_brake_mode(MOTOR_BRAKE_BRAKE);
  angle.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift.set_brake_mode(MOTOR_BRAKE_BRAKE);


  //puncher.tare_position();
  //angle.tare_position();
  //puncher.move_absolute(-1200,200);

  //ineInit=line.get_value();
  //TASK
  //pros::Task a (angleTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "angle");
  pros::Task d (driveTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "drive");
  pros::Task i (intakeTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "intake");
  pros::Task b (boringAngleTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "boring");
  //pros::Task p (brakingTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "brake");
  //pros::Task p (puncherTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "puncher");
  //pros::Task x (printTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "print");
  pros::Task l (liftTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift");
  //pros::Task v (visionTask, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "vision");
  //pros::Task y (testing, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "print");

  bool coast=true;
  while(true)
  {
    if(master.get_digital(DIGITAL_RIGHT)&&coast==true)
    {
      coast=false;
      setDriveHold();
      while(master.get_digital(DIGITAL_RIGHT))
        pros::delay(2);
    }
    else if(master.get_digital(DIGITAL_RIGHT)&&coast==false)
    {
      coast=true;
      setDriveCoast();
      while(master.get_digital(DIGITAL_RIGHT))
        pros::delay(2);
    }
    pros::delay(200);
  }

}
