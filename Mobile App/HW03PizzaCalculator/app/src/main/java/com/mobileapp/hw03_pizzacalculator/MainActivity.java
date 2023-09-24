/******************************************************************
Mobile App Development I -- COMP.4630 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and training as a practicing computing
professional upon graduation. This practice is manifested in the
University's Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein. All programming assignments in
this class are to be done by the student alone unless otherwise
specified. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and
was generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: 9/24/2023
Name: Daniel Bergeron
***********************************************************************
 Author: Daniel Bergeron
 Date: 9/24//2023
 Purpose: The purpose of this homework was to demonstrate proficiency
 with linearLayouts, frame layouts, onclick listeners, editText, textView,
 buttons, and spinners. It required me to use a basic understanding of
 java and xml to make these components aesthetic and functional.
 What Learned: Learned how to deal with input in java from the android api.
 Learned how to make basic methods in java. Learned how to nest layouts, so
 they can work well together.
 Sources of Help: Class notes and exercises, used java point to learn
 how to convert from string to int.
 https://www.javatpoint.com/java-integer-parseint-method
 Time Spent: 3hrs
 Extra Points Explanation: <briefly explain what the surprise is>
 **********************************************************************/

package com.mobileapp.hw03_pizzacalculator;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // get reference to button then set rules for when it is clicked
        Button calculate = findViewById(R.id.button);
        calculate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // variables
                int num_people;
                int multiplier;
                // A temp string to hold different value that will be converted
                String delta_string;

                // Finds references to app objects
                EditText input_num_people = findViewById(R.id.editText1);
                TextView answer_display = findViewById(R.id.textView4);
                Spinner hunger_spinner = findViewById(R.id.spinner);

                // performs pizza calculation
                delta_string = input_num_people.getText().toString();
                num_people = Integer.parseInt(delta_string);
                multiplier = getSpinnerIntValue(hunger_spinner.getSelectedItem().toString());
                delta_string = Integer.toString(calculatePizza(num_people, multiplier));
                answer_display.setText(delta_string);
            }
        });
    }
    static int calculatePizza(int amount, int multiplier) {
        return amount * multiplier;
    }
    static int getSpinnerIntValue(String item) {
        switch (item) {
            case "Light":
                return 2;
            case "Medium":
                return 3;
            case "Ravenous":
                return 4;
            default:
                return 0;
        }
    }
}

