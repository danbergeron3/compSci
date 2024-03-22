//-----------------------------------------------------------------------------
// Course: COMP.4270
// Instructor: Krishnan Seetharaman
// DDA Algorithm for lines
// From Foley, van Dam et al., Second Edition in C, Page 75
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <math.h> 

// to compile
// gcc -o dda dda.c -lm
//

//DD A Function for line generation 
void DDA(int x0, int y0, int x1, int y1) 
{ 
    int x;

    double dy = y1 - y0;
    double dx = x1 - x0;
    double m = dy / dx;
    double y = y0;

    for (x = x0; x <= x1; x++) {
        printf("x=%d, y=%ld\n", x, (long)round(y));
        y = y + m;
    }
} 

// main program 
int main() 
{ 
    int x0 = 1;
    int y0 = 2;
    int x1 = 20;
    int y1 = 8; 
    
    DDA(x0, y0, x1, y1);
    
    return 0; 
} 

