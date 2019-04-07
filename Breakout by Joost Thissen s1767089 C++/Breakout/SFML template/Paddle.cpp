#include "stdafx.h"
#include "Paddle.h"

Paddle::Paddle()
	:location(337.5f, 420.f), velocity(7.f, 0.f), acceleration(0.f, 0.f)
{
}

void Paddle::paddle_settings()
{
	paddle_txt.loadFromFile("images/paddle_v2.png");
	paddle_spr.setTexture(paddle_txt);
	paddle_spr.setPosition(location.x, location.y);
}

void Paddle::paddle_update(bool &paddle_right, bool &paddle_left)
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		paddle_right = true;
		location += velocity;
		if (location.x + width >= W)
		{
			location.x = W - width;
			paddle_spr.setPosition(W - width, location.y);
		}
		else 
		{
			paddle_spr.setPosition(location.x, location.y);
		}
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		paddle_left = true;
		location -= velocity;
		if (location.x <= 0)
		{
			location.x = 0;
			paddle_spr.setPosition(0, location.y);
		}
		else
		{
			paddle_spr.setPosition(location.x, location.y);
		}
	}
	
	paddle_width = location.x + width;
	location_min.x = location.x;
	location_min.y = location.y + height;
	location_max.x = location.x + width;
	location_max.y = location.y;
}

void Paddle::paddle_draw(RenderWindow & window)
{
	window.draw(paddle_spr);
}



