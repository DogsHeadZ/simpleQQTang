/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAME_H
#define GAME_H
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include "game_level.h"

// Represents the current state of the game
enum GameState {
	GAME_START,
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_LOSE
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(49, 49);
// Initial velocity of the player paddle
const GLfloat PLAYER_VELOCITY(200.0f);

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLboolean			   Mouse;
	GLuint                 Width, Height;
	std::vector<GameLevel> Levels;
	GLuint                 Level;
	GLuint                 Daoju;
	glm::vec2              Mouseposition;
	glm::vec2              Gouposition;
	GLint                  Soundchoic;
	enum Color { red, blue, yellow, green, pink, orange, purple, gray };
	Color color;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();
	GLboolean CheckCollision(GameObject &one, GameObject &two, GLint n);
	void ResetLevel();
	void ResetPlayer();
	void Sound();
};

#endif