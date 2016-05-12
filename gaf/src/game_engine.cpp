#include <include/game_engine.h>

// global
GameEngine *gameEngine;

void main_game_loop()
{
	gameEngine->loop();
}

GameEngine::GameEngine()
{
	timer = new Timer();
	keyboard = new Keyboard();
	world_transform = new Transform_Old();
	world_transform->scale = 1.0f;
}

GameEngine::~GameEngine()
{
	for (unsigned int i = 0; i < inputTasks.size(); i++)
	{
		delete(inputTasks[i]);
	}
	for (unsigned int i = 0; i < updateTasks.size(); i++)
	{
		delete(updateTasks[i]);
	}
	for (unsigned int i = 0; i < drawTasks.size(); i++)
	{
		delete(drawTasks[i]);
	}

	delete(keyboard);
	delete(timer);
}

void GameEngine::loop()
{
	timer->tick();
	input();
	update();
	display();
}

void GameEngine::register_inputTask(InputTask *task)
{
	inputTasks.push_back(task);
}

void GameEngine::register_updateTask(UpdateTask * task)
{
	updateTasks.push_back(task);
}

void GameEngine::register_drawTask(DrawTask *task)
{
	drawTasks.push_back(task);
}

void GameEngine::input()
{
	for (unsigned int i = 0; i < inputTasks.size(); i++)
	{
		inputTasks[i]->input(keyboard);
	}
}

void GameEngine::update()
{
	for (unsigned int i = 0; i < updateTasks.size(); i++)
	{
		updateTasks[i]->update(timer);
	}
}

void GameEngine::display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	world_transform->applyST();

	for (unsigned int i = 0; i < drawTasks.size(); i++)
	{
		drawTasks[i]->draw();
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

