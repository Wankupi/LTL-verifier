#pragma once
#include "utils/state.h"
#include "utils/type.h"
#include <format>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct TransitionSystem {
	int num_states = 0; // number of states
	int num_actions = 0;

	using StateSet = unsigned long long;
	using State = int;
	using Action = int;

	StateSet init_states = 0;                                // initial states
	std::vector<std::string> AP;                             // atomic propositions
	std::map<State, std::map<Action, StateSet>> transitions; // transitions
	std::vector<AtomicPropositionSet> labels;                // labels

	// Constructor
	TransitionSystem(std::istream &is) {
		auto linestream = [&is]() {
			std::string line;
			std::getline(is, line);
			return std::istringstream(std::move(line));
		};
		auto line = linestream(); // line 1
		int num_transitions = 0;
		line >> num_states >> num_transitions;
		line = linestream(); // line 2
		int x = 0;
		while (line >> x) init_states |= (1 << x);
		line = linestream(); // line 3
		while (line >> x) num_actions += 1;

		line = linestream(); // line 4
		std::string str;
		while (line >> str)
			AP.emplace_back(std::move(str));

		for (int i = 0; i < num_transitions; ++i) {
			line = linestream();
			int from = 0, action = 0, to = 0;
			line >> from >> action >> to;
			transitions[from][action] |= (1 << to);
		}
		labels.resize(num_states);
		for (int i = 0; i < num_states; ++i) {
			line = linestream();
			AtomicPropositionSet ap = 0;
			while (line >> x) ap |= (1 << x);
			labels[i] = ap;
		}
	}
};


template<>
struct std::formatter<TransitionSystem> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) {
		return ctx.begin();
	}

	template<typename FormatContext>
	auto format(const TransitionSystem &ts, FormatContext &ctx) const {
		auto it = ctx.out();
		std::format_to(it, "TransitionSystem: {} states, {} actions, {} AtomicPropositions\n", ts.num_states, ts.num_actions, ts.AP.size());
		std::format_to(it, " AP: ");
		for (const auto &ap: ts.AP)
			std::format_to(it, "{} ", ap);
		std::format_to(it, "\n labels: ");
		for (const auto &label: ts.labels)
			std::format_to(it, "{:0{}b} ", label, ts.AP.size());
		std::format_to(it, "\n init_states: ");
		for (auto s: States(ts.init_states))
			std::format_to(it, "{} ", s);

		std::format_to(it, "\n transitions:\n");
		for (const auto &[from, actions]: ts.transitions) {
			for (const auto &[action, to]: actions) {
				for (auto s: States(to))
					std::format_to(it, "  {} - {} -> {}\n", from, action, s);
			}
		}
		return it;
	}
};
