#include "Game.h"


#include "../WindowManager/WindowManager.h"
#include "../AssetManager/AssetManager.h"
#include "../Renderer/Renderer.h"
#include "../InputManager/InputManager.h"

#include "../VisualInterface/MainMenuVisualInterface/MainMenuVisualInterface.h"
#include "../VisualInterface//SettingsMenuVisualInterface/SettingsMenuVisualInterface.h"

#include <enet/enet.h>

#include <iostream>

Game::Game()
	: status(Status::IN_MAIN_MENU)
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

void Game::setStatus(Status status)
{
	// TODO: switch dupa status pentru reset la interfete

	if (this->status != status)
	{
		switch (status)
		{
		case Status::IN_MAIN_MENU:
			MainMenuVisualInterface::get().resetResources();
			break;
		case Status::IN_SETTINGS_MENU:
			SettingsMenuVisualInterface::get().resetResources();
			break;
		}
	}

	this->status = status;
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
	// TODO: switch dupa status, desenam interfetele

	switch (this->status)
	{
	case Status::IN_MAIN_MENU:
		MainMenuVisualInterface::get().draw();
		break;
	case Status::IN_SETTINGS_MENU:
		SettingsMenuVisualInterface::get().draw();
		break;
	}
}

void Game::update()
{
	// TODO: switch dupa status pentru update la interfete

	switch (this->status)
	{
	case Status::IN_MAIN_MENU:
		MainMenuVisualInterface::get().update();
		break;
	case Status::IN_SETTINGS_MENU:
		SettingsMenuVisualInterface::get().update();
		break;
	}

	if (this->status == Status::EXITING)
	{
		glfwSetWindowShouldClose(WindowManager::get().getWindow(), GLFW_TRUE);
	}
	else if (InputManager::get().isKeyReleased(GLFW_KEY_ESCAPE))
	{
		this->status = Status::EXITING;
	}

	InputManager::get().update(); // Trebuie sa fie ultimul update, deoarece curata ce butoane s-au apasat.
}

void Game::start()
{
	this->loadResources();
	this->run();
}




