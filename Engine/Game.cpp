/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	grd(gfx)
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float DT = ft.Mark();;

	//World
	grd.world.Update(DT);
	//World

	//Player
	grd.player.Update(grd.world, wnd.kbd, wnd.mouse, DT);
	//Player

	//Mobs
	for (unsigned int i = 0; i < grd.world.mobs.size(); i++)
	{
		grd.world.mobs[i].Update(grd, DT);
	}
	//Mobs
}

void Game::ComposeFrame()
{
	//World
	for (unsigned int i = 0; i < Grid::Width * Grid::Height; i++)
	{
		grd.world.blocksInGrid[i].Draw(grd);
	}
	//World

	//Player
	grd.player.Draw(grd);
	//Player

	//Mobs
	for (unsigned int i = 0; i < grd.world.mobs.size(); i++)
	{
		grd.world.mobs[i].Draw(grd);
	}
	//Mobs
}
