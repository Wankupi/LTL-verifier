#pragma once
#include "utils/type.h"
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct TransitionSystem {
	int num_states = 0;      // number of states
	int num_transitions = 0; // number of transitions
	int num_actions = 0;

	using StateSet = unsigned long long;
	using State = int;
	using Action = int;

	StateSet init_states;                                    // initial states
	std::vector<std::string> AP;                             // atomic propositions
	std::map<State, std::map<Action, StateSet>> transitions; // transitions
	std::map<State, AtomicPropositionSet> labels;            // labels

	// Constructor
	TransitionSystem(std::istream &is) {
		auto linestream = [&is]() {
			std::string line;
			std::getline(is, line);
			return std::istringstream(std::move(line));
		};
		auto line = linestream(); // line 1
		line >> num_states >> num_transitions;
		line = linestream(); // line 2
		int x = 0;
		while (line >> x) init_states |= (1 << x);
		line = linestream(); // line 3
		while (line >> x) num_actions += 1;

		line = linestream();
		std::string str;
		while (line >> str)
			AP.emplace_back(std::move(str));

		for (int i = 0; i < num_transitions; ++i) {
			line = linestream();
			int from = 0, action = 0, to = 0;
			line >> from >> action >> to;
			transitions[from][action] |= (1 << to);
		}
		for (int i = 0; i < num_states; ++i) {
			line = linestream();
			AtomicPropositionSet ap = 0;
			while (line >> x) ap |= (1 << x);
			labels[i] = ap;
		}
	}
};
