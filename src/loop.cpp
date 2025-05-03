#include "FindLoop.h"
#include "utils/state.h"
#include <set>

struct LoopFinder {
	TransitionSystem const &ts;
	GNBA const &gnba;

	LoopFinder(TransitionSystem const &ts, GNBA const &gnba) : ts(ts), gnba(gnba) {
		assert(gnba.final_states_list.size() <= 1);
	}

	std::vector<std::pair<int, int>> stack;
	std::map<std::pair<int, int>, int> record_num_final_states;
	std::set<std::pair<int, int>> visited;
	int num_final_states_in_stack = 0;

	bool has_find = false;

	struct StackDaemon {
		int s;
		int q;
		LoopFinder &lf;
		StackDaemon(int s, int q, LoopFinder &lf) : s(s), q(q), lf(lf) {
			lf.stack.emplace_back(s, q);
			lf.record_num_final_states[{s, q}] = lf.num_final_states_in_stack;
			lf.num_final_states_in_stack += lf.gnba.is_final_state(q);
		}
		~StackDaemon() {
			lf.num_final_states_in_stack -= lf.gnba.is_final_state(q);
			lf.stack.pop_back();
		}
	};

	bool dfs(int s, int q) {
		if (std::find(stack.begin(), stack.end(), std::pair<int, int>{s, q}) != stack.end()) {
			return has_find = (record_num_final_states[{s, q}] < num_final_states_in_stack);
		}

		if (visited.count({s, q}))
			return false;
		visited.insert({s, q});

		StackDaemon sd(s, q, *this);

		auto trans = ts.transitions.find(s);

		if (trans == ts.transitions.end())
			return false;

		for (auto const &[action, next_states]: trans->second) {
			for (auto t: States(next_states)) {
				auto t_label = ts.labels.at(t);
				for (auto p: States(gnba.get_next_states(q, t_label)))
					if (dfs(t, p))
						return true;
			}
		}
		return false;
	}

	bool find_loop(int start_state) {
		if (start_state < 0) {
			for (int i = 0; i < ts.num_states; ++i)
				if ((ts.init_states >> i) & 1)
					if (find_loop(i))
						return true;
			return false;
		}
		GNBA::StateSet nba_init_states = 0;
		for (auto i: States(gnba.init_states))
			nba_init_states |= gnba.get_next_states(i, ts.labels[start_state]);
		for (auto q: States(nba_init_states)) {
			if (dfs(start_state, q))
				return true;
		}
		return false;
	}
};

bool find_loop(TransitionSystem &ts, GNBA &gnba, int start_state) {
	LoopFinder finder(ts, gnba);
	return finder.find_loop(start_state);
}
