#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <wiringPi.h>

class GPIO{
	public:
		GPIO();
		void forward();
		void reverse();
		void left();
		void right();
		void close();
};

GPIO::GPIO(){
	wiringPiSetup();
	pinMode(0, OUTPUT);
	pinMode(2, INPUT);
	pinMode(8, OUTPUT);
	pinMode(9, INPUT);
	pinMode(10, OUTPUT);
	pinMode(11, INPUT);

	pinMode(6, OUTPUT);
	digitalWrite(6, LOW);
	pinMode(3, OUTPUT);
	digitalWrite(3, LOW);
	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
	pinMode(5, OUTPUT);
	digitalWrite(5, LOW);
	}

void GPIO::forward(){
	digitalWrite(6, FALSE);
	digitalWrite(3, TRUE);
	digitalWrite(4, FALSE);
	digitalWrite(5, TRUE);
	}

void GPIO::reverse(){
	digitalWrite(6, TRUE);
	digitalWrite(3, FALSE);
	digitalWrite(4, TRUE);
	digitalWrite(5, FALSE);
	}

void GPIO::left(){
	digitalWrite(6, FALSE);
	digitalWrite(3, TRUE);
	digitalWrite(4, FALSE);
	digitalWrite(5, FALSE);
	}

void GPIO::right(){
	digitalWrite(6, FALSE);
	digitalWrite(3, FALSE);
	digitalWrite(4, FALSE);
	digitalWrite(5, TRUE);
	}

void GPIO::close(){
	digitalWrite(6, FALSE);
	digitalWrite(3, FALSE);
	digitalWrite(4, FALSE);
	digitalWrite(5, FALSE);
	}

GPIO gpio;

void velcallback(geometry_msgs::Twist::ConstPtr& vel){
	geometry_msgs::Twist new_vel=vel;
	if(new_vel.linear.x>0)
		gpio.forward();
	if(new_vel.linear.x<0)
		gpio.forward();
	if(new_vel.linear.x==0)
		gpio.close();
	if(new_vel.angular.z>0)
		gpio.right();
	if(new_vel.angular.z<0)
		gpio.left();
	if(new_vel.angular.z==0)
		gpio.close();
}

int main(int argc, char **argv)
{

ros::init(argc, argv, "robotcar_vel_subsriber");
ros::NodeHandle n;

ros::Subscriber sub=n.subscribe("robotcar_vel_pub", 10, velcallback);

ros::spin();

return 0;
}







