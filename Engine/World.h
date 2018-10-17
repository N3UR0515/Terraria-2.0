#pragma once

#include "Vec2.h"
#include "Colors.h"
#include <vector>
#include "Noise.h"
#include <random>
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Grid
{
private:
	Graphics& gfx;
public:
	static constexpr int Width = 128; //64
	static constexpr int Height = 64; //32
public:
	//World class
	class World
	{
	public:
		//Block class
		class Block
		{
		public:
			enum class BlockType
			{
				Air,
				Grass,
				Dirt,
				Stone,
				Water,
				Coal,
				Iron,
				Diamond
			};
		public:
			//Functions
			Block() = default;
			Block(Vec2 in_loc, BlockType in_type);
			void Draw(Grid& grd);
			Vec2 GetLocation();
			BlockType GetType();
			void SetType(BlockType _type);
			void SetLocation(Vec2 v);
			//Functions
		private:
			//Data
			Vec2 loc;
			BlockType type;
			//Data
		};
		//Block class

		//Player class
		class Player
		{
		private:
			void ClampToScreen();
			void PlayerWithBlocksCollision(Vec2& dl, Block* blocks);
			void Jump(Keyboard& kbd, Vec2& dl, Block* blocks);
			void MoveBy(const Vec2 delta_loc);
			void BlockBreaking(Vec2& mousePos, Block* blocks);
			void BlockPlacing(Vec2& mousePos, Block* blocks);
		public:
			Player(const Vec2 in_loc);
			void Draw(Grid& grd) const;
			void Update(World& wrd, Keyboard& kbd, Mouse& mouse);
		private:
			Vec2 loc;
			Color c = Colors::Magenta;
			static constexpr int movePeriod = 5;
			int moveCounter = 0;
			bool jumping = false;
			int jumpForce = 3; //Number of blocks the player can jump
			static constexpr char playerBreakingReach = 3;
		};
		//Player class

		//Mob class
		class Mob
		{
		public:
			enum class MobType
			{
				Zombie,
				Skeleton,
				Creeper,
			};
		public:
			//Functions
			Mob(Mob::MobType type, Vec2 loc);
			void Draw(Grid& grd);
			//Functions
		private:
			//Functions
			void Update(float dt);
			//Functions
		private:
			//Data
			Vec2 loc;
			MobType type;
			//Data
		};
		//Mob class
	public:
		//Functions
		World();
		void Update(float dt);
		//Functions
	private:
		//Functions
		void AddOres(Block::BlockType type, World::Block* blocks, float chanceOfSpawningOnEachBlock, std::mt19937& rng);
		void AddOres(Block::BlockType type, World::Block* blocks, float chanceOfSpawningCentre, float chanceOfCluster, float minChance, float chanceScalar, std::mt19937& rng);
		Vec2 FindTunnelEntranceOnSurface(int leftExtremity, int rightExtremity, Block* blocks, std::mt19937& rng);
		void MobSpawning(Mob::MobType type, std::vector<Mob>& m, int propabillity);
		static int GetId(int _x, int _y);
		static int GetId(Vec2& v);
		//Functions
	public:
		//Data
		Block blocksInGrid[Grid::Width * Grid::Height];
		std::vector<Mob> mobs;
		Color skyColor = { 204, 255, 238 };
		//Data
	private:
		//Data
		float timeWorld = 0.0f;
		float mobSpawnTime = 0.0f;
		char backgroundSprite = 12;
		//Data
	};
	//World class

	World::Player player;
	World world;
public:
	static constexpr int CellDimensions = 8; //16
	static constexpr int Spacing = 0; //2

	Grid(Graphics& gfx);
	void DrawCell(Vec2 loc, Color c);
	void DrawCell(Vec2 loc, World::Block::BlockType type);
	void DrawCell(Vec2 loc, World::Mob::MobType type);
};
