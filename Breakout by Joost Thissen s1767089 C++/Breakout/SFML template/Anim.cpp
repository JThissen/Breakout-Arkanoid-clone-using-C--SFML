#include "stdafx.h"
#include "Anim.h"

Anim::Anim()
{
}

Anim::Anim(Texture & texture, int x, int y, int w, int h, int count, float speed)
{
	frame = 0;
	Speed = speed;
	Count = count;
	for (int i = 0; i < Count; i++)
		{
			frames.push_back(IntRect(x + i*w, y, w, h));
		}
	sprite.setTexture(texture);
	sprite.setTextureRect(frames[0]);
	sprite.setOrigin((float)w / 2, (float)h / 2);
}

//continuous animation//
void Anim::update()
{
	frame += Speed;
	if (frame >= Count)
	{
		frame -= Count;
	}
	if (Count > 0)
	{
		sprite.setTextureRect(frames[(int)frame]);
	}
}

//one full animation//
void Anim::update_once(bool &x)
{
	if (x == true)
	{
		frame += Speed;
		if (frame >= Count)
		{
			frame -= Count;
			x = false;
		}
		
		if (Count > 0)
		{
			sprite.setTextureRect(frames[(int)frame]);
		}
	}
}

