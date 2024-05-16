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

#ifndef __MML_HPP__
#define __MML_HPP__


#include <definitions.hpp>
#include <file.hpp>
#include <functions.hpp>
#include <help.hpp>
#include <log.hpp>
#include <shell.hpp>
#include <standards.hpp>
#include <Thread.hpp>
#include <Timer.hpp>
#include <Unix.hpp>
#include <vector.hpp>

#endif
