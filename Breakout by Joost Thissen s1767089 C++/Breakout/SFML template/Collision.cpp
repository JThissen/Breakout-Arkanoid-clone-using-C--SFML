#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
	:blocks_destroyed(0)
{
}

void Collision::ball_bounce_wall(Anim &animation1, Anim &animation2, Anim &animation3, int offset, bool &border_eff_left, bool &border_eff_right, bool &border_eff_top, Vector2f location, Vector2f &velocity, int ball_radius)
{
	if (location.x - ball_radius <= 0)
	{
		animation1.sprite.setPosition(location.x - offset, location.y);
		border_eff_left = true;
		velocity.x = -velocity.x;
	}
	if (location.x + ball_radius >= W)
	{
		animation2.sprite.setPosition(location.x + offset, location.y);
		border_eff_right = true;
		velocity.x = -velocity.x;
	}
	if (location.y - ball_radius <= 0)
	{
		animation3.sprite.setPosition(location.x, location.y - offset);
		border_eff_top = true;
		velocity.y = -velocity.y;
	}
}

void Collision::collision_paddle(Vector2f min_a, Vector2f max_a, Vector2f min_b, Vector2f max_b, Vector2f location_paddle, Vector2f &location_ball, Vector2f &velocity_ball, int width, int height, int height_ball, int width_ball, bool &effect_paddle)
{
	//NEW COLLISION METHOD BASED ON AABB (axis-aligned bounding boxes)
	//distances between min max
	float x_1 = min_a.x - max_b.x;
	float y_1 = min_a.y - max_b.y;
	float x_2 = min_b.x - max_a.x;
	float y_2 = min_b.y - max_a.y;
	
	//top
	if (min_a.x > location_paddle.x && max_a.x < max_b.x)
	{
		if (y_1 >= 0 && y_1 <= height && x_2 <= 0 && x_1 <= 0)
		{
			velocity_magnitude = sqrt(velocity_ball.x*velocity_ball.x + (velocity_ball.y*velocity_ball.y));
			ratio_x_ball_paddle = ((location_ball.x - (location_paddle.x + width / 2)) / (width / 2));
			velocity_ball.x = (velocity_magnitude*ratio_x_ball_paddle);
			velocity_ball.y = sqrt(velocity_magnitude*velocity_magnitude - (velocity_ball.x*velocity_ball.x))*(velocity_ball.y > 0 ? -1 : 1); //condition ? result if true: result if false
			effect_paddle = true;
		}
	}
}

void Collision::ball_bounce_block(int block_amount, vector<Sprite> &block_sprite, int width, int height, int radius, float &velocity_x, float &velocity_y, Vector2f location, bool &set_score_effect, int random_loc_1, bool &extra_ball, bool &extra_ball2, bool &extra_ball3, int random_location, int random_location2, int random_location3)
{
	for (int i = 0; i < block_amount; i++)
	{
		//OLD COLLISION METHOD
			//left side block//
			if (location.x + radius <= (block_sprite[i].getPosition().x + (width / 2)))
			{
				if (((location.x + radius) >= block_sprite[i].getPosition().x) && (location.y <= (block_sprite[i].getPosition().y + height))
					&& (location.y >= block_sprite[i].getPosition().y))
				{
					velocity_x = -abs(velocity_x);
					block_sprite[i].setPosition(-1000, -1000);
					blocks_destroyed += 1;
					set_score_effect = true;
				}
			}

			//right side block//
			if (location.x + radius >= (block_sprite[i].getPosition().x + (width / 2)))
			{
				if (((location.x - radius) <= (block_sprite[i].getPosition().x + width)) && (location.y <= (block_sprite[i].getPosition().y + height))
					&& (location.y >= block_sprite[i].getPosition().y))
				{
					velocity_x = abs(velocity_x);
					block_sprite[i].setPosition(-1000, -1000);
					blocks_destroyed += 1;
					set_score_effect = true;
				}
			}

			//top side block//
			if (location.y + radius <= (block_sprite[i].getPosition().y + (height / 2)))
			{
				if (((location.y + radius) >= block_sprite[i].getPosition().y) && (location.x >= block_sprite[i].getPosition().x)
					&& (location.x <= (block_sprite[i].getPosition().x + width)))
				{
					velocity_y = -abs(velocity_y);
					block_sprite[i].setPosition(-1000, -1000);
					blocks_destroyed += 1;
					set_score_effect = true;
				}
			}

			//bottom side block//
			if (location.y - radius >= (block_sprite[i].getPosition().y + (height / 2)))
			{
				if (((location.y - radius) <= (block_sprite[i].getPosition().y + height)) && (location.x >= block_sprite[i].getPosition().x)
					&& (location.x <= (block_sprite[i].getPosition().x + width)))
				{
					velocity_y = abs(velocity_y);
					block_sprite[i].setPosition(-1000, -1000);
					blocks_destroyed += 1;
					set_score_effect = true;
				}
			}		
		}
	if (block_sprite[random_location].getPosition().x == -1000 && set_score_effect == true)
	{
		extra_ball = true;
	}
	if (block_sprite[random_location2].getPosition().x == -1000 && set_score_effect == true)
	{
		extra_ball2 = true;
	}
	if (block_sprite[random_location3].getPosition().x == -1000 && set_score_effect == true)
	{
		extra_ball3 = true;
	}
}