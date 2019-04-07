#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
using namespace sf;
using namespace std;

class Paddle
{
public:
	
	Texture paddle_txt;
	Sprite paddle_spr;
	
	Vector2f location;
	Vector2f velocity;
	Vector2f acceleration;
	Vector2f location_min;
	Vector2f location_max;
	

	const int W = 765;
	const int H = 450;
	const float width = 90;
	const float height = 12;
	float paddle_width;
	
	
	
	Paddle();
	void paddle_settings();
	void paddle_update(bool &paddle_right, bool &paddle_left);
	void paddle_draw(RenderWindow &window);
};

