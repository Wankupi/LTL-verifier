#include "LTL/LTL.h"
#include "NBA/NBA.h"
#include "TransitionSystem.h"
#include "utils/color.h"
#include <cassert>
#include <curses.h>
#include <fstream>
#include <iostream>
#include <string>

TransitionSystem read_ts() {
	std::ifstream ts_file("TS.txt");
	assert(bool(ts_file));
	return TransitionSystem(ts_file);
}

int main() {
	TransitionSystem TS = read_ts();

	std::cout << "start" << std::endl;
	std::ifstream ltl_file("benchmark.txt");
	if (!ltl_file) {
		std::cerr << "Error opening file benchmark.txt" << std::endl;
		return 1;
	}
	int A = 0, B = 0;
	ltl_file >> A >> B;
	while (ltl_file.get() != '\n'); // skip

	LTL::LTLAllocator allocator{TS};

	for (int i = 0; i < A; ++i) {
		std::string str;
		std::getline(ltl_file, str);
		auto root = LTL::LTL_parse(str, allocator);
		std::cout << DBG_GREEN << "LTL: " << root << DBG_RESET << std::endl;
		NBA::GNBA gnba(allocator, root, TS.AP.size());
		gnba.remove_unreachable();
	}
	for (int i = 0; i < B; ++i) {
		int state = 0;
		ltl_file >> state;
		std::string str;
		std::getline(ltl_file, str);
		auto root = LTL::LTL_parse(str, allocator);
		std::cout << DBG_GREEN << "LTL: " << root << DBG_RESET << std::endl;
		NBA::GNBA gnba(allocator, root, TS.AP.size());
		gnba.remove_unreachable();
	}
	return 0;
}