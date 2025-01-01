#include "Game.h"

#include "../WindowManager/WindowManager.h"
#include "../AssetManager/AssetManager.h"
#include "../Renderer/Renderer.h"
#include "../InputManager/InputManager.h"

#include <enet/enet.h>

#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

Game& Game::get()
{
	static Game instance;
	return instance;
}

void Game::initializeENet()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Error: An error occurred while initializing ENet" << std::endl;
	}
	atexit(enet_deinitialize);
}

void Game::loadResources()
{
	WindowManager::get(); // Asigura setup-ul la OpenGL, trebuie sa fie primul apelat.
	AssetManager::get().loadResources();
	this->initializeENet(); // Enet
}

void Game::run()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(WindowManager::get().getWindow()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		this->update();
		this->draw();

		glfwSwapBuffers(WindowManager::get().getWindow());
		glfwPollEvents();
	}
}

void Game::draw()
{

}

void Game::update()
{
	InputManager::get().update();
}

void Game::start()
{
	this->loadResources();
	this->run();
}




