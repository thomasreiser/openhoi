// Copyright 2019 the openhoi authors. See COPYING.md for legal info.

#include "hoibase/helper/log_listener.hpp"
#include "hoibase/openhoi.hpp"

namespace openhoi {

// Log listener constructor
LogListener::LogListener() {
#ifndef OPENHOI_OS_WINDOWS
  // Set syslog log mask
  setlogmask(LOG_UPTO(LOG_NOTICE));

  // Open syslog
  openlog(OPENHOI_GAME_NAME, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
#endif
}

// Log listener destructor
LogListener::~LogListener() {
#ifndef OPENHOI_OS_WINDOWS
  // Close syslog
  closelog();
#endif
}

// This is called whenever the log receives a message and is about to write it
// out
void LogListener::messageLogged(const Ogre::String& message,
                                Ogre::LogMessageLevel lml, bool maskDebug,
                                const Ogre::String& logName,
                                bool& skipThisMessage) {
#ifndef OPENHOI_OS_WINDOWS
  int logLevel;
  switch (lml) {
    case Ogre::LogMessageLevel::LML_NORMAL:
      logLevel = LOG_INFO;
      break;
    case Ogre::LogMessageLevel::LML_WARNING:
      logLevel = LOG_WARNING;
      break;
    case Ogre::LogMessageLevel::LML_CRITICAL:
      logLevel = LOG_ERR;
      break;
    default:
      logLevel = LOG_NOTICE;
  }

  syslog(logLevel, message);
#endif
}

}  // namespace openhoi