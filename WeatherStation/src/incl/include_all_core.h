
#pragma once

#ifndef INCLUDE_ALL_CORE_H
#define INCLUDE_ALL_CORE_H

#define PROJECT_NAME "Weather-Station-V3"
#define PROJECT_VERSION "v3.0.0"
#define PROJECT_SUBVERSION 0


#include <Arduino.h>

/**
 *  Main defs
 */
#include "config_persistence.h"


/**
 * Include user + board + solar tracer configs
 */
#include "../../config.h"

/**
 * Include only not-external-dependant headers
 */
#include "../core/Util.h"
#include "../core/Text.h"

#endif