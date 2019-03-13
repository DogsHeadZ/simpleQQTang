#include<iostream>
#define GLEW_STATIC
#include<glew.h>
#include<glfw3.h>
#include<cmath>
#include<ctime>
#include<SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
void cursor_enter_callback(GLFWwindow* window, int entered);
void draw_circle(float centerx, float centery);
const GLuint WIDTH = 1000, HEIGHT = 1000;
GLfloat x = 0.1f, y = 0.1f;
GLfloat verticesb[675], verticesw[675], circles[1200], Points[3];
int circleindices[300];
static int  White[31][31], Black[31][31];
int count = 0, nb, nw, ib, iw, countb, countw, circlei, circlen = 40;
int soe;
const float pi = 3.1415926536f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, mouse_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);
	Shader ourShader("myshader1.vs", "myshader1.frag");
	GLfloat vertices[] = {
		-0.7f,-0.9f,0.0f,
		0.7f,-0.9f,0.0f,
	};
	GLfloat vertices2[] = {
		-0.8f,-0.8f,0.0f,
		-0.8f,0.6f,0.0f
	};

	GLuint VBO[3], VAO[3];
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Points), Points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint VBO1[3], VAO1[3], EBO[3];
	glGenVertexArrays(3, VAO1);
	glGenBuffers(3, VBO1);
	glGenBuffers(3, EBO);
	glBindVertexArray(VAO1[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint VBO2[3], VAO2[3], EBO1[3];
	glGenVertexArrays(3, VAO2);
	glGenBuffers(3, VBO2);
	glGenBuffers(3, EBO1);
	glBindVertexArray(VAO2[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1[2]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Shader ourShader1("myshader2.vs", "myshader2.frag");
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat start_or_exit[] = {
		-0.3f,  0.15f, 0.0f,1,1,1,0.0f,1.0f,
		0.3f, 0.15f, 0.0f,1,1,1,1.0f,1.0f,
		0.3f, -0.3f, 0.0f,1,1,1,1.0f,0.0f,
		-0.3f,  -0.3f, 0.0f ,0.0f,0.0f
	};
	GLint soeindices[] = {
		0, 1, 2,  // First Triangle
		0, 2, 3
	};

	GLuint VBO5, VAO5, EBO5;
	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	glBindVertexArray(VAO5);
	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(start_or_exit), start_or_exit, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(soeindices), soeindices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO

						  // Load and create a texture 
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
											// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width1, height1;
	unsigned char* image1 = SOIL_load_image("黑赢.jpg", &width1, &height1, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
											// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width2, height2;
	unsigned char* image2 = SOIL_load_image("白赢.jpg", &width2, &height2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image("开始退出.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	Shader ourShader3("myshader4.vs", "myshader4.frag");
	GLfloat giveup[] = {
		-0.1f,  -0.9f, 0.0f,1,1,1,0.0f,1.0f,
		0.1f, -0.9f, 0.0f,1,1,1,1.0f,1.0f,
		0.1f, -0.95f, 0.0f,1,1,1,1.0f,0.0f,
		-0.1f,  -0.95f, 0.0f ,0.0f,0.0f
	};
	GLint guindices[] = {
		0, 1, 2,  // First Triangle
		0, 2, 3
	};
	GLuint VBO7, VAO7, EBO7;
	glGenVertexArrays(1, &VAO7);
	glGenBuffers(1, &VBO7);
	glGenBuffers(1, &EBO7);
	glBindVertexArray(VAO7);
	glBindBuffer(GL_ARRAY_BUFFER, VBO7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(giveup), giveup, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO7);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(guindices), guindices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO

	GLuint texture7;
	glGenTextures(1, &texture7);
	glBindTexture(GL_TEXTURE_2D, texture7);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width7, height7;
	unsigned char* image7 = SOIL_load_image("认输.jpg", &width7, &height7, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width7, height7, 0, GL_RGB, GL_UNSIGNED_BYTE, image7);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image7);
	glBindTexture(GL_TEXTURE_2D, 0);

	Shader ourShader2("myshader3.vs", "myshader3.frag");     //这一段看似无用可删去，但删去它会产生无法理解的bug
	GLuint VBO6, VAO6, EBO6;
	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	glBindVertexArray(VAO6);
	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(start_or_exit), start_or_exit, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(soeindices), soeindices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		ourShader.Use();
		GLint vertexColorLocation = glGetUniformLocation(ourShader.Program, "myColor");
		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::mat4 trans;
		for (int i = 0; i < 15; i++) {
			trans = glm::translate(trans, glm::vec3(0, 0.1, 0));
			GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			glBindVertexArray(VAO[0]);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}
		glm::mat4 transs;
		for (int i = 0; i < 15; i++) {
			transs = glm::translate(transs, glm::vec3(0.1, 0, 0));
			GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transs));
			glBindVertexArray(VAO[1]);
			glDrawArrays(GL_LINES, 0, 2);
			glBindVertexArray(0);
		}
		glm::mat4 inittranc;
		GLuint transformLoc = glGetUniformLocation(ourShader.Program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(inittranc));
		if (soe == 0) {
			glBindTexture(GL_TEXTURE_2D, texture);
			// Activate shader
			ourShader1.Use();
			glBindVertexArray(VAO5);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		ourShader.Use();
		if (soe == 1) {
			glBindTexture(GL_TEXTURE_2D, texture7);
			// Activate shader
			ourShader3.Use();
			glBindVertexArray(VAO7);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			ourShader.Use();

			glBindVertexArray(VAO1[0]);
			for (int i = 0; i < iw; i++) {
				draw_circle(verticesw[3 * i], verticesw[3 * i + 1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(circles), circles, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circleindices), circleindices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glUniform4f(vertexColorLocation, 1.0f, 1.0f, 1.0f, 1.0f);
				glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);

			glBindVertexArray(VAO2[2]);
			for (int i = 0; i < ib; i++) {
				draw_circle(verticesb[3 * i], verticesb[3 * i + 1]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(circles), circles, GL_STATIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circleindices), circleindices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 1.0f);
				glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
			}
			glBindVertexArray(0);

			if (ib > iw) {
				Points[0] = verticesb[3 * ib - 3];
				Points[1] = verticesb[3 * ib - 2];
				Points[2] = 0;
				glBindVertexArray(VAO[2]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Points), Points, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glPointSize(10);
				glDrawArrays(GL_POINTS, 0, 1);
				glBindVertexArray(0);
			}
			if (ib <= iw&&iw>0) {
				Points[0] = verticesw[3 * iw - 3];
				Points[1] = verticesw[3 * iw - 2];
				Points[2] = 0;
				glBindVertexArray(VAO[2]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(Points), Points, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
				glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 1.0f);
				glPointSize(10);
				glDrawArrays(GL_POINTS, 0, 1);
				glBindVertexArray(0);
			}
		}

		if (countb == 5) {
			glBindTexture(GL_TEXTURE_2D, texture1);
			// Activate shader
			ourShader1.Use();
			glBindVertexArray(VAO5);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		if (countw == 5) {
			glBindTexture(GL_TEXTURE_2D, texture2);
			// Activate shader
			ourShader1.Use();
			glBindVertexArray(VAO5);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		ourShader.Use();
		glfwSwapBuffers(window);

		if (countb == 5 || countw == 5) {
			glfwSetWindowShouldClose(window, GL_TRUE);
			clock_t delay = 1 * CLOCKS_PER_SEC;
			clock_t start = clock();
			while (clock() - start < delay)
				;
		}
	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glfwTerminate();
	return 0;
}

void mouse_button_callback(GLFWwindow* window, int botton, int action, int mode)
{
	double xpos1, ypos1;
	glfwGetCursorPos(window, &xpos1, &ypos1);
	x = (xpos1 / WIDTH - 0.5) * 2;
	y = (0.5 - ypos1 / HEIGHT) * 2;
	if (action == GLFW_PRESS&&soe == 1) {
		int xi;
		int yi;
		for (int k = 0; k <= 14; k++) {
			if (abs(x + 0.7 - 0.1*k)<0.015)
			{
				for (int j = 0; j <= 14; j++)
					if (abs(y + 0.8 - 0.1*j) < 0.015) {
						count++;
						if (count % 2 == 1) {
							verticesb[nb] = 0.1*k - 0.7;
							verticesb[nb + 1] = 0.1*j - 0.8;
							verticesb[nb + 2] = 0;
							Black[k][j] = 1;
							nb += 3;
							ib++;
						}
						else {
							White[k][j] = 1;
							verticesw[nw] = 0.1*k - 0.7;
							verticesw[nw + 1] = 0.1*j - 0.8;
							verticesw[nw + 2] = 0;
							nw += 3;
							iw++;
						}
					}
			}
		}
		int m, n, v;
		for (m = 0; m < 15; m++) {
			for (n = 0; n < 15; n++) {
				for (v = n; v < n + 5; v++) {
					if (Black[m][v] == 1) countb++;
					if (White[m][v] == 1) countw++;
					if (countb == 5 || countw == 5) {
						return;
					}
				}
				countb = 0; countw = 0;
				for (v = m; v < m + 5; v++) {
					if (Black[v][n] == 1) countb++;
					if (White[v][m] == 1) countw++;
					if (countb == 5 || countw == 5) {
						return;
					}
				}
				countb = 0; countw = 0;
				for (int i = 0; i < 5; i++) {
					if (Black[m + i][n + i] == 1) countb++;
					if (White[m + i][n + i] == 1) countw++;
					if (countb == 5 || countw == 5) {
						return;
					}
				}
				countb = 0; countw = 0;
			}
		}
		for (m = 0; m < 15; m++) {
			for (n = 14; n >= 4; n--) {
				for (int i = 0; i < 5; i++) {
					if (Black[m + i][n - i] == 1) countb++;
					if (White[m + i][n - i] == 1) countw++;
					if (countb == 5 || countw == 5) {
						return;
					}
				}
				countb = 0; countw = 0;
			}
		}
	}

	if (action == GLFW_PRESS&&soe == 0) {
		if (x > -0.2625&&x<-0.0375 && y>-0.225 && y < -0.075) {
			soe = 1;
		}
		if (x <0.2625&&x>0.0375 && y>-0.225 && y < -0.075) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}

	if (action == GLFW_PRESS) {
		if (x > -0.1&&x<0.1&&y>-0.95&&y < -0.9) {
			if (ib > iw) countb = 5;
			else countw = 5;
		}
	}
}

void key_callback(GLFWwindow* window, int key, int ss, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	float x = (xpos / WIDTH - 0.5) * 2;
	float y = (0.5 - ypos / HEIGHT) * 2;
	if (soe == 1) {
		for (int i = 0; i <= 14; i++) {
			if (abs(x + 0.7 - 0.1*i) < 0.015)
			{
				for (int i = 0; i <= 14; i++)
					if (abs(y + 0.8 - 0.1*i) < 0.015) {
						GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
						glfwSetCursor(window, cursor);
						// The cursor entered the client area of the window
						return;
					}
			}
		}
		if (x > -0.1&&x<0.1&&y>-0.95&&y < -0.9) {
			GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			glfwSetCursor(window, cursor);
			return;
		}
	}
	if (soe == 0) {
		if (x > -0.2625&&x<-0.0375 && y>-0.225 && y < -0.075) {
			GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			glfwSetCursor(window, cursor);
			// The cursor entered the client area of the window
			return;
		}
		if (x <0.2625&&x>0.0375 && y>-0.225 && y < -0.075) {
			GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
			glfwSetCursor(window, cursor);
			// The cursor entered the client area of the window
			return;
		}
	}
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CURSOR_NORMAL);
	glfwSetCursor(window, cursor);
}

void draw_circle(float centerx, float centery)
{
	circles[0] = centerx;
	circles[1] = centery;
	circles[2] = 0;
	for (circlei = 0; circlei < circlen; circlei++) {
		circles[3 * circlei + 3] = 0.035*cos(2 * pi / circlen*circlei) + centerx;
		circles[3 * circlei + 4] = 0.035*sin(2 * pi / circlen*circlei) + centery;
		circles[3 * circlei + 5] = 0;
	}
	for (circlei = 0; circlei < circlen - 1; circlei++) {
		circleindices[3 * circlei] = 0;
		circleindices[3 * circlei + 1] = circlei + 1;
		circleindices[3 * circlei + 2] = circlei + 2;
	}
	circleindices[3 * circlei] = 0;
	circleindices[3 * circlei + 1] = 1;
	circleindices[3 * circlei + 2] = circlei + 1;
}

void cursor_enter_callback(GLFWwindow* window, int entered)

{

	if (entered)

	{


	}

	else

	{

		// The cursor left the client area of the window

	}

}


