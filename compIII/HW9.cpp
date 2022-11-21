/***********************************************
Author: Daniel Bergeron
Date: 11/18/2022
Purpose: The purpose is to modify the integer guessing game 
we created earlier in the semester using the new programing methods
we've learned
Sources of Help:Class notes
Time Spent: 2hr
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
Date:11/18/2022
Name:Daniel Bergeron
*/
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//need functions to set the privat variables
//neew funcs to compare value and decide which is closer
class Player{
public: 
    Player(): playerGuess(0), toHigh(false){}
    //every func that sets a val must have a virtual func pass it
    virtual int getGuess(void){return 0;}
    virtual void setMax(int max) = 0;
    virtual void setMin(int min) = 0;
    void setPlayerGuess(int guess){playerGuess = guess;} 
    int getPlayerGuess(void){return playerGuess;}  
    void setToHigh(bool high){toHigh = high;}
    bool getToHigh(void){return toHigh;}
private:
    int playerGuess; 
    bool toHigh;
};

class HumanPlayer : public Player{
public:
    int getGuess(void) override{
        int guess = 0;
        while(guess <= 0  || guess >= 100){
            //cout << "Please Enter the number of guesses(greater than 0, less than 100)!\n";
            cin >> guess;
            setPlayerGuess(guess);
        }
        return guess;
    }
    void setMax(int max)override{return;}
    void setMin(int min)override{return;}
};

class ComputerPlayer : public Player{
public:
    ComputerPlayer(): _Max(100), _Min(0){}
    int getGuess(void) override {
        int guess = rand() % (_Max + 1 - _Min) + _Min;
        cout << "The computer guesses: " << guess << endl;
        setPlayerGuess(guess);
        return guess;
    }
    void setMax(int max)final{_Max = max-1;}
    void setMin(int min)final{_Min = min+1;}
private:
    int _Max;
    int _Min;
};
//compares p1 and p2, p1 modules behavior after p2
void determineRange(Player &p1,Player &p2){
    //both high
    if(p1.getToHigh() && p2.getToHigh()){
        if(p1.getPlayerGuess() < p2.getPlayerGuess()){
            p2.setMax(p1.getPlayerGuess());
        } else {
            p2.setMax(p2.getPlayerGuess());
        }
    } else if (!(p1.getToHigh() || p2.getToHigh())){
        //both low 
        if(p1.getPlayerGuess() <= p2.getPlayerGuess()){
            p2.setMin(p2.getPlayerGuess());
        } else {
            p2.setMin(p1.getPlayerGuess());
        }
    }else if(p2.getToHigh() && !(p1.getToHigh())){
       //computer high player low
       p2.setMax(p2.getPlayerGuess());
       p2.setMin(p1.getPlayerGuess());
    }else if(p1.getToHigh() && !(p2.getToHigh())){
        //computer low player high
        p2.setMin(p2.getPlayerGuess());
        p2.setMax(p1.getPlayerGuess());
    }
    return;
}

//////////////////////////////////////
// Global functions given in project
//////////////////////////////////////
bool checkForWin(int guess, int answer, Player &p1)
{
    if (answer == guess){
        cout << "You're right! You win!" << endl;
        return true;
    } else if (answer < guess){
        cout << "   Your guess is too high." << endl;
        p1.setToHigh(true);
    } else {
        cout << "   Your guess is too low." << endl;
        p1.setToHigh(false);
    }
    return false;
}

// The play function takes as input two Player objects.
void play(Player &player1, Player &player2) {
    int answer = 0, guess = 0;
    answer = rand() % 100;
    bool win = false;
    while (!win)
    {
        cout << "Player 1's turn to guess. ";
        guess = player1.getGuess();
        win = checkForWin(guess, answer, player1);
        if (win) return;
        cout << "Player 2's turn to guess. ";
        guess = player2.getGuess();
        win = checkForWin(guess, answer, player2);
        determineRange(player1, player2);
    }
}

int main(int agrc, char* argv[]){
    srand(time(NULL));
    HumanPlayer p1;
    ComputerPlayer p2;
    play(p1, p2);
    return 0;
}