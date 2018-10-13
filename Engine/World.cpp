#include "World.h"
#include <assert.h>

Grid::Grid::World::Block::Block(Vec2 in_loc, Grid::Grid::World::Block::BlockType in_type)
	:
	loc(in_loc),
	type(in_type)
{
}

void Grid::Grid::World::Block::Draw(Grid & grd)
{
	grd.DrawCell(loc, type);
}

Vec2 Grid::Grid::World::Block::GetLocation()
{
	return Vec2(float(int(loc.x)), float(int(loc.y)));
}

Grid::World::Block::BlockType Grid::World::Block::GetType()
{
	return type;
}

void Grid::World::Block::SetType(BlockType _type)
{
	type = _type;
}

void Grid::World::Block::SetLocation(Vec2 v)
{
	loc = v;
}



//WORLD GENERATION
Grid::World::World()
{
	//Organizing the array
	{
		int id = 0;
		for (int i = 0; i < Grid::Width; i++)
		{
			for (int j = 0; j < Grid::Height; j++, id++)
			{
				blocksInGrid[id].SetType(World::Block::BlockType::Air);
				blocksInGrid[id].SetLocation(Vec2(float(i), float(j)));
			}
		}
	}

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> seeding(0, 100000.0f); //You can change 100000 with any number you want
																 //But if it's a small number there are big chances that there
																 //Might be similarities with previous or next maps
																 //So with a big number, this chance gets smaller

	//Surface generation
	float seed = seeding(rng); //Taking a random seed/xoffset in time;

	for (int i = 0; i < Grid::Width; i++, seed += 0.0800000f) //If you change 0.2f with bigger numbers, it will get suddenly random
	{
		float j = Noise::PerlinNoise_1D(seed, 2.7182818f, 6.2831853f); //Taking a random noise value based on the seed
														//With a frequency of 3.5f, that's what I thought would be the best one
														//And with a amplitude of 3, you can change the freq and the ampl if u want

		j += float(Grid::Height / 2 - 1);				//The perlin values are between 0 and double the amplitude
															//So I just translate it to the middle of the y plane

		blocksInGrid[GetId(i, int(j + 0.5f))].SetType(Block::BlockType::Grass);
	}
	//Surface generation

	////Underground filling
	for (int i = 0; i < Grid::Width; i++)
	{
		int firstDirtBlock = 0;

		//Finding the surfaceBlock's y location
		for (int testForBlock = 0; blocksInGrid[GetId(i, testForBlock - 2)].GetType() != World::Block::BlockType::Grass; testForBlock++)
		{
			firstDirtBlock = testForBlock;
		}

		std::uniform_int_distribution<int> dirtLayer(2, 4);

		const int dLayer = dirtLayer(rng);

		//Adding the underground blocks
		for (int j = firstDirtBlock; j < Grid::Height; j++)
		{
			if (j <= firstDirtBlock + dLayer)
			{
				blocksInGrid[GetId(i, j)].SetType(Grid::World::Block::BlockType::Dirt);
			}
			else
			{
				blocksInGrid[GetId(i, j)].SetType(Grid::World::Block::BlockType::Stone);
			}
		}
	}

	//Ores
	AddOres(Block::BlockType::Coal, blocksInGrid, 1.3333333f, 80.0000000f, 2.0000000f, 1.1000000f);
	/*AddOres(Block::BlockType::Coal, blocksInGrid, 1.3333333f, 80.0000000f, 2.0000000f, 1.5000000f);*/
	/*AddOres(Block::BlockType::Iron, blocksInGrid, 1.3333333f, 90.0000000f, 1.0000000f, 3.0000000f);
	AddOres(Block::BlockType::Diamond, blocksInGrid, 0.0100000f);*/
	//Ores
	//Underground filling
}
//WORLD GENERATION


void Grid::World::Update(float dt)
{
	timeWorld += dt;
	mobSpawnTime += dt;

	if (timeWorld >= 25.0f) // One day durates 10 minutes, so 10 min * 60 to get 600 seconds and then / 24 (for each phase)
	{
		//Reset the animation
		if (backgroundSprite == 24)
		{
			backgroundSprite = 0;
		}

		switch (backgroundSprite)
		{
		case 0: //Perfect night
		{
			skyColor = { 0, 37, 51 };
			backgroundSprite++;
			break;
		}
		case 1:
		{
			skyColor = { 17, 67, 62 };
			backgroundSprite++;
			break;
		}
		case 2:
		{
			skyColor = { 34, 85, 78 };
			backgroundSprite++;
			break;
		}
		case 3:
		{
			skyColor = { 51, 103, 94 };
			backgroundSprite++;
			break;
		}
		case 4:
		{
			skyColor = { 68, 121, 110 };
			backgroundSprite++;
			break;
		}
		case 5:
		{
			skyColor = { 85, 139, 126 };
			backgroundSprite++;
			break;
		}
		case 6:
		{
			skyColor = { 102, 157, 142 };
			backgroundSprite++;
			break;
		}
		case 7:
		{
			skyColor = { 119, 175, 158 };
			backgroundSprite++;
			break;
		}
		case 8:
		{
			skyColor = { 136, 193, 174 };
			backgroundSprite++;
			break;
		}
		case 9:
		{
			skyColor = { 153, 201, 190 };
			backgroundSprite++;
			break;
		}
		case 10:
		{
			skyColor = { 170, 219, 206 };
			backgroundSprite++;
			break;
		}
		case 11:
		{
			skyColor = { 187, 237, 222 };
			backgroundSprite++;
			break;
		}
		case 12: //Perfect day
		{
			skyColor = { 204, 255, 238 };
			backgroundSprite++;
			break;
		}
		case 13:
		{
			skyColor = { 187, 237, 222 };
			backgroundSprite++;
			break;
		}
		case 14:
		{
			skyColor = { 170, 219, 206 };
			backgroundSprite++;
			break;
		}
		case 15:
		{
			skyColor = { 153, 201, 190 };
			backgroundSprite++;
			break;
		}
		case 16:
		{
			skyColor = { 136, 193, 174 };
			backgroundSprite++;
			break;
		}
		case 17:
		{
			skyColor = { 119, 175, 158 };
			backgroundSprite++;
			break;
		}
		case 18:
		{
			skyColor = { 102, 157, 142 };
			backgroundSprite++;
			break;
		}
		case 19:
		{
			skyColor = { 85, 139, 126 };
			backgroundSprite++;
			break;
		}
		case 20:
		{
			skyColor = { 68, 121, 110 };
			backgroundSprite++;
			break;
		}
		case 21:
		{
			skyColor = { 51, 103, 94 };
			backgroundSprite++;
			break;
		}
		case 22:
		{
			skyColor = { 34, 85, 78 };
			backgroundSprite++;
			break;
		}
		case 23:
		{
			skyColor = { 17, 67, 62 };
			backgroundSprite++;
			break;
		}
		}

		timeWorld = 0.0f;
	}

	//If is night, because night is starts at 20:00 to 4:00
	if (mobSpawnTime >= 0.3333333f)
	{
		if ((backgroundSprite >= 20 && backgroundSprite <= 23) || (backgroundSprite >= 0 && backgroundSprite <= 4))
		{
			MobSpawning(World::Mob::MobType::Zombie, mobs, 60);
			MobSpawning(World::Mob::MobType::Skeleton, mobs, 30);
			MobSpawning(World::Mob::MobType::Creeper, mobs, 10);
		}
	}
}

void Grid::World::AddOres(Block::BlockType type, World::Block* blocks, float chanceOfSpawningOnEachBlock)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> randomNumber(0.0000000f, 100.0000000f);

	//Create the ores
	int id = 0;
	for (int i = 0; i < Grid::Width; i++)
	{
		for (int j = 0; j < Grid::Height; j++, id++)
		{
			if ((blocks[id].GetType() == Block::BlockType::Stone) &&
				(randomNumber(rng) < chanceOfSpawningOnEachBlock))
			{
				blocks[id].SetType(type);
			}
		}
	}
}

void Grid::World::AddOres(Block::BlockType type, World::Block* blocks, float chanceOfSpawningCentre, float chanceOfCluster, float minChance, float chanceScalar)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> randomNumber(0.0000000f, 100.0000000f);

	std::vector<Block> SpawnerOreCentre;
	std::vector<Block> Branch;

	//Creating the SpawnerOreCentre
	{
		int id = 0;
		for (int i = 0; i < Grid::Width; i++)
		{
			for (int j = 0; j < Grid::Height; j++, id++)
			{
				if ((blocks[id].GetType() == Block::BlockType::Stone) &&
					(randomNumber(rng) < chanceOfSpawningCentre))
				{
					SpawnerOreCentre.push_back(blocks[id]);
					blocks[id].SetType(type);
				}
			}
		}
	}

	//Creating the ore chunking
	for (unsigned int oreCentreIterator = 0; oreCentreIterator < SpawnerOreCentre.size(); oreCentreIterator++)
	{
		float chanceOfChunk = chanceOfCluster;
		
		Branch.push_back(SpawnerOreCentre.at(oreCentreIterator));

		for (unsigned int branchIterator = 0; branchIterator < Branch.size() && chanceOfChunk > minChance; branchIterator++)
		{
				//TOP TESTING
				if (blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))].GetType() == World::Block::BlockType::Stone && randomNumber(rng) < chanceOfChunk)
				{
						Branch.push_back(blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))]);
						blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))].SetType(type);
				}
				//RIGHT TESTING
				if (blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(1, 0))].GetType() == World::Block::BlockType::Stone && randomNumber(rng) < chanceOfChunk)
				{
					Branch.push_back(blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))]);
					blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))].SetType(type);
				}
				//BOTTOM TESTING
				if (blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, 1))].GetType() == World::Block::BlockType::Stone && randomNumber(rng) < chanceOfChunk)
				{
					Branch.push_back(blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))]);
					blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))].SetType(type);
				}
				//LEFT TESTING
				if (blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(-1, 0))].GetType() == World::Block::BlockType::Stone && randomNumber(rng) < chanceOfChunk)
				{
					Branch.push_back(blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))]);
					blocks[GetId(Branch.at(branchIterator).GetLocation() + Vec2(0, -1))].SetType(type);
				}

			chanceOfChunk /= chanceScalar;
		}

		Branch.clear();
	}
}

Grid::Grid(Graphics & gfx)
	:
	gfx(gfx)
{
}

void Grid::DrawCell(Vec2 loc, Color c)
{
	for (int X = int(loc.x) * CellDimensions + Spacing; X < int(loc.x) * CellDimensions + CellDimensions; X++)
	{
		for (int Y = int(loc.y) * CellDimensions + Spacing; Y < int(loc.y) * CellDimensions + CellDimensions; Y++)
		{
			gfx.PutPixel(X, Y, c);
		}
	}
}

void Grid::DrawCell(Vec2 loc, World::Block::BlockType type)
{
	Color blockColor;

	switch (type)
	{
	case Grid::World::Block::BlockType::Air:
	{
		blockColor = world.skyColor;
		break;
	}
	case Grid::World::Block::BlockType::Grass:
	{
		blockColor = { 124, 181, 0 };
		break;
	}
	case Grid::World::Block::BlockType::Dirt:
	{
		blockColor = { 153, 102, 51 };
		break;
	}
	case Grid::World::Block::BlockType::Stone:
	{
		blockColor = { 77, 77, 77 };
		break;
	}
	case Grid::World::Block::BlockType::Water:
	{
		blockColor = { 0, 153, 255 };
		break;
	}
	case Grid::World::Block::BlockType::Coal:
	{
		blockColor = { 51, 26, 0 };
		break;
	}
	case Grid::World::Block::BlockType::Iron:
	{
		blockColor = { 255, 217, 179 };
		break;
	}
	case Grid::World::Block::BlockType::Diamond:
	{
		blockColor = { 26, 255, 209 };
		break;
	}
	}

	for (int X = int(loc.x) * CellDimensions + Spacing; X < int(loc.x) * CellDimensions + CellDimensions; X++)
	{
		for (int Y = int(loc.y) * CellDimensions + Spacing; Y < int(loc.y) * CellDimensions + CellDimensions; Y++)
		{
			gfx.PutPixel(X, Y, blockColor);
		}
	}
}

void Grid::DrawCell(Vec2 loc, World::Mob::MobType type)
{
	Color mobColor;

	switch (type)
	{
	case Grid::World::Mob::MobType::Zombie:
	{
		mobColor = { 64, 128, 0 };
		break;
	}
	case Grid::World::Mob::MobType::Skeleton:
	{
		mobColor = { 102, 102, 102 };
		break;
	}
	case Grid::World::Mob::MobType::Creeper:
	{
		mobColor = { 128, 255, 128 };
		break;
	}
	}

	for (int X = int(loc.x) * CellDimensions + Spacing; X < int(loc.x) * CellDimensions + CellDimensions; X++)
	{
		for (int Y = int(loc.y) * CellDimensions + Spacing; Y < int(loc.y) * CellDimensions + CellDimensions; Y++)
		{
			gfx.PutPixel(X, Y, mobColor);
		}
	}
}

Grid::World::Mob::Mob(Mob::MobType type, Vec2 loc)
	:
	type(type),
	loc(loc)
{
}

void Grid::World::Mob::Draw(Grid & grd)
{
	grd.DrawCell(loc, type);
}

void Grid::World::Mob::Update(float dt)
{
	loc += Vec2(1.0f, 0.0f) * dt;
}

void Grid::World::MobSpawning(Mob::MobType type, std::vector<Mob>& m, int propabillity)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> rand(0, 100);

	if (rand(rng) <= propabillity)
	{
		World::Mob mob = World::Mob(type, Vec2(10.0f, 0.0f));
		m.push_back(mob);
	}
}

int Grid::World::GetId(int _x, int _y)
{
	return _x * Grid::Height + _y;
}

int Grid::World::GetId(Vec2 & v)
{
	return v.x * Grid::Height + v.y;
}

void Grid::World::Player::ClampToScreen()
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

void Grid::World::Player::PlayerWithBlocksCollision(Vec2& dl, std::vector<Grid::World::Block>& b)
{
	//Checking if there is a block on the player's right/left/down/up/diagonals and respond by changing the delta_loc
	if ((dl.x != 0 && dl.y == 0) || (dl.x == 0 && dl.y != 0) || (dl.x != 0 && dl.y != 0))
	{
		for (unsigned int i = 0; i < b.size(); i++)
		{
			if (b.at(i).GetLocation() == loc + dl)
			{
				dl = { 0,0 };
			}
		}
	}
}

void Grid::World::Player::Jump(Keyboard & kbd, Vec2 & dl, std::vector<Grid::World::Block>& b)
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
			for (unsigned int i = 0; i < b.size(); i++)
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
		for (unsigned int i = 0; i < b.size(); i++)
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

Grid::World::Player::Player(const Vec2 in_loc)
{
	loc = in_loc;
}

void Grid::World::Player::MoveBy(const Vec2 delta_loc)
{
	loc += delta_loc;
}

void Grid::World::Player::BlockBreaking(Vec2& mousePos, std::vector<Grid::World::Block>& b)
{
	Vec2 gridPos = mousePos / Grid::CellDimensions;

	gridPos.x = float(int(gridPos.x));
	gridPos.y = float(int(gridPos.y));

	assert(gridPos.x >= 0 && gridPos.x < Grid::Width && gridPos.y >= 0 && gridPos.y < Grid::Height);

	Vec2 distanceBetweenMouseBreakingAndPlayer = gridPos - loc;

	if (distanceBetweenMouseBreakingAndPlayer.GetLength() > float(playerBreakingReach))
	{
	}
	else
	{
		for (unsigned int i = 0; i < b.size(); i++)
		{
			if (b.at(i).GetLocation() == gridPos)
			{
				b.erase(b.begin() + i);
			}
		}
	}
}

void Grid::World::Player::Draw(Grid & grd) const
{
	grd.DrawCell(loc, c);
}

void Grid::World::Player::Update(Keyboard& kbd, Mouse& mouse, std::vector<Grid::World::Block>& b)
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
