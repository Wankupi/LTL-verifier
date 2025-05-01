#include "LTL/LTL.h"
#include "NBA.h"
#include "utils/type.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <queue>
#include <set>
#include <stdexcept>
#include <unistd.h>
#include <utility>
#include <vector>

using namespace LTL;

std::vector<LTL::BaseNode *> get_closure(LTL::BaseNode *root) {
	std::queue<LTL::BaseNode *> q;
	std::set<LTL::BaseNode *> closure;
	q.push(root);

	while (!q.empty()) {
		auto node = q.front();
		q.pop();

		node = node->remove_not();

		// do not add literal true or false to the closure
		if (node->as<LiteralTrue>())
			continue;

		if (closure.find(node) != closure.end()) continue;
		closure.insert(node);

		if (auto unary_node = dynamic_cast<LTL::UnaryNode *>(node))
			q.push(unary_node->child);
		else if (auto binary_node = dynamic_cast<LTL::BinaryNode *>(node)) {
			q.push(binary_node->left);
			q.push(binary_node->right);
		}
	}
	return std::vector<LTL::BaseNode *>(closure.begin(), closure.end());
}


// This class is used to test whether a set of LTL formulas is consistent.
// That's to check whether a set of formulas could be a state of GNBA.
// Formulas should be passed to the function validate one by one and ORDERED by of height
struct Validator {
	std::map<LTL::BaseNode *, bool> value;

	bool resolve(LTL::BaseNode *node, bool expected) const {
		if (node->as<AtomNode>())
			return expected;
		else if (node->as<LiteralTrue>())
			return true;
		else if (auto binary_node = node->as<BinaryNode>()) {
			if (node->as<UntilNode>())
				// local: a until b = b or (a and next(a until b))
				// because the value of next is just as expected
				// so the value is b or (a and expected)
				return (expected && get(binary_node->left)) || get(binary_node->right);
			else if (node->as<ImplicationNode>())
				return !get(binary_node->left) || get(binary_node->right);
			else if (node->as<AndNode>())
				return get(binary_node->left) && get(binary_node->right);
			else if (node->as<OrNode>())
				return get(binary_node->left) || get(binary_node->right);
		}
		else if (auto unary_node = node->as<UnaryNode>()) {
			if (node->as<NotNode>())
				return !get(unary_node->child);
			else if (node->as<AlwaysNode>())
				return get(unary_node->child) && expected;
			else if (node->as<EventuallyNode>())
				return expected || get(unary_node->child);
			else if (node->as<NextNode>())
				return expected;
		}
		std::unreachable();
	}

	bool validate(LTL::BaseNode *node, bool expected) {
		if (auto p = value.find(node); p != value.end())
			return p->second;
		return (value[node] = resolve(node, expected)) == expected;
	}
	bool get(LTL::BaseNode *node) const {
		bool negate = false;
		if (auto not_node = node->as<NotNode>())
			node = not_node->child, negate = true;
		if (node->is_bool()) // node is already a "true"
			return !negate;
		auto p = value.find(node);
		if (p == value.end()) {
			std::cerr << "Validator: Can not find node in current value set: ";
			std::cerr << *node << std::endl;
			throw std::runtime_error("Validator: cannot find node in value");
		}
		// std::cout << std::format("Validator: get {} = {}  p->second={} negate={}\n", *node, p->second ^ negate, p->second, negate);
		return p->second ^ negate;
	}
};

using ElementSet = unsigned long long;
std::vector<ElementSet> get_all_element_set(std::vector<BaseNode *> const &closure) {
	std::vector<ElementSet> result;
	int n = closure.size();
	for (int B = 0; B < (1 << n); ++B) {
		// std::cout << std::format("B = {:0{}b}\n", B, n);
		Validator validator;
		bool pass = false;
		for (int i = 0; i < n; ++i)
			if (!validator.validate(closure[i], (B >> i) & 1)) {
				pass = true;
				break;
			}
		if (pass) continue;
		result.emplace_back(B);
	}
	return result;
}

bool is_formula_in_element_set(std::vector<BaseNode *> const &closure, ElementSet B, BaseNode *formula) {
	auto pure_node = formula->remove_not();
	if (pure_node->as<LiteralTrue>()) return !formula->is_not();
	size_t index = std::find(closure.begin(), closure.end(), pure_node) - closure.begin();
	assert(index < closure.size());
	return ((B >> index) & 1) == !formula->is_not();
};

struct Mask {
	ElementSet must_set;
	ElementSet value;
	Mask not_() const {
		return {must_set, (~value) & must_set};
	}
};
Mask operator&(Mask const &lhs, Mask const &rhs) {
	return {lhs.must_set & rhs.must_set, lhs.value & rhs.value};
}

Mask get_masked_set(std::vector<BaseNode *> const &closure, BaseNode *node, bool positive, ElementSet B) {
	auto formula2mask = [&closure](BaseNode *node) -> Mask {
		if (auto not_node = node->as<NotNode>())
			node = not_node->child;
		for (size_t i = 0; i < closure.size(); ++i)
			if (closure[i] == node)
				return {1ull << i, ElementSet(closure[i] == node) << i};
		throw std::runtime_error("get_masked_set: cannot find node in closure");
	};
	auto is_in_B = [&closure, &B](BaseNode *node) -> bool { return is_formula_in_element_set(closure, B, node); };
	if (auto always_node = node->as<AlwaysNode>(); always_node) {
		if (positive)
			// always(a): a and next (always(a))
			return formula2mask(always_node);
		else
			// not always(a): not a or not next(always(a))
			// if a in B, then not always(a) in B'
			return is_in_B(always_node->child) ? formula2mask(always_node).not_() : Mask{0, 0};
	}
	else if (auto eventually_node = node->as<EventuallyNode>()) {
		if (positive)
			// eventually(a): a or next(eventually(a))
			return is_in_B(eventually_node->child) ? Mask{0, 0} : formula2mask(eventually_node);
		else
			// not eventually(a): not a and not next(eventually(a))
			return formula2mask(eventually_node).not_();
	}
	else if (auto next_node = node->as<NextNode>(); next_node) {
		// if "not next(a)" in B, then "not a" in B'
		if (positive)
			return formula2mask(next_node->child);
		else
			return formula2mask(next_node->child).not_();
	}
	else if (auto until_node = node->as<UntilNode>(); until_node) {
		if (positive)
			// For positive case,
			// a until b = b or (a and next(a until b))
			return is_in_B(until_node->right) ? Mask{0, 0} : formula2mask(until_node);
		else
			// For negative case,
			// not (a until b) = not b and (not a or (not a until b) next time)
			return is_in_B(until_node->left) ? formula2mask(until_node).not_() : Mask{0, 0};
	}
	return {0, 0};
}

/// @brief get the must set bits
/// @returns {must_set, value}
/// @details forall B', B -> B', must_set & B' = value
Mask get_masked_set(std::vector<BaseNode *> const &closure, ElementSet B) {
	ElementSet must_set = 0, value = 0;
	int n = closure.size();
	for (int i = 0; i < n; ++i) {
		int positive = (B >> i) & 1;
		auto [must_set_i, value_i] = get_masked_set(closure, closure[i], positive, B);
		must_set |= must_set_i;
		value |= value_i;
		assert((value_i & ~must_set_i) == 0);
	}
	return {must_set, value};
}

AtomicPropositionSet get_AP_set(std::vector<LTL::BaseNode *> const &closure, ElementSet B) {
	AtomicPropositionSet result{};
	for (size_t i = 0; i < closure.size(); ++i)
		if (auto atom_node = closure[i]->as<AtomNode>(); atom_node && ((B >> i) & 1))
			result |= AtomicPropositionSet(1) << atom_node->id;
	return result;
}

/// @attention from this function, we should take care of the LiteralBooleanNode
GNBA::StateSet generate_final_states(
		LTL::LTLAllocator &ltl_allocator,
		std::vector<LTL::BaseNode *> const &closure,
		std::vector<ElementSet> const &element_sets,
		LTL::BaseNode *formula) {
	// only return non-zero when is { Always, Eventually, Until }
	// unify them to a until b
	// a is useless
	BaseNode *b = nullptr;
	if (formula->as<AlwaysNode>()) {
		// always a = a until false
		// a = always_node->child;
		b = ltl_allocator.createLiteralBooleanNode(false);
	}
	else if (auto eventually_node = formula->as<EventuallyNode>()) {
		// eventually a = true until a
		// a = ltl_allocator.createLiteralBooleanNode(true);
		b = eventually_node->child;
	}
	else if (auto until_node = formula->as<UntilNode>()) {
		// a = until_node->left;
		b = until_node->right;
	}
	else
		return 0;
	// a until b
	GNBA::StateSet result = 0;
	for (size_t i = 0; i < element_sets.size(); ++i) {
		// std::cout << std::format("")
		if (!is_formula_in_element_set(closure, element_sets[i], formula) // (a until b) not in B
			|| is_formula_in_element_set(closure, element_sets[i], b))    // b in B
			result |= (1ull << i);
	}
	return result;
}

GNBA::GNBA(
		LTL::LTLAllocator &allocator,
		LTL::BaseNode *ltl_formula,
		int num_AP) : Automaton() {
	this->num_AP = num_AP;

	auto closure = get_closure(ltl_formula);

	std::sort(closure.begin(), closure.end(), [](LTL::BaseNode *lhs, LTL::BaseNode *rhs) {
		return *lhs < *rhs;
	});

	// debug
	for (auto expr: closure)
		std::cout << expr << ", ";
	std::cout << std::endl;
	// debug end

	auto element_sets = get_all_element_set(closure);

	// debug
	auto output_binary = [n = closure.size()](ElementSet B) {
		for (int i = n - 1; i >= 0; --i)
			std::cout << ((B >> i) & 1);
	};
	std::cout << "get primary set: ";
	for (auto B: element_sets) {
		output_binary(B);
		std::cout << " ";
	}
	std::cout << std::endl;
	// debug end

	this->num_states = element_sets.size();
	this->transitions.resize(this->num_states);
	for (int i = 0; i < this->num_states; ++i) {
		auto [must_set, value] = get_masked_set(closure, element_sets[i]);
		StateSet out_edges = 0;
		for (int j = 0; j < this->num_states; ++j) {
			if (value != (element_sets[j] & must_set))
				continue;
			out_edges |= (1ull << j);
		}
		auto ap_set = get_AP_set(closure, element_sets[i]);
		transitions[i][ap_set] = out_edges;
	}

	// debug
	for (int i = 0; i < this->num_states; ++i) {
		for (auto [ap_set, out_edges]: transitions[i]) {
			std::cout << std::format("{:0{}b} - {:0{}b} -> {:0{}b}", element_sets[i], closure.size(), ap_set, num_AP, out_edges, element_sets.size()) << std::endl;
			assert(
					element_sets[i] >> closure.size() == 0 &&
					ap_set >> num_AP == 0 &&
					out_edges >> element_sets.size() == 0);
		}
	}
	// debug end

	// set initial states
	unsigned formula_index = std::find(closure.begin(), closure.end(), ltl_formula->remove_not()) - closure.begin();
	assert(formula_index < closure.size());
	bool formula_positive = !ltl_formula->is_not();
	for (int i = 0; i < this->num_states; ++i)
		if (((element_sets[i] >> formula_index) & 1) == formula_positive)
			this->init_states |= (1ull << i);

	// debug
	std::cout << std::format("init_states: {:0{}b}\n", this->init_states, this->num_states);
	// debug end

	// set used_ap
	for (auto const &trans: transitions)
		for (auto const &[ap, _]: trans)
			this->used_ap |= ap;

	// debug
	std::cout << std::format("used_ap: {:0{}b}\n", this->used_ap, num_AP);
	// debug end

	// set final states
	for (auto node: closure) {
		auto fs = generate_final_states(allocator, closure, element_sets, node);
		if (fs)
			this->final_states_list.emplace_back(fs);
	}


	// debug
	std::cout << "final states list: ";
	for (auto fs: final_states_list)
		std::cout << std::format("{:0{}b} ", fs, this->num_states);
	std::cout << std::endl;
	// debug end
}

void GNBA::remove_unreachable() {
	// remove unreachable states
	StateSet reachable = this->init_states;
	std::queue<int> q;
	for (int i = 0; i < this->num_states; ++i)
		if ((this->init_states >> i) & 1)
			q.push(i);
	while (!q.empty()) {
		auto state = q.front();
		q.pop();
		for (auto [_, out_edges]: this->transitions[state])
			for (int i = 0; i < this->num_states; ++i)
				if (((out_edges >> i) & 1) && ((reachable >> i) & 1) == 0) {
					q.push(i);
					reachable |= (1ull << i);
				}
	}

	std::vector<int> new_states_map(this->num_states, -1);
	int lastStateCnt = this->num_states;
	this->num_states = 0;
	for (int i = 0; i < lastStateCnt; ++i)
		if ((reachable >> i) & 1)
			new_states_map[i] = this->num_states++;

	auto old_state_set_to_new_state_set = [&](StateSet old_state_set) {
		StateSet new_state_set = 0;
		for (int i = 0; i < lastStateCnt; ++i)
			if (((old_state_set >> i) & 1) && ((reachable >> i) & 1))
				new_state_set |= (1ull << new_states_map[i]);
		return new_state_set;
	};

	// modify transitions
	decltype(this->transitions) new_transitions(this->num_states);
	for (int i = 0; i < lastStateCnt; ++i) {
		if (!((reachable >> i) & 1))
			continue;
		for (auto [ap_set, out_edges]: this->transitions[i]) {
			auto new_out_edges = old_state_set_to_new_state_set(out_edges);
			if (new_out_edges == 0)
				continue;
			new_transitions[new_states_map[i]][ap_set] = new_out_edges;
		}
	}
	std::swap(new_transitions, this->transitions);

	// modify init_states
	this->init_states = old_state_set_to_new_state_set(this->init_states);

	// modify final_states_list
	decltype(this->final_states_list) new_final_states_list;
	for (auto &fs: this->final_states_list) {
		fs = old_state_set_to_new_state_set(fs);
		if (fs != 0)
			new_final_states_list.emplace_back(fs);
	}
}


void GNBA::transform_to_NBA() {
	if (this->final_states_list.size() <= 1)
		return;

	int k = this->final_states_list.size();

	int lastStateCnt = this->num_states;
	this->num_states *= k;

	auto id = [&](int state, int j) {
		return state + j * lastStateCnt;
	};
	auto new_state_set = [&](StateSet states, int j) {
		StateSet new_state_set = 0;
		for (int i = 0; i < lastStateCnt; ++i)
			if ((states >> i) & 1)
				new_state_set |= (1ull << id(i, j));
		return new_state_set;
	};
	// modify transitions
	decltype(this->transitions) new_transitions(this->num_states);
	for (int j = 0; j < k; ++j) {
		for (int i = 0; i < lastStateCnt; ++i) {
			int to = (j + ((this->final_states_list[j] >> i) & 1)) % k;
			new_transitions[id(i, j)] = transitions[i];
			for (auto &[ap_set, out_edges]: new_transitions[id(i, j)])
				out_edges = new_state_set(out_edges, to);
		}
	}
	this->transitions = std::move(new_transitions);
	// modify init_states
	this->init_states = new_state_set(this->init_states, 0);
	// modify final_states_list
	final_states_list.resize(1);
	final_states_list[0] = new_state_set(final_states_list[0], 0);
}