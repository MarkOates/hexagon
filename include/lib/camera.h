#pragma once


#include <allegro_flare/vec3d.h>
#include <allegro5/allegro.h>


class Camera
{
public:
	vec3d position;
	vec3d stepback;
	vec3d rotation;
	float tilt;

	float zoom_min;
	float zoom_max;
	float zoom_pos;

	Camera(float x, float y, float z);

   void set45_isometric();

   void setup_camera_perspective(ALLEGRO_BITMAP *bmp);
};


