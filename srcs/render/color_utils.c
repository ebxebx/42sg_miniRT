#include "miniRT.h"

t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3	vec3_clamp(t_vec3 v)
{
	if (v.x < 0.0)
		v.x = 0.0;
	if (v.y < 0.0)
		v.y = 0.0;
	if (v.z < 0.0)
		v.z = 0.0;
	if (v.x > 1.0)
		v.x = 1.0;
	if (v.y > 1.0)
		v.y = 1.0;
	if (v.z > 1.0)
		v.z = 1.0;
	return (v);
}

int	pack_color(t_vec3 color)
{
	color = vec3_clamp(color);
	return (((int)(color.x * 255.999) << 16)
		| ((int)(color.y * 255.999) << 8)
		| (int)(color.z * 255.999));
}
