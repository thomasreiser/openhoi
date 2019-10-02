// Copyright 2018-2019 the openhoi authors. See COPYING.md for legal info.

#include "options.hpp"

namespace openhoi {

// Options constructor
Options::Options()
    : videoMode(""),
      fullScreenAntiAliasing(8),
      windowMode(WindowMode::FULLSCREEN),
      verticalSync(true),
      audioDevice("") {}

// Gets the video mode name
std::string const& Options::getVideoMode() const { return videoMode; }

// Sets the video mode name
void Options::setVideoMode(std::string const& videoMode) {
  this->videoMode = videoMode;
}

// Gets the FSAA level
byte const& Options::getFullScreenAntiAliasing() const {
  return this->fullScreenAntiAliasing;
}

// Sets the FSAA flag
void Options::setFullScreenAntiAliasing(byte const& fullScreenAntiAliasing) {
  this->fullScreenAntiAliasing = fullScreenAntiAliasing;
}

// Gets the window mode
WindowMode const& Options::getWindowMode() const { return windowMode; }

// Sets the window mode
void Options::setWindowMode(WindowMode const& windowMode) {
  this->windowMode = windowMode;
}

// Gets the vertical sync flag
bool const& Options::isVerticalSync() const { return verticalSync; }

// Sets the vertical sync flag
void Options::setVerticalSync(bool const& verticalSync) {
  this->verticalSync = verticalSync;
}

// Gets the audio device name
std::string const& Options::getAudioDevice() const { return audioDevice; }

// Sets the audio device name
void Options::setAudioDevice(std::string const& audioDevice) {
  this->audioDevice = audioDevice;
}

}  // namespace openhoi