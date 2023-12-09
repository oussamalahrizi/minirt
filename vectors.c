#include "header.h"

float length2(t_vec3 *a)
{
	return (pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

float length(t_vec3 *a)
{
	return (sqrtf(length2(a)));
}

float normalize(t_vec3 *a)
{
	float l;

	l = length(a);
	if (l != 0)
	{
		a->x /= l;
		a->y /= l;
		a->z /= l;
	}
	return (l);
}

t_vec3 normalized(t_vec3 a)
{
	t_vec3 new;

	copy_vec_values(&new, &a);
	normalize(&new);
	return (new);
}

float dot_product(t_vec3 *a, t_vec3 *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_vec3 cross(t_vec3 *a, t_vec3 *b)
{
	t_vec3 new;

	new.x = (a->y * b->z) - (a->z * b->y);
	new.y = (a->z * b->x) - (a->x * b->z);
	new.z = (a->x * b->y) - (a->y * b->x);
	return (new);
}

t_vec3 scale_vector(t_vec3 *a, float t)
{
	return ( (t_vec3) {a->x * t, a->y * t, a->z * t} );
}

t_vec3 vec_sub(t_vec3 *a, t_vec3 *b)
{
	return ( (t_vec3) {a->x - b->x, a->y - b->y, a->z - b->z} );
}

t_vec3 vec_add(t_vec3 *a, t_vec3 *b)
{
	return ( (t_vec3) {a->x + b->x, a->y + b->y, a->z + b->z} );
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

t_vec3 reflect(t_vec3 *d, t_vec3 *normal)
{
	t_vec3 part2 = scale_vector(normal, 2.0f * dot_product(d, normal));
	return normalized(vec_sub(d, &part2));
}

t_vec3 get_rotation_vector(t_vec3 *normal)
{
    if (normal)
    {
        double y = atan2(normal->x, -normal->z);

        double cosAngleX = cos(y);
        double sinAngleX = sin(y);
        double x = atan2(-normal->y, normal->x * sinAngleX + normal->z * cosAngleX);

        double cosAngleZ = cos(y);
        double sinAngleZ = sin(y);
        double z = atan2(normal->y * cosAngleZ - normal->z * sinAngleZ, normal->x * cosAngleZ + normal->z * sinAngleZ);
		if (normal->x < 0)
			x *= -1;
		if (normal->y < 0)
			y *= -1;
		if (normal->z < 0)
			z *= -1;
        return (new_vector(x, y, z));
    }
    return (new_vector(0, 0, 0));
}

t_vec3 get_up_vector(t_vec3 *forward)
{
    t_vec3 up;
    double d;

    up = new_vector(0, 1, 0);
    d = dot_product(&up, forward);
    if (d > 0.9)
        up = new_vector(0, 0, 1);
    else if (d < -0.9)
        up = new_vector(0, 0, -1);
    return (up);
}

void print_vector(t_vec3 a)
{
	printf("%f %f %f\n", a.x, a.y, a.z);
}