#pragma once
#include <algorithm>
#include <unordered_map>
#include <map>
#include <string>
#include "../dependencies/fmod/inc/fmod.hpp"

// Helper class to manage sound loading, playback and volume
class SoundManager {
public:
    bool initialize();       // Initialise FMOD system
    void shutdown();         // Shutdown and clean up FMOD system

    bool loadSound(const std::string& name, const std::string& filepath); // Load sound file
    void playSound(const std::string& name);                               // Play loaded sound
    void stopAllSounds();                                                 // Stop all active sounds

    bool adjustVolume(const std::string& name, float delta);             // Increment/decrement volume
    bool getVolume(const std::string& name, float& volume) const;        // Retrieve volume level
    bool setVolume(const std::string& name, float volume);               // Set volume to specific level

private:
    FMOD::System* m_fmodSystem = nullptr;  // Pointer to FMOD system
    std::map<std::string, FMOD::Sound*> m_sounds;      // Loaded sounds
    std::map<std::string, FMOD::Channel*> m_channels;  // Channels playing each sound
    std::unordered_map<std::string, float> m_volumes;  // Stored volumes per sound
};
