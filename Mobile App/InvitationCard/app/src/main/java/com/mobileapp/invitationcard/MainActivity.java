/**********************************************
Mobile App Development I -- COMP.4630 Honor Statement
The practice of good ethical behavior is essential for maintaining good order in the classroom, providing an enriching learning experience for students, and training as a practicing computing professional upon graduation. This practice is manifested in the University's Academic Integrity policy. Students are expected to strictly avoid academic dishonesty and adhere to the Academic Integrity policy as outlined in the course catalog. Violations will be dealt with as outlined therein. All programming assignments in this class are to be done by the student alone unless otherwise specified. No outside help is permitted except the instructor and approved tutors.

I certify that the work submitted with this assignment is mine and was generated in a manner consistent with this document, the course academic policy on the course website on Blackboard, and the UMass Lowell academic code.

Date: 9/16/2023
Name: Daniel Bergeron
*********************************************/
/***********************************************
 Author: Daniel Bergeron
 Date: 9/16/2023
 Purpose: The assignment was designed to test our understanding of linear layouts, as
 well as practice xml concepts such as strings and image.
 What Learned: Learned how to change colors of things in xml, also learned how to
 use custom fonts. custom font from https://www.tigadestd.com/.
 Sources of Help: used the following video to learn about adding fonts
 https://www.youtube.com/watch?v=FvK4diZYmTw
 Time Spent: 2hrs
 Extra Points Explanation:
 Added a cool birthday font to the title of the app
 used the following video to learn about adding fonts
 https://www.youtube.com/watch?v=FvK4diZYmTw
 ***********************************************/

package com.mobileapp.invitationcard;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}