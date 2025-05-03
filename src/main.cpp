#include "FindLoop.h"
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
	std::ifstream ltl_file("benchmark.txt");
	if (!ltl_file) {
		std::cerr << "Error opening file benchmark.txt" << std::endl;
		return 1;
	}
	int A = 0, B = 0;
	ltl_file >> A >> B;
	while (ltl_file.get() != '\n'); // skip

	LTL::LTLAllocator allocator{TS};

	auto verify = [&](int start_state) -> bool {
		std::string str;
		std::getline(ltl_file, str);
		auto root = LTL::LTL_parse(str, allocator);
		root = allocator.create<LTL::NotNode>(root);
		GNBA gnba(allocator, root, TS.AP.size());
		gnba.transform_to_NBA();
		auto result = !find_loop(TS, gnba, start_state);
		return result;
	};

	std::ofstream out("result.txt");
	for (int i = 0; i < A; ++i) {
		out << verify(-1) << '\n';
	}
	for (int i = 0; i < B; ++i) {
		int state = 0;
		ltl_file >> state;
		out << verify(state) << '\n';
	}
	return 0;
}