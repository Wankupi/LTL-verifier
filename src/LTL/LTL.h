#pragma once
#include <format>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <typeindex>
#include <unordered_map>

namespace LTL {

struct BaseNode {
	virtual ~BaseNode() = default;
	virtual std::string stringify() const {
		return {};
	}
};

// using NodePtr = std::unique_ptr<BaseNode>;
using NodePtr = BaseNode *;

struct UnaryNode : public BaseNode {
	NodePtr child;
	UnaryNode(NodePtr child) : child(std::move(child)) {}
};

struct BinaryNode : public BaseNode {
	NodePtr left;
	NodePtr right;
	BinaryNode(NodePtr left, NodePtr right) : left(std::move(left)), right(std::move(right)) {}
};

struct AtomNode : public BaseNode {
	std::string name;
	AtomNode(std::string name) : name(std::move(name)) {}
	std::string stringify() const override {
		return name;
	}
};

struct LiteralBooleanNode : public BaseNode {
	bool value;
	LiteralBooleanNode(bool value) : value(value) {}
	std::string stringify() const override {
		return value ? "True" : "False";
	}
};

struct NotNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("Not({})", child->stringify());
	}
};

struct AlwaysNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("Always({})", child->stringify());
	}
};

struct EventuallyNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("Eventually({})", child->stringify());
	}
};

struct NextNode : public UnaryNode {
	using UnaryNode::UnaryNode;
	std::string stringify() const override {
		return std::format("Next({})", child->stringify());
	}
};

struct UntilNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) Until ({})", left->stringify(), right->stringify());
	}
};

struct ImplicationNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) Implication ({})", left->stringify(), right->stringify());
	}
};

struct AndNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) And ({})", left->stringify(), right->stringify());
	}
};

struct OrNode : public BinaryNode {
	using BinaryNode::BinaryNode;
	std::string stringify() const override {
		return std::format("({}) Or ({})", left->stringify(), right->stringify());
	}
};


class LTLAllocator {
	std::unordered_map<std::string, std::unique_ptr<AtomNode>> atom_nodes;
	std::unique_ptr<LiteralBooleanNode> bool_nodes[2];
	std::map<std::tuple<std::type_index, BaseNode *>, std::unique_ptr<UnaryNode>> unary_nodes;
	std::map<std::tuple<std::type_index, BaseNode *, BaseNode *>, std::unique_ptr<BinaryNode>> binary_nodes;

public:
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
		auto it = atom_nodes.find(name);
		if (it != atom_nodes.end())
			return it->second.get();
		auto node = std::make_unique<AtomNode>(name);
		auto ptr = node.get();
		atom_nodes[name] = std::move(node);
		return ptr;
	}
	BaseNode *createLiteralBooleanNode(bool value) {
		auto index = value ? 1 : 0;
		if (bool_nodes[index])
			return bool_nodes[index].get();
		auto node = std::make_unique<LiteralBooleanNode>(value);
		auto ptr = node.get();
		bool_nodes[index] = std::move(node);
		return ptr;
	}
};

NodePtr LTL_parse(const std::string &formula, LTLAllocator &allocator);

} // namespace LTL
