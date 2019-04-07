#include "stdafx.h"
#include "Blocks.h"


Blocks::Blocks()
	:block_sprv(90), block_amount(0), counter(0)
{
}

void Blocks::block_settings()
{
	
	block_red.loadFromFile("images/block_red.png");
	block_orange.loadFromFile("images/block_orange.png");
	block_yellow.loadFromFile("images/block_yellow.png");
	block_green.loadFromFile("images/block_green.png");
	block_blue.loadFromFile("images/block_blue.png");

	for (int i = 1; i <= 15; i++)
	{
		for (int j = 1; j <= 6; j++)
		{
			if (counter == 0 || counter == 1 || counter == 2)
			{
				block_sprv[block_amount].setTexture(block_red);
			}
			if (counter == 3 || counter == 4 || counter == 5)
			{
				block_sprv[block_amount].setTexture(block_orange);
			}
			if (counter == 6 || counter == 7 || counter == 8)
			{
				block_sprv[block_amount].setTexture(block_yellow);
			}
			if (counter == 9 || counter == 10 || counter == 11)
			{
				block_sprv[block_amount].setTexture(block_green);
			}
			if (counter == 12 || counter == 13 || counter == 14)
			{
				block_sprv[block_amount].setTexture(block_blue);
			}
			block_sprv[block_amount].setPosition(i * (block_width + 2), j * (block_height + 2) + 23);
			block_amount++;
		}
		counter += 1;
	}
}

void Blocks::draw_blocks(RenderWindow &window)
{
	for (int i = 0; i < block_amount; i++)
	{
		window.draw(block_sprv[i]);
	}
}
