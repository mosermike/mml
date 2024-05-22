/**
 * @author Mike Moser
 * 
 * @name mml.hpp
 * Enthält verschiedene Headerdateien
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
#include "mml/functions.hpp"
#include "mml/help.hpp"
#include "mml/log.hpp"
#include "mml/shell.hpp"
#include "mml/standards.hpp"
#include "mml/Thread.hpp"
#include "mml/Timer.hpp"
#include "mml/Unix.hpp"
#include "mml/vector.hpp"

#endif
