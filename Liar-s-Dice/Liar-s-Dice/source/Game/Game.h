#pragma once

class Game
{
public:
	enum class Status
	{
		EXITING,
		IN_MAIN_MENU,
		IN_SETTINGS_MENU,
		IN_MULTIPLAYER_MENU,
		IN_CREATE_GAME_MENU,
		IN_JOIN_GAME_MENU,
		IN_GAME,

		NONE,
		// etc..
	};

private:
	Game();
	~Game();
	Game(const Game& other) = delete;
	Game& operator= (const Game& other) = delete;
	Game(const Game&& other) = delete;
	Game& operator= (const Game&& other) = delete;

	Status status;

	void loadResources();
	void run();
	void draw();
	void update();

	void initializeENet();

public:
	static Game& get();
	void start();

	inline Status getStatus() const { return this->status; }
	inline void setStatus(Status status) { this->status = status; }
};

