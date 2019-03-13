/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include<ctime>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
	// Object state
	glm::vec2   Position, Size;
	glm::vec3   Color;
	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	GLboolean   Ismove;
	GLboolean   countr = GL_FALSE;
	GLboolean   countl = GL_FALSE;
	GLboolean   countu = GL_FALSE;
	GLboolean   countd = GL_FALSE;
	GLboolean   Paoexist;
	GLboolean   Islive=GL_TRUE;
	clock_t     Time=0;
	GLboolean   Rightwalk=GL_TRUE, Leftwalk= GL_TRUE, Upwalk= GL_TRUE, Downwalk= GL_TRUE;
	enum direction { up, down, left, right };
	direction stopdirection;
	// Render state
	Texture2D   Sprite;
	GLint       Velocity;
	GLint       Strength;
	GLint       Paopaonum;
	GLint       Feibiaonum;
	GLint       Livenum;
	GLboolean   Destroyeddonghua;
	// Constructor(s)
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f));
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
};

#endif