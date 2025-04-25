#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using bitset = unsigned long long;

struct TransitionSystem {
	int num_states = 0;      // number of states
	int num_transitions = 0; // number of transitions
	int num_actions = 0;

	using state_set = unsigned long long;
	using ap_set = unsigned long long;
	using state = int;
	using action = int;

	bitset init_states;                                       // initial states
	std::vector<std::string> AP;                              // atomic propositions
	std::map<state, std::map<action, state_set>> transitions; // transitions
	std::map<state, ap_set> labels;                           // labels

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
			ap_set ap = 0;
			while (line >> x) ap |= (1 << x);
			labels[i] = ap;
		}
	}
};
