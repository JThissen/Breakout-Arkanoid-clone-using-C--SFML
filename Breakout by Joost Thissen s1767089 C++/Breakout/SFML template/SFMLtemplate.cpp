// SFMLtemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Anim.h"
#include "Ball.h"
#include "Paddle.h"
#include "Blocks.h"
#include "Collision.h"
#include "PowerUps.h"
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h> //physics engine for future versions of the game
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace sf;
using namespace std;

int main()
{
	//CLASSES//
	Ball ball, ball2, ball3, ball4;
	Paddle paddle;
	Blocks blocks;
	Anim animation;
	Collision collision;
	PowerUps powerup;

	//VARIABLES//
	const int W = 765;
	const int H = 450;
	bool pause = true;
	bool set_effect_paddle = false;
	bool set_effect_block = false;
	bool bounce_border_left = false;
	bool bounce_border_right = false;
	bool bounce_border_top = false;
	int border_effect_offset = 5;
	bool paddle_right = false;
	bool paddle_left = false;
	bool set_score_effect = false;
	bool defeat_menu = false;
	
	//WINDOW, TEXTURES, SPRITES, ANIMATIONS//
	RenderWindow window;
	window.create(VideoMode(W, H), "Breakout");
	window.setFramerateLimit(60);
	
	Texture background, magic_shield, effect1, effect1_white, effect_score, arrow_right, arrow_right_pressed, arrow_left, arrow_left_pressed;
	background.loadFromFile("images/background.png");
	magic_shield.loadFromFile("images/magic_shield_small.png");
	effect1.loadFromFile("images/effect1_purple.png");
	effect1_white.loadFromFile("images/effect1_v2_white.png");
	effect_score.loadFromFile("images/effect_score.png");
	arrow_right.loadFromFile("images/arrow_right.png");
	arrow_right_pressed.loadFromFile("images/arrow_right_pressed.png");
	arrow_left.loadFromFile("images/arrow_left.png");
	arrow_left_pressed.loadFromFile("images/arrow_left_pressed.png");
	arrow_right.setSmooth(true);
	arrow_right_pressed.setSmooth(true);
	arrow_left.setSmooth(true);
	arrow_left_pressed.setSmooth(true);
	
	Sprite background_spr, arrow_right_spr, arrow_right_pressed_spr, arrow_left_spr, arrow_left_pressed_spr;
	background_spr.setTexture(background);
	arrow_right_spr.setTexture(arrow_right);
	arrow_right_spr.setScale(0.75f, 0.75f);
	arrow_right_spr.setPosition(paddle.location.x + (paddle.width / 2), paddle.location.y);
	arrow_right_pressed_spr.setTexture(arrow_right_pressed);
	arrow_right_pressed_spr.setScale(0.75f, 0.75f);
	arrow_right_pressed_spr.setPosition(-1000, -1000);
	arrow_left_spr.setTexture(arrow_left);
	arrow_left_spr.setScale(0.75f, 0.75f);
	arrow_left_spr.setPosition(paddle.location.x + (paddle.width / 2) - 26, paddle.location.y);
	arrow_left_pressed_spr.setTexture(arrow_left_pressed);
	arrow_left_pressed_spr.setScale(0.75f, 0.75f);
	arrow_left_pressed_spr.setPosition(-1000, -1000);

	Anim score_effect(effect_score, 0, 0, 192, 192, 20, 1.5f);
	score_effect.sprite.setScale(0.3f, 0.3f);
	score_effect.sprite.setPosition(122, 410);

	Anim shield(magic_shield, 1056, 0, 96, 96, 9, 0.3f);
	shield.sprite.setScale(0.185f, 0.185f);
	shield.sprite.setPosition(ball.location.x, ball.location.y);

	//Powerup - Extra balls 1, 2 and 3
	Anim shield2(magic_shield, 1056, 0, 96, 96, 9, 0.3f);
	shield2.sprite.setScale(0.185f, 0.185f);
	shield2.sprite.setPosition(-1000,1000);

	Anim shield3(magic_shield, 1056, 0, 96, 96, 9, 0.3f);
	shield3.sprite.setScale(0.185f, 0.185f);
	shield3.sprite.setPosition(-1000, 1000);

	Anim shield4(magic_shield, 1056, 0, 96, 96, 9, 0.3f);
	shield4.sprite.setScale(0.185f, 0.185f);
	shield4.sprite.setPosition(-1000, 1000);
	//

	Anim effect_paddle(effect1, 0, 0, 192, 192, 26, 0.5f);
	effect_paddle.sprite.setPosition(paddle.location.x, paddle.location.y);
	
	Anim effect_border_left(effect1_white, 0, 0, 192, 192, 26, 2.f);
	effect_border_left.sprite.setScale(0.3f, 0.3f);
	effect_border_left.sprite.setRotation(90);

	Anim effect_border_right(effect1_white, 0, 0, 192, 192, 26, 2.f);
	effect_border_right.sprite.setScale(0.3f, 0.3f);
	effect_border_right.sprite.setRotation(270);
	
	Anim effect_border_top(effect1_white, 0, 0, 192, 192, 26, 2.f);
	effect_border_top.sprite.setScale(0.3f, 0.3f);
	effect_border_top.sprite.setRotation(180);

	//BALL, PADDLE, BLOCKS SETTINGS & POWERUP SETTINGS//
	ball.ball_settings();
	paddle.paddle_settings();
	blocks.block_settings();

	//3 extra balls
	powerup.randomize_location(powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3, blocks.block_amount);
	powerup.extra_ball_settings(ball2.location, ball2.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_1);
	powerup.extra_ball_settings(ball3.location, ball3.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_2);
	powerup.extra_ball_settings(ball4.location, ball4.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_3);

	//TEXT MESSAGES//
	Font font_1;
	font_1.loadFromFile("images/AGENCYR.TTF");
	String display_blocks_destroyed = "Blocks destroyed:";
	string total_blocks = to_string(blocks.block_amount);
	string blocks_left = to_string(collision.blocks_destroyed);
	Text display_score, level_complete, paused, start, restart, breakout, defeat;
	
	display_score.setString(display_blocks_destroyed + " " + blocks_left + "/" + total_blocks);
	display_score.setFont(font_1);
	display_score.setCharacterSize(18);
	display_score.setPosition(10, 400);
	
	level_complete.setString("Level complete!");
	level_complete.setFont(font_1);
	level_complete.setCharacterSize(60);
	level_complete.setPosition((W / 2)-150, (H / 2)-60);

	breakout.setString("Breakout");
	breakout.setFont(font_1);
	breakout.setCharacterSize(60);
	breakout.setPosition((W / 2) - 85, (H / 2) - 60);

	start.setString("Play (Enter), Exit (Esc)");
	start.setFont(font_1);
	start.setCharacterSize(25);
	start.setPosition((W / 2)-87, (H / 2));

	restart.setString("Restart (R), Exit (Esc)");
	restart.setFont(font_1);
	restart.setCharacterSize(25);
	restart.setPosition((W / 2) - 87, (H / 2));

	defeat.setString("Game over!");
	defeat.setFont(font_1);
	defeat.setCharacterSize(60);
	defeat.setPosition((W / 2) - 108, (H / 2) - 60);

	//VERTICES//
	vector<Vertex> vertices;
	vector<Vertex> vertices_extra_ball_1;
	vector<Vertex> vertices_extra_ball_2;
	vector<Vertex> vertices_extra_ball_3;

	//MAIN GAME LOOP//
	while (window.isOpen())
	{
		//EVENTS//
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == Keyboard::R)
				{
					//RESTART GAME
					paddle.location.x = 337.5, paddle.location.y = 420;
					paddle.paddle_settings();
					ball.location.x = 250, ball.location.y = 300;
					ball.velocity.x = 4, ball.velocity.y = 4;
					ball.ball_settings();
					collision.blocks_destroyed = 0;
					blocks.counter = 0;
					blocks.block_amount = 0;
					blocks.block_sprv.empty();
					blocks.block_settings();
					vertices.clear();
					vertices_extra_ball_1.clear();
					vertices_extra_ball_2.clear();
					vertices_extra_ball_3.clear();
					powerup.draw_extra_ball_1 = false;
					powerup.draw_extra_ball_2 = false;
					powerup.draw_extra_ball_3 = false;
					powerup.randomize_location(powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3, blocks.block_amount);
					powerup.extra_ball_settings(ball2.location, ball2.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_1);
					powerup.extra_ball_settings(ball3.location, ball3.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_2);
					powerup.extra_ball_settings(ball4.location, ball4.velocity, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, powerup.rand_loc_3);
				}
				if (event.key.code == Keyboard::Return)
				{
					pause = false;
				}
			}
			if (event.type == Event::LostFocus)
			{
				pause = true;
			}
			if (event.type == Event::GainedFocus)
			{
				pause = false;
			}
		}

		//NOT PAUSED
		if (pause == false)
		{
			//UPDATE & SET POSITION//
			ball.game_over(ball.location, ball2.location, ball3.location, ball4.location, pause, defeat_menu, powerup.draw_extra_ball_1, powerup.draw_extra_ball_2, powerup.draw_extra_ball_3);
			paddle.paddle_update(paddle_right, paddle_left);
			ball.ball_update();
			shield.update();
			shield.sprite.setPosition(ball.location.x, ball.location.y);
			effect_paddle.sprite.setPosition(paddle.location.x + (paddle.width / 2), paddle.location.y + (paddle.height / 2));
			arrow_right_spr.setPosition(paddle.location.x+(paddle.width/2), paddle.location.y);
			arrow_right_pressed_spr.setPosition(paddle.location.x + (paddle.width / 2), paddle.location.y);
			arrow_left_spr.setPosition(paddle.location.x + (paddle.width / 2)-26, paddle.location.y);
			arrow_left_pressed_spr.setPosition(paddle.location.x + (paddle.width / 2)-26, paddle.location.y);
			blocks_left = to_string(collision.blocks_destroyed);
			display_score.setString(display_blocks_destroyed + " " + blocks_left + "/" + total_blocks);
			vertices.push_back(Vertex(Vector2f(ball.location.x, ball.location.y)));
			vertices_extra_ball_1.push_back(Vertex(Vector2f(ball2.location.x, ball2.location.y)));
			vertices_extra_ball_2.push_back(Vertex(Vector2f(ball3.location.x, ball3.location.y)));
			vertices_extra_ball_3.push_back(Vertex(Vector2f(ball4.location.x, ball4.location.y)));

			//Powerup - Extra balls 1,2 and 3
			if (powerup.draw_extra_ball_1 == true)
			{
				ball2.ball_update();
				shield2.update();
				shield2.sprite.setPosition(ball2.location.x, ball2.location.y);
			}
			if (powerup.draw_extra_ball_2 == true)
			{
				ball3.ball_update();
				shield3.update();
				shield3.sprite.setPosition(ball3.location.x, ball3.location.y);
			}
			if (powerup.draw_extra_ball_3 == true)
			{
				ball4.ball_update();
				shield4.update();
				shield4.sprite.setPosition(ball4.location.x, ball4.location.y);
			}
			
			//Collisions main ball//
			collision.ball_bounce_wall(effect_border_left, effect_border_right, effect_border_top, border_effect_offset, bounce_border_left, bounce_border_right, bounce_border_top, ball.location, ball.velocity, ball.ball_radius);
			collision.collision_paddle(ball.location_min, ball.location_max, paddle.location_min, paddle.location_max, paddle.location, ball.location, ball.velocity, paddle.width, paddle.height, ball.ball_radius*2, ball.ball_radius*2, set_effect_paddle);
			collision.ball_bounce_block(blocks.block_amount, blocks.block_sprv, blocks.block_width, blocks.block_height, ball.ball_radius, ball.velocity.x, ball.velocity.y, ball.location, set_score_effect, powerup.rand_loc_1, powerup.draw_extra_ball_1, powerup.draw_extra_ball_2, powerup.draw_extra_ball_3, powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3);
			
			//Collisions extra balls 1,2 an 3 powerup//
			if (powerup.draw_extra_ball_1 == true)
			{
				collision.ball_bounce_wall(effect_border_left, effect_border_right, effect_border_top, border_effect_offset, bounce_border_left, bounce_border_right, bounce_border_top, ball2.location, ball2.velocity, ball.ball_radius);
				collision.collision_paddle(ball2.location_min, ball2.location_max, paddle.location_min, paddle.location_max, paddle.location, ball2.location, ball2.velocity, paddle.width, paddle.height, ball.ball_radius * 2, ball.ball_radius * 2, set_effect_paddle);
				collision.ball_bounce_block(blocks.block_amount, blocks.block_sprv, blocks.block_width, blocks.block_height, ball2.ball_radius, ball2.velocity.x, ball2.velocity.y, ball2.location, set_score_effect, powerup.rand_loc_1, powerup.draw_extra_ball_1, powerup.draw_extra_ball_2, powerup.draw_extra_ball_3, powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3);
			}
			if (powerup.draw_extra_ball_2 == true)
			{
				collision.ball_bounce_wall(effect_border_left, effect_border_right, effect_border_top, border_effect_offset, bounce_border_left, bounce_border_right, bounce_border_top, ball3.location, ball3.velocity, ball.ball_radius);
				collision.collision_paddle(ball3.location_min, ball3.location_max, paddle.location_min, paddle.location_max, paddle.location, ball3.location, ball3.velocity, paddle.width, paddle.height, ball.ball_radius * 2, ball.ball_radius * 2, set_effect_paddle);
				collision.ball_bounce_block(blocks.block_amount, blocks.block_sprv, blocks.block_width, blocks.block_height, ball3.ball_radius, ball3.velocity.x, ball3.velocity.y, ball3.location, set_score_effect, powerup.rand_loc_1, powerup.draw_extra_ball_1, powerup.draw_extra_ball_2, powerup.draw_extra_ball_3, powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3);
			}
			if (powerup.draw_extra_ball_3 == true)
			{
				collision.ball_bounce_wall(effect_border_left, effect_border_right, effect_border_top, border_effect_offset, bounce_border_left, bounce_border_right, bounce_border_top, ball4.location, ball4.velocity, ball.ball_radius);
				collision.collision_paddle(ball4.location_min, ball4.location_max, paddle.location_min, paddle.location_max, paddle.location, ball4.location, ball4.velocity, paddle.width, paddle.height, ball.ball_radius * 2, ball.ball_radius * 2, set_effect_paddle);
				collision.ball_bounce_block(blocks.block_amount, blocks.block_sprv, blocks.block_width, blocks.block_height, ball4.ball_radius, ball4.velocity.x, ball4.velocity.y, ball4.location, set_score_effect, powerup.rand_loc_1, powerup.draw_extra_ball_1, powerup.draw_extra_ball_2, powerup.draw_extra_ball_3, powerup.rand_loc_1, powerup.rand_loc_2, powerup.rand_loc_3);
			}
			
			//UPDATE ONCE//
			effect_border_left.update_once(bounce_border_left);
			effect_border_right.update_once(bounce_border_right);
			effect_border_top.update_once(bounce_border_top);
			effect_paddle.update_once(set_effect_paddle);
			score_effect.update_once(set_score_effect);

			//DRAW ON SCREEN//
			window.clear();
			window.draw(background_spr);
			blocks.draw_blocks(window);
			window.draw(vertices.data(), vertices.size(), Points);
			ball.ball_draw(window);
			
			//Extra balls 1,2 and 3//
			if (powerup.draw_extra_ball_1 == true)
			{
				ball2.ball_draw(window);
				window.draw(shield2.sprite);
				window.draw(vertices_extra_ball_1.data(), vertices_extra_ball_1.size(), Points);
			}
			if (powerup.draw_extra_ball_2 == true)
			{
				ball3.ball_draw(window);
				window.draw(shield3.sprite);
				window.draw(vertices_extra_ball_2.data(), vertices_extra_ball_2.size(), Points);
			}
			if (powerup.draw_extra_ball_3 == true)
			{
				ball4.ball_draw(window);
				window.draw(shield4.sprite);
				window.draw(vertices_extra_ball_3.data(), vertices_extra_ball_3.size(), Points);
			}
			//

			window.draw(effect_paddle.sprite);
			paddle.paddle_draw(window);
			window.draw(shield.sprite);
			if (bounce_border_left == true)
			{
				window.draw(effect_border_left.sprite);
			}
			
			if (bounce_border_right == true)
			{
				window.draw(effect_border_right.sprite);
			}
			if (bounce_border_top == true)
			{
				window.draw(effect_border_top.sprite);
			}
			if (set_score_effect == true)
			{
				window.draw(score_effect.sprite);
			}
			window.draw(display_score);
			if (collision.blocks_destroyed == blocks.block_amount)
			{
				pause = true;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				window.draw(arrow_right_pressed_spr);
			}
			else
			{
				window.draw(arrow_right_spr);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				window.draw(arrow_left_pressed_spr);
			}
			else
			{
				window.draw(arrow_left_spr);
			}
			window.display();

			//ERASE FROM SCREEN//
			if (vertices.size() > 75)
			{
				vertices.erase(vertices.begin());
			}
			if (vertices_extra_ball_1.size() > 75)
			{
				vertices_extra_ball_1.erase(vertices_extra_ball_1.begin());
			}
			if (vertices_extra_ball_2.size() > 75)
			{
				vertices_extra_ball_2.erase(vertices_extra_ball_2.begin());
			}
			if (vertices_extra_ball_3.size() > 75)
			{
				vertices_extra_ball_3.erase(vertices_extra_ball_3.begin());
			}
		}
		//PAUSED
		else if (pause == true)
		{
			window.clear();
			window.draw(background_spr);
			if (defeat_menu == true)
			{
				window.draw(defeat);
				window.draw(restart);
			}
			else if (collision.blocks_destroyed == blocks.block_amount)
			{
				window.draw(level_complete);
				window.draw(restart);
			}
			else
			{
				window.draw(breakout);
				window.draw(start);
			}
			shield.update();
			shield2.update();
			shield3.update();
			shield4.update();
			blocks.draw_blocks(window);
			window.draw(vertices.data(), vertices.size(), Points);
			window.draw(vertices_extra_ball_1.data(), vertices_extra_ball_1.size(), Points);
			window.draw(vertices_extra_ball_2.data(), vertices_extra_ball_2.size(), Points);
			window.draw(vertices_extra_ball_3.data(), vertices_extra_ball_3.size(), Points);
			ball.ball_draw(window);
			if (powerup.draw_extra_ball_1 == true)
			{
				ball2.ball_draw(window);
				window.draw(shield2.sprite);
			}
			paddle.paddle_draw(window);
			window.draw(shield.sprite);
			window.draw(display_score);
			window.draw(arrow_right_spr);
			window.draw(arrow_left_spr);
			window.display();
			if (event.key.code == Keyboard::R)
			{
				pause = false;
				defeat_menu = false;
			}
		}
	}
	return 0;
}
