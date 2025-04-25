
// Generated from antlr/LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "LTLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by LTLParser.
 */
class  LTLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by LTLParser.
   */
    virtual std::any visitProgram(LTLParser::ProgramContext *context) = 0;

    virtual std::any visitNot(LTLParser::NotContext *context) = 0;

    virtual std::any visitParenthesis(LTLParser::ParenthesisContext *context) = 0;

    virtual std::any visitDisjunction(LTLParser::DisjunctionContext *context) = 0;

    virtual std::any visitNext(LTLParser::NextContext *context) = 0;

    virtual std::any visitEventually(LTLParser::EventuallyContext *context) = 0;

    virtual std::any visitConjunction(LTLParser::ConjunctionContext *context) = 0;

    virtual std::any visitTrue(LTLParser::TrueContext *context) = 0;

    virtual std::any visitAlways(LTLParser::AlwaysContext *context) = 0;

    virtual std::any visitFalse(LTLParser::FalseContext *context) = 0;

    virtual std::any visitImplication(LTLParser::ImplicationContext *context) = 0;

    virtual std::any visitAtom(LTLParser::AtomContext *context) = 0;

    virtual std::any visitUntil(LTLParser::UntilContext *context) = 0;


};

