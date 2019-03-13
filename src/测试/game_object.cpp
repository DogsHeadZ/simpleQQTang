/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game_object.h"


GameObject::GameObject()
	: Position(0, 0), Size(1, 1), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false), stopdirection(right), Paoexist(false) {
}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: Position(pos), Size(size),  Color(color),  Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), stopdirection(right),Paoexist(false) {
	Velocity = 1; Strength = 1; Paopaonum = 1; Feibiaonum = 2; Livenum = 2; Destroyeddonghua = GL_FALSE;
}

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}