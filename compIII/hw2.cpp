//C:\Users\Danie\source\repos\HW2\input.txt

/***********************************************
Author: Daniel Bergeron
Date: 9/15/2022
COMP.2010 HW 02 F22 - Dr. Lin
Purpose: This program will open a file, read its contents and print it to an
output file, the program will also attempt to change some words before sending the strings 
to the output stream. 
Sources of Help: absolute C++, https://cplusplus.com/reference/string/string/
Time Spent: 
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
Date: 9/15/2022
Name: Daniel Bergeron
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[])
{
	ifstream inStream;
	string key = "dislike";
	string word;
	
	inStream.open("input.txt");
	if (inStream.fail()) {
		cout << "Error: Input file failed to open\n";
		exit(1);
	}
	
	inStream >> word;
	while (!inStream.eof())
	{
		if (key == word)
		{
			word = "love";
		}
		cout << " " << word;
		inStream >> word;
	}

	inStream.close();
	return 0;
}
