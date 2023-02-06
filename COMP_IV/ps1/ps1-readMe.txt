/**********************************************************************
 *  Linear Feedback Shift Register (part A) ps1a-readme.txt template
 **********************************************************************/

Name: Daniel Bergeron 
Hours to complete assignment: 15
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.

 **********************************************************************/
In this assignment I created a class that uses a binary string to 
construct an object that emulates a linear Feedback register with 3 tap 
points. With this program I can take a string input and create pseudo-
randomness.  I created step funtion to simulate a single shift and return
the new random value. Also a generate function to simulate many steps in 
additon it will return a number bassed on the bits produced 
/**********************************************************************
 *  Explain the representation you used for the register bits 
 *  (how it works, and why you selected it)
 **********************************************************************/
First I created a short int data type to store the registers bits, 
but I soon discovered a the bitset container and decided to
go with that since it is more in line with how CPP is meant to be used. 
I am used to C approach to problems so I wanted to do this project from 
a diffirent lens. This container could take bit strings of any size and
store them, in addtion it supports random access, this made it an ideal
canadate for my representation. 
/**********************************************************************
 * Discuss what's being tested in your two additional Boost unit tests
  **********************************************************************/
My first test is a the zero test which checks if given a string of all 0s
only 0's would be produced. Since the XOR gates in the tap will always evaluate
to zero. This is a good edge case to check because if you get a 1(or anything else) 
you know the LFSR is broken.

My second test is a ones tests, this test the edge case when the string is all 1's 
this case simply says that if the seed is all ones the only values that should be produced 
are zeros until the first zero producedis shifted into the tap at which point you 
you can predict that the following value will be a one which will therefore sustain the 
pseudo randomness.
/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
Looked up make file tutorials on youtube, used stackOverflow for troubles
shooting. Used links in the project handout.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
Unfortunate situation led to the all my files being deleted they where not 
recovered. Was forced to recode everything quickly so some aspects of the 
code may seem rushed.
/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/