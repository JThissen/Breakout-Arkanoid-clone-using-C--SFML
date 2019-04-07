#include "stdafx.h"
#include "PowerUps.h"


PowerUps::PowerUps()
{
}

void PowerUps::randomize_location(int &one, int &two, int &three, int block_amount)
{
	srand(time(0));
	one = (rand() % block_amount)+1;
	two = (rand() % block_amount)+1;
	three = (rand() % block_amount)+1;
	//four = (rand() % block_amount)+1;
	//five = (rand() % block_amount)+1;
	//six = (rand() % block_amount)+1;
}


void PowerUps::extra_ball_settings(Vector2f &location, Vector2f &velocity, vector<Sprite> block_sprt, int width, int height, int radius, int random_location)
{
	ball_txt.loadFromFile("images/ball_image.png");
	ball_spr.setTexture(ball_txt);
	ball_spr.setPosition(location.x, location.y);
	location.x = block_sprt[random_location].getPosition().x + (width/2), location.y = block_sprt[random_location].getPosition().y + (height/2);
	velocity.x = -4, velocity.y = -4;
	
}