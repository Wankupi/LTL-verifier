
// Generated from antlr/LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LTLVisitor.h"


/**
 * This class provides an empty implementation of LTLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  LTLBaseVisitor : public LTLVisitor {
public:

  virtual std::any visitProgram(LTLParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNot(LTLParser::NotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesis(LTLParser::ParenthesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDisjunction(LTLParser::DisjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNext(LTLParser::NextContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventually(LTLParser::EventuallyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConjunction(LTLParser::ConjunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrue(LTLParser::TrueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlways(LTLParser::AlwaysContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalse(LTLParser::FalseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplication(LTLParser::ImplicationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtom(LTLParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUntil(LTLParser::UntilContext *ctx) override {
    return visitChildren(ctx);
  }


};

