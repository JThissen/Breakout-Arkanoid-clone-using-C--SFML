#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Anim.h"
#include "Ball.h"
#include <vector>
#include <math.h>

class Blocks
{
public:
	Texture block_red, block_orange, block_yellow, block_green, block_blue;
	vector<Sprite>block_sprv;

	const int block_width = 43;
	const int block_height = 20;
	int block_amount;
	float counter;

	Blocks();
	void block_settings();
	void draw_blocks(RenderWindow &window);
};

