#include "main.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor leftFront(6, true);
pros::Motor rightFront(3,false);
pros::Motor leftBack(5, true);
pros::Motor rightBack(18,false);
pros::Motor puncher(9,false);
pros::Motor intake(19,false);
pros::Motor angle(16,false);
pros::Motor lift(20,false);

pros::ADIDigitalIn iLimitA('h');
pros::ADIDigitalIn pLimitA('a');

void driveOneSquare(double squares, bool forward, int speed)
{
    if(forward==false)
    {
      leftFrontA.move_velocity(180);
      rightFrontA.move_velocity(180);
      leftBackA.move_velocity(180);
      rightBackA.move_velocity(180);
      pros::delay(333*squares);
    }
    else
    {
      leftFrontA.move_velocity(-180);
      rightFrontA.move_velocity(-180);
      leftBackA.move_velocity(-180);
      rightBackA.move_velocity(-180);
      pros::delay(333*squares);
    }
    leftFrontA.move_velocity(0);
    rightFrontA.move_velocity(0);
    leftBackA.move_velocity(0);
    rightBackA.move_velocity(0);
}
void left(double amount)
{
  leftFrontA.move_velocity(100);
  rightFrontA.move_velocity(-100);
  leftBackA.move_velocity(100);
  rightBackA.move_velocity(-100);
  pros::delay(440*amount);
  leftFrontA.move_velocity(0);
  rightFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightBackA.move_velocity(0);
}
void right(double amount)
{
  leftFrontA.move_velocity(-100);
  rightFrontA.move_velocity(100);
  leftBackA.move_velocity(-100);
  rightBackA.move_velocity(100);
  pros::delay(440*amount);
  leftFrontA.move_velocity(0);
  rightFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightBackA.move_velocity(0);
}
void autonomous()
{
  liftA.tare_position();
  intakeA.set_brake_mode(MOTOR_BRAKE_BRAKE);
  intakeA.tare_position();

  puncherA.tare_position();
  puncherA.move_absolute(-1200,200);

  leftFrontA.set_brake_mode(MOTOR_BRAKE_COAST);
  leftBackA.set_brake_mode(MOTOR_BRAKE_COAST);
  rightFrontA.set_brake_mode(MOTOR_BRAKE_COAST);
  rightBackA.set_brake_mode(MOTOR_BRAKE_COAST);

  //intake
  intakeA.move_velocity(200);
  driveOneSquare(1.4,true,200);
  pros::delay(1500);

  //back up
  intakeA.move_velocity(200);
  driveOneSquare(3,false,150);
  intakeA.move_velocity(0);
  pros::delay(300);
  intakeA.move_velocity(-200);
  //get ready to shoot

  left(0.99);
  angleA.move_absolute(0,200);
  pros::delay(300);

  puncherA.move_relative(-1800,200);
  pros::delay(250);
  angleA.move_absolute(350,200);
  intakeA.move_velocity(200);
  while (!((angleA.get_position()<360)&&(angleA.get_position()>340)))
    pros::delay(2);
  pros::delay(400);
  puncherA.move_relative(-1800,200);
  intakeA.move_velocity(0);
  pros::delay(400);

  liftA.move_absolute(400,200);
  left(0.2);
  pros::delay(300);
  driveOneSquare(2.2,true,150);
  pros::delay(600);

  driveOneSquare(2.2,false,200);
  liftA.move_absolute(0,200);
  pros::delay(500);

  right(0.71);
  pros::delay(300);
  angleA.move_absolute(0,200);
  leftFrontA.move_velocity(-80);
  leftBackA.move_velocity(-80);
  rightFrontA.move_velocity(-80);
  rightBackA.move_velocity(-80);
  pros::delay(880);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);
  pros::delay(400);

  liftA.move_absolute(700,200);
  pros::delay(400);
  intakeA.move_velocity(200);
  leftFrontA.move_velocity(100);
  leftBackA.move_velocity(100);
  rightFrontA.move_velocity(100);
  rightBackA.move_velocity(100);
  pros::delay(720);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);
  pros::delay(200);
  leftFrontA.move_velocity(-100);
  leftBackA.move_velocity(-100);
  rightFrontA.move_velocity(-100);
  rightBackA.move_velocity(-100);
  pros::delay(200);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);
  pros::delay(1500);

  intakeA.move_velocity(-200);
  right(0.05);
  angleA.move_absolute(0,200);
  pros::delay(300);

  puncherA.move_relative(-1800,200);
  pros::delay(250);
  angleA.move_absolute(350,200);
  intakeA.move_velocity(200);
  while (!((angleA.get_position()<360)&&(angleA.get_position()>340reerq)))
    pros::delay(2);
  pros::delay(400);
  puncherA.move_relative(-1800,200);
  pros::delay(600);

  driveOneSquare(0.7,false,200);
  pros::delay(500);
/*
  puncherA.move_relative(-1800,200);
  pros::delay(250);
  angleA.move_absolute(350,200);
  intakeA.move_velocity(200);
  while (!((angleA.get_position()<360)&&(angleA.get_position()>340)))
    pros::delay(2);
  pros::delay(400);
  puncherA.move_relative(-1800,200);

  liftA.tare_position();
  liftA.move_absolute(700,200);
  pros::delay(400);

  driveOneSquare(1.4,false,150);
  pros::delay(400);
  liftA.move_absolute(0,200);

  left(0.65);
  angleA.move_absolute(0,200);
  pros::delay(400);

  puncherA.move_relative(-1800,200);
  pros::delay(250);
  angleA.move_absolute(350,200);
  intakeA.move_velocity(200);
  while (!((angleA.get_position()<360)&&(angleA.get_position()>340)))
    pros::delay(2);
  pros::delay(400);
  puncherA.move_relative(-1800,200);*/
}
