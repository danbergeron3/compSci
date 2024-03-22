#include <stdio.h>

typedef struct point_s {
    double x;
    double y;
} point;

#define PRINT_XY(x,y)     printf("x=%lf y=%lf\n", x, y)
#define PRINT_TXY(t,x,y)  printf("t=%lf x=%lf y=%lf\n", t, x, y)
#define PRINT_POINT(p)    printf("x=%lf y=%lf\n", p.x, p.y)


// n: how many subdivisions for t in the range [0,1]
void hermite(int n, point p1, point p4, point r1, point r4)
{

    int i;
    double x, y, z;
    double delta = 1.0/(double)n;
    double t;

    printf("HERMITE: \n");
    printf("p1: "); PRINT_POINT(p1);
    printf("p4: "); PRINT_POINT(p4);
    printf("r1: "); PRINT_POINT(r1);
    printf("r4: "); PRINT_POINT(r4);
    printf("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    PRINT_TXY(t,x,y);
    for (i = 0; i < n; i++) {
        t += delta;
        double t2 = t * t;
        double t3 = t2 * t;

        x = ((2*t3)-(3*t2)+1)*p1.x + ((-2*t3)+(3*t2))*p4.x + (t3-(2*t2)+t)*r1.x + (t3-t2)*r4.x;
        y = ((2*t3)-(3*t2)+1)*p1.y + ((-2*t3)+(3*t2))*p4.y + (t3-(2*t2)+t)*r1.y + (t3-t2)*r4.y;
        PRINT_TXY(t,x,y);
    }
    printf("\n\n");
}

// n: how many subdivisions for t in the range [0,1]
void bezier(int n, point p1, point p2, point p3, point p4)
{

    int i;
    double x, y, z;
    double delta = 1.0/(double)n;
    double t;

    printf("BEZIER: \n");
    printf("p1: "); PRINT_POINT(p1);
    printf("p2: "); PRINT_POINT(p2);
    printf("p3: "); PRINT_POINT(p3);
    printf("p4: "); PRINT_POINT(p4);
    printf("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    PRINT_TXY(t,x,y);
    for (i = 0; i < n; i++) {
        t += delta;
        double t2 = t * t;
        double t3 = t2 * t;
           
        double q1=(1-t);
        double q2=q1*q1;
        double q3=q2*q1;
        x = q3*p1.x + (3*t*q2)*p2.x + (3*t2*q1)*p3.x + t3*p4.x;
        y = q3*p1.y + (3*t*q2)*p2.y + (3*t2*q1)*p3.y + t3*p4.y;
        PRINT_TXY(t,x,y);
    }
    printf("\n\n");
}

// n: how many subdivisions for t in the range [0,1]
void spline(int n, point p1, point p2, point p3, point p4)
{

    int i;
    double x, y, z;
    double delta = 1.0/(double)n;
    double t;

    printf("SPLINE: \n");
    printf("p1: "); PRINT_POINT(p1);
    printf("p4: "); PRINT_POINT(p2);
    printf("r1: "); PRINT_POINT(p3);
    printf("r4: "); PRINT_POINT(p4);
    printf("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    PRINT_TXY(t,x,y);
    for (i = 0; i < n; i++) {
        t += delta;
        double t2 = t * t;
        double t3 = t2 * t;

        x = (((1-t3)/6)*p1.x)+(((3*t3-6*t2+4)/6)*p2.x)+(((-3*t3+3*t2+3*t+1)/6)*p3.x)+((t3/6)*p4.x);
        y = (((1-t3)/6)*p1.y)+(((3*t3-6*t2+4)/6)*p3.y)+(((-3*t3+3*t2+3*t+1)/6)*p3.y)+((t3/6)*p4.y);
        
        PRINT_TXY(t,x,y);
    }
    printf("\n\n");
}

int main(int argc, char* argv[])
{
    int n = 100;
    point p1;
    point p4;
    point r2;
    point r3;

    p1.x=10;
    p1.y=20;
    p4.x=100;
    p4.y=40;
    r2.x=30;
    r2.y=30;
    r3.x=20;
    r3.y=70;

    hermite(n, p1, p4, r2, r3);
    bezier(n, p1, p4, r2, r3);
    spline(n, p1, p4, r2, r3);
}

