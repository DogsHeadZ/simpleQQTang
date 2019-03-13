/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "text_renderer.h"
#include "game_object.h"
#include<ctime>
#include<cmath>
#include<string>
#include <irrKlang.h>

using namespace irrklang;
ISoundEngine *SoundEngine = createIrrKlangDevice();
// Game-related State data
SpriteRenderer  *Renderer;
GameObject      *Player;
GameObject      *Player2;
GameObject      *Paopao[6];
GameObject      *Paopao2[6];
GameObject      *Paopaobaozha[6][21];
GameObject      *Paopaobaozha2[6][21];
GameObject      *Monster;
TextRenderer    *Text, *Textproperty, *Texttime;
char Usersname[30];
char Userspassword[30];
char Paopaonum[3];
char Paopaovelocity[3];
char Paopaostrength[3];
char Feibiaonum[3];
char Livenum[3];
char Time[6] = "00:00";
clock_t Gametime;
glm::vec2 Usersnameposition = glm::vec2(711, 268);
glm::vec2 Userspasswordposition = glm::vec2(711, 324);
extern GLboolean Inputname ;
extern GLboolean Inputpassword ;
extern int scene;
extern GLboolean Mapchoose;
extern GLboolean Mapchoice[13];
extern GLboolean Mistakewindow;
int count, countstring, countsound, k = 12, k2 = 12, num = 0, counto = 0, countnum = 0, Monstercount = 0, counte = 0, counttai = 0, num2 = 0, countnum2 = 0, counte2 = 0, counttai2 = 0, countfeibiao, countfeibiaokey, countfeibiaokey2, countlivekey, countlivekey2;
enum { left0, left1, left2, left3, right0, right1, right2, right3, up0, up1, up2, up3, down0, down1, down2, down3 };
std::string Picture[16] = { "0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15" };
std::string Picture2[16] = { "00","100","20","30","40","50","60","70","80","90","1000","110","120","130","140","150" };
GLint Feature;
std::string Map[13] = { "机械世界","夺宝","英雄","足球","抢包山","糖客战","比武","功夫","水面","野外","中国城","沙漠","矿洞" };
std::string Map2[13] = { "机械世界2","夺宝2","英雄2","足球2","抢包山2","糖客战2","比武2","功夫2","水面2","野外2","中国城2","沙漠2","矿洞2" };
std::string Mapbackground[13] = { "机械世界背景","夺宝背景","英雄背景","足球背景","抢包山背景","糖客战背景","比武背景","功夫背景","水面背景","野外背景","中国城背景","沙漠背景","矿洞背景" };
//std::string Paopaostrength[16] = { "22101","11121","21121","321211","42111","5121","61212","17","81","91","110","111","112","131","114","115" };
clock_t startl, startr, startu, startd;
GLboolean Feibiaoexist=GL_FALSE;
GLboolean Feibiaomove = GL_FALSE;
glm::vec2 Feibiaoposition = glm::vec2(0, 0);
int Feibiaodirection;
GLboolean CheckCollision2(GameObject &one, GameObject &two);
GLboolean CheckCollisiondaoju(GameObject &one, GameObject &two);
GLboolean CheckCollisionMonster(GameObject &one, GameObject &two);
Game::Game(GLuint width, GLuint height)
	: State(GAME_MENU), Keys(), Mouse(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete Player;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("底面背景.png", true, "底面背景");
	ResourceManager::LoadTexture("背景.jpg", GL_FALSE, "中国城背景");
	ResourceManager::LoadTexture("登陆界面.jpg", GL_FALSE, "登陆界面");
	ResourceManager::LoadTexture("登陆时的线.png", true, "登陆时的线");
	ResourceManager::LoadTexture("Mistakewindow.png", true, "Mistakewindow");
	ResourceManager::LoadTexture("房间界面.png", true, "房间界面");
	ResourceManager::LoadTexture("选颜色的勾.png", true, "选颜色的勾");
	ResourceManager::LoadTexture("选择地图.png", true, "选择地图");
	ResourceManager::LoadTexture("机械世界小地图.png", true, "机械世界");
	ResourceManager::LoadTexture("机械世界大地图.png", true, "机械世界2");
	ResourceManager::LoadTexture("夺宝小地图.png", true, "夺宝");
	ResourceManager::LoadTexture("夺宝大地图.png", true, "夺宝2");
	ResourceManager::LoadTexture("英雄小地图.png", true, "英雄");
	ResourceManager::LoadTexture("英雄大地图.png", true, "英雄2");
	ResourceManager::LoadTexture("足球小地图.png", true, "足球");
	ResourceManager::LoadTexture("足球大地图.png", true, "足球2");
	ResourceManager::LoadTexture("抢包山小地图.png", true, "抢包山");
	ResourceManager::LoadTexture("抢包山大地图.png", true, "抢包山2");
	ResourceManager::LoadTexture("糖客战小地图.png", true, "糖客战");
	ResourceManager::LoadTexture("糖客战大地图.png", true, "糖客战2");
	ResourceManager::LoadTexture("比武小地图.png", true, "比武");
	ResourceManager::LoadTexture("比武大地图.png", true, "比武2");
	ResourceManager::LoadTexture("功夫小地图.png", true, "功夫");
	ResourceManager::LoadTexture("功夫大地图.png", true, "功夫2");
	ResourceManager::LoadTexture("水面小地图.png", true, "水面");
	ResourceManager::LoadTexture("水面大地图.png", true, "水面2");
	ResourceManager::LoadTexture("野外小地图.png", true, "野外");
	ResourceManager::LoadTexture("野外大地图.png", true, "野外2");
	ResourceManager::LoadTexture("新年瑞兽小地图.png", true, "中国城");
	ResourceManager::LoadTexture("新年瑞兽大地图.png", true, "中国城2");
	ResourceManager::LoadTexture("爱的体验小地图.png", true, "沙漠");
	ResourceManager::LoadTexture("爱的体验大地图.png", true, "沙漠2");
	ResourceManager::LoadTexture("矿洞小地图.png", true, "矿洞");
	ResourceManager::LoadTexture("矿洞大地图.png", true, "矿洞2");
	ResourceManager::LoadTexture("底面背景.png", true, "底面背景");
	ResourceManager::LoadTexture("机械世界背景.png", true, "机械世界背景");
	ResourceManager::LoadTexture("夺宝背景.png", true, "夺宝背景");
	ResourceManager::LoadTexture("英雄背景.png", true, "英雄背景");
	ResourceManager::LoadTexture("足球背景.png", true, "足球背景");
	ResourceManager::LoadTexture("抢包山背景.png", true, "抢包山背景");
	ResourceManager::LoadTexture("糖客战背景.png", true, "糖客战背景");
	ResourceManager::LoadTexture("比武背景.png", true, "比武背景");
	ResourceManager::LoadTexture("功夫背景.png", true, "功夫背景");
	ResourceManager::LoadTexture("水面背景.png", true, "水面背景");
	ResourceManager::LoadTexture("野外背景.png", true, "野外背景");
	ResourceManager::LoadTexture("新年瑞兽背景.png", true, "中国城背景");
	ResourceManager::LoadTexture("爱的体验背景.png", true, "沙漠背景");
	ResourceManager::LoadTexture("矿洞背景.png", true, "矿洞背景");
	ResourceManager::LoadTexture("透明.png", true, "透明");
	ResourceManager::LoadTexture("白板.png", true, "白板");
	ResourceManager::LoadTexture("红中.png", true, "红中");
	ResourceManager::LoadTexture("酒桶.png", true, "酒桶");
	ResourceManager::LoadTexture("鼓.png", true, "鼓");
	ResourceManager::LoadTexture("橙色方块.png", true, "橙色方块");
	ResourceManager::LoadTexture("黄色方块.png", true, "黄色方块");
	ResourceManager::LoadTexture("植物.png", true, "植物");
	ResourceManager::LoadTexture("仙人掌.png", true, "仙人掌");
	ResourceManager::LoadTexture("井.png", true, "井");
	ResourceManager::LoadTexture("豆子.png", true, "豆子");
	ResourceManager::LoadTexture("功夫木箱.png", true, "功夫木箱");
	ResourceManager::LoadTexture("功夫砖块.png", true, "功夫砖块");
	ResourceManager::LoadTexture("比.png", true, "比");
	ResourceManager::LoadTexture("武.png", true, "武");
	ResourceManager::LoadTexture("泡泡数量道具.png", true, "泡泡数量道具");
	ResourceManager::LoadTexture("泡泡威力道具.png", true, "泡泡威力道具");
	ResourceManager::LoadTexture("速度道具.png", true, "速度道具");
	ResourceManager::LoadTexture("叉子.png", true, "叉子");
	ResourceManager::LoadTexture("飞镖图标.png", true, "飞镖图标");
	ResourceManager::LoadTexture("飞镖右.png", true, "飞镖右");
	ResourceManager::LoadTexture("飞镖上.png", true, "飞镖上");
	ResourceManager::LoadTexture("飞镖左.png", true, "飞镖左");
	ResourceManager::LoadTexture("飞镖下.png", true, "飞镖下");
	ResourceManager::LoadTexture("泡泡.png", true, "泡泡");
	ResourceManager::LoadTexture("泡泡爆炸中心.png", true, "泡泡爆炸中心");
	ResourceManager::LoadTexture("泡泡爆炸右.png", true, "泡泡爆炸右");
	ResourceManager::LoadTexture("泡泡爆炸左.png", true, "泡泡爆炸左");
	ResourceManager::LoadTexture("泡泡爆炸上.png", true, "泡泡爆炸上");
	ResourceManager::LoadTexture("泡泡爆炸下.png", true, "泡泡爆炸下");
	ResourceManager::LoadTexture("泡泡爆炸末尾右.png", true, "泡泡爆炸末尾右");
	ResourceManager::LoadTexture("泡泡爆炸末尾上.png", true, "泡泡爆炸末尾上");
	ResourceManager::LoadTexture("泡泡爆炸末尾左.png", true, "泡泡爆炸末尾左");
	ResourceManager::LoadTexture("泡泡爆炸末尾下.png", true, "泡泡爆炸末尾下");
	ResourceManager::LoadTexture("黏泡泡.png", true, "黏泡泡");
	//人物1
	ResourceManager::LoadTexture("人物左静止.png", true, Picture[left0]);
	ResourceManager::LoadTexture("人物左1.png", true, Picture[left1]);
	ResourceManager::LoadTexture("人物左2.png", true, Picture[left2]);
	ResourceManager::LoadTexture("人物左3.png", true, Picture[left3]);
	ResourceManager::LoadTexture("人物右静止.png", true, Picture[right0]);
	ResourceManager::LoadTexture("人物右1.png", true, Picture[right1]);
	ResourceManager::LoadTexture("人物右2.png", true, Picture[right2]);
	ResourceManager::LoadTexture("人物右3.png", true, Picture[right3]);
	ResourceManager::LoadTexture("人物上静止.png", true, Picture[up0]);
	ResourceManager::LoadTexture("人物上1.png", true, Picture[up1]);
	ResourceManager::LoadTexture("人物上2.png", true, Picture[up2]);
	ResourceManager::LoadTexture("人物上3.png", true, Picture[up3]);
	ResourceManager::LoadTexture("人物下静止.png", true, Picture[down0]);
	ResourceManager::LoadTexture("人物下1.png", true, Picture[down1]);
	ResourceManager::LoadTexture("人物下2.png", true, Picture[down2]);
	ResourceManager::LoadTexture("人物下3.png", true, Picture[down3]);
	//人物2
	ResourceManager::LoadTexture("人物2左静止.png", true, Picture2[left0]);
	ResourceManager::LoadTexture("人物2左1.png", true, Picture2[left1]);
	ResourceManager::LoadTexture("人物2左2.png", true, Picture2[left2]);
	ResourceManager::LoadTexture("人物2左3.png", true, Picture2[left3]);
	ResourceManager::LoadTexture("人物2右静止.png", true, Picture2[right0]);
	ResourceManager::LoadTexture("人物2右1.png", true, Picture2[right1]);
	ResourceManager::LoadTexture("人物2右2.png", true, Picture2[right2]);
	ResourceManager::LoadTexture("人物2右3.png", true, Picture2[right3]);
	ResourceManager::LoadTexture("人物2上静止.png", true, Picture2[up0]);
	ResourceManager::LoadTexture("人物2上1.png", true, Picture2[up1]);
	ResourceManager::LoadTexture("人物2上2.png", true, Picture2[up2]);
	ResourceManager::LoadTexture("人物2上3.png", true, Picture2[up3]);
	ResourceManager::LoadTexture("人物2下静止.png", true, Picture2[down0]);
	ResourceManager::LoadTexture("人物2下1.png", true, Picture2[down1]);
	ResourceManager::LoadTexture("人物2下2.png", true, Picture2[down2]);
	ResourceManager::LoadTexture("人物2下3.png", true, Picture2[down3]);
	SoundEngine->play2D("M09.ogg", GL_TRUE);
	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//set font
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("simhei.TTF", 24);
	Textproperty = new TextRenderer(this->Width, this->Height);
	Textproperty->Load("impact.TTF", 24);
	Texttime = new TextRenderer(this->Width, this->Height);
	Texttime->Load("comicbd.TTF", 48);
	// Load levels
	GameLevel one; one.Load("levels/ZJU.txt", this->Width, this->Height);
	GameLevel two; two.Load("levels/新年瑞兽.txt", this->Width, this->Height);
	GameLevel three; three.Load("levels/新年瑞兽道具.txt", this->Width, this->Height);
	GameLevel four; four.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel five; five.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel six; six.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel seven; seven.Load("levels/比武.txt", this->Width, this->Height);
	GameLevel eight; eight.Load("levels/功夫.txt", this->Width, this->Height);
	GameLevel nine; nine.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel ten; ten.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel eleven; eleven.Load("levels/新年瑞兽.txt", this->Width, this->Height);
	GameLevel twelve; twelve.Load("levels/爱的体验.txt", this->Width, this->Height);
	GameLevel thirteen; thirteen.Load("levels/爱的体验.txt", this->Width, this->Height);
	//道具
	GameLevel fourteen; 
	GameLevel fifteen; 
	GameLevel sixteen; 
	GameLevel seventeen; 
	GameLevel eighteen; 
	GameLevel nineteen; 
	GameLevel twenty; 
	GameLevel twentyone; 
	GameLevel twentytwo; 
	GameLevel twentythree; 
	GameLevel twentyfour; 
	GameLevel twentyfive;
	GameLevel twentysix; 
	//关卡
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Levels.push_back(five);
	this->Levels.push_back(six);
	this->Levels.push_back(seven);
	this->Levels.push_back(eight);
	this->Levels.push_back(nine);
	this->Levels.push_back(ten);
	this->Levels.push_back(eleven);
	this->Levels.push_back(twelve);
	this->Levels.push_back(thirteen);
	//道具
	this->Levels.push_back(fourteen);
	this->Levels.push_back(fifteen);
	this->Levels.push_back(sixteen);
	this->Levels.push_back(seventeen);
	this->Levels.push_back(eighteen);
	this->Levels.push_back(nineteen);
	this->Levels.push_back(twenty);
	this->Levels.push_back(twentyone);
	this->Levels.push_back(twentytwo);
	this->Levels.push_back(twentythree);
	this->Levels.push_back(twentyfour);
	this->Levels.push_back(twentyfive);
	this->Levels.push_back(twentysix);
	this->Level = 3;
	this->Daoju = 2;
	// Configure game objects
	glm::vec2 playerPos = glm::vec2(200, 0);
	this->Gouposition = glm::vec2(650, 400);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture(Picture[right0]), glm::vec3(0.9686f, 0.1176f, 0.1098f));
	Player2 = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture(Picture[right0]), glm::vec3(0.0627f, 0.2353, 0.7843f));
	for (int i = 0; i < 6; i++) {
		Paopao[i] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡"));
		Paopao2[i] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡"));
	}
	for (int i = 0; i < 6; i++) {
		Paopaobaozha[i][0] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸中心"));
		Paopaobaozha2[i][0] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸中心"));
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 1; j <= 5; j++) {
			Paopaobaozha[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸右"));
			Paopaobaozha2[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸右"));
		}
		for (int j = 6; j <= 10; j++) {
			Paopaobaozha[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸上"));
			Paopaobaozha2[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸上"));
		}
		for (int j = 11; j <= 15; j++) {
			Paopaobaozha[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸左"));
			Paopaobaozha2[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸左"));
		}
		for (int j = 16; j <= 20; j++) {
			Paopaobaozha[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸下"));
			Paopaobaozha2[i][j] = new GameObject(glm::vec2(-50, -50), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡爆炸下"));
		}
	}
	Monster = new GameObject(glm::vec2(100, 100), glm::vec2(50, 50), ResourceManager::GetTexture("泡泡"), glm::vec3(1.0f, 1.0f, 1.0f));
	Monster->Velocity = 1;
}

void Game::Update(GLfloat dt)
{
	countsound++;
	this->DoCollisions();
}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		if (this->Mouse) {
			;
		}
		GLfloat PlayerVelocity = (150 + (Player->Velocity - 1) * 50) * dt;
		GLfloat Player2Velocity = (150 + (Player2->Velocity - 1) * 50) * dt;
		GLfloat MonsterVelocity = (150 + 50 * Monster->Velocity)* dt;
		//测试用外挂
		if (this->Keys[GLFW_KEY_F5] && !countfeibiaokey) {
			Feibiaoexist = GL_TRUE;
			countfeibiao = 1;
			countfeibiaokey = 1;
		}
		if (!this->Keys[GLFW_KEY_F5]) {
			countfeibiaokey = 0;
		}
		if (this->Keys[GLFW_KEY_F2]) {
			Player->Velocity = 4;
			Player->Paopaonum = 6;
			Player->Strength = 5;
		}
		if (!Player->Islive) {
			if (this->Keys[GLFW_KEY_2] && !countlivekey&&Player->Livenum > 0) {
				Player->Islive = GL_TRUE;
				Player->Size = PLAYER_SIZE;
				Player->Position.x += 20;
				Player->Position.y += 20;
				countlivekey = 1;
			}
			if (this->Keys[GLFW_KEY_F1]) {
				Player->Islive = GL_TRUE;
				Player->Size = PLAYER_SIZE;
				Player->Position.x += 20;
				Player->Position.y += 20;
			}
		}
		if (!this->Keys[GLFW_KEY_2] && countlivekey) {
			countlivekey = 0;
			Player->Livenum--;
		}
		if (this->Keys[GLFW_KEY_F4]) {
			Player2->Velocity = 4;
			Player2->Paopaonum = 6;
			Player2->Strength = 5;
		}
		if (!Player2->Islive) {
			if (this->Keys[GLFW_KEY_F3]) {
				Player2->Islive = GL_TRUE;
				Player2->Size = PLAYER_SIZE;
				Player2->Position.x += 20;
				Player2->Position.y += 20;
			}
		}
		// Move player
		if (Player->Islive) {
			//飞镖
			if (this->Keys[GLFW_KEY_1] && !countfeibiaokey2&&Player->Feibiaonum > 0) {
				Feibiaoexist = GL_TRUE;
				countfeibiao = 1;
				countfeibiaokey2 = 1;
			}
			if (!this->Keys[GLFW_KEY_1] && countfeibiaokey2) {
				countfeibiaokey2 = 0;
				Player->Feibiaonum--;
			}
			if (Feibiaomove) {
				if (k >= right0&&k <= right3&&countfeibiao) {
					Feibiaodirection = 1;
					countfeibiao = 0;
				}
				if (k >= up0&&k <= up3&&countfeibiao) {
					Feibiaodirection = 2;
					countfeibiao = 0;
				}
				if (k >= left0&&k <= left3&&countfeibiao) {
					Feibiaodirection = 3;
					countfeibiao = 0;
				}
				if (k >= down0&&k <= down3&&countfeibiao) {
					Feibiaodirection = 4;
					countfeibiao = 0;
				}
				if (Feibiaodirection == 1) {
					Feibiaoposition.x += 5 * PlayerVelocity;
					for (int i = 0; i < Player->Paopaonum; i++) {
						if (abs(Paopao[i]->Position.x - Feibiaoposition.x - 50) <= 5 && abs(Paopao[i]->Position.y - Feibiaoposition.y) <= 30) {
							this->Soundchoic = 4;
							this->Sound();
							Paopao[i]->Paoexist = GL_FALSE;
							Paopaobaozha[i][0]->Paoexist = GL_TRUE;
							Paopaobaozha[i][0]->Time = clock();
							Paopaobaozha[i][0]->Position.x = Paopao[i]->Position.x;
							Paopaobaozha[i][0]->Position.y = Paopao[i]->Position.y;
							Paopaobaozha[i][0]->Size = glm::vec2(50, 50);
							Paopao[i]->Position = glm::vec2(-50, -50);
							Feibiaoexist = GL_FALSE;
							Feibiaomove = GL_FALSE;
							Feibiaoposition = glm::vec2(-50, -50);
						}
					}
				}
				if (Feibiaodirection == 2) {
					Feibiaoposition.y -= 5 * PlayerVelocity;
					for (int i = 0; i < Player->Paopaonum; i++) {
						if (abs(Paopao[i]->Position.y - Feibiaoposition.y + 50) <= 5 && abs(Paopao[i]->Position.x - Feibiaoposition.x) <= 30) {
							this->Soundchoic = 4;
							this->Sound();
							Paopao[i]->Paoexist = GL_FALSE;
							Paopaobaozha[i][0]->Paoexist = GL_TRUE;
							Paopaobaozha[i][0]->Time = clock();
							Paopaobaozha[i][0]->Position.x = Paopao[i]->Position.x;
							Paopaobaozha[i][0]->Position.y = Paopao[i]->Position.y;
							Paopaobaozha[i][0]->Size = glm::vec2(50, 50);
							Paopao[i]->Position = glm::vec2(-50, -50);
							Feibiaoexist = GL_FALSE;
							Feibiaomove = GL_FALSE;
							Feibiaoposition = glm::vec2(-50, -50);
						}
					}
				}
				if (Feibiaodirection == 3) {
					Feibiaoposition.x -= 5 * PlayerVelocity;
					for (int i = 0; i < Player->Paopaonum; i++) {
						if (abs(Paopao[i]->Position.x - Feibiaoposition.x + 50) <= 5 && abs(Paopao[i]->Position.y - Feibiaoposition.y) <= 30) {
							this->Soundchoic = 4;
							this->Sound();
							Paopao[i]->Paoexist = GL_FALSE;
							Paopaobaozha[i][0]->Paoexist = GL_TRUE;
							Paopaobaozha[i][0]->Time = clock();
							Paopaobaozha[i][0]->Position.x = Paopao[i]->Position.x;
							Paopaobaozha[i][0]->Position.y = Paopao[i]->Position.y;
							Paopaobaozha[i][0]->Size = glm::vec2(50, 50);
							Paopao[i]->Position = glm::vec2(-50, -50);
							Feibiaoexist = GL_FALSE;
							Feibiaomove = GL_FALSE;
							Feibiaoposition = glm::vec2(-50, -50);
						}
					}
				}
				if (Feibiaodirection == 4) {
					Feibiaoposition.y += 5 * PlayerVelocity;
					for (int i = 0; i < Player->Paopaonum; i++) {
						if (abs(Paopao[i]->Position.y - Feibiaoposition.y - 50) <= 5 && abs(Paopao[i]->Position.x - Feibiaoposition.x) <= 30) {
							this->Soundchoic = 4;
							this->Sound();
							Paopao[i]->Paoexist = GL_FALSE;
							Paopaobaozha[i][0]->Paoexist = GL_TRUE;
							Paopaobaozha[i][0]->Time = clock();
							Paopaobaozha[i][0]->Position.x = Paopao[i]->Position.x;
							Paopaobaozha[i][0]->Position.y = Paopao[i]->Position.y;
							Paopaobaozha[i][0]->Size = glm::vec2(50, 50);
							Paopao[i]->Position = glm::vec2(-50, -50);
							Feibiaoexist = GL_FALSE;
							Feibiaomove = GL_FALSE;
							Feibiaoposition = glm::vec2(-50, -50);
						}
					}
				}
				if (Feibiaoposition.x >= 1200 || Feibiaoposition.x <= -100 || Feibiaoposition.y >= 1000 || Feibiaoposition.y <= -100) {
					Feibiaoexist = GL_FALSE;
					Feibiaomove = GL_FALSE;
				}
			}
			//人物
			if (this->Keys[GLFW_KEY_LEFT] && Player->Leftwalk)
			{
				startl = clock();
				Player->Ismove = GL_TRUE;
				//Player->stopdirection = GameObject::direction::left;
				k = left0;
				if (Player->Position.x >= 0)
					Player->Position.x -= PlayerVelocity;
				//return;
			}
			else
				if (this->Keys[GLFW_KEY_RIGHT] && Player->Rightwalk)
				{
					startr = clock();
					Player->Ismove = GL_TRUE;
					//Player->stopdirection = GameObject::direction::right;
					k = right0;
					if (Player->Position.x <= this->Width - Player->Size.x)
						Player->Position.x += PlayerVelocity;
					//return;
				}
				else
					if (this->Keys[GLFW_KEY_UP] && Player->Upwalk)
					{
						startu = clock();
						Player->Ismove = GL_TRUE;
						//Player->stopdirection = GameObject::direction::up;
						k = up0;
						if (Player->Position.x <= this->Width - Player->Size.x)
							Player->Position.y -= PlayerVelocity;
						//return;
					}
					else
						if (this->Keys[GLFW_KEY_DOWN] && Player->Downwalk)
						{
							startd = clock();
							Player->Ismove = GL_TRUE;
							//Player->stopdirection = GameObject::direction::down;
							k = down0;
							if (Player->Position.x <= this->Width - Player->Size.x)
								Player->Position.y += PlayerVelocity;
							//return;
						}
						else
							Player->Ismove = GL_FALSE;
		}

		if (Player2->Islive) {
			if (this->Keys[GLFW_KEY_A] && Player2->Leftwalk)
			{
				startl = clock();
				Player2->Ismove = GL_TRUE;
				//Player->stopdirection = GameObject::direction::left;
				k2 = left0;
				if (Player2->Position.x >= 0)
					Player2->Position.x -= Player2Velocity;
				//return;
			}
			else
				if (this->Keys[GLFW_KEY_D] && Player2->Rightwalk)
				{
					startr = clock();
					Player2->Ismove = GL_TRUE;
					//Player->stopdirection = GameObject::direction::right;
					k2 = right0;
					if (Player2->Position.x <= this->Width - Player2->Size.x)
						Player2->Position.x += Player2Velocity;
					//return;
				}
				else
					if (this->Keys[GLFW_KEY_W] && Player2->Upwalk)
					{
						startu = clock();
						Player2->Ismove = GL_TRUE;
						//Player->stopdirection = GameObject::direction::up;
						k2 = up0;
						if (Player2->Position.x <= this->Width - Player->Size.x)
							Player2->Position.y -= Player2Velocity;
						//return;
					}
					else
						if (this->Keys[GLFW_KEY_S] && Player2->Downwalk)
						{
							startd = clock();
							Player2->Ismove = GL_TRUE;
							//Player->stopdirection = GameObject::direction::down;
							k2 = down0;
							if (Player2->Position.x <= this->Width - Player2->Size.x)
								Player2->Position.y += Player2Velocity;
							//return;
						}
						else
							Player2->Ismove = GL_FALSE;
		}

		int sx = 0, sy = 0;
		if (this->Keys[GLFW_KEY_SPACE] && num < Player->Paopaonum) {
			double sdistance = 10000, distance;
			if (!Paopao[num]->Paoexist || countnum>0) {
				for (int x = 0; x < 15; x++)
					for (int y = 0; y < 15; y++) {
						distance = abs(Player->Position.x - 50 * x) + abs(Player->Position.y - 50 * y);
						if (distance < sdistance) {
							sdistance = distance;
							sx = x;
							sy = y;
						}
					}
				//使有泡泡的地方不能再放泡泡
				for (int i = 0; i < Player->Paopaonum; i++) {
					if (i != num && 50 * sx == Paopao[i]->Position.x && 50 * sy == Paopao[i]->Position.y) {
						counte = 0;
						break;
					}
					counte = 1;
				}
				if (counte == 1) {
					countnum++;
					if (countnum > 20000)
						countnum = 2;
				}
			}
			counttai = 1;
		}
		if (countnum == 1) {
			Paopao[num]->Time = clock();
			Paopao[num]->Position = glm::vec2(50 * sx, 50 * sy);
			Paopao[num]->Paoexist = GL_TRUE;
		}
		if (!this->Keys[GLFW_KEY_SPACE] && num < Player->Paopaonum) {
			//num++;
			countnum = 0;
			counttai = 0;
		}

		for (int i = 0; i < Player->Paopaonum; i++) {
			if (!Paopao[i]->Paoexist && !Paopaobaozha[i][0]->Paoexist&&counttai == 0) {
				num = i;
				countnum = 0;
				break;
			}
		}

		//if (num == 5 && !Paopao[0]->Paoexist&&Paopao[5]->Paoexist||Paopaobaozha[5]->Paoexist ) {
		//	num = 0;
		//	countnum = 0;
		//}
		int sx2 = 0, sy2 = 0;
		if (this->Keys[GLFW_KEY_ENTER] && num2 < Player2->Paopaonum) {
			double sdistance2 = 10000, distance2;
			if (!Paopao2[num2]->Paoexist || countnum2>0) {
				for (int x = 0; x < 15; x++)
					for (int y = 0; y < 15; y++) {
						distance2 = abs(Player2->Position.x - 50 * x) + abs(Player2->Position.y - 50 * y);
						if (distance2 < sdistance2) {
							sdistance2 = distance2;
							sx2 = x;
							sy2 = y;
						}
					}
				//使有泡泡的地方不能再放泡泡
				for (int i = 0; i < Player2->Paopaonum; i++) {
					if (i != num2 && 50 * sx2 == Paopao2[i]->Position.x && 50 * sy2 == Paopao2[i]->Position.y) {
						counte2 = 0;
						break;
					}
					counte2 = 1;
				}
				if (counte2 == 1) {
					countnum2++;
					if (countnum2 > 20000)
						countnum2 = 2;
				}
			}
			counttai2 = 1;
		}
		if (countnum2 == 1) {
			Paopao2[num2]->Time = clock();
			Paopao2[num2]->Position = glm::vec2(50 * sx2, 50 * sy2);
			Paopao2[num2]->Paoexist = GL_TRUE;
		}
		if (!this->Keys[GLFW_KEY_ENTER] && num2 < Player2->Paopaonum) {
			//num++;
			countnum2 = 0;
			counttai2 = 0;
		}

		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (!Paopao2[i]->Paoexist && !Paopaobaozha2[i][0]->Paoexist&&counttai2 == 0) {
				num2 = i;
				countnum2 = 0;
				break;
			}
		}
		//泡泡爆炸
		for (int i = 0; i < Player->Paopaonum; i++)
			if (clock() - Paopao[i]->Time >= 3.3 * CLOCKS_PER_SEC&&Paopao[i]->Paoexist) {
				this->Soundchoic = 4;
				this->Sound();
				Paopao[i]->Paoexist = GL_FALSE;
				Paopaobaozha[i][0]->Paoexist = GL_TRUE;
				Paopaobaozha[i][0]->Time = clock();
				Paopaobaozha[i][0]->Position.x = Paopao[i]->Position.x ;
				Paopaobaozha[i][0]->Position.y = Paopao[i]->Position.y ;
				Paopaobaozha[i][0]->Size = glm::vec2(50, 50);
				//if (CheckCollision(*Player, *Paopao[i]))
				//this->State = GAME_LOSE;
				Paopao[i]->Position = glm::vec2(-50, -50);
			}

		for (int i = 0; i < Player2->Paopaonum; i++)
			if (clock() - Paopao2[i]->Time >= 3.3 * CLOCKS_PER_SEC&&Paopao2[i]->Paoexist) {
				this->Soundchoic = 4;
				this->Sound();
				Paopao2[i]->Paoexist = GL_FALSE;
				Paopaobaozha2[i][0]->Paoexist = GL_TRUE;
				Paopaobaozha2[i][0]->Time = clock();
				Paopaobaozha2[i][0]->Position.x = Paopao2[i]->Position.x;
				Paopaobaozha2[i][0]->Position.y = Paopao2[i]->Position.y;
				Paopaobaozha2[i][0]->Size = glm::vec2(50, 50);
				//if (CheckCollision(*Player, *Paopao[i]))
				//this->State = GAME_LOSE;
				Paopao2[i]->Position = glm::vec2(-50, -50);
			}

		for (int i = 0; i < Player->Paopaonum; i++) {
			if (Paopaobaozha[i][0]->Paoexist) {
				for (int j = 1; j <= Player->Strength; j++) {
					int flag = 0;
					Paopaobaozha[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha[i][j]->Position.x = Paopaobaozha[i][0]->Position.x + 50 * j;
					Paopaobaozha[i][j]->Position.y = Paopaobaozha[i][0]->Position.y;
					Paopaobaozha[i][j]->Sprite= ResourceManager::GetTexture("泡泡爆炸右");
					if (j == Player->Strength)
						Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾右");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾右");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 6; j <= 5 + Player->Strength; j++) {
					int flag = 0;
					Paopaobaozha[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha[i][j]->Position.x = Paopaobaozha[i][0]->Position.x;
					Paopaobaozha[i][j]->Position.y = Paopaobaozha[i][0]->Position.y - 50 * (j - 5);
					Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸上");
					if (j == 5 + Player->Strength)
						Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾上");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾上");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 11; j <= 10 + Player->Strength; j++) {
					int flag = 0;
					Paopaobaozha[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha[i][j]->Position.x = Paopaobaozha[i][0]->Position.x - 50 * (j - 10);
					Paopaobaozha[i][j]->Position.y = Paopaobaozha[i][0]->Position.y;
					Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸左");
					if (j == 10 + Player->Strength)
						Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾左");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾左");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 16; j <= 15 + Player->Strength; j++) {
					int flag = 0;
					Paopaobaozha[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha[i][j]->Position.x = Paopaobaozha[i][0]->Position.x;
					Paopaobaozha[i][j]->Position.y = Paopaobaozha[i][0]->Position.y + 50 * (j - 15);
					Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸下");
					if(j == 15 + Player->Strength)
						Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾下");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾下");
							break;
						}
					}
					if (flag) break;
				}
			}
		}

		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (Paopaobaozha2[i][0]->Paoexist) {
				for (int j = 1; j <= Player2->Strength; j++) {
					int flag = 0;
					Paopaobaozha2[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha2[i][j]->Position.x = Paopaobaozha2[i][0]->Position.x + 50 * j;
					Paopaobaozha2[i][j]->Position.y = Paopaobaozha2[i][0]->Position.y;
					Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸右");
					if (j == Player2->Strength)
						Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾右");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾右");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 6; j <= 5 + Player2->Strength; j++) {
					int flag = 0;
					Paopaobaozha2[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha2[i][j]->Position.x = Paopaobaozha2[i][0]->Position.x;
					Paopaobaozha2[i][j]->Position.y = Paopaobaozha2[i][0]->Position.y - 50 * (j - 5);
					Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸上");
					if (j == 5 + Player2->Strength)
						Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾上");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾上");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 11; j <= 10 + Player2->Strength; j++) {
					int flag = 0;
					Paopaobaozha2[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha2[i][j]->Position.x = Paopaobaozha2[i][0]->Position.x - 50 * (j - 10);
					Paopaobaozha2[i][j]->Position.y = Paopaobaozha2[i][0]->Position.y;
					Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸左");
					if (j == 10 + Player2->Strength)
						Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾左");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾左");
							break;
						}
					}
					if (flag) break;
				}
				for (int j = 16; j <= 15 + Player2->Strength; j++) {
					int flag = 0;
					Paopaobaozha2[i][j]->Paoexist = GL_TRUE;
					Paopaobaozha2[i][j]->Position.x = Paopaobaozha2[i][0]->Position.x;
					Paopaobaozha2[i][j]->Position.y = Paopaobaozha2[i][0]->Position.y + 50 * (j - 15);
					Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸下");
					if (j == 15 + Player2->Strength)
						Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾下");
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && (!box.Destroyeddonghua || box.IsSolid)) {
							flag = 1;
							Paopaobaozha2[i][j]->Sprite = ResourceManager::GetTexture("泡泡爆炸末尾下");
							break;
						}
					}
					if (flag) break;
				}
			}
		}

		//泡泡联动爆炸
		for (int i = 0; i < Player->Paopaonum; i++) {
			if (Paopaobaozha[i][0]->Paoexist)
				for (int j = 0; j < Player->Paopaonum; j++) {
					if (j != i) {
						for (int k = 0; k < 21; k++) {
							if (Paopaobaozha[i][k]->Paoexist) {
								if (abs(Paopao[j]->Position.x - Paopaobaozha[i][k]->Position.x) <= 1 && abs(Paopao[j]->Position.y - Paopaobaozha[i][k]->Position.y) <= 1)
								{
									Paopao[j]->Paoexist = GL_FALSE;
									Paopaobaozha[j][0]->Paoexist = GL_TRUE;
									Paopaobaozha[j][0]->Time = clock();
									Paopaobaozha[j][0]->Position.x = Paopao[j]->Position.x;
									Paopaobaozha[j][0]->Position.y = Paopao[j]->Position.y;
									Paopaobaozha[j][0]->Size = glm::vec2(50, 50);
									Paopao[j]->Position = glm::vec2(-50, -50);
								}
							}
						}
					}
				}
		}

		for (int i = 0; i < Player->Paopaonum; i++) {
			if (Paopaobaozha[i][0]->Paoexist)
				for (int j = 0; j < Player2->Paopaonum; j++) {
					for (int k = 0; k < 21; k++) {
						if (Paopaobaozha[i][k]->Paoexist) {
							if (abs(Paopao2[j]->Position.x - Paopaobaozha[i][k]->Position.x) <= 1 && abs(Paopao2[j]->Position.y - Paopaobaozha[i][k]->Position.y) <= 1)
							{
								Paopao2[j]->Paoexist = GL_FALSE;
								Paopaobaozha2[j][0]->Paoexist = GL_TRUE;
								Paopaobaozha2[j][0]->Time = clock();
								Paopaobaozha2[j][0]->Position.x = Paopao2[j]->Position.x;
								Paopaobaozha2[j][0]->Position.y = Paopao2[j]->Position.y;
								Paopaobaozha2[j][0]->Size = glm::vec2(50, 50);
								Paopao2[j]->Position = glm::vec2(-50, -50);
							}
						}
					}
					
				}
		}

		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (Paopaobaozha2[i][0]->Paoexist)
				for (int j = 0; j < Player2->Paopaonum; j++) {
					if (j != i) {
						for (int k = 0; k < 21; k++) {
							if (Paopaobaozha2[i][k]->Paoexist) {
								if (abs(Paopao2[j]->Position.x - Paopaobaozha2[i][k]->Position.x) <= 1 && abs(Paopao2[j]->Position.y - Paopaobaozha2[i][k]->Position.y) <= 1)
								{
									Paopao2[j]->Paoexist = GL_FALSE;
									Paopaobaozha2[j][0]->Paoexist = GL_TRUE;
									Paopaobaozha2[j][0]->Time = clock();
									Paopaobaozha2[j][0]->Position.x = Paopao2[j]->Position.x;
									Paopaobaozha2[j][0]->Position.y = Paopao2[j]->Position.y;
									Paopaobaozha2[j][0]->Size = glm::vec2(50, 50);
									Paopao2[j]->Position = glm::vec2(-50, -50);
								}
							}
						}
					}
				}
		}
		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (Paopaobaozha2[i][0]->Paoexist)
				for (int j = 0; j < Player->Paopaonum; j++) {
					for (int k = 0; k < 21; k++) {
						if (Paopaobaozha2[i][k]->Paoexist) {
							if (abs(Paopao[j]->Position.x - Paopaobaozha2[i][k]->Position.x) <= 1 && abs(Paopao[j]->Position.y - Paopaobaozha2[i][k]->Position.y) <= 1)
							{
								Paopao[j]->Paoexist = GL_FALSE;
								Paopaobaozha[j][0]->Paoexist = GL_TRUE;
								Paopaobaozha[j][0]->Time = clock();
								Paopaobaozha[j][0]->Position.x = Paopao[j]->Position.x;
								Paopaobaozha[j][0]->Position.y = Paopao[j]->Position.y;
								Paopaobaozha[j][0]->Size = glm::vec2(50, 50);
								Paopao[j]->Position = glm::vec2(-50, -50);
							}
						}
					}
				}
		}
		//判断人物是否炸到
		for (int i = 0; i < Player->Paopaonum; i++) {
			for (int j = 1; j < 6; j++) {
				if (Paopaobaozha[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.x - Paopaobaozha[i][j]->Position.x <= 30 && Player->Position.x - Paopaobaozha[i][j]->Position.x >= 0 && abs(Player->Position.y - Paopaobaozha[i][j]->Position.y) <= 20
						|| Player->Position.x - Paopaobaozha[i][j]->Position.x >= -30 && Player->Position.x - Paopaobaozha[i][j]->Position.x <= 0 && abs(Player->Position.y - Paopaobaozha[i][j]->Position.y) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.x - Paopaobaozha[i][j]->Position.x <= 30 && Player2->Position.x - Paopaobaozha[i][j]->Position.x >= 0 && abs(Player2->Position.y - Paopaobaozha[i][j]->Position.y) <= 20
						|| Player2->Position.x - Paopaobaozha[i][j]->Position.x >= -30 && Player2->Position.x - Paopaobaozha[i][j]->Position.x <= 0 && abs(Player2->Position.y - Paopaobaozha[i][j]->Position.y) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 6; j < 11; j++) {
				if (Paopaobaozha[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.y - Paopaobaozha[i][j]->Position.y >= -30 && Player->Position.y - Paopaobaozha[i][j]->Position.y <= 0 && abs(Player->Position.x - Paopaobaozha[i][j]->Position.x) <= 20
						|| Player->Position.y - Paopaobaozha[i][j]->Position.y <= 30 && Player->Position.y - Paopaobaozha[i][j]->Position.y >= 0 && abs(Player->Position.x - Paopaobaozha[i][j]->Position.x) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.y - Paopaobaozha[i][j]->Position.y >= -30 && Player2->Position.y - Paopaobaozha[i][j]->Position.y <= 0 && abs(Player2->Position.x - Paopaobaozha[i][j]->Position.x) <= 20
						|| Player2->Position.y - Paopaobaozha[i][j]->Position.y <= 30 && Player2->Position.y - Paopaobaozha[i][j]->Position.y >= 0 && abs(Player2->Position.x - Paopaobaozha[i][j]->Position.x) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 11; j < 16; j++) {
				if (Paopaobaozha[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.x - Paopaobaozha[i][j]->Position.x >= -30 && Player->Position.x - Paopaobaozha[i][j]->Position.x <= 0 && abs(Player->Position.y - Paopaobaozha[i][j]->Position.y) <= 20
						|| Player->Position.x - Paopaobaozha[i][j]->Position.x <= 30 && Player->Position.x - Paopaobaozha[i][j]->Position.x >= 0 && abs(Player->Position.y - Paopaobaozha[i][j]->Position.y) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.x - Paopaobaozha[i][j]->Position.x >= -30 && Player2->Position.x - Paopaobaozha[i][j]->Position.x <= 0 && abs(Player2->Position.y - Paopaobaozha[i][j]->Position.y) <= 20
						|| Player2->Position.x - Paopaobaozha[i][j]->Position.x <= 30 && Player2->Position.x - Paopaobaozha[i][j]->Position.x >= 0 && abs(Player2->Position.y - Paopaobaozha[i][j]->Position.y) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 16; j < 21; j++) {
				if (Paopaobaozha[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.y - Paopaobaozha[i][j]->Position.y <= 30 && Player->Position.y - Paopaobaozha[i][j]->Position.y >= 0 && abs(Player->Position.x - Paopaobaozha[i][j]->Position.x) <= 20
						|| Player->Position.y - Paopaobaozha[i][j]->Position.y >= -30 && Player->Position.y - Paopaobaozha[i][j]->Position.y <= 0 && abs(Player->Position.x - Paopaobaozha[i][j]->Position.x) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.y - Paopaobaozha[i][j]->Position.y <= 30 && Player2->Position.y - Paopaobaozha[i][j]->Position.y >= 0 && abs(Player2->Position.x - Paopaobaozha[i][j]->Position.x) <= 20
						|| Player2->Position.y - Paopaobaozha[i][j]->Position.y >= -30 && Player2->Position.y - Paopaobaozha[i][j]->Position.y <= 0 && abs(Player2->Position.x - Paopaobaozha[i][j]->Position.x) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
		}

		for (int i = 0; i < Player2->Paopaonum; i++) {
			for (int j = 1; j < 6; j++) {
				if (Paopaobaozha2[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.x - Paopaobaozha2[i][j]->Position.x <= 30 && Player->Position.x - Paopaobaozha2[i][j]->Position.x >= 0 && abs(Player->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20
						|| Player->Position.x - Paopaobaozha2[i][j]->Position.x >= -30 && Player->Position.x - Paopaobaozha2[i][j]->Position.x <= 0 && abs(Player->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha2[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.x - Paopaobaozha2[i][j]->Position.x <= 30 && Player2->Position.x - Paopaobaozha2[i][j]->Position.x >= 0 && abs(Player2->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20
						|| Player2->Position.x - Paopaobaozha2[i][j]->Position.x >= -30 && Player2->Position.x - Paopaobaozha2[i][j]->Position.x <= 0 && abs(Player2->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 6; j < 11; j++) {
				if (Paopaobaozha2[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.y - Paopaobaozha2[i][j]->Position.y >= -30 && Player->Position.y - Paopaobaozha2[i][j]->Position.y <= 0 && abs(Player->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20
						|| Player->Position.y - Paopaobaozha2[i][j]->Position.y <= 30 && Player->Position.y - Paopaobaozha2[i][j]->Position.y >= 0 && abs(Player->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha2[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.y - Paopaobaozha2[i][j]->Position.y >= -30 && Player2->Position.y - Paopaobaozha2[i][j]->Position.y <= 0 && abs(Player2->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20
						|| Player2->Position.y - Paopaobaozha2[i][j]->Position.y <= 30 && Player2->Position.y - Paopaobaozha2[i][j]->Position.y >= 0 && abs(Player2->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 11; j < 16; j++) {
				if (Paopaobaozha2[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.x - Paopaobaozha2[i][j]->Position.x >= -30 && Player->Position.x - Paopaobaozha2[i][j]->Position.x <= 0 && abs(Player->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20
						|| Player->Position.x - Paopaobaozha2[i][j]->Position.x <= 30 && Player->Position.x - Paopaobaozha2[i][j]->Position.x >= 0 && abs(Player->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha2[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.x - Paopaobaozha2[i][j]->Position.x >= -30 && Player2->Position.x - Paopaobaozha2[i][j]->Position.x <= 0 && abs(Player2->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20
						|| Player2->Position.x - Paopaobaozha2[i][j]->Position.x <= 30 && Player2->Position.x - Paopaobaozha2[i][j]->Position.x >= 0 && abs(Player2->Position.y - Paopaobaozha2[i][j]->Position.y) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
			for (int j = 16; j < 21; j++) {
				if (Paopaobaozha2[i][j]->Paoexist&&Player->Islive) {
					if (Player->Position.y - Paopaobaozha2[i][j]->Position.y <= 30 && Player->Position.y - Paopaobaozha2[i][j]->Position.y >= 0 && abs(Player->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20
						|| Player->Position.y - Paopaobaozha2[i][j]->Position.y >= -30 && Player->Position.y - Paopaobaozha2[i][j]->Position.y <= 0 && abs(Player->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20)
					{
						Player->Ismove = GL_FALSE;
						Player->Islive = GL_FALSE;
						Player->Position.x -= 20;
						Player->Position.y -= 20;
						break;
					}
				}
				if (Paopaobaozha2[i][j]->Paoexist&&Player2->Islive) {
					if (Player2->Position.y - Paopaobaozha2[i][j]->Position.y <= 30 && Player2->Position.y - Paopaobaozha2[i][j]->Position.y >= 0 && abs(Player2->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20
						|| Player2->Position.y - Paopaobaozha2[i][j]->Position.y >= -30 && Player2->Position.y - Paopaobaozha2[i][j]->Position.y <= 0 && abs(Player2->Position.x - Paopaobaozha2[i][j]->Position.x) <= 20)
					{
						Player2->Ismove = GL_FALSE;
						Player2->Islive = GL_FALSE;
						Player2->Position.x -= 20;
						Player2->Position.y -= 20;
						break;
					}
				}
			}
		}

		for (int i = 0; i < Player->Paopaonum; i++) {
			if (clock() - Paopaobaozha[i][0]->Time >= 0.3 * CLOCKS_PER_SEC&&Paopaobaozha[i][0]->Paoexist) {
				for (int j = 0; j < 21; j++) {
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && !box.Destroyeddonghua) {
							box.Destroyeddonghua = GL_TRUE;
						}
					}
					Paopaobaozha[i][j]->Paoexist = GL_FALSE;
				}
			}
		}

		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (clock() - Paopaobaozha2[i][0]->Time >= 0.3 * CLOCKS_PER_SEC&&Paopaobaozha2[i][0]->Paoexist) {
				for (int j = 0; j < 21; j++) {
					for (GameObject &box : this->Levels[this->Level].Bricks)
					{
						if (abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1 && abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && !box.Destroyeddonghua) {
							box.Destroyeddonghua = GL_TRUE;
						}
					}
					Paopaobaozha2[i][j]->Paoexist = GL_FALSE;
				}
			}
		}
		//怪物移动
		if (Monster->Position.x >= 50 * 13)
			Monstercount = 1;
		if (Monster->Position.x <= 50)
			Monstercount = 0;
		if (Monstercount > 0)
			MonsterVelocity = -MonsterVelocity;
		Monster->Position.x += MonsterVelocity;
	}
}
int istring;
int istring2;
void Game::Render()
{
	if (scene == 1) {
		Renderer->DrawSprite(ResourceManager::GetTexture("登陆界面"), glm::vec2(0, 0), glm::vec2(988, 724), 0.0f);
		if (Inputname) {
			countstring++;
			if (countstring >= 0 && countstring <= 400)
				Renderer->DrawSprite(ResourceManager::GetTexture("登陆时的线"), glm::vec2(710 + 9.8 * istring, 260), glm::vec2(1, 30), 0.0f);
			if (countstring >= 800)
				countstring = 0;
		}
		if (Inputpassword) {
			countstring++;
			if (countstring >= 0 && countstring <= 400)
				Renderer->DrawSprite(ResourceManager::GetTexture("登陆时的线"), glm::vec2(710 + 9.8 * istring2, 314), glm::vec2(1, 30), 0.0f);
			if (countstring >= 800)
				countstring = 0;
		}
		Text->RenderText(Usersname, Usersnameposition.x, Usersnameposition.y, 0.8f);
		Text->RenderText(Userspassword, Userspasswordposition.x, Userspasswordposition.y, 0.8f);
		if (Mistakewindow) {
			Renderer->DrawSprite(ResourceManager::GetTexture("Mistakewindow"), glm::vec2(270, 150), glm::vec2(450, 400), 0.0f);
		}
	}
	if (scene == 2) {
		Inputname = GL_FALSE;
		Inputpassword = GL_FALSE;
		if (color == Color::red) {
			Player->Color = glm::vec3(0.9686f, 0.1176f, 0.1098f);
		}
		if (color == Color::blue) {
			Player->Color = glm::vec3(0.0627f, 0.2353, 0.7843f);
		}
		if (color==Color::yellow) {
			Player->Color = glm::vec3(0.9411f, 0.8941f, 0.2196f);
		}
		if (color == Color::green) {
			Player->Color = glm::vec3(0.2196f, 0.5647f, 0.0941f);
		}
		if (color == Color::pink) {
			Player->Color = glm::vec3(0.8784f, 0.1412f, 0.5333f);
		}
		if (color == Color::orange) {
			Player->Color = glm::vec3(0.9412f, 0.6118f, 0.1569f);
		}
		if (color == Color::purple) {
			Player->Color = glm::vec3(0.6902f, 0.0941f, 0.7529);
		}
		if (color == Color::gray) {
			Player->Color = glm::vec3(0.3450f, 0.3450f, 0.3450f);
		}
		if (!Mapchoose) {
			Renderer->DrawSprite(ResourceManager::GetTexture("房间界面"), glm::vec2(0, 0), glm::vec2(988, 724), 0.0f);
			if (Feature == 0) {
				Player->Sprite = ResourceManager::GetTexture(Picture[down0]);
			}
			if (Feature == 1) {
				Player->Sprite = ResourceManager::GetTexture(Picture2[down0]);
			}
			Player->Position = glm::vec2(70, 150);
			Player->Size = glm::vec2(55, 75);
			Player->Draw(*Renderer);
			Renderer->DrawSprite(ResourceManager::GetTexture("选颜色的勾"), this->Gouposition, glm::vec2(40, 41), 0.0f);
			for (int i = 0; i < 13; i++) {
				if (this->Level == i) {
					Renderer->DrawSprite(ResourceManager::GetTexture(Map2[i]), glm::vec2(787, 58), glm::vec2(186, 182), 0.0f);
				}
			}
		}
		if (Mapchoose) {
			Renderer->DrawSprite(ResourceManager::GetTexture("选择地图"), glm::vec2(0, 0), glm::vec2(988, 724), 0.0f);
			if (Feature == 0) {
				Player->Sprite = ResourceManager::GetTexture(Picture[down0]);
			}
			if (Feature == 1) {
				Player->Sprite = ResourceManager::GetTexture(Picture2[down0]);
			}
			Player->Position = glm::vec2(70, 150);
			Player->Size = glm::vec2(55, 75);
			Player->Draw(*Renderer);
			for (int i = 0; i < 13; i++) {
				if (Mapchoice[i]) {
					Renderer->DrawSprite(ResourceManager::GetTexture(Map[i]), glm::vec2(790, 66), glm::vec2(187, 152), 0.0f);
				}
			}
		}
	}

	if (this->State == GAME_ACTIVE)
	{
		// Draw background
		Renderer->DrawSprite(ResourceManager::GetTexture("底面背景"), glm::vec2(0, 0), glm::vec2(988, 724), 0.0f);
		for (int i = 0; i < 13; i++) {
			if (this->Level == i) {
				Renderer->DrawSprite(ResourceManager::GetTexture(Mapbackground[i]), glm::vec2(0, 0), glm::vec2(752, 650), 0.0f);
			}
		}
		if (Player->Feibiaonum > 0) {
			Renderer->DrawSprite(ResourceManager::GetTexture("飞镖图标"), glm::vec2(220, 662), glm::vec2(60, 60), 0.0f);
		}
		if (Player->Livenum > 0) {
			Renderer->DrawSprite(ResourceManager::GetTexture("叉子"), glm::vec2(290, 662), glm::vec2(60, 60), 0.0f);
		}
		if (Player->Paopaonum < 11) {
			Paopaonum[0] = Player->Paopaonum - 1 + '0';
			Paopaonum[1] = 0;
		}
		if (Player->Paopaonum >= 11) {
			Paopaonum[0] = '0' + (Player->Paopaonum-1) / 10;
			Paopaonum[1] = (Player->Paopaonum-1) % 10 + '0';
			Paopaonum[2] = 0;
		}
		Textproperty->RenderText(Paopaonum, 50, 700, 0.8f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		if (Player->Velocity < 11) {
			Paopaovelocity[0] = Player->Velocity - 1 + '0';
			Paopaovelocity[1] = 0;
		}
		if (Player->Velocity >= 11) {
			Paopaovelocity[0] = (Player->Velocity - 1) / 10 + '0';
			Paopaovelocity[1] = (Player->Velocity - 1) % 10 + '0';
			Paopaovelocity[2] = 0;
		}
		Textproperty->RenderText(Paopaovelocity, 178, 700, 0.8f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		if (Player->Strength < 11) {
			Paopaostrength[0] = Player->Strength - 1 + '0';
			Paopaostrength[1] = 0;
		}
		if (Player->Strength >= 11) {
			Paopaostrength[0] = (Player->Strength - 1) / 10 + '0';
			Paopaostrength[1] = (Player->Strength - 1) % 10 + '0';
			Paopaostrength[2] = 0;
		}
		Textproperty->RenderText(Paopaostrength, 115, 700, 0.8f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		if (Player->Feibiaonum < 10) {
			Feibiaonum[0] = Player->Feibiaonum + '0';
			Feibiaonum[1] = 0;
		}
		if (Player->Feibiaonum >= 10) {
			Feibiaonum[0] = (Player->Feibiaonum) / 10 + '0';
			Feibiaonum[1] = (Player->Feibiaonum) % 10 + '0';
			Feibiaonum[2] = 0;
		}
		if (Player->Feibiaonum > 0) {
			Textproperty->RenderText(Feibiaonum, 260, 700, 0.8f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		}
		if (Player->Livenum < 10) {
			Livenum[0] = Player->Livenum + '0';
			Livenum[1] = 0;
		}
		if (Player->Livenum >= 10) {
			Livenum[0] = (Player->Livenum) / 10 + '0';
			Livenum[1] = (Player->Livenum) % 10 + '0';
			Livenum[2] = 0;
		}
		if (Player->Livenum > 0) {
			Textproperty->RenderText(Livenum, 330, 700, 0.8f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		}
		if (abs(clock() - Gametime - 1 * CLOCKS_PER_SEC)<=5) {
			Time[4]++;
			Gametime = clock();
		}
		if (Time[4] == '0' + 10) {
			Time[4] = '0';
			Time[3]++;
		}
		if (Time[3] == '0' + 6) {
			Time[3] = '0';
			Time[1]++;
		}
		if (Time[1] == '0' + 10) {
			Time[1] = '0';
			Time[0]++;
		}
		Texttime->RenderText(Time, 820, 50, 1.0f, glm::vec3(0.9412f, 0.6118f, 0.1569f));
		// Draw Paopao
		for (int i = 0; i < Player->Paopaonum; i++) {
			if (Paopao[i]->Paoexist) {
				Paopao[i]->Draw(*Renderer);
			}
		}
		for (int i = 0; i < Player2->Paopaonum; i++) {
			if (Paopao2[i]->Paoexist) {
				Paopao2[i]->Draw(*Renderer);
			}
		}
		for(int i=0;i<Player->Paopaonum;i++)
			for (int j = 0; j < 21; j++) {
				if (Paopaobaozha[i][j]->Paoexist) {
					Paopaobaozha[i][j]->Draw(*Renderer);
				}
			}
		for (int i = 0; i<Player2->Paopaonum; i++)
			for (int j = 0; j < 21; j++) {
				if (Paopaobaozha2[i][j]->Paoexist) {
					Paopaobaozha2[i][j]->Draw(*Renderer);
				}
			}
		//Draw daoju
		this->Levels[this->Daoju].Draw(*Renderer);
		// Draw level
		this->Levels[this->Level].Draw(*Renderer);
		Monster->Draw(*Renderer);
		// Draw player
		if (Player->Islive) {
			if (Player->Ismove) {
				if (Feature == 0) {
					count++;
					if (count <= 50 && count > 0)
						Player->Sprite = ResourceManager::GetTexture(Picture[k + 1]);
					Player->Draw(*Renderer);
					if (count > 50 && count <= 100)
						Player->Sprite = ResourceManager::GetTexture(Picture[k + 2]);
					if (count > 100 && count <= 150)
						Player->Sprite = ResourceManager::GetTexture(Picture[k + 3]);
					Player->Draw(*Renderer);
					if (count == 150)
						count = 0;
				}
				if (Feature == 1) {
					count++;
					if (count <= 50 && count > 0)
						Player->Sprite = ResourceManager::GetTexture(Picture2[k + 1]);
					Player->Draw(*Renderer);
					if (count > 50 && count <= 100)
						Player->Sprite = ResourceManager::GetTexture(Picture2[k + 2]);
					if (count > 100 && count <= 150)
						Player->Sprite = ResourceManager::GetTexture(Picture2[k + 3]);
					Player->Draw(*Renderer);
					if (count == 150)
						count = 0;
				}
			}
				else {
					if (Feature == 0) {
						Player->Sprite = ResourceManager::GetTexture(Picture[k]);
						//Player->Color = glm::vec3(0.0f, 1.0f, 1.0f);
						Player->Draw(*Renderer);
					}
					if (Feature == 1) {
						Player->Sprite = ResourceManager::GetTexture(Picture2[k]);
						//Player->Color = glm::vec3(0.0f, 1.0f, 1.0f);
						Player->Draw(*Renderer);
					}
				}
	
			if (Feibiaoexist) {
				Feibiaoposition = Player->Position;
				Feibiaomove = GL_TRUE;
				Feibiaoexist = GL_FALSE;
			}
			if (Feibiaomove) {
				if (Feibiaodirection == 1)
					Renderer->DrawSprite(ResourceManager::GetTexture("飞镖右"), Feibiaoposition, glm::vec2(50, 50), 0.0f);
				if (Feibiaodirection == 2)
					Renderer->DrawSprite(ResourceManager::GetTexture("飞镖上"), Feibiaoposition, glm::vec2(50, 50), 0.0f);
				if (Feibiaodirection == 3)
					Renderer->DrawSprite(ResourceManager::GetTexture("飞镖左"), Feibiaoposition, glm::vec2(50, 50), 0.0f);
				if (Feibiaodirection == 4)
					Renderer->DrawSprite(ResourceManager::GetTexture("飞镖下"), Feibiaoposition, glm::vec2(50, 50), 0.0f);
			}
		}
		else {
			Player->Sprite = ResourceManager::GetTexture("黏泡泡");
			Player->Size = glm::vec2(80, 80);
			Player->Draw(*Renderer);
		}

		if (Player2->Islive) {
			if (Player2->Ismove) {
				count++;
				if (count <= 50 && count > 0)
					Player2->Sprite = ResourceManager::GetTexture(Picture[k2 + 1]);
				Player2->Draw(*Renderer);
				if (count > 50 && count <= 100)
					Player2->Sprite = ResourceManager::GetTexture(Picture[k2 + 2]);
				if (count > 100 && count <= 150)
					Player2->Sprite = ResourceManager::GetTexture(Picture[k2 + 3]);
				Player2->Draw(*Renderer);
				if (count == 150)
					count = 0;
			}
			else {
				Player2->Sprite = ResourceManager::GetTexture(Picture[k2]);
				//Player->Color = glm::vec3(0.0f, 1.0f, 1.0f);
				Player2->Draw(*Renderer);
			}
		}
		else {
			Player2->Sprite = ResourceManager::GetTexture("黏泡泡");
			Player2->Size = glm::vec2(80, 80);
			Player2->Draw(*Renderer);
		}
	}
}

GLboolean Game::CheckCollision(GameObject &one, GameObject &two, GLint n) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	bool collisionXR = abs(one.Position.x + one.Size.x - two.Position.x) <= 1;
	bool collisionXL = abs(two.Position.x + two.Size.x - one.Position.x) <= 1;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	bool collisionY1 = one.Position.y + one.Size.y >= two.Position.y &&
		one.Position.y + one.Size.y <= two.Position.y + 0.6*two.Size.y;
	bool collisionY2 = two.Position.y + two.Size.y <= one.Position.y + 0.6*one.Size.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	bool collisionYD = abs(one.Position.y + one.Size.y - two.Position.y) <= 1;
	bool collisionYU = abs(two.Position.y + two.Size.y - one.Position.y) <= 1;
	bool collisionX1 = one.Position.x + one.Size.x >= two.Position.x &&
		one.Position.x + one.Size.x <= two.Position.x + 0.6*two.Size.x;
	bool collisionX2 = two.Position.x + two.Size.x >= one.Position.x &&
		two.Position.x + two.Size.x <= one.Position.x + 0.6*one.Size.x;
	if (collisionXR&&collisionY1&&this->Keys[GLFW_KEY_RIGHT] && n == 1 || collisionXR&&collisionY1&&this->Keys[GLFW_KEY_D] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.x - two.Position.x)<1 && abs(box.Position.y + box.Size.y - two.Position.y)<1) {
				collisionY1 = GL_FALSE;
			}
		}
		while (collisionY1) {
			one.Position.y -= 0.6;
			break;
		}
	}
	if (collisionXL&&collisionY1&&this->Keys[GLFW_KEY_LEFT] && n == 1 || collisionXL&&collisionY1&&this->Keys[GLFW_KEY_A] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.x - two.Position.x)<1 && abs(box.Position.y + box.Size.y - two.Position.y)<1) {
				collisionY1 = GL_FALSE;
			}
		}
		while (collisionY1) {
			one.Position.y -= 0.6;
			break;
		}
	}
	if (collisionXL&&collisionY2&&this->Keys[GLFW_KEY_LEFT] && n == 1 || collisionXL&&collisionY2&&this->Keys[GLFW_KEY_A] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.x - two.Position.x)<1 && abs(box.Position.y - box.Size.y - two.Position.y)<1) {
				collisionY2 = GL_FALSE;
			}
		}
		while (collisionY2) {
			one.Position.y += 0.6;
			break;
		}
	}
	if (collisionXR&&collisionY2&&this->Keys[GLFW_KEY_RIGHT] && n == 1 || collisionXR&&collisionY2&&this->Keys[GLFW_KEY_D] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.x - two.Position.x)<1 && abs(box.Position.y - box.Size.y - two.Position.y)<1) {
				collisionY2 = GL_FALSE;
			}
		}
		while (collisionY2) {
			one.Position.y += 0.6;
			break;
		}
	}
	if (collisionYD&&collisionX1&&this->Keys[GLFW_KEY_DOWN] && n == 1 || collisionYD&&collisionX1&&this->Keys[GLFW_KEY_S] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.y - two.Position.y)<1 && abs(box.Position.x + box.Size.x - two.Position.x)<1) {
				collisionX1 = GL_FALSE;
			}
		}
		while (collisionX1) {
			one.Position.x -= 0.6;
			break;
		}
	}
	if (collisionYU&&collisionX1&&this->Keys[GLFW_KEY_UP] && n == 1 || collisionYU&&collisionX1&&this->Keys[GLFW_KEY_W] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.y - two.Position.y)<1 && abs(box.Position.x + box.Size.x - two.Position.x)<1) {
				collisionX1 = GL_FALSE;
			}
		}
		while (collisionX1) {
			one.Position.x -= 0.6;
			break;
		}
	}
	if (collisionYD&&collisionX2&&this->Keys[GLFW_KEY_DOWN] && n == 1 || collisionYD&&collisionX2&&this->Keys[GLFW_KEY_S] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.y - two.Position.y)<1 && abs(box.Position.x - box.Size.x - two.Position.x)<1) {
				collisionX2 = GL_FALSE;
			}
		}
		while (collisionX2) {
			one.Position.x += 0.6;
			break;
		}
	}
	if (collisionYU&&collisionX2&&this->Keys[GLFW_KEY_UP] && n == 1 || collisionYU&&collisionX2&&this->Keys[GLFW_KEY_W] && n == 2) {
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&abs(box.Position.y - two.Position.y)<1 && abs(box.Position.x - box.Size.x - two.Position.x)<1) {
				collisionX2 = GL_FALSE;
			}
		}
		while (collisionX2) {
			one.Position.x += 0.6;
			break;
		}
	}

	if (collisionXR&&collisionY) {
		one.Rightwalk = GL_FALSE;
		one.countr = GL_TRUE;
	}
	if (collisionXL&&collisionY) {
		one.Leftwalk = GL_FALSE;
		one.countl = GL_TRUE;
	}
	if (collisionYU&&collisionX) {
		one.Upwalk = GL_FALSE;
		one.countu = GL_TRUE;
	}
	if (collisionYD&&collisionX) {
		one.Downwalk = GL_FALSE;
		one.countd = GL_TRUE;
	}
	return collisionXR&&collisionY || collisionXL&&collisionY || collisionYU&&collisionX || collisionYD&&collisionX;
}

GLboolean CheckCollision2(GameObject &one, GameObject &two)
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

GLboolean CheckCollisiondaoju(GameObject &one, GameObject &two)
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x + two.Size.x*0.2&&
		two.Position.x + two.Size.x >= one.Position.x + one.Size.x*0.2;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y + two.Size.y*0.2&&
		two.Position.y + two.Size.y >= one.Position.y + one.Size.y*0.2;
	// Collision only if on both axes
	return collisionX && collisionY;
}

GLboolean CheckCollisionMonster(GameObject &one, GameObject &two)
{
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}

void Game::DoCollisions()
{
	if (this->State == GAME_ACTIVE) {
		int count = 0;
		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			if (!box.Destroyed&&CheckCollision(*Player, box, 1)) {
				;
			}
			if (!box.Destroyed&&CheckCollision(*Player2, box, 2)) {
				;
			}
		}
		for (int i = 0; i < Player->Paopaonum; i++) {
			CheckCollision(*Player, *Paopao[i], 1);
			CheckCollision(*Player2, *Paopao[i], 2);
		}
		for (int i = 0; i < Player2->Paopaonum; i++) {
			CheckCollision(*Player, *Paopao2[i], 1);
			CheckCollision(*Player2, *Paopao2[i], 2);
		}
		if (!Player->countr)
			Player->Rightwalk = GL_TRUE;
		if (!Player->countl)
			Player->Leftwalk = GL_TRUE;
		if (!Player->countu)
			Player->Upwalk = GL_TRUE;
		if (!Player->countd)
			Player->Downwalk = GL_TRUE;
		Player->countr = Player->countl = Player->countu = Player->countd = GL_FALSE;
		//Player2
		if (!Player2->countr)
			Player2->Rightwalk = GL_TRUE;
		if (!Player2->countl)
			Player2->Leftwalk = GL_TRUE;
		if (!Player2->countu)
			Player2->Upwalk = GL_TRUE;
		if (!Player2->countd)
			Player2->Downwalk = GL_TRUE;
		Player2->countr = Player2->countl = Player2->countu = Player2->countd = GL_FALSE;

		for (GameObject &box : this->Levels[this->Level].Dous)
		{
			if (CheckCollision2(*Player, box)) {
				box.Destroyed = true;
			}
			if (box.Destroyed == false) {
				counto = 1;
			}
			if (CheckCollision2(*Player2, box)) {
				box.Destroyed = true;
			}
			if (box.Destroyed == false) {
				counto = 1;
			}
		}
		if (!counto) {
			this->State = GAME_WIN;
		}
		counto = 0;

		for (GameObject &box : this->Levels[this->Daoju].Numproperty)
		{
			if (CheckCollisiondaoju(*Player, box) && !box.Destroyed) {
				clock_t delay = clock();
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player->Paopaonum < 6)
					Player->Paopaonum++;
			}
			if (CheckCollisiondaoju(*Player2, box) && !box.Destroyed) {
				clock_t delay = clock();
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player2->Paopaonum < 6)
					Player2->Paopaonum++;
			}
		}

		for (GameObject &box : this->Levels[this->Daoju].Strengthproperty)
		{
			if (CheckCollisiondaoju(*Player, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player->Strength < 5)
					Player->Strength++;
			}
			if (CheckCollisiondaoju(*Player2, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player2->Strength < 5)
					Player2->Strength++;
			}
		}

		for (GameObject &box : this->Levels[this->Daoju].Velocityproperty)
		{
			if (CheckCollisiondaoju(*Player, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player->Velocity <= 3)
					Player->Velocity += 1;
			}
			if (CheckCollisiondaoju(*Player2, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				if (Player2->Velocity <= 3)
					Player2->Velocity += 1;
			}
		}

		for (GameObject &box : this->Levels[this->Daoju].Feibiaoproperty)
		{
			if (CheckCollisiondaoju(*Player, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				Player->Feibiaonum += 2;
			}
			if (CheckCollisiondaoju(*Player2, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				Player2->Feibiaonum += 2;
			}
		}

		for (GameObject &box : this->Levels[this->Daoju].Liveproperty)
		{
			if (CheckCollisiondaoju(*Player, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				Player->Livenum += 1;
			}
			if (CheckCollisiondaoju(*Player2, box) && !box.Destroyed) {
				this->Soundchoic = 5;
				this->Sound();
				box.Destroyed = true;
				Player2->Livenum += 1;
			}
		}

		for (GameObject &box : this->Levels[this->Level].Bricks)
		{
			for (int i = 0; i < Player->Paopaonum; i++) {
				for (int j = 0; j < 20; j++) {
					if (Paopaobaozha[i][j]->Paoexist && !box.Destroyed && !box.IsSolid) {
						if (abs(box.Position.x - Paopaobaozha[i][j]->Position.x) <= 1 && abs(box.Position.y - Paopaobaozha[i][j]->Position.y) <= 1)			
						{
							box.Destroyed = true;
						}
					}
				}
			}
			for (int i = 0; i < Player2->Paopaonum; i++) {
				for (int j = 0; j < 20; j++) {
					if (Paopaobaozha2[i][j]->Paoexist && !box.Destroyed && !box.IsSolid) {
						if (abs(box.Position.x - Paopaobaozha2[i][j]->Position.x) <= 1 && abs(box.Position.y - Paopaobaozha2[i][j]->Position.y) <= 1)
						{
							box.Destroyed = true;
						}
					}
				}
			}
		}
	}
	//if (CheckCollisionMonster(*Player, *Monster)) {
		//this->State = GAME_LOSE;
	//}
}

void Game::ResetLevel()
{
	Gametime = clock();
	Time[0] = '0';
	Time[1] = '0';
	Time[2] = ':';
	Time[3] = '0';
	Time[4] = '0';
	SoundEngine->removeAllSoundSources();
	if (this->Level == 0)this->Levels[0].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 1)
		this->Levels[1].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 2)
		this->Levels[2].Load("levels/新年瑞兽.txt", this->Width, this->Height);
	else if (this->Level == 3) {
		this->Levels[3].Load("levels/爱的体验.txt", this->Width, this->Height);
	}
	else if (this->Level == 4)
		this->Levels[4].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 5)
		this->Levels[5].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 6) {
		this->Levels[6].Load("levels/比武.txt", this->Width, this->Height);
		this->Levels[19].Load("levels/比武道具.txt", this->Width, this->Height);
		SoundEngine->play2D("M15.ogg", GL_TRUE);
	}
	else if (this->Level == 7) {
		this->Levels[7].Load("levels/功夫.txt", this->Width, this->Height);
		SoundEngine->play2D("sene1.ogg", GL_TRUE);
	}
	else if (this->Level == 8)
		this->Levels[8].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 9)
		this->Levels[9].Load("levels/爱的体验.txt", this->Width, this->Height);
	else if (this->Level == 10) {
		this->Levels[10].Load("levels/新年瑞兽.txt", this->Width, this->Height);
		SoundEngine->play2D("match.ogg", GL_TRUE);
	}
	else if (this->Level == 11) {
		this->Levels[11].Load("levels/爱的体验.txt", this->Width, this->Height);
		SoundEngine->play2D("desert.ogg", GL_TRUE);
	}
	else if (this->Level == 12)
		this->Levels[12].Load("levels/爱的体验.txt", this->Width, this->Height);
}

void Game::ResetPlayer()
{
	if (this->Level == 6) {
		Player->Position = glm::vec2(50, 200);
		Player2->Position = glm::vec2(650, 200);
	}
	if (this->Level == 7) {
		Player->Position = glm::vec2(50, 150);
		Player2->Position = glm::vec2(650, 150);
	}
	if (this->Level == 10) {
		Player->Position = glm::vec2(50, 150);
		Player2->Position = glm::vec2(650, 150);
	}
	if (this->Level == 11) {
		Player->Position = glm::vec2(50, 150);
		Player2->Position = glm::vec2(650, 150);
	}
	Player->Islive = GL_TRUE;
	Player->Size = glm::vec2(49, 49);
	Player->Velocity = 1;
	Player->Paopaonum = 1;
	Player->Strength = 1;
	Player->Feibiaonum = 2;
	Player->Livenum = 2;
	Player2->Islive = GL_TRUE;
	Player2->Size = glm::vec2(49, 49);
	Player2->Velocity = 1;
	Player2->Paopaonum = 1;
	Player2->Strength = 1;
	Player2->Feibiaonum = 1;
	Player2->Livenum = 1;
}

void Game::Sound()
{
	switch (Soundchoic) {
	case 1:SoundEngine->play2D("uiNormal.wav", GL_FALSE); break;
	case 2:SoundEngine->play2D("uiMain.wav", GL_FALSE); break;
	case 3:SoundEngine->play2D("uiLeave.wav", GL_FALSE); break;
	case 4:SoundEngine->play2D("paopaobaozha.wav", GL_FALSE); break;
	case 5:SoundEngine->play2D("chidaoju.wav", GL_FALSE); break;
	}
}
