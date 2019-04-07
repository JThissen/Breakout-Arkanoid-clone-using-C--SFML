#pragma once

#include "stdafx.h"
#include "Anim.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
using namespace sf;
using namespace std;

class Collision
{
public:
	const int W = 765;
	const int H = 450;
	float velocity_magnitude;
	float ratio_x_ball_paddle;
	int blocks_destroyed;

	Collision();
	void ball_bounce_wall(Anim &animation1, Anim &animation2, Anim &animation3, int offset, bool &border_eff_left, bool &border_eff_right, bool &border_eff_top, Vector2f location, Vector2f &velocity, int ball_radius);
	void collision_paddle(Vector2f min_a, Vector2f max_a, Vector2f min_b, Vector2f max_b, Vector2f location_paddle, Vector2f &location_ball, Vector2f &velocity_ball, int width, int height, int height_ball, int width_ball, bool &effect_paddle);
	void ball_bounce_block(int block_amount, vector<Sprite> &block_sprite, int width, int height, int radius, float &velocity_x, float &velocity_y, Vector2f location, bool &set_score_effect, int random_loc_1, bool &extra_ball, bool &extra_ball2, bool &extra_ball3, int random_location, int random_location2, int random_location3);
};
