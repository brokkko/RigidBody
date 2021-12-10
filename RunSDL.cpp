#include <iostream>
#include <SDL.h> // Библиотека SDL 2
#include <glut.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "RBody.h"

SDL_Window* window;

const int width = 640; // ширина окна
const int height = 580; // высота окна

void init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	// Включаем двойной буфер, настраиваем цвета
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.
	window = SDL_CreateWindow(":)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window); // создаем контекст OpenGL

	if (window == NULL) {	// если не получилось создать окно, то выходим
		exit(1);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)width / (float)height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим

}

void draw(RBody* body) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(0.0f, -5.0f, -10);	// Сдвинуть вглубь экрана
	glRotatef(45.0f, 0, 1, 0);

	glPushMatrix();

	std::vector<Vector> global;
	global.push_back(body->localToGlobal(body->localVertex[0]));
	global.push_back(body->localToGlobal(body->localVertex[1]));
	global.push_back(body->localToGlobal(body->localVertex[2]));
	global.push_back(body->localToGlobal(body->localVertex[3]));
	global.push_back(body->localToGlobal(body->localVertex[4]));

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(global[0].x, global[0].y, global[0].z);
	glVertex3f(global[2].x, global[2].y, global[2].z);
	glVertex3f(global[1].x, global[1].y, global[1].z);

	glColor3f(0.5f, 0.0f, 1.0f);
	glVertex3f(global[0].x, global[0].y, global[0].z);
	glVertex3f(global[4].x, global[4].y, global[4].z);
	glVertex3f(global[1].x, global[1].y, global[1].z);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(global[0].x, global[0].y, global[0].z);
	glVertex3f(global[3].x, global[3].y, global[3].z);
	glVertex3f(global[2].x, global[2].y, global[2].z);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(global[1].x, global[1].y, global[1].z);
	glVertex3f(global[4].x, global[4].y, global[4].z);
	glVertex3f(global[2].x, global[2].y, global[2].z);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(global[2].x, global[2].y, global[2].z);
	glVertex3f(global[4].x, global[4].y, global[4].z);
	glVertex3f(global[3].x, global[3].y, global[3].z);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(global[3].x, global[3].y, global[3].z);
	glVertex3f(global[4].x, global[4].y, global[4].z);
	glVertex3f(global[0].x, global[0].y, global[0].z);

	glEnd();
	glDisable(GL_TRIANGLES);

	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(0.9f, 0.9f, 0.9f);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glEnd();
	glDisable(GL_LINE);

	glPopMatrix();

}

int main(int argc, char* argv[]) {

	init();

	bool running = true;

	double t = 0, dt = 0.01;
	RBody body;
	body.initialization(&body);
	body.state.particlePos.y = 10;

	while (running) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN: // если нажата клавиша
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: // клавиша ESC
					running = false;
					break;
				}
				break;
			}

		}

		body.state = body.oneFrame(body, dt, t);
		t += dt;

		draw(&body);

		// обновляем экран
		SDL_Delay(15);

		glFlush();
		SDL_GL_SwapWindow(window);
	}

	SDL_Quit();
	return 0;
}

