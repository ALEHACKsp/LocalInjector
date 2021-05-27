#pragma once

#ifndef Includes_hh
#define Includes_hh

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <TlHelp32.h>
#include <FileSystem>
#include <IoStream>
#include <Stdio.h>
#include <Cstdio>
#include <Thread>
#include <Random>

#include "Utilities/Singleton.hh"
#include "Utilities/LazyImporter.hh"
#include "Utilities/XorStr.hh"

#include "Utilities/Utilities.hh"

using namespace std::chrono_literals;

#endif // !Includes_hh