# FMODAudioDemo

This project is my 2D application built using C++ and the AIE game framework that demonstrates basic audio programming with FMOD.  My custom `SoundManager` class is used to load, play and adjust volume for sounds at runtime using FMOD's Core API.

---

##  Controls

- `SPACE`: Play the "coin" sound once per key press.
- `W`: Increase the volume of the sound.
- `S`: Decrease the volume of the sound.
- `ESC`: Exit the application.

The current volume level is displayed on-screen as a percentage.

---

##  Features

- FMOD Core API integration.
- Dynamic sound loading and playback.
- Real-time volume adjustment.
- Clean and modular `SoundManager` implementation.
- On-screen volume feedback.
- Key debounce logic to prevent repeated triggering on hold.
