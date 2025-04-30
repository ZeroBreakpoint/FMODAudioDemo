#include "SoundManager.h"

bool SoundManager::initialize() {
    FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
    if (result != FMOD_OK) return false;

    result = m_fmodSystem->init(512, FMOD_INIT_NORMAL, nullptr);
    return result == FMOD_OK;
}

void SoundManager::shutdown() {
    // Release all loaded sounds
    for (auto& pair : m_sounds) {
        pair.second->release();
    }
    m_sounds.clear();

    // Properly shutdown FMOD system
    if (m_fmodSystem) {
        m_fmodSystem->close();
        m_fmodSystem->release();
    }
}

bool SoundManager::loadSound(const std::string& name, const std::string& filepath) {
    FMOD::Sound* sound = nullptr;
    FMOD_RESULT result = m_fmodSystem->createSound(filepath.c_str(), FMOD_DEFAULT, nullptr, &sound);
    if (result != FMOD_OK) return false;

    m_sounds[name] = sound;

    // Default volume set to 1.0f (100%) if not previously assigned
    if (m_volumes.find(name) == m_volumes.end()) {
        m_volumes[name] = 1.0f;
    }

    // Pre-create a channel with paused playback (so volume can be set)
    FMOD::Channel* channel = nullptr;
    m_fmodSystem->playSound(sound, nullptr, true, &channel);
    if (channel) {
        m_channels[name] = channel;
        channel->setVolume(m_volumes[name]); // Set the stored volume
    }

    return true;
}

void SoundManager::playSound(const std::string& name) {
    auto it = m_sounds.find(name);
    if (it != m_sounds.end()) {
        float volume = m_volumes.count(name) ? m_volumes[name] : 1.0f;

        // Do not play if volume is muted
        if (volume <= 0.0f) return;

        FMOD::Channel* channel = nullptr;
        m_fmodSystem->playSound(it->second, nullptr, false, &channel);
        m_channels[name] = channel;

        // Apply the stored volume to the new channel
        channel->setVolume(volume);
    }
}

void SoundManager::stopAllSounds() {
    // Update FMOD system state (not used for stopping in this example)
    m_fmodSystem->update();
}

bool SoundManager::adjustVolume(const std::string& name, float delta) {
    auto it = m_channels.find(name);
    if (it != m_channels.end() && it->second) {
        float currentVolume;
        it->second->getVolume(&currentVolume);

        // Clamp volume between 0 and 1
        currentVolume = std::max(0.0f, std::min(currentVolume + delta, 1.0f));
        it->second->setVolume(currentVolume);

        // Update internal volume record
        m_volumes[name] = currentVolume;

        return true;
    }
    return false;
}

bool SoundManager::getVolume(const std::string& name, float& volume) const {
    auto it = m_channels.find(name);
    if (it != m_channels.end() && it->second) {
        it->second->getVolume(&volume);
        return true;
    }
    return false;
}

bool SoundManager::setVolume(const std::string& name, float volume) {
    auto it = m_channels.find(name);
    if (it != m_channels.end() && it->second) {
        volume = std::max(0.0f, std::min(volume, 1.0f));
        it->second->setVolume(volume);
        return true;
    }
    return false;
}