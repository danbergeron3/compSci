/*
Mobile App Development I -- COMP.4630 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and training as a practicing computing
professional upon graduation. This practice is manifested in the
University's Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations
will be dealt with as outlined therein. All programming assignments
in this class are to be done by the student alone unless otherwise
specified. No outside help is permitted except the instructor and
approved tutors.
COMP 4630 Lecture 4 Class Exercise – Interactive UI
I certify that the work submitted with this assignment is mine
and was generated in a manner consistent with this document, the
course academic policy on the course website on Blackboard, and
the UMass Lowell academic code.
Date: 9/18/2023
Name: Daniel Bergeron
*/
package com.mobileapp.lecture04exer;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button updateButton = findViewById(R.id.button);
        updateButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {
                Spinner getSpinner = findViewById(R.id.spinner1);
                TextView text = findViewById(R.id.text);
                text.setTextColor(getColor(getSpinner.getSelectedItem().toString()));
                EditText getEditText = findViewById(R.id.editWordText);
                text.setText(getEditText.getText().toString());
            }
        });

    }
    static int getColor(String color_name) {
        switch (color_name){
            case "black":
                return Color.BLACK;
            case "blue":
                return Color.BLUE;
            case "gray":
                return Color.GRAY;
            case "yellow":
                return Color.YELLOW;
            case "red":
                return Color.RED;
        };
        return Color.BLACK;
    }
}