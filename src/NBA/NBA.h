#pragma once
#include "LTL/LTL.h"
#include "utils/type.h"
#include <unordered_map>
#include <vector>

namespace NBA {


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

	GNBA(LTL::BaseNode *root, int num_AP);
};

struct NBA : Automaton {
	StateSet final_states = 0; // final states

	NBA(GNBA const &gnba);
};


} // namespace NBA