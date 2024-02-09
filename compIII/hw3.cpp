#include <iostream>
using namespace std;
/***********************************************
Author: Daniel Bergeron
Date: 9/21/2022
Purpose: This Program will create a point class 
which allows users to set point in space and time

Sources of Help: class recordings
Time Spent: 30mins
***********************************************/
/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 9/21/2022
Name: Daniel Bergeron
*/

class Point {
public: 
	//sets the x & y cordinate 
	void set_point(int x_cordinate, int y_cordinate);
	
	//outputs current point
	void display_point(void);
	
	//retrieves x & y point from class
	int get_point_x(void);
	int get_point_y(void);
	
	//moves point specified amout on x & y axis
	void move_point(int x_cordinate,int y_cordinate);
	
	//rotates point 90 degrees about the origin
	void rotate_point(void);
private:
	int x;
	int y;
};

//driver
int main(int argv, char* argc[])
{
	Point a1;
	a1.set_point(0, 0);
	a1.display_point();
	a1.move_point(1, 2);
	a1.display_point();
	a1.rotate_point();
	a1.display_point();
	a1.rotate_point();
	a1.display_point();
	a1.rotate_point();
	a1.display_point();
	a1.rotate_point();
	cout << a1.get_point_x() << "," << a1.get_point_y() << endl;
	return 0;
}

//member func defs
void Point::set_point(int x_cordinate, int y_cordinate)
{
	x = x_cordinate;
	y = y_cordinate;
	return;
}

void Point::display_point(void) 
{
	cout << " (" << get_point_x() << "," << get_point_y() << ") " << endl;
	return;
}

int Point::get_point_x(void)
{
	return x;
}

int Point::get_point_y(void)
{
	return y;
}

void Point::move_point(int x_cordinate, int y_cordinate)
{
	x = x + x_cordinate;
	y = y + y_cordinate;
	return;
}

void Point::rotate_point(void)
{
	int temp = x;
	x = y - (2 * y);
	y = temp;
	return;
}





