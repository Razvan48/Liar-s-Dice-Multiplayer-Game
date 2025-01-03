#include "AssetManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../Game/Game.h"

AssetManager::AssetManager()
	: FONT_SIZE(48), soundEnabled(true)
{
	stbi_set_flip_vertically_on_load(true);

	this->soundEngine = irrklang::createIrrKlangDevice();

	if (FT_Init_FreeType(&this->freeType))
	{
		std::cout << "Error: Could not init FreeType Library" << std::endl;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

AssetManager::~AssetManager()
{
	FT_Done_FreeType(this->freeType);
	this->soundEngine->drop();
}

AssetManager& AssetManager::get()
{
	static AssetManager instance;
	return instance;
}

void AssetManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	if (this->textures.find(textureName) != this->textures.end())
		std::cout << "Warning: Texture " + textureName + " already loaded" << std::endl;
	else
		this->textures[textureName] = AssetManager::Texture();

	glGenTextures(1, &this->textures[textureName].texture);
	glBindTexture(GL_TEXTURE_2D, this->textures[textureName].texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* textureData = stbi_load(texturePath.c_str(),
		&this->textures[textureName].width,
		&this->textures[textureName].height,
		&this->textures[textureName].nrChannels,
		0);

	if (!textureData)
	{
		std::cout << "Error: Failed to load texture " + textureName + " at path : " << texturePath << std::endl;
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->textures[textureName].width, this->textures[textureName].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(textureData);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void AssetManager::loadSound(const std::string& soundName, const std::string& soundPath)
{
	if (this->sounds.find(soundName) != this->sounds.end())
		std::cout << "Warning: Sound " + soundName + " already loaded" << std::endl;
	else
		this->sounds[soundName] = soundPath;
}

void AssetManager::loadFont(const std::string& fontName, const std::string& fontPath)
{
	FT_Face freeTypeFace;

	if (FT_New_Face(this->freeType, fontPath.c_str(), 0, &freeTypeFace)) // 0 = un singur tip de font, nu avem bold/italic/etc.
	{
		std::cout << "Error: Failed to load font " << fontName << " from path " << fontPath << std::endl;
	}
	else
	{
		if (this->fonts.find(fontName) != this->fonts.end())
			std::cout << "Warning: Font " + fontName + " already loaded" << std::endl;
		else
			this->fonts[fontName] = std::vector<AssetManager::Character>();

		FT_Set_Pixel_Sizes(freeTypeFace, 0, this->FONT_SIZE); // Setam inaltimea, latimea se seteaza automat

		for (unsigned char character = 0; character < 128; character++) // Cu primele 128 de caractere din tabela ascii putem desena cam orice text
		{
			if (FT_Load_Char(freeTypeFace, character, FT_LOAD_RENDER)) // Incarcare caracter
			{
				std::cout << "Error: Failed to load Glyph for " << character << std::endl;
				continue;
			}

			// Generare textura
			this->fonts[fontName].emplace_back();

			this->fonts[fontName].back().size = glm::ivec2(freeTypeFace->glyph->bitmap.width, freeTypeFace->glyph->bitmap.rows);
			this->fonts[fontName].back().bearing = glm::ivec2(freeTypeFace->glyph->bitmap_left, freeTypeFace->glyph->bitmap_top);
			this->fonts[fontName].back().advance = freeTypeFace->glyph->advance.x;

			glGenTextures(1, &this->fonts[fontName].back().texture);
			glBindTexture(GL_TEXTURE_2D, this->fonts[fontName].back().texture);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->fonts[fontName].back().size[0],
				this->fonts[fontName].back().size[1], 0, GL_RED, GL_UNSIGNED_BYTE,
				freeTypeFace->glyph->bitmap.buffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	FT_Done_Face(freeTypeFace);
}

void AssetManager::loadResources()
{
	this->loadFont("arialFont", "assets/fonts/arialFont.ttf");



	this->loadSound("boardStart0Sound", "assets/sounds/boardStart0Sound.mp3");
	this->loadSound("boardStart1Sound", "assets/sounds/boardStart1Sound.mp3");

	this->loadSound("dice0Sound", "assets/sounds/dice0Sound.mp3");
	this->loadSound("dice1Sound", "assets/sounds/dice1Sound.mp3");

	this->loadSound("draw0Sound", "assets/sounds/draw0Sound.mp3");
	this->loadSound("draw1Sound", "assets/sounds/draw1Sound.mp3");
	this->loadSound("draw2Sound", "assets/sounds/draw2Sound.mp3");

	this->loadSound("errorSound", "assets/sounds/errorSound.mp3");

	this->loadSound("hoveredButtonSound", "assets/sounds/hoveredButtonSound.mp3");

	this->loadSound("lose0Sound", "assets/sounds/lose0Sound.mp3");

	this->loadSound("pressedButtonSound", "assets/sounds/pressedButtonSound.mp3");

	this->loadSound("win0Sound", "assets/sounds/win0Sound.mp3");
	this->loadSound("win1Sound", "assets/sounds/win1Sound.mp3");



	this->loadTexture("arrowTexture", "assets/textures/arrowTexture.png");
	this->loadTexture("buttonTexture", "assets/textures/buttonTexture.png");

	this->loadTexture("creditsMenuBackgroundTexture", "assets/textures/creditsMenuBackgroundTexture.png");

	this->loadTexture("cupTexture", "assets/textures/cupTexture.png");
	this->loadTexture("dataBoxTexture", "assets/textures/dataBoxTexture.png");

	this->loadTexture("dice1Texture", "assets/textures/dice1Texture.png");
	this->loadTexture("dice2Texture", "assets/textures/dice2Texture.png");
	this->loadTexture("dice3Texture", "assets/textures/dice3Texture.png");
	this->loadTexture("dice4Texture", "assets/textures/dice4Texture.png");
	this->loadTexture("dice5Texture", "assets/textures/dice5Texture.png");
	this->loadTexture("dice6Texture", "assets/textures/dice6Texture.png");

	this->loadTexture("handHidingTexture.png", "assets/textures/handHidingTexture.png");
	this->loadTexture("handPointingTexture.png", "assets/textures/handPointingTexture.png");

	this->loadTexture("hoveredArrowTexture", "assets/textures/hoveredArrowTexture.png");
	this->loadTexture("hoveredButtonTexture", "assets/textures/hoveredButtonTexture.png");
	this->loadTexture("inactiveArrowTexture", "assets/textures/inactiveArrowTexture.png");
	this->loadTexture("inactiveButtonTexture", "assets/textures/inactiveButtonTexture.png");

	this->loadTexture("inGameBackgroundTexture", "assets/textures/inGameBackgroundTexture.png");
	this->loadTexture("inputMenuBackgroundTexture", "assets/textures/inputMenuBackgroundTexture.png");
	this->loadTexture("mainMenuBackgroundTexture", "assets/textures/mainMenuBackgroundTexture.png");

	this->loadTexture("markedDice1Texture.png", "assets/textures/markedDice1Texture.png");
	this->loadTexture("markedDice2Texture.png", "assets/textures/markedDice2Texture.png");
	this->loadTexture("markedDice3Texture.png", "assets/textures/markedDice3Texture.png");
	this->loadTexture("markedDice4Texture.png", "assets/textures/markedDice4Texture.png");
	this->loadTexture("markedDice5Texture.png", "assets/textures/markedDice5Texture.png");
	this->loadTexture("markedDice6Texture.png", "assets/textures/markedDice6Texture.png");

	this->loadTexture("multiplayerMenuBackgroundTexture", "assets/textures/multiplayerMenuBackgroundTexture.png");
	this->loadTexture("pointingArrowTexture", "assets/textures/pointingArrowTexture.png");
	this->loadTexture("settingsMenuBackgroundTexture", "assets/textures/settingsMenuBackgroundTexture.png");
}

GLuint AssetManager::getTexture(const std::string& textureName)
{
	if (this->textures.find(textureName) == this->textures.end())
	{
		std::cout << "Error: Texture " + textureName + " not found" << std::endl;
		return 0;
	}

	return this->textures[textureName].texture;
}

std::vector<AssetManager::Character>& AssetManager::getFont(const std::string& fontName)
{
	if (this->fonts.find(fontName) == this->fonts.end())
	{
		std::cout << "Error: Font " + fontName + " not found" << std::endl;
		return this->fonts.end()->second;
	}

	return this->fonts[fontName];
}

void AssetManager::playSound(const std::string& soundName, bool isLooping, bool canOverlapSameSound)
{
	if (this->sounds.find(soundName) == this->sounds.end())
	{
		std::cout << "Error: Sound " + soundName + " not found" << std::endl;
		return;
	}

	if (this->soundEnabled)
	{
		if (!canOverlapSameSound)
		{
			if (!this->soundEngine->isCurrentlyPlaying(this->sounds[soundName].c_str()))
			{
				this->soundEngine->play2D(this->sounds[soundName].c_str(), isLooping);
			}
		}
		else
		{
			this->soundEngine->play2D(this->sounds[soundName].c_str(), isLooping);
		}
	}
	else
	{
		std::cout << "Info: Sound " + soundName + " was not played because sound is disabled" << std::endl;
	}
}

