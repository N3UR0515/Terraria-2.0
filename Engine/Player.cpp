#include "Player.h"
#include <assert.h>

void Player::ClampToScreen()
{
	if (loc.x >= Grid::Width)
	{
		loc.x = Grid::Width - 1;
	}
	if (loc.x < 0)
	{
		loc.x = 0;
	}
	if (loc.y >= Grid::Height)
	{
		loc.y = Grid::Height - 1;
	}
	if (loc.y < 0)
	{
		loc.y = 0;
	}
}

void Player::PlayerWithBlocksCollision(Vec2& dl, std::vector<Grid::World::Block>& b)
{
	//Checking if there is a block on the player's right/left/down/up/diagonals and respond by changing the delta_loc
	if ((dl.x != 0 && dl.y == 0) || (dl.x == 0 && dl.y != 0) || (dl.x != 0 && dl.y != 0))
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (b.at(i).GetLocation() == loc + dl)
			{
				dl = { 0,0 };
			}
		}
	}
}

void Player::Jump(Keyboard & kbd, Vec2 & dl, std::vector<Grid::World::Block>& b)
{
	//Jumping Algorithm
	if (kbd.KeyIsPressed(VK_UP))
	{
		if (jumping)
		{
			if (jumpForce != 0)
			{
				dl += {0, -1};
				jumpForce--;
			}
			else
			{
				jumping = false;
			}
		}
		else
		{
			//Check if it can jump
			Vec2 underBlock = { 0,1 };
			for (int i = 0; i < b.size(); i++)
			{
				if (b.at(i).GetLocation() == loc + underBlock)
				{
					jumping = true;
					jumpForce = 3; //If you change the jumpForce then you must change this too!
					break;
				}
			}
		}
	}
	else if (jumping)
	{
		jumping = false;
	}
	//Jumping Algorithm

	//Gravity
	if (!jumping)
	{
		dl += {0, 1};

		Vec2 underBlock = { 0,1 };
		for (int i = 0; i < b.size(); i++)
		{
			if (b.at(i).GetLocation() == loc + underBlock)
			{
				dl += {0, -1}; //Reset dl;
				jumping = false;
				jumpForce = 0;
			}
		}
	}
	//Gravity
}

Player::Player(const Vec2 in_loc)
{
	loc = in_loc;
}

void Player::MoveBy(const Vec2 delta_loc)
{
	loc += delta_loc;
}

void Player::BlockBreaking(Vec2& mousePos, std::vector<Grid::World::Block>& b)
{
	Vec2 gridPos = mousePos / Grid::CellDimensions;

	gridPos.x = int(gridPos.x);
	gridPos.y = int(gridPos.y);

	assert(gridPos.x >= 0 && gridPos.x < Grid::Width && gridPos.y >= 0 && gridPos.y < Grid::Height);
	
	Vec2 distanceBetweenMouseBreakingAndPlayer = gridPos - loc;

	if (distanceBetweenMouseBreakingAndPlayer.GetLength() > float(playerBreakingReach))
	{
	}
	else
	{
		for (int i = 0; i < b.size(); i++)
		{
			if (b.at(i).GetLocation() == gridPos)
			{
				b.erase(b.begin() + i);
			}
		}
	}
}

void Player::Draw(Grid & grd) const
{
	grd.DrawCell(loc, c);
}

void Player::Update(Keyboard& kbd, Mouse& mouse, std::vector<Grid::World::Block>& b)
{
	Vec2 delta_loc = { 0,0 };

	//Horizontal movement
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		delta_loc += { 1, 0 };
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		delta_loc += { -1, 0 };
	}
	//Horizontal movement

	//Block Breaking
	if (mouse.LeftIsPressed())
	{
		BlockBreaking(Vec2(float(mouse.GetPosX()), float(mouse.GetPosY())), b);
	}

	if (moveCounter++ == movePeriod)
	{
		moveCounter = 0; //Reset moveCounter

		Jump(kbd, delta_loc, b);
		PlayerWithBlocksCollision(delta_loc, b);
		MoveBy(delta_loc);
		ClampToScreen();
	}
}
