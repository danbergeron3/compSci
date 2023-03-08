/**********************************************************************
 *                                                  
 *  PS2b: Sokoban
 **********************************************************************/

Name: Daniel Bergeron

Hours to complete assignment : 36hrs

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Yes, everything should be working properly.I was able to get the player and 
crates to move. As well the win condtions work. THe player can restart at anytime
for the most part there are no issues and the map seemlisy refreshes without blinking.
I created three test maps of various complexity and tested extensivly on them. The
allowed me to debug all the major issues, as well each map functions the way the 
game has intended. 
/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  
 **********************************************************************/
no
/**********************************************************************
 *  Did your code pass cpplint?
 *  Indicate yes or no, and explain how you did it.
 **********************************************************************/
Yes, ran cpplint through terminal it detected multiple foromating errors
corrected all of them and ran it again it reported no errors.

/**********************************************************************
 *  List whatever help (if any) you received from TAs,
 *  classmates, or anyone else.
 **********************************************************************/
During class disscusions and outside of class disscused the overall design 
of the code and brain stormed ways to implement them. Besides that consulted 
internet on how to use various containers.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
Problems I econuntered  was figuring out how to store textures to speed the 
game up. Also how to create to move player and crate blocks without loosing 
the sprites underneath it. The current only problem I haven't been able to 
solve and isn't game ending, is when the player spams the restart button the 
player object moves to a couple spaces almost like the matrix gets inverted 
and he appears on the wrong axis. 

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
Data structures used: Used maps, vectors, pairs, strings, also built a matrix 
structure using two vectors.
Classes: Used three classes; Sokoban handles the game map information and interactions
on the map; Game object class that holds information about each tile of the map; and
finaly the moveObject which holds information about blocks being moved, that way 
the map dosenlt loose data when objects are being moved.

Lambda: My Lambda expression is used in the isWon() functions.

Algorythm: My Algorythm is used in the isWon() function.

font from: https://www.dafont.com/new.php?page=2