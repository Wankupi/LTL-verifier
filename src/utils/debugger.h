#pragma once
#include <syncstream>
#ifdef DEBUG
#include <iostream>
#endif

inline std::osyncstream debugger() {
#ifdef DEBUG
	return std::osyncstream{std::cerr};
#else
	return std::osyncstream{nullptr};
#endif
}