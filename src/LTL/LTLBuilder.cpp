#include "LTL.h"
#include "LTLLexer.h"
#include "LTLParser.h"
#include "LTLVisitor.h"
#include <cassert>
#include <string>

using namespace LTL;

class LTLBuilder : public LTLVisitor {
	LTLAllocator &allocator;

public:
	LTLBuilder(LTLAllocator &allocator) : allocator(allocator) {}

	template<typename T>
	NodePtr visit(T *ctx) {
		auto val = LTLVisitor::visit(ctx);
		auto ptr = std::any_cast<NodePtr>(&val);
		if (!ptr) {
			std::cerr << "Error: visit() failed to return NodePtr" << std::endl;
			std::cerr << "ctx: " << ctx->getText() << std::endl;
			assert(false);
		}
		return *ptr;
	}

	std::any visitProgram(LTLParser::ProgramContext *ctx) override {
		return visit(ctx->formula());
	}

	std::any visitNot(LTLParser::NotContext *ctx) override {
		return allocator.create<NotNode>(visit(ctx->child));
	}
	std::any visitParenthesis(LTLParser::ParenthesisContext *ctx) override {
		return visit(ctx->child);
	}
	std::any visitDisjunction(LTLParser::DisjunctionContext *ctx) override {
		return allocator.create<OrNode>(visit(ctx->lhs), visit(ctx->rhs));
	}
	std::any visitNext(LTLParser::NextContext *ctx) override {
		return allocator.create<NextNode>(visit(ctx->child));
	}
	std::any visitEventually(LTLParser::EventuallyContext *ctx) override {
		return allocator.create<EventuallyNode>(visit(ctx->child));
	}
	std::any visitConjunction(LTLParser::ConjunctionContext *ctx) override {
		return allocator.create<AndNode>(visit(ctx->lhs), visit(ctx->rhs));
	}
	std::any visitTrue(LTLParser::TrueContext *ctx) override {
		return allocator.createLiteralBooleanNode(true);
	}
	std::any visitAlways(LTLParser::AlwaysContext *ctx) override {
		return allocator.create<AlwaysNode>(visit(ctx->child));
	}
	std::any visitFalse(LTLParser::FalseContext *ctx) override {
		return allocator.createLiteralBooleanNode(false);
	}
	std::any visitImplication(LTLParser::ImplicationContext *ctx) override {
		return allocator.create<ImplicationNode>(visit(ctx->lhs), visit(ctx->rhs));
	}
	std::any visitAtom(LTLParser::AtomContext *ctx) override {
		return allocator.createAtomNode(ctx->getText());
	}
	std::any visitUntil(LTLParser::UntilContext *ctx) override {
		return allocator.create<UntilNode>(visit(ctx->lhs), visit(ctx->rhs));
	}
};

NodePtr LTL::LTL_parse(const std::string &formula, LTLAllocator &allocator) {
	auto input = antlr4::ANTLRInputStream(formula);
	auto lexer = LTLLexer(&input);
	auto tokens = antlr4::CommonTokenStream(&lexer);
	auto parser = LTLParser(&tokens);
	auto tree = parser.program();

	auto visitor = LTLBuilder(allocator);
	auto result = visitor.visit(tree);
	return result;
}