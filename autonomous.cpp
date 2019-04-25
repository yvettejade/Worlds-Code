#include "main.h"

pros::Controller masterA(pros::E_CONTROLLER_MASTER);
pros::Motor leftFrontA(6, true);
pros::Motor rightFrontA(3,false);
pros::Motor leftBackA(5, true);
pros::Motor rightBackA(18,false);
pros::Motor puncherA(9,false);
pros::Motor intakeA(19,false);
pros::Motor angleA(13,true);
pros::Motor liftA(20,false);

pros::ADIGyro gyro1('a');
//pros::ADIGyro gyro2('b');

void driveOneSquare(double squares, bool forward, int speed)
{
    if(forward==false)
    {
      leftFrontA.move_velocity(75);
      rightFrontA.move_velocity(75);
      leftBackA.move_velocity(75);
      rightBackA.move_velocity(75);
      pros::delay(1400*squares);
    }
    else
    {
      leftFrontA.move_velocity(-75);
      rightFrontA.move_velocity(-75);
      leftBackA.move_velocity(-75);
      rightBackA.move_velocity(-75);
      pros::delay(1400*squares);
    }
    leftFrontA.move_velocity(0);
    rightFrontA.move_velocity(0);
    leftBackA.move_velocity(0);
    rightBackA.move_velocity(0);
}
void left(double amount)
{
  leftFrontA.move_velocity(50);
  rightFrontA.move_velocity(-50);
  leftBackA.move_velocity(50);
  rightBackA.move_velocity(-50);
  pros::delay(880*amount);
  leftFrontA.move_velocity(0);
  rightFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightBackA.move_velocity(0);
}
void right(double amount)
{
  leftFrontA.move_velocity(-50);
  rightFrontA.move_velocity(50);
  leftBackA.move_velocity(-50);
  rightBackA.move_velocity(50);
  pros::delay(880*amount);
  leftFrontA.move_velocity(0);
  rightFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightBackA.move_velocity(0);
}

void printTaskA(void* param)
{
  while(true)
  {

    pros::lcd::print(0, "%d", gyro1.get_value()+10);
    pros::lcd::print(1, "%f", gyro1.get_value());
    pros::lcd::print(2,"%s", "there");
    //pros::lcd::print(2,"%d",(gyro1.get_value()*-1+gyro2.get_value())/2);
    pros::delay(2000);
  }
}

void autonomous()
{
  intakeA.set_brake_mode(MOTOR_BRAKE_BRAKE);
  intakeA.tare_position();
  liftA.tare_position();
  puncherA.tare_position();
  puncherA.move_absolute(-1200,200);

  leftFrontA.set_brake_mode(MOTOR_BRAKE_BRAKE);
  leftBackA.set_brake_mode(MOTOR_BRAKE_BRAKE);
  rightFrontA.set_brake_mode(MOTOR_BRAKE_BRAKE);
  rightBackA.set_brake_mode(MOTOR_BRAKE_BRAKE);

  //intake
  intakeA.move_velocity(200);
  driveOneSquare(1.6,true,200);
  pros::delay(1500);

  //back up
  intakeA.move_velocity(-200);
  pros::delay(300);
  intakeA.move_velocity(0);
  driveOneSquare(0.43,false,200);
  pros::delay(600);

  right(1.1);
  pros::delay(500);

  driveOneSquare(0.8,true,200);
  pros::delay(200);

  leftFrontA.set_brake_mode(MOTOR_BRAKE_HOLD);
  leftBackA.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightFrontA.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightBackA.set_brake_mode(MOTOR_BRAKE_HOLD);

  intakeA.move_velocity(-200);
  leftFrontA.move_velocity(-150);
  leftBackA.move_velocity(-150);
  rightFrontA.move_velocity(-150);
  rightBackA.move_velocity(-150);
  pros::delay(700);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);
  pros::delay(1000);
  intakeA.move_velocity(0);

  //far
  //left(0.56);
  //close
  left(0.22);
  pros::delay(200);

  liftA.move_absolute(0,100);
  //far
  //pros::delay(2600);
  //close
  pros::delay(3200);

  //far
  angleA.move_absolute(0,200);
  while (!((angleA.get_position()<10)&&(angleA.get_position()>-10)))
    pros::delay(2);
  puncherA.move_relative(-1800,200);
  pros::delay(800);
  intakeA.move_velocity(200);
  angleA.move_absolute(400,100);
  while (!((angleA.get_position()<410)&&(angleA.get_position()>390)))
    pros::delay(2);
  puncherA.move_relative(-1800,200);
  pros::delay(400);

  //close
  angleA.move_absolute(130,200);
  while (!((angleA.get_position()<140)&&(angleA.get_position()>120)))
    pros::delay(2);
  puncherA.move_relative(-1800,200);
  pros::delay(800);
  intakeA.move_velocity(200);
  angleA.move_absolute(420,100);
  while (!((angleA.get_position()<430)&&(angleA.get_position()>410)))
    pros::delay(2);
  puncherA.move_relative(-1800,200);
  pros::delay(400);

  /*leftFrontA.move_velocity(100);
  leftBackA.move_velocity(100);
  pros::delay(670);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  pros::delay(200);
  intakeA.move_velocity(-200);
  driveOneSquare(2.4,true,200);
  pros::delay(1300);
  intakeA.move_velocity(0);

  driveOneSquare(0.62,false,150);
  pros::delay(500);

  right(1.35);
  pros::delay(500);

  leftFrontA.move_velocity(50);
  leftBackA.move_velocity(50);
  rightFrontA.move_velocity(50);
  rightBackA.move_velocity(50);
  pros::delay(1500);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);


  leftFrontA.set_brake_mode(MOTOR_BRAKE_HOLD);
  leftBackA.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightFrontA.set_brake_mode(MOTOR_BRAKE_HOLD);
  rightBackA.set_brake_mode(MOTOR_BRAKE_HOLD);
  driveOneSquare(4,true,200);
  pros::delay(600);
  //right(0.25);
  left(0.58);*/


}
