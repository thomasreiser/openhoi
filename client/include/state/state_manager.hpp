// Copyright 2018-2019 the openhoi authors. See COPYING.md for legal info.

#pragma once

#include "state.hpp"

namespace openhoi {

// State manager class
class StateManager final {
 public:
  // StateManager destructor
  ~StateManager();

  // Starts up the state manager *
  void startup(State* firstState);

  // Update the current state
  void updateState();

  // Request state manager to change state
  void requestStateChange(State* newState);

 private:
  // Switch to the new state
  void switchToNewState(State* newState);

  // Describes the current state
  State* currentState = nullptr;
  // Describes the (possible) new state
  State* newState = nullptr;
};

}  // namespace openhoi