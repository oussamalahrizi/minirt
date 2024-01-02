#include "header.h"



float dot_product(t_vec3 a, t_vec3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_vec3 cross(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.y * b.z) - (a.z * b.y);
	new.y = (a.z * b.x) - (a.x * b.z);
	new.z = (a.x * b.y) - (a.y * b.x);
	return (new);
}



t_vec3 vec_sub(t_vec3 a, t_vec3 b)
{
	return ( (t_vec3) {a.x - b.x, a.y - b.y, a.z - b.z} );
}

t_vec3 vec_add(t_vec3 a, t_vec3 b)
{
	return ( (t_vec3) {a.x + b.x, a.y + b.y, a.z + b.z} );
}

t_vec3 new_vector(float x, float y, float z)
{
	return ((t_vec3) {x, y, z});
}

void copy_vec_values(t_vec3 *a, t_vec3 *b)
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
}

t_vec3 reflect(t_vec3 d, t_vec3 normal)
{
	return normalized(vec_sub(d,
		scale_vector(normal, 2.0f * dot_product(d, normal))));
}

t_vec3 get_rotation_vector(t_vec3 *normal)
{
    if (normal)
    {
        float x = atan2(normal->y, -normal->z);
    	float y = atan2(-normal->x, sqrtf(square(normal->y) + square(normal->z)));
    	float z = atan2(normal->x, normal->y);
		return (new_vector(x, y, z));
    }
    return (new_vector(0, 0, 0));
}

t_vec3 get_up_vector(t_vec3 forward)
{
    t_vec3	up;
	float		d;

	up = (t_vec3){0, 1, 0};
	d = dot_product(up, forward);
	if (d > 0.9)
		up = (t_vec3){0, 0, 1};
	else if (d < -0.9)
		up = (t_vec3){0, 0, -1};
	return (up);
}

void print_vector(t_vec3 a)
{
	printf("%f %f %f\n", a.x, a.y, a.z);
}
