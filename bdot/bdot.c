#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846
#define DEG2RAD (PI/180.0)

typedef struct {
    double x;
    double y;
    double z;
} vector;

void bdot_algorithm(vector B, vector Bdot, double *q)
{
    double Bx, By, Bz, Bdotx, Bdoty, Bdotz;
    double normB, normBdot, phi, theta;
    
    Bx = B.x;
    By = B.y;
    Bz = B.z;
    Bdotx = Bdot.x;
    Bdoty = Bdot.y;
    Bdotz = Bdot.z;
    
    normB = sqrt(Bx*Bx + By*By + Bz*Bz);
    normBdot = sqrt(Bdotx*Bdotx + Bdoty*Bdoty + Bdotz*Bdotz);
    
    phi = atan2(Bdoty*normB - By*normBdot, Bdotx*normB - Bx*normBdot);
    theta = asin((Bdotz*normB - Bz*normBdot) / (normB*normBdot));
    
    q[0] = cos(theta/2)*cos(phi/2);
    q[1] = cos(theta/2)*sin(phi/2);
    q[2] = sin(theta/2)*cos(phi/2);
    q[3] = -sin(theta/2)*sin(phi/2);
}

int main()
{
    vector B = {0.0, 0.0, 1.0};
    vector Bdot = {0.0, -1.0, 0.0};
    double q[4];
    
    bdot_algorithm(B, Bdot, q);
    
    printf("q0 = %f, q1 = %f, q2 = %f, q3 = %f\n", q[0], q[1], q[2], q[3]);
    
    return 0;
}

