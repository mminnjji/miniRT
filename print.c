#include "print.h"
#include <math.h>

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
// [0,1] 로 되어있는 rgb 값을 각각 [0,255]에 맵핑 해서 출력.
void    write_color(t_color3 pixel_color)
{
	double cc[3];
	double scale;

	scale = 0.01;
	cc[0] = sqrt(pixel_color.x * scale);
	cc[1] = sqrt(pixel_color.y * scale);
	cc[2] = sqrt(pixel_color.z * scale);
    printf("%d %d %d\n", (int)(255.999 * clamp(cc[0], 0.0, 0.999)),
                        (int)(255.999 * clamp(cc[1], 0.0, 0.999)),
                        (int)(255.999 * clamp(cc[2], 0.0, 0.999)));
}