#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

class Ball
{
public:
	Texture ball_txt;
	Sprite ball_spr;

	Vector2f location;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f vel_acc_sum;
	
	Vector2f location_min;
	Vector2f location_max;

	const int W = 765;
	const int H = 450;
	float ball_radius = 7;
	
	Ball();
	void ball_settings();
	void ball_update();
	void trigger_velocity_increase(int blocks_destroyed);
	void game_over(Vector2f location1, Vector2f location2, Vector2f location3, Vector2f location4, bool &pause, bool &defeat, bool extra_ball, bool extra_ball2, bool extra_ball3);
	void ball_draw(RenderWindow &window);

	
};

