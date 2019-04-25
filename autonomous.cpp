#include "main.h"

pros::Controller masterA(pros::E_CONTROLLER_MASTER);
pros::Motor leftFrontA(6, true);
pros::Motor rightFrontA(3,false);
pros::Motor leftBackA(5, true);
pros::Motor rightBackA(18,false);
pros::Motor puncherA(9,false);
pros::Motor intakeA(19,false);
pros::Motor angleA(13,false);
pros::Motor liftA(20,false);

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
  driveOneSquare(1.5,true,200);
  pros::delay(1800);

  //back up
  intakeA.move_velocity(200);
  driveOneSquare(2.9,false,150);
  intakeA.move_velocity(0);
  pros::delay(300);
  intakeA.move_velocity(-200);
  //get ready to shoot

  right(1);
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
  right(0.25);
  pros::delay(300);
  driveOneSquare(2.2,true,150);
  pros::delay(600);

  driveOneSquare(2.1,false,200);
  liftA.move_absolute(0,200);
  pros::delay(500);

  left(0.68);
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
  pros::delay(500);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);
  pros::delay(200);

  liftA.move_absolute(0,200);

  leftFrontA.move_velocity(100);
  leftBackA.move_velocity(100);
  rightFrontA.move_velocity(100);
  rightBackA.move_velocity(100);
  pros::delay(220);
  leftFrontA.move_velocity(0);
  leftBackA.move_velocity(0);
  rightFrontA.move_velocity(0);
  rightBackA.move_velocity(0);

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
  right(0.075);
  angleA.move_absolute(40,200);
  pros::delay(300);

  puncherA.move_relative(-1800,200);
  pros::delay(250);
  angleA.move_absolute(350,200);
  intakeA.move_velocity(200);
  while (!((angleA.get_position()<360)&&(angleA.get_position()>340)))
    pros::delay(2);
  pros::delay(400);
  puncherA.move_relative(-1800,200);
  pros::delay(600);

}
