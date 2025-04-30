#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D()
	: m_2dRenderer(nullptr),
	m_texture(nullptr),
	m_font(nullptr),
	m_timer(0.0f),
	m_sound(nullptr),
	m_fmodSystem(nullptr),
	m_channel(nullptr)
{
}

Application2D::~Application2D() {}

bool Application2D::startup() {
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_font = new aie::Font("./font/consolas.ttf", 26);

	m_timer = 0;

	// Initialise SoundManager system
	if (!m_soundManager.initialize()) {
		printf("Failed to initialise SoundManager\n");
		return false;
	}

	// Load a sound asset for use during runtime
	if (!m_soundManager.loadSound("coin", "../sounds/coin.wav")) {
		printf("Failed to load sound: coin.wav\n");
		return false;
	}

	return true;
}

void Application2D::shutdown() {
	delete m_font;
	delete m_texture;
	delete m_2dRenderer;

	// Properly shutdown SoundManager system
	m_soundManager.shutdown();
}

void Application2D::update(float deltaTime) {
	m_timer += deltaTime;

	// Get keyboard input system
	aie::Input* input = aie::Input::getInstance();

	// Detect SPACE key press to play the coin sound (single press only)
	static bool wasSpacePressed = false;
	if (input->isKeyDown(aie::INPUT_KEY_SPACE)) {
		if (!wasSpacePressed) {
			m_soundManager.playSound("coin");
			wasSpacePressed = true;
		}
	}
	else {
		wasSpacePressed = false;
	}

	// Use W to increase sound volume
	if (input->isKeyDown(aie::INPUT_KEY_W)) {
		m_soundManager.adjustVolume("coin", 0.005f); // Adjust volume up
	}

	// Use S to decrease sound volume
	if (input->isKeyDown(aie::INPUT_KEY_S)) {
		m_soundManager.adjustVolume("coin", -0.005f); // Adjust volume down
	}

	// Exit application using ESCAPE key
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {
	// Clear the screen with the background colour
	clearScreen();

	// Begin 2D rendering pass
	m_2dRenderer->begin();

	m_2dRenderer->drawText(m_font, "Controls:", 0, 720 - 28);
	m_2dRenderer->drawText(m_font, "- Use SPACE key to play the sound.", 0, 720 - 56);
	m_2dRenderer->drawText(m_font, "- Use W key to increase volume, S key to decrease volume.", 0, 720 - 82);

	// Retrieve and display current sound volume
	float volume = 1.0f;
	m_soundManager.getVolume("coin", volume);
	char volumeText[32];
	sprintf_s(volumeText, 32, "Volume: %.0f%%", volume * 100);
	m_2dRenderer->drawText(m_font, volumeText, 0, 720 - 128);

	// End 2D rendering pass
	m_2dRenderer->end();
}