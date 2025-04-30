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

		// do not add literal true or false to the closure
		if (node->as<LiteralBooleanNode>())
			continue;

		node = remove_not(node);
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
		else if (auto literal = node->as<LiteralBooleanNode>())
			return literal->value;
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
	size_t index = std::find(closure.begin(), closure.end(), remove_not(formula)) - closure.begin();
	assert(index < closure.size());
	return ((B >> index) & 1) == !is_not(formula);
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
NBA::GNBA::StateSet generate_final_states(
		std::vector<LTL::BaseNode *> const &closure,
		std::vector<ElementSet> const &element_sets,
		LTL::BaseNode *formula) {
	// only return non-zero when is { Always, Eventually, Until }
	BaseNode *left = nullptr, *right = nullptr;
	LiteralBooleanNode true_(true), false_(false);
	if (auto always_node = formula->as<AlwaysNode>()) {
		// always a = a until false
		left = always_node->child;
		right = &false_;
	}
	else if (auto eventually_node = formula->as<EventuallyNode>()) {
		// eventually a = true until a
		left = &true_;
		right = eventually_node->child;
	}
	else if (auto until_node = formula->as<UntilNode>()) {
		left = until_node->left;
		right = until_node->right;
	}
	else
		return 0;
	// TODO:
}

NBA::GNBA::GNBA(LTL::BaseNode *ltl_formula, int num_AP) : Automaton() {
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
	unsigned formula_index = std::find(closure.begin(), closure.end(), remove_not(ltl_formula)) - closure.begin();
	assert(formula_index < closure.size());
	bool formula_positive = !is_not(ltl_formula);
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
}