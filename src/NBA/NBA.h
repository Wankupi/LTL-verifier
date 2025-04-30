#pragma once
#include "LTL/LTL.h"
#include "utils/type.h"
#include <unordered_map>
#include <vector>

struct Automaton {
	int num_states = 0;
	int num_AP = 0;

	using StateSet = unsigned long long;
	std::vector<std::unordered_map<AtomicPropositionSet, StateSet>> transitions; // transitions

	StateSet init_states = 0;         // initial states
	AtomicPropositionSet used_ap = 0; // used atomic propositions
};

struct GNBA : Automaton {
	std::vector<StateSet> final_states_list;

	GNBA(LTL::LTLAllocator &allocator, LTL::BaseNode *formula, int num_AP);

	void remove_unreachable();
	void transform_to_NBA();
};

template<>
class std::formatter<GNBA> {
public:
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) {
		return ctx.begin();
	}

	template<typename FormatContext>
	auto format(GNBA const &gnba, FormatContext &ctx) const {
		auto it = ctx.out();
		std::format_to(it, R"!(GNBA(num_states={})
  init_states={:0{}b}
  final_states=)!",
					   gnba.num_states, gnba.init_states, gnba.num_states);

		for (auto const &fs: gnba.final_states_list)
			std::format_to(it, "{:0{}b} ", fs, gnba.num_states);
		std::format_to(it, "\n  transitions:\n");
		for (int i = 0; i < gnba.num_states; ++i) {
			for (auto const &[ap, out_edges]: gnba.transitions[i]) {
				std::format_to(it, "    {} - {:0{}b} -> {{", i, ap, gnba.num_AP);
				for (int j = 0; j < gnba.num_states; ++j)
					if ((out_edges >> j) & 1)
						std::format_to(it, "{},", j);
				std::format_to(it, "}}\n");
			}
		}
		return it;
	}
};