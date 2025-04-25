
// Generated from antlr/LTL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LTLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, Eventually = 3, Always = 4, Next = 5, Until = 6, 
    Not = 7, Conjunction = 8, Disjunction = 9, Implication = 10, True = 11, 
    False = 12, Atom = 13, Whitespace = 14
  };

  enum {
    RuleProgram = 0, RuleFormula = 1
  };

  explicit LTLParser(antlr4::TokenStream *input);

  LTLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~LTLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class FormulaContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    FormulaContext *formula();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  FormulaContext : public antlr4::ParserRuleContext {
  public:
    FormulaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    FormulaContext() = default;
    void copyFrom(FormulaContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NotContext : public FormulaContext {
  public:
    NotContext(FormulaContext *ctx);

    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *child = nullptr;
    antlr4::tree::TerminalNode *Not();
    FormulaContext *formula();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenthesisContext : public FormulaContext {
  public:
    ParenthesisContext(FormulaContext *ctx);

    LTLParser::FormulaContext *child = nullptr;
    FormulaContext *formula();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DisjunctionContext : public FormulaContext {
  public:
    DisjunctionContext(FormulaContext *ctx);

    LTLParser::FormulaContext *lhs = nullptr;
    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *rhs = nullptr;
    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Disjunction();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NextContext : public FormulaContext {
  public:
    NextContext(FormulaContext *ctx);

    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *child = nullptr;
    antlr4::tree::TerminalNode *Next();
    FormulaContext *formula();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EventuallyContext : public FormulaContext {
  public:
    EventuallyContext(FormulaContext *ctx);

    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *child = nullptr;
    antlr4::tree::TerminalNode *Eventually();
    FormulaContext *formula();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConjunctionContext : public FormulaContext {
  public:
    ConjunctionContext(FormulaContext *ctx);

    LTLParser::FormulaContext *lhs = nullptr;
    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *rhs = nullptr;
    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Conjunction();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  TrueContext : public FormulaContext {
  public:
    TrueContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *True();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AlwaysContext : public FormulaContext {
  public:
    AlwaysContext(FormulaContext *ctx);

    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *child = nullptr;
    antlr4::tree::TerminalNode *Always();
    FormulaContext *formula();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FalseContext : public FormulaContext {
  public:
    FalseContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *False();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ImplicationContext : public FormulaContext {
  public:
    ImplicationContext(FormulaContext *ctx);

    LTLParser::FormulaContext *lhs = nullptr;
    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *rhs = nullptr;
    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Implication();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AtomContext : public FormulaContext {
  public:
    AtomContext(FormulaContext *ctx);

    antlr4::tree::TerminalNode *Atom();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UntilContext : public FormulaContext {
  public:
    UntilContext(FormulaContext *ctx);

    LTLParser::FormulaContext *lhs = nullptr;
    antlr4::Token *op = nullptr;
    LTLParser::FormulaContext *rhs = nullptr;
    std::vector<FormulaContext *> formula();
    FormulaContext* formula(size_t i);
    antlr4::tree::TerminalNode *Until();

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  FormulaContext* formula();
  FormulaContext* formula(int precedence);

  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool formulaSempred(FormulaContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

