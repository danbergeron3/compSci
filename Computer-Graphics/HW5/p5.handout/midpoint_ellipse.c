//-----------------------------------------------------------------------------
// Course: COMP.4270
// Instructor: Krishnan Seetharaman
// Midpoint Algorithm for ellipses
// From Foley, van Dam et al., Second Edition in C, Page 90
//-----------------------------------------------------------------------------

#include <stdio.h> 
#include <math.h> 

// to compile
// gcc -o midpoint_ellipse midpoint_ellipse.c

void EllipsePoints(int x, int y)
{
    printf("x=%d, y=%d\n", x, y);
    printf("x=%d, y=%d\n", -x, y);
    printf("x=%d, y=%d\n", x, -y);
    printf("x=%d, y=%d\n", -x, -y);
}

// midpoint algorith for ellipses; assumes center is at (0, 0);
void MidpointEllipse(int a, int b) 
{ 
    double d2;
    int x = 0;
    int y = b;
    double d1 = (b*b) - (a*a*b) + (0.25*a*a);
    
    EllipsePoints(x, y);
  
    // test gradient if still in region 1
    while (((a*a)*(y-0.5)) > ((b*b)*(x+1))) {
        if (d1 < 0) {
            d1 = d1 + ((b*b)*(2*x+3));
        }
        else {
            d1 = d1 + ((b*b)*(2*x+3)) + ((a*a)*(-2*y+2));
            y--;
        }
        x++;
        EllipsePoints(x, y);
    }   // Region 1
    
    d2 = ((b*b)*(x+0.5)*(x+0.5))+((a*a)*(y-1)*(y-1))-(a*a*b*b);
    while (y > 0) {
        if (d2 < 0) {
            d2 = d2 + ((b*b)*(2*x+2)) + ((a*a)*(-2*y+3));
            x++;
        }
        else {
            d2 = d2 + ((a*a)*(-2*y+3));
        }
        y--;
        EllipsePoints(x, y);
    }   // Region 2
} 

// main program 
int main() 
{ 
    int radius = 20;
    
    MidpointEllipse(20, 30);
    
    return 0; 
} 

