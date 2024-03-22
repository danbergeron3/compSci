//-----------------------------------------------------------------------------
// Course: COMP.4270
// Instructor: Krishnan Seetharaman
// Midpoint Algorithm for circles
// From Foley, van Dam et al., Second Edition in C, Page 82, 86
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <math.h> 

// to compile
// gcc -o midpoint_circle2 midpoint_circle2.c
//

void CirclePoints(int x, int y)
{
    printf("x=%d, y=%d\n", x, y);
    printf("x=%d, y=%d\n", y, x);
    printf("x=%d, y=%d\n", y, -x);
    printf("x=%d, y=%d\n", x, -y);
    printf("x=%d, y=%d\n", -x, -y);
    printf("x=%d, y=%d\n", -y, -x);
    printf("x=%d, y=%d\n", -y, x);
    printf("x=%d, y=%d\n", -x, y);
}

// midpoint algorith for circles; assumes center is at (0, 0);
void MidpointCircle(int radius) 
{ 
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    CirclePoints(x, y);
    
    while (y > x) {
        if (d < 0) {
            d = d + 2 * x + 3;
        }
        else {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        CirclePoints(x, y);
    }
} 

// main program 
int main() 
{ 
    int radius = 20;
    
    MidpointCircle(radius);
    
    return 0; 
} 

