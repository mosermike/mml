/**
 * @file mml.hpp
 * @author Mike Moser
 * @brief Imports all functions from the this library
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#if __GNUC__
#if __x86_64__ || __ppc64__
#define __ENVIRONMENT64__
#else
#define __ENVIRONMENT32__
#endif
#endif

#ifndef MML_INCLUDE_MML_HPP
#define MML_INCLUDE_MML_HPP


#include "mml/definitions.hpp"
#include "mml/file.hpp"
#include "mml/help.hpp"
#include "mml/log.hpp"
#include "mml/shell.hpp"
#include "mml/standards.hpp"
#include "mml/string.hpp"
#include "mml/thread.hpp"
#include "mml/time.hpp"
#include "mml/Unix.hpp"
#include "mml/vector.hpp"

#endif
