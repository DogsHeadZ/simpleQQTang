/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#define GLEW_STATIC
#include <GL/glew.h>
#include <glfw3.h>
#include<ctime>
#include<iostream>
#include<SOIL.h>
#include <irrKlang.h>
#include "game.h"
#include<string>
#include "resource_manager.h"
FILE *fp;
using namespace irrklang;
extern ISoundEngine *SoundEngine;

// GLFW function declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

// The Width of the screen
const GLuint SCREEN_WIDTH = 988;
// The height of the screen
const GLuint SCREEN_HEIGHT = 724;
Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int scene = 1;
extern int countsound;
extern GLint Feature;
extern char Usersname[30];
extern glm::vec2 Usersnameposition;
extern char Userspassword[30];
extern glm::vec2 Userspasswordposition;
GLboolean Mistakewindow;
GLboolean Inputname = GL_FALSE;
GLboolean Inputpassword = GL_FALSE;
GLboolean Mapchoose = GL_FALSE;
GLboolean Mapchoice[13] = { GL_FALSE,GL_FALSE,GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE,
						 GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE };
int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Breakout", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // Call it once to catch glewInit() bug, all other errors are now from our application.

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_position_callback);

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	Breakout.Init();

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	// Start Game within Menu State
	//Breakout.State = GAME_ACTIVE;
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
		//deltaTime = 0.001f;
		// Manage user input
		Breakout.ProcessInput(deltaTime);

		// Update Game state
		Breakout.Update(deltaTime);
		// Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Breakout.Render();
		glfwSwapBuffers(window);
		
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

extern int istring;
extern int istring2;
int iname;
int ipassword;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
	if (key >= 48 && key <= 122 && action == GLFW_PRESS) {
		if (Inputname) {
			Usersname[iname] = key;
			Usersname[iname+1] = 0;
			++iname;
			++istring;
		}
	}
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && Inputname) {
		--iname;
		Usersname[iname] = 0;
		--istring;
	}
	if (key >= 48 && key <= 122 && action == GLFW_PRESS) {
		if (Inputpassword) {
			Userspassword[ipassword] = '*';
			Userspassword[ipassword + 1] = 0;
			++ipassword;
			++istring2;
		}
	}
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS && Inputpassword) {
		--ipassword;
		Userspassword[ipassword] = 0;
		--istring2;
	}
}

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	int width, height;
	int width2, height2;
	unsigned char* image1 = SOIL_load_image("水晶鼠标.png", &width, &height, 0, SOIL_LOAD_RGBA);
	unsigned char* image2 = SOIL_load_image("手套鼠标.png", &width2, &height2, 0, SOIL_LOAD_RGBA);
	GLFWimage Image;
	Image.width = width;
	Image.height = height;
	Image.pixels = image1;
	GLFWcursor* cursor = glfwCreateCursor(&Image, 0, 0);
	GLFWimage Image2;
	Image2.width = width2;
	Image2.height = height2;
	Image2.pixels = image2;
	GLFWcursor* cursor2 = glfwCreateCursor(&Image2, 0, 0);
	if (scene == 1) {
		if (!Mistakewindow) {
			if ((xpos >= 771 && xpos <= 872 && xpos <= 928 && ypos >= 451 && ypos <= 485) || (xpos >= 876 && xpos <= 928 && ypos >= 451 && ypos <= 485)) {
				glfwSetCursor(window, cursor2);
			}
			else {
				glfwSetCursor(window, cursor);
			}
		}
		else {
			if ((xpos >= 467 && xpos <= 518 && ypos >= 500 && ypos <= 535)) {
				glfwSetCursor(window, cursor2);
			}
			else {
				glfwSetCursor(window, cursor);
			}
		}
	}

	if (scene == 2) {
		if (!Mapchoose) {
			if ((xpos >= 887 && xpos <= 952 && ypos >= 647 && ypos <= 702) || (xpos >= 673 && xpos <= 811 && ypos >= 647 && ypos <= 699) || (xpos >= 651 && xpos <= 974 && ypos >= 261 && ypos <= 439)
				|| (xpos >= 651 && xpos <= 769 && ypos >= 162 && ypos <= 203)) {
				glfwSetCursor(window, cursor2);
			}
			else {
				glfwSetCursor(window, cursor);
			}
		}
		if (Mapchoose) {
			if ((xpos >= 602 && xpos <= 662 && ypos >= 669 && ypos <= 705)|| (xpos >= 688 && xpos <= 741 && ypos >= 669 && ypos <= 705)
				|| (xpos >= 598 && xpos <= 744 && ypos >= 77 && ypos <= 647)) {
				glfwSetCursor(window, cursor2);
			}
			else {
				glfwSetCursor(window, cursor);
			}
		}
	}

	if (scene == 3) {
		if (xpos >= 906 && xpos <= 971 && ypos >= 646 && ypos <= 700) {
			glfwSetCursor(window, cursor2);
		}
		else {
			glfwSetCursor(window, cursor);
		}
	}
	Breakout.Mouseposition = glm::vec2(xpos, ypos);
	//std::cout << xpos << "   " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	static int flag;
	int width, height;
	int width2, height2;
	int width3, height3;
	unsigned char* image1 = SOIL_load_image("水晶鼠标.png", &width, &height, 0, SOIL_LOAD_RGBA);
	unsigned char* image2 = SOIL_load_image("手套鼠标.png", &width2, &height2, 0, SOIL_LOAD_RGBA);
	unsigned char* image3 = SOIL_load_image("手套鼠标闭合.png", &width3, &height3, 0, SOIL_LOAD_RGBA);
	GLFWimage Image;
	Image.width = width;
	Image.height = height;
	Image.pixels = image1;
	GLFWcursor* cursor = glfwCreateCursor(&Image, 0, 0);
	GLFWimage Image2;
	Image2.width = width2;
	Image2.height = height2;
	Image2.pixels = image2;
	GLFWcursor* cursor2 = glfwCreateCursor(&Image2, 0, 0);
	GLFWimage Image3;
	Image3.width = width3;
	Image3.height = height3;
	Image3.pixels = image3;
	GLFWcursor* cursor3 = glfwCreateCursor(&Image3, 0, 0);
	if (scene == 1) {
		if (action == GLFW_PRESS) {
			//登陆
			if (Breakout.Mouseposition.x >= 771 && Breakout.Mouseposition.x <= 872 && Breakout.Mouseposition.y >= 451 && Breakout.Mouseposition.y <= 485) {
				glfwSetCursor(window, cursor3);
				Breakout.Soundchoic = 2;
				Breakout.Sound();
				clock_t delay = clock();
				while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
				glfwSetCursor(window, cursor2);
				//scene = 2;
				fp = fopen("Usersname.txt", "r");
				rewind(fp);
				char name[20];
				while (!feof(fp))
				{
					fscanf(fp, "%s", name);
					if (strcmp(Usersname, name) == 0) {
						flag = 1;
						glfwSetCursor(window, cursor);
						scene = 2;
						SoundEngine->removeAllSoundSources();
						SoundEngine->play2D("M10.ogg", GL_TRUE);
						break;
					}
				}
				if (!flag) {
					Mistakewindow = GL_TRUE;
				}
			}
			if (Mistakewindow) {
				if (Breakout.Mouseposition.x >= 467 && Breakout.Mouseposition.x <= 518 && Breakout.Mouseposition.y >= 500 && Breakout.Mouseposition.y <= 535) {
					glfwSetCursor(window, cursor3);
					Breakout.Soundchoic = 2;
					Breakout.Sound();
					clock_t delay = clock();
					while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor);
					Mistakewindow = GL_FALSE;
				}
			}
			//退出
			if (Breakout.Mouseposition.x >= 876 && Breakout.Mouseposition.x <= 928 && Breakout.Mouseposition.y >= 451 && Breakout.Mouseposition.y <= 485) {
				glfwSetCursor(window, cursor3);
				clock_t delay = clock();
				Breakout.Soundchoic = 3;
				Breakout.Sound();
				while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
				glfwSetCursor(window, cursor);
				glfwSetWindowShouldClose(window, GL_TRUE);
			}
		    //输入用户名
			if (Breakout.Mouseposition.x >= 708 && Breakout.Mouseposition.x <= 893 && Breakout.Mouseposition.y >= 256 && Breakout.Mouseposition.y <= 297) {
				Inputname = GL_TRUE;
				Inputpassword = GL_FALSE;
			}
			//输入密码
			if (Breakout.Mouseposition.x >= 708 && Breakout.Mouseposition.x <= 893 && Breakout.Mouseposition.y >= 307 && Breakout.Mouseposition.y <= 352) {
				Inputname = GL_FALSE;
				Inputpassword = GL_TRUE;
			}
		}
	}

	if (scene == 2) {
		if (action == GLFW_PRESS) {
			if (!Mapchoose) {
				//返回
				if (Breakout.Mouseposition.x >= 887 && Breakout.Mouseposition.x <= 952 && Breakout.Mouseposition.y >= 647 && Breakout.Mouseposition.y <= 702) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 3;
					Breakout.Sound();
					while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor);
					SoundEngine->removeAllSoundSources();
					SoundEngine->play2D("M09.ogg", GL_TRUE);
					scene = 1;
					flag = 0;
				}
				//开始游戏
				if (Breakout.Mouseposition.x >= 673 && Breakout.Mouseposition.x <= 811 && Breakout.Mouseposition.y >= 647 && Breakout.Mouseposition.y <= 699) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 2;
					Breakout.Sound();
					while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor);
					Breakout.ResetPlayer();
					Breakout.ResetLevel();
					scene = 3;
					Breakout.State = GAME_ACTIVE;
					SoundEngine->play2D("ReadyGo.wav", GL_FALSE);
				}
				//选择颜色
				if (Breakout.Mouseposition.x >= 651 && Breakout.Mouseposition.x <= 974 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
					Breakout.Mouse = GL_TRUE;
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					if (Breakout.Mouseposition.x >= 650 && Breakout.Mouseposition.x <= 690 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition =glm::vec2(652, 398);
						Breakout.color = Breakout.red;
					}
					if (Breakout.Mouseposition.x >= 690 && Breakout.Mouseposition.x <= 730 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(692, 398);
						Breakout.color = Breakout.blue;
					}
					if (Breakout.Mouseposition.x >= 730 && Breakout.Mouseposition.x <= 770 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(732, 398);
						Breakout.color = Breakout.yellow;
					}
					if (Breakout.Mouseposition.x >= 770 && Breakout.Mouseposition.x <= 810 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(772, 398);
						Breakout.color = Breakout.green;
					}
					if (Breakout.Mouseposition.x >= 810 && Breakout.Mouseposition.x <= 850 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(812, 398);
						Breakout.color = Breakout.pink;
					}
					if (Breakout.Mouseposition.x >= 850 && Breakout.Mouseposition.x <= 890 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(852, 398);
						Breakout.color = Breakout.orange;
					}
					if (Breakout.Mouseposition.x >= 890 && Breakout.Mouseposition.x <= 930 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(892, 398);
						Breakout.color = Breakout.purple;
					}
					if (Breakout.Mouseposition.x >= 930 && Breakout.Mouseposition.x <= 970 && Breakout.Mouseposition.y >= 398 && Breakout.Mouseposition.y <= 439) {
						Breakout.Gouposition = glm::vec2(932, 398);
						Breakout.color = Breakout.gray;
					}
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
				}
				//选择人物
				//火影
				if (Breakout.Mouseposition.x >= 747 && Breakout.Mouseposition.x <= 811 && Breakout.Mouseposition.y >= 261 && Breakout.Mouseposition.y <= 322) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
					Feature = 0;
				}
				//孙悟空
				if (Breakout.Mouseposition.x >= 878 && Breakout.Mouseposition.x <= 943 && Breakout.Mouseposition.y >= 261 && Breakout.Mouseposition.y <= 322) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
					Feature = 1;
				}
				//进入地图选择
				if (Breakout.Mouseposition.x >= 651 && Breakout.Mouseposition.x <= 769 && Breakout.Mouseposition.y >= 162 && Breakout.Mouseposition.y <= 203) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					Mapchoose = GL_TRUE;
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
				}
			}
			if (Mapchoose) {
				//选择地图
				if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 77 && Breakout.Mouseposition.y <= 647) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
					//机械世界
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 77 && Breakout.Mouseposition.y <= 122) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[0] = GL_TRUE;
					}
					//夺宝
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 122 && Breakout.Mouseposition.y <= 167) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[1] = GL_TRUE;
					}
					//英雄
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 167 && Breakout.Mouseposition.y <= 212) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[2] = GL_TRUE;
					}
					//足球
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 212 && Breakout.Mouseposition.y <= 257) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[3] = GL_TRUE;
					}
					//抢包山
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 257 && Breakout.Mouseposition.y <= 302) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[4] = GL_TRUE;
					}
					//糖客战
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 302 && Breakout.Mouseposition.y <= 347) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[5] = GL_TRUE;
					}
					//比武
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 347 && Breakout.Mouseposition.y <= 392) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[6] = GL_TRUE;
					}
					//功夫
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 392 && Breakout.Mouseposition.y <= 437) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[7] = GL_TRUE;
					}
					//水面
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 437 && Breakout.Mouseposition.y <= 472) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[8] = GL_TRUE;
					}
					//野外
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 472 && Breakout.Mouseposition.y <= 517) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[9] = GL_TRUE;
					}
					//中国城
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 517 && Breakout.Mouseposition.y <= 562) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[10] = GL_TRUE;
					}
					//沙漠
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 562 && Breakout.Mouseposition.y <= 607) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[11] = GL_TRUE;
					}
					//矿洞
					if (Breakout.Mouseposition.x >= 598 && Breakout.Mouseposition.x <= 744 && Breakout.Mouseposition.y >= 607 && Breakout.Mouseposition.y <= 652) {
						for (int i = 0; i < 13; i++) {
							Mapchoice[i] = GL_FALSE;
						}
						Mapchoice[12] = GL_TRUE;
					}
				}
				//确定
				if (Breakout.Mouseposition.x >= 606 && Breakout.Mouseposition.x <= 662 && Breakout.Mouseposition.y >= 669 && Breakout.Mouseposition.y <= 705) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					Mapchoose = GL_FALSE;
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
					for (int i = 0; i < 13; i++) {
						if (Mapchoice[i]) {
							Breakout.Level = i;
							Breakout.Daoju = i+13;
						}
					}
				}
				//取消
				if (Breakout.Mouseposition.x >= 688 && Breakout.Mouseposition.x <= 741 && Breakout.Mouseposition.y >= 669 && Breakout.Mouseposition.y <= 705) {
					glfwSetCursor(window, cursor3);
					clock_t delay = clock();
					Breakout.Soundchoic = 1;
					Breakout.Sound();
					Mapchoose = GL_FALSE;
					while (clock() - delay <= 0.3 * CLOCKS_PER_SEC);
					glfwSetCursor(window, cursor2);
					for (int i = 0; i < 13; i++) {
						Mapchoice[i] = GL_FALSE;
					}
				}
			}
		}
	}

	if (scene == 3) {
		if (action == GLFW_PRESS) {
			//退出
			if (Breakout.Mouseposition.x >= 906 && Breakout.Mouseposition.x <= 971 && Breakout.Mouseposition.y >= 646 && Breakout.Mouseposition.y <= 700) {
				glfwSetCursor(window, cursor3);
				clock_t delay = clock();
				for (GameObject &box : Breakout.Levels[Breakout.Daoju].Numproperty)
				{
					box.Destroyed = true;
				}
				for (GameObject &box : Breakout.Levels[Breakout.Daoju].Velocityproperty)
				{
					box.Destroyed = true;
				}
				for (GameObject &box : Breakout.Levels[Breakout.Daoju].Strengthproperty)
				{
					box.Destroyed = true;
				}
				for (GameObject &box : Breakout.Levels[Breakout.Daoju].Feibiaoproperty)
				{
					box.Destroyed = true;
				}
				for (GameObject &box : Breakout.Levels[Breakout.Daoju].Liveproperty)
				{
					box.Destroyed = true;
				}
				SoundEngine->play2D("uiMain.wav", GL_FALSE);
				while (clock() - delay <= 0.5 * CLOCKS_PER_SEC);
				SoundEngine->removeAllSoundSources();
				glfwSetCursor(window, cursor);
				Breakout.State = GAME_MENU;
				scene = 2;
				SoundEngine->play2D("M10.ogg", GL_TRUE);
			}
		}
	}
}

