/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_level.h"

#include <fstream>
#include <sstream>


void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
	// Clear old data
	this->Bricks.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : this->Bricks)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Dous)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Velocityproperty)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Numproperty)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Strengthproperty)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Feibiaoproperty)
		if (!tile.Destroyed)
			tile.Draw(renderer);
	for (GameObject &tile : this->Liveproperty)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (GameObject &tile : this->Bricks)
		if (!tile.IsSolid && !tile.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / static_cast<GLfloat>(height);
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 0) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(20, 20);
				GameObject obj(pos, size, ResourceManager::GetTexture("豆子"), glm::vec3(1.0f, 1.0f, 1.0f));
				this->Dous.push_back(obj);
			}
			if (tileData[y][x] == 1) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50,50);
				GameObject obj(pos, size, ResourceManager::GetTexture("白板"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 2) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("红中"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 3) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("酒桶"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 4) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("橙色方块"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 5) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("黄色方块"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.Destroyed = GL_FALSE;
				obj.Destroyeddonghua = GL_FALSE;
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 6) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("鼓"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 7) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("植物"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 8) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("功夫木箱"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 9)
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("功夫砖块"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 10) 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("透明"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 11) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("仙人掌"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 12) // 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("井"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 13) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("比"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 14) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("武"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Bricks.push_back(obj);
			}
			if (tileData[y][x] == 21) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("泡泡威力道具"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Strengthproperty.push_back(obj);
			}
			if (tileData[y][x] == 22) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("速度道具"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;;
				this->Velocityproperty.push_back(obj);
			}
			if (tileData[y][x] == 23) //
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("泡泡数量道具"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Numproperty.push_back(obj);
			}
			if (tileData[y][x] == 24) // 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("飞镖图标"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Feibiaoproperty.push_back(obj);
			}
			if (tileData[y][x] == 25) // 
			{
				glm::vec2 pos(50 * x, 50 * y);
				glm::vec2 size(50, 50);
				GameObject obj(pos, size, ResourceManager::GetTexture("叉子"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.IsSolid = GL_FALSE;
				this->Liveproperty.push_back(obj);
			}
		}
	}
}