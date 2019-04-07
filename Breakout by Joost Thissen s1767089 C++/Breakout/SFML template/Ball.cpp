#include "stdafx.h"
#include "Ball.h"


Ball::Ball()
	:location(250.f, 300.f), velocity(4.f, 4.f), acceleration(0.f, 0.f)
{
}

void Ball::ball_settings()
{
	ball_txt.loadFromFile("images/ball_image.png");
	ball_spr.setTexture(ball_txt);
	ball_spr.setPosition(location.x, location.y);
}

void Ball::ball_update()
{
	location = location + velocity;
	location_min.x = location.x - ball_radius;
	location_min.y = location.y + ball_radius;
	location_max.x = location.x + ball_radius;
	location_max.y = location.y - ball_radius;
	//cout << abs(velocity.x) << " " << abs(velocity.y) << " " << sqrt(velocity.x*velocity.x + (velocity.y*velocity.y)) << endl;;
}

void Ball::trigger_velocity_increase(int blocks_destroyed)
{
}

void Ball::game_over(Vector2f location1, Vector2f location2, Vector2f location3, Vector2f location4, bool &pause, bool &defeat, bool extra_ball, bool extra_ball2, bool extra_ball3)
{
	if (location1.y + ball_radius > H + 50 &&
		extra_ball == false &&
		extra_ball2 == false &&
		extra_ball3 == false
		||
		location1.y + ball_radius > H + 50 &&
		location2.y + ball_radius > H + 50 &&
		extra_ball2 == false &&
		extra_ball3 == false
		||
		location1.y + ball_radius > H + 50 &&
		extra_ball == false &&
		location3.y + ball_radius > H + 50 &&
		extra_ball3 == false
		||
		location1.y + ball_radius > H + 50 &&
		extra_ball == false &&
		extra_ball2 == false &&
		location4.y + ball_radius > H + 50
		||
		location1.y + ball_radius > H + 50 &&
		location2.y + ball_radius > H + 50 &&
		location3.y + ball_radius > H + 50 &&
		extra_ball3 == false
		||
		location1.y + ball_radius > H + 50 &&
		location2.y + ball_radius > H + 50 &&
		extra_ball2 == false &&
		location4.y + ball_radius > H + 50
		||
		location1.y + ball_radius > H + 50 &&
		extra_ball == false &&
		location3.y + ball_radius > H + 50 &&
		location4.y + ball_radius > H + 50
		||
		location1.y + ball_radius > H + 50 &&
		location2.y + ball_radius > H + 50 &&
		location3.y + ball_radius > H + 50 &&
		location4.y + ball_radius > H + 50
		)
	{
		pause = true;
		defeat = true;
	}
}

void Ball::ball_draw(RenderWindow &window)
{
	window.draw(ball_spr);
}



