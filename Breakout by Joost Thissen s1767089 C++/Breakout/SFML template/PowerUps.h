#pragma once

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>
using namespace sf;
using namespace std;

class PowerUps
{
public:
	Texture ball_txt;
	Sprite ball_spr;

	int rand_loc_1;
	int rand_loc_2;
	int rand_loc_3;
	//int rand_loc_4;
	//int rand_loc_5;
	//int rand_loc_6;
	bool draw_extra_ball_1 = false;
	bool draw_extra_ball_2 = false;
	bool draw_extra_ball_3 = false;

	PowerUps();
	void randomize_location(int &one, int &two, int &three, int block_amount);
	void extra_ball_settings(Vector2f &location, Vector2f &velocity, vector<Sprite> block_sprt, int width, int height, int radius, int random_location);


		


	
	
};

