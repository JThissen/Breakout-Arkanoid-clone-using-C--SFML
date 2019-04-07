#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class Anim
{
public:
	Sprite sprite;
	float frame;
	float Speed;
	int Count;
	int x;
	int y;
	bool on_off = 0;
	vector<IntRect>frames;
	
	Anim();
	Anim(Texture &texture, int x, int y, int w, int h, int count, float speed);
	void update();
	void update_once(bool &x);
};



