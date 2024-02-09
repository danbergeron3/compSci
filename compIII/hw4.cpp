/***********************************************
Author: Daniel Bergeron
Date: 9/24/2022
Purpose: Program creates a class to represent a zipcode, it stores the the
zip as an integer. The zip code can also be created by representing the code as
a barcode, which the class converts and stores as an int, the class allows user too
access the zip in its number form or access it as a string of ones and zeros. The user 
not have the ability to modify it once an object is created
Sources of Help: string library, book, class, notes 
Time Spent: 8h
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
Date:9/24/2022
Name:Daniel Bergeron
*/
#include <iostream>
#include <string>
#include<cmath>
using namespace std;

class ZipCode {
public:
    //constructors
    ZipCode(int zipcode);
    ZipCode(string barcode);
    //accesors
    string getBarCode(void) const;
    int getZipCode(void) const;
private:
    //function combines the numbers in an int array and returns the value
    int convert_list_to_number(int number[], int length);
    //function takes a string checks if its valid and returns an integer value
    int convert_barcode_to_zipcode(string barcode);
    int zip;
};

int const BARCODE_SEGMENT = 5;
int const BARCODE_ZERO = 11;
int const ZIPCODE_LENGTH = 5;
int const BARCODE_LENGTH = 27;

int main(int argc, char* argv[]) {
    ZipCode zip(99504),
        zip2("100101010011100001100110001"),
        zip3(12345),
        zip4(67890);

    cout << zip.getZipCode() << "'s bar code is '"
        << zip.getBarCode() << "'" << endl;
    cout << zip2.getZipCode() << "'s bar code is '"
        << zip2.getBarCode() << "'" << endl;
    cout << zip3.getZipCode() << "'s bar code is '"
        << zip3.getBarCode() << "'" << endl;
    cout << zip4.getZipCode() << "'s bar code is '"
        << zip4.getBarCode() << "'" << endl;

    cout << endl;

    // Test a range of values by first constructing a zip code
    // with an integer, then retrieving the bar code and using
    // that to construct another ZipCode.
    int zip_int = 0;
    for (int i = 0; i < 25; i++)
    {
        // Make an aribrary 5-digit zip code integer, and use it
        // to construct a ZipCode
        int five_digit_zip = (zip_int * zip_int) % 100000;
        ZipCode z1(five_digit_zip);

        // Construct a second ZipCode from the first's bar code
        string z1_barcode = z1.getBarCode();
        ZipCode z2(z1_barcode);

        cout.width(3);
        cout << (i + 1) << ": ";
        cout.width(5);
        cout << z2.getZipCode() << " has code '"
            << z1_barcode << "'";

        if ((z1_barcode == z2.getBarCode()) &&
            (z1.getZipCode() == z2.getZipCode()) &&
            (z2.getZipCode() == five_digit_zip))
        {
            cout << " [OK]" << endl;
        }
        else
        {
            cout << " [ERR]" << endl;
        }

        // Increment the test value arbitrarily
        zip_int += (233 + zip_int % 7);
    }
    cout << endl;

    // Test some error conditions. This test assumes that
    // ZipCode will simply set its value to a flag that indicates
    // an error, and will not exit the program.
    int BAD_ZIP_COUNT = 2;
    string bad_zips[][2] = {
        { "100101010011100001100110000", "bad start/end character" },
        { "100101010011100001100110021", "bad digit" },
    };
    for (int i = 0; i < BAD_ZIP_COUNT; i++)
    {
        cout << "Testing: " << bad_zips[i][1] << " " << bad_zips[i][0] << endl;
        ZipCode test(bad_zips[i][0]);
        cout << endl;
    }

    cout << "Enter a character to quit." << endl;
    char c;
    cin >> c;
    return 0;
}

ZipCode::ZipCode(int iZipcode)
{
    zip = iZipcode;
}

ZipCode::ZipCode(string barcode)
{
    zip = convert_barcode_to_zipcode(barcode);
}
string ZipCode::getBarCode(void) const
{
    //uses postional weight, division & modulous 
    //to pull out zipcodes digits 
    int zipCode_digits[ZIPCODE_LENGTH];
    int weight = ZIPCODE_LENGTH - 1;
    int zip_copy = zip;

    for (int i = 0; i < ZIPCODE_LENGTH; i++)
    {
        int divider = pow(10, weight);
        zipCode_digits[i] = (zip_copy / divider);
        zip_copy = zip_copy % divider;
        weight--;
    }

    //analyze each segment & create string
    //caclulate binary value by dividing,
    int barToDigitKey[] = { 7, 4, 2, 1, 0 };
    string barcode;
    barcode += '1';
    for (int i = 0; i < ZIPCODE_LENGTH; i++)
    {
        //stores numbers in various temps to manipulate values
        //uses j to iterate through key, and counter is used to
        //ensure each barcode segment only has two ones if counter 
        //reaches two program fills segment with zero, if it doesent,
        //last spot will be one
        int zip_single_digit = zipCode_digits[i];
        int temp = zipCode_digits[i], temp2 = zipCode_digits[i];
        int j = 0;
        int counter = 0;
        while (j < BARCODE_SEGMENT - 1)
        {
            if (zip_single_digit == 0)
            {
                barcode += "11000";
                counter = 3;
                break;
            }
            else if (counter < 2)
            {
                temp = temp2 / barToDigitKey[j];
                if (temp == 0)
                {
                    barcode += '0';
                }
                else
                {
                    barcode += '1';
                    counter++;
                    temp2 = zip_single_digit % barToDigitKey[j];
                }
            }
            else
            {
                barcode += '0';
            }
            j++;
        }
        if (counter == 2)
        {
            barcode += '0';
        }
        else if (counter < 2)
        {
            barcode += '1';
        }
    }
    //adds 1 to the ending to complete barcode
    barcode += '1';
    return barcode; 
}
int ZipCode::getZipCode(void) const
{
    return zip;
}
int ZipCode::convert_list_to_number(int array_number[], int length)
{
    //multiplies number by positional weight to give it its spot in
    //the new integer
    int number = 0;
    int weight = length - 1;
    for (int i = 0; i < length; i++)
    {
        number = number + array_number[i] * pow(10, weight);
        weight--;
    }
    return number;
}

int ZipCode::convert_barcode_to_zipcode(string barcode)
{
    int segment_index = 0, number_position = 0;
    int barToDigitKey[] = { 7, 4, 2, 1, 0 };
    bool error = false;
    char barcode_segment[BARCODE_SEGMENT];
    int zipCodeDigits[BARCODE_SEGMENT];
    //checks begaining & end for possible error
    //then uses for loop to chop up and sum each string
    if (barcode[0] == '1' && barcode[barcode.length() - 1] == '1')
    {

        for (int i = 1; i < barcode.length(); i++)
        {
            //fill string with barcode chars and check for error
            if (barcode[i] != '0' && barcode[i] != '1')
            {
                cout << "Wrong barcode! A barcode can only contain '0' and '1'.\n";
                error = true;
            }
            if (segment_index < BARCODE_SEGMENT)
            {
                barcode_segment[segment_index] = barcode[i];
                segment_index++;
            }
            else if (segment_index == BARCODE_SEGMENT)
            {
                //calculate the sum, store it and reset segment, 
                //calcualte assume string full 
                int j = 0;
                int key_index = 0;
                int sum = 0;

                while (j < BARCODE_SEGMENT)
                {
                    if (barcode_segment[j] == '1')
                    {
                        sum = sum + barToDigitKey[key_index];
                    }
                    key_index++;
                    j++;
                }
                if (sum == BARCODE_ZERO)
                {
                    zipCodeDigits[number_position] = 0;
                }
                else
                {
                    //store digits value & moves array to next position
                    zipCodeDigits[number_position] = sum;
                }
                number_position++;
                //resets segmet_index
                segment_index = 0;
                i--;
            }
            else
            {
                cout << "ERROR THE STRING IS OUT OF BOUNDS!\n";
            }
        }
        if (!error)
        {
            return convert_list_to_number(zipCodeDigits, BARCODE_SEGMENT);
        }
    }
    cout << "Wrong start / end character in the barcode!\n";
    return -1;
}