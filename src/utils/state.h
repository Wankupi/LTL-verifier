#pragma once
#include <vector>

struct States : std::vector<int> {
	constexpr States(unsigned long long states) {
		for (int i = 0; i < 64; ++i) {
			if ((states >> i) & 1)
				this->emplace_back(i);
		}
	}
};