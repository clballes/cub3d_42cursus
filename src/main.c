#include "cub3d.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    double angle = 24; // Angle in degrees
    double radians = angle * (M_PI / 180.0); // Convert angle from degrees to radians
    double sine = sin(radians);

    printf("The sine of %lf degrees is: %lf\n", angle, sine);
    return 0;
}