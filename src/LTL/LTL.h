#pragma once
#include "TransitionSystem.h"
#include <cassert>
#include <compare>
#include <curses.h>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <typeindex>
#include <utility>

namespace LTL {

struct BaseNode {
	int height = 0;

public:
	BaseNode() = default;
	BaseNode(int height) : height(height) {}
	virtual ~BaseNode() = default;
	virtual std::string stringify() const = 0;
	template<typename T>
		requires std::is_base_of_v<BaseNode, T>
	T *as() {
		return dynamic_cast<T *>(this);
	}
	template<typename T>
		requires std::is_base_of_v<BaseNode, T>
	T const *as() const {
		return dynamic_cast<T const *>(this);
	}
	bool is_not() const;
	BaseNode const *remove_not() const;
	BaseNode *remove_not() {
		return const_cast<BaseNode *>(static_cast<BaseNode const *>(this)->remove_not());
	}
	bool is_bool() const;
};

inline std::ostream &operator<<(std::ostream &os, BaseNode const *node) {
	// os << std::format("{}({}){}", DBG_RED, (void const *) (node), DBG_RESET);
	return os << node->stringify();
}

inline std::ostream &operator<<(std::ostream &os, BaseNode const &node) {
	return os << &node;
}

// using NodePtr = std::unique_ptr<BaseNode>;
using NodePtr = BaseNode *;

struct UnaryNode : public BaseNode {
	NodePtr child;
	UnaryNode(NodePtr child) : BaseNode(child->height + 1), child(std::move(child)) {}
};

struct BinaryNode : public BaseNode {
	NodePtr left;
	NodePtr right;
	BinaryNode(NodePtr left, NodePtr right) : BaseNode(std::max(left->height, right->height) + 1), left(std::move(left)), right(std::move(right)) {}
};

struct AtomNode : public BaseNode {
	std::string name;
	int id = 0;
	AtomNode(std::string name, int id) : name(std::move(name)), id(id) {}
	std::string stringify() const override {
		return name;
	}
};

struct LiteralTrue : public BaseNode {
	LiteralTrue() = default;
	std::string stringify() const override {
		return "true";
	}
};

struct NotNode : public UnaryNode {
	NotNode(NodePtr child) : UnaryNode(child) {
		if (child->as<LiteralTrue>()) // one special case
			this->height = child->height;
	}
	std::string stringify() const override {
		if (child->as<LiteralTrue>())
			return "false"; // special case
		return std::format("not({})", child->stringify());
	}
};

struct AlwaysNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("always({})", child->stringify());
	}
};

struct EventuallyNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("eventually({})", child->stringify());
	}
};

struct NextNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("next({})", child->stringify());
	}
};

struct UntilNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) until ({})", left->stringify(), right->stringify());
	}
};

struct ImplicationNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) -> ({})", left->stringify(), right->stringify());
	}
};

struct AndNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) and ({})", left->stringify(), right->stringify());
	}
};

struct OrNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) or ({})", left->stringify(), right->stringify());
	}
};


class LTLAllocator {
	TransitionSystem const &ts;
	std::vector<std::unique_ptr<AtomNode>> atom_nodes;
	LiteralTrue true_node;
	std::map<std::tuple<std::type_index, BaseNode *>, std::unique_ptr<UnaryNode>> unary_nodes;
	std::map<std::tuple<std::type_index, BaseNode *, BaseNode *>, std::unique_ptr<BinaryNode>> binary_nodes;

public:
	LTLAllocator(TransitionSystem const &ts) : ts(ts), atom_nodes(ts.AP.size()) {}

	template<typename T>
	BaseNode *create(BaseNode *child) {
		auto it = unary_nodes.find({typeid(T), child});
		if (it != unary_nodes.end())
			return static_cast<T *>(it->second.get());
		auto node = std::make_unique<T>(child);
		auto ptr = node.get();
		unary_nodes[{typeid(T), child}] = std::move(node);
		return ptr;
	}
	template<typename T>
	BaseNode *create(BaseNode *lhs, BaseNode *rhs) {
		auto it = binary_nodes.find({typeid(T), lhs, rhs});
		if (it != binary_nodes.end())
			return static_cast<T *>(it->second.get());
		auto node = std::make_unique<T>(lhs, rhs);
		auto ptr = node.get();
		binary_nodes[{typeid(T), lhs, rhs}] = std::move(node);
		return ptr;
	}
	BaseNode *createAtomNode(std::string const &name) {
		unsigned long id = std::find(ts.AP.begin(), ts.AP.end(), name) - ts.AP.begin();
		assert(id < ts.AP.size());
		if (!atom_nodes[id])
			atom_nodes[id] = std::make_unique<AtomNode>(name, id);
		return atom_nodes[id].get();
	}
	BaseNode *createLiteralBooleanNode(bool value) {
		if (value)
			return &true_node;
		return create<NotNode>(&true_node);
	}
};

NodePtr LTL_parse(const std::string &formula, LTLAllocator &allocator);

inline BaseNode const *BaseNode::remove_not() const {
	if (auto not_node = this->as<NotNode>())
		return not_node->child;
	return this;
}

inline bool BaseNode::is_not() const {
	return this->as<NotNode>();
}

inline bool BaseNode::is_bool() const {
	return this->remove_not()->as<LiteralTrue>();
}

inline std::strong_ordering operator<=>(BaseNode const &lhs, BaseNode const &rhs) {
	if (lhs.height != rhs.height)
		return lhs.height <=> rhs.height;
	auto lhs_type = std::type_index(typeid(lhs));
	auto rhs_type = std::type_index(typeid(rhs));
	if (lhs_type != rhs_type)
		return lhs_type <=> rhs_type;
	if (auto lhs_atom = lhs.as<AtomNode>()) {
		auto rhs_atom = rhs.as<AtomNode>();
		return lhs_atom->id <=> rhs_atom->id;
	}
	else if (lhs.as<LiteralTrue>()) {
		return std::strong_ordering::equal;
		// auto rhs_literal = rhs.as<LiteralTrue>();
		// return lhs_literal->value <=> rhs_literal->value;
	}
	else if (auto lhs_unary = lhs.as<UnaryNode>()) {
		auto rhs_unary = rhs.as<UnaryNode>();
		return *(lhs_unary->child) <=> *(rhs_unary->child);
	}
	else if (auto lhs_binary = lhs.as<BinaryNode>()) {
		auto rhs_binary = rhs.as<BinaryNode>();
		auto cmp = *(lhs_binary->left) <=> *(rhs_binary->left);
		if (cmp != std::strong_ordering::equal)
			return cmp;
		return *(lhs_binary->right) <=> *(rhs_binary->right);
	}
	std::unreachable();
}

} // namespace LTL

template<>
struct std::formatter<LTL::BaseNode> : public std::formatter<std::string> {
	formatter() = default;
	auto format(LTL::BaseNode const &node, std::format_context &ctx) const {
		return this->std::formatter<std::string>::format(node.stringify(), ctx);
	}
};
