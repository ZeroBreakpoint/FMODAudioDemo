#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "SoundManager.h"
#include "../dependencies/fmod/inc/fmod.hpp"
#include "../dependencies/fmod/inc/fmod_errors.h"
#include "../glfw/include/GLFW/glfw3.h"
#include <iostream>

// The main application class for 2D rendering and sound
class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();   // Called once on application start
	virtual void shutdown();  // Called once on application close

	virtual void update(float deltaTime); // Called each frame to update logic
	virtual void draw();                  // Called each frame to render graphics

protected:

	aie::Renderer2D* m_2dRenderer;   // Responsible for drawing 2D elements
	aie::Texture* m_texture;      // Placeholder texture for visual testing
	aie::Font* m_font;         // Font for on-screen text

	FMOD::System* m_fmodSystem;     // FMOD system interface (not used directly here)
	FMOD::Channel* m_channel;       // FMOD channel for audio playback
	FMOD::Sound* m_sound;           // FMOD sound object

	float m_timer; // Internal timer for use in updates

	SoundManager m_soundManager; // Manages loading, playing and adjusting audio
};