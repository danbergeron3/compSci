//-----------------------------------------------------------------------------
// Course: COMP.4270
// Instructor: Krishnan Seetharaman
// Midpoint Algorithm for lines
// From Foley, van Dam et al., Second Edition in C, Page 78
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <math.h> 

// to compile
// gcc -o midpoint midpoint.c
//

//DD A Function for line generation 
void MidpointLine(int x0, int y0, int x1, int y1) 
{ 
    int dx = x1 - x0;
    int dy = y1 - y0;
    int d = 2 * dy - dx;
    int incrE = 2 * dy;
    int incrNE = 2 * (dy - dx);
    int x = x0;
    int y = y0;
    
    printf("x=%d, y=%d\n", x, y);
    while (x < x1) {
        if (d <= 0) {
            d = d + incrE;
            x++;
        }
        else {
            d = d + incrNE;
            x++;
            y++;
        }
        printf("x=%d, y=%d\n", x, y);
    }
} 

// main program 
int main() 
{ 
    int x0 = 1;
    int y0 = 2;
    int x1 = 20;
    int y1 = 8; 
    
    MidpointLine(x0, y0, x1, y1);
    
    return 0; 
} 

