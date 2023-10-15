#include "minirt.h"

t_object* init_objects()
{
    t_object *objects;

    objects = malloc(sizeof(t_object) * 2);
    // plane
    objects[1].type = PLANE;
    objects[1].id = 1;
    objects[1].base_color = new_vector3(128.0, 128.0, 128.0);
    objects[1].mat_color = new_vector3(255.0, 0.0, 10.0);
    objects[1].translation = new_vector3(0.0, 0.0, 0.75);
    objects[1].rotation = new_vector3(0.0, 0.0, 0.0);
    objects[1].scale = new_vector3(4.0, 4.0, 1.0);
    objects[1].has_material = 0;
    objects[1].shininess = 0.0;
    objects[1].reflectivity = 0.0;
    objects[1].gtfm = set_transform(objects[1].translation, objects[1].rotation, objects[1].scale);

    // sphere
    objects[0].type = SPHERE;
    objects[0].id = 0;
    objects[0].base_color = new_vector3(10.0, 0.0, 255.0);
    objects[0].mat_color = new_vector3(255.0, 0.0, 10.0);
    objects[0].translation = new_vector3(0.0, 0.0, 0.0);
    objects[0].rotation = new_vector3(0.0, 0.0, 0.0);
    objects[0].scale = new_vector3(0.5, 0.5, 0.5);
    objects[0].has_material = 1;
    objects[0].shininess = 10.0;
    objects[0].reflectivity = 0.5;
    objects[0].gtfm = set_transform(objects[0].translation, objects[0].rotation, objects[0].scale);
    return (objects);
}

t_light *init_light()
{
    t_light *light_list = malloc(sizeof(t_light) * 3);

    light_list[0].color = new_vector3(255, 0, 0);
    light_list[0].position = new_vector3(5, -10, -5);
    light_list[0].intensity = 0.8;

    light_list[1].color = new_vector3(0, 255, 0);
    light_list[1].position = new_vector3(0, -10, -5);
    light_list[1].intensity = 0.8;

    light_list[2].color = new_vector3(0, 0, 255);
    light_list[2].position = new_vector3(-5, -10, -5);
    light_list[2].intensity = 0.8;

    return (light_list);
}