
// Generated from antlr/LTL.g4 by ANTLR 4.13.2


#include "LTLVisitor.h"

#include "LTLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LTLParserStaticData final {
  LTLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLParserStaticData(const LTLParserStaticData&) = delete;
  LTLParserStaticData(LTLParserStaticData&&) = delete;
  LTLParserStaticData& operator=(const LTLParserStaticData&) = delete;
  LTLParserStaticData& operator=(LTLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ltlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<LTLParserStaticData> ltlParserStaticData = nullptr;

void ltlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ltlParserStaticData != nullptr) {
    return;
  }
#else
  assert(ltlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LTLParserStaticData>(
    std::vector<std::string>{
      "program", "formula"
    },
    std::vector<std::string>{
      "", "'('", "')'", "", "", "", "", "", "", "", "", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "Eventually", "Always", "Next", "Until", "Not", "Conjunction", 
      "Disjunction", "Implication", "True", "False", "Atom", "Whitespace"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,14,43,2,0,7,0,2,1,7,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,24,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,5,1,38,8,1,10,1,12,1,41,9,1,1,1,0,1,2,2,0,2,0,0,
  	51,0,4,1,0,0,0,2,23,1,0,0,0,4,5,3,2,1,0,5,6,5,0,0,1,6,1,1,0,0,0,7,8,6,
  	1,-1,0,8,9,5,7,0,0,9,24,3,2,1,12,10,11,5,4,0,0,11,24,3,2,1,11,12,13,5,
  	3,0,0,13,24,3,2,1,10,14,15,5,5,0,0,15,24,3,2,1,9,16,24,5,11,0,0,17,24,
  	5,12,0,0,18,19,5,1,0,0,19,20,3,2,1,0,20,21,5,2,0,0,21,24,1,0,0,0,22,24,
  	5,13,0,0,23,7,1,0,0,0,23,10,1,0,0,0,23,12,1,0,0,0,23,14,1,0,0,0,23,16,
  	1,0,0,0,23,17,1,0,0,0,23,18,1,0,0,0,23,22,1,0,0,0,24,39,1,0,0,0,25,26,
  	10,8,0,0,26,27,5,6,0,0,27,38,3,2,1,9,28,29,10,7,0,0,29,30,5,10,0,0,30,
  	38,3,2,1,8,31,32,10,6,0,0,32,33,5,9,0,0,33,38,3,2,1,7,34,35,10,5,0,0,
  	35,36,5,8,0,0,36,38,3,2,1,6,37,25,1,0,0,0,37,28,1,0,0,0,37,31,1,0,0,0,
  	37,34,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,3,1,0,0,0,
  	41,39,1,0,0,0,3,23,37,39
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltlParserStaticData = std::move(staticData);
}

}

LTLParser::LTLParser(TokenStream *input) : LTLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LTLParser::LTLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LTLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ltlParserStaticData->atn, ltlParserStaticData->decisionToDFA, ltlParserStaticData->sharedContextCache, options);
}

LTLParser::~LTLParser() {
  delete _interpreter;
}

const atn::ATN& LTLParser::getATN() const {
  return *ltlParserStaticData->atn;
}

std::string LTLParser::getGrammarFileName() const {
  return "LTL.g4";
}

const std::vector<std::string>& LTLParser::getRuleNames() const {
  return ltlParserStaticData->ruleNames;
}

const dfa::Vocabulary& LTLParser::getVocabulary() const {
  return ltlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLParser::getSerializedATN() const {
  return ltlParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

LTLParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LTLParser::FormulaContext* LTLParser::ProgramContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

tree::TerminalNode* LTLParser::ProgramContext::EOF() {
  return getToken(LTLParser::EOF, 0);
}


size_t LTLParser::ProgramContext::getRuleIndex() const {
  return LTLParser::RuleProgram;
}


std::any LTLParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::ProgramContext* LTLParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, LTLParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(4);
    formula(0);
    setState(5);
    match(LTLParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FormulaContext ------------------------------------------------------------------

LTLParser::FormulaContext::FormulaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t LTLParser::FormulaContext::getRuleIndex() const {
  return LTLParser::RuleFormula;
}

void LTLParser::FormulaContext::copyFrom(FormulaContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NotContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NotContext::Not() {
  return getToken(LTLParser::Not, 0);
}

LTLParser::FormulaContext* LTLParser::NotContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NotContext::NotContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::NotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesisContext ------------------------------------------------------------------

LTLParser::FormulaContext* LTLParser::ParenthesisContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::ParenthesisContext::ParenthesisContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::ParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DisjunctionContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::DisjunctionContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::DisjunctionContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::DisjunctionContext::Disjunction() {
  return getToken(LTLParser::Disjunction, 0);
}

LTLParser::DisjunctionContext::DisjunctionContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::DisjunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitDisjunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NextContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::NextContext::Next() {
  return getToken(LTLParser::Next, 0);
}

LTLParser::FormulaContext* LTLParser::NextContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::NextContext::NextContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::NextContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitNext(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EventuallyContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::EventuallyContext::Eventually() {
  return getToken(LTLParser::Eventually, 0);
}

LTLParser::FormulaContext* LTLParser::EventuallyContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::EventuallyContext::EventuallyContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::EventuallyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitEventually(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConjunctionContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::ConjunctionContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::ConjunctionContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::ConjunctionContext::Conjunction() {
  return getToken(LTLParser::Conjunction, 0);
}

LTLParser::ConjunctionContext::ConjunctionContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::ConjunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitConjunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::TrueContext::True() {
  return getToken(LTLParser::True, 0);
}

LTLParser::TrueContext::TrueContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::TrueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitTrue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlwaysContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AlwaysContext::Always() {
  return getToken(LTLParser::Always, 0);
}

LTLParser::FormulaContext* LTLParser::AlwaysContext::formula() {
  return getRuleContext<LTLParser::FormulaContext>(0);
}

LTLParser::AlwaysContext::AlwaysContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::AlwaysContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAlways(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::FalseContext::False() {
  return getToken(LTLParser::False, 0);
}

LTLParser::FalseContext::FalseContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::FalseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitFalse(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ImplicationContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::ImplicationContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::ImplicationContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::ImplicationContext::Implication() {
  return getToken(LTLParser::Implication, 0);
}

LTLParser::ImplicationContext::ImplicationContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::ImplicationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitImplication(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AtomContext ------------------------------------------------------------------

tree::TerminalNode* LTLParser::AtomContext::Atom() {
  return getToken(LTLParser::Atom, 0);
}

LTLParser::AtomContext::AtomContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitAtom(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UntilContext ------------------------------------------------------------------

std::vector<LTLParser::FormulaContext *> LTLParser::UntilContext::formula() {
  return getRuleContexts<LTLParser::FormulaContext>();
}

LTLParser::FormulaContext* LTLParser::UntilContext::formula(size_t i) {
  return getRuleContext<LTLParser::FormulaContext>(i);
}

tree::TerminalNode* LTLParser::UntilContext::Until() {
  return getToken(LTLParser::Until, 0);
}

LTLParser::UntilContext::UntilContext(FormulaContext *ctx) { copyFrom(ctx); }


std::any LTLParser::UntilContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<LTLVisitor*>(visitor))
    return parserVisitor->visitUntil(this);
  else
    return visitor->visitChildren(this);
}

LTLParser::FormulaContext* LTLParser::formula() {
   return formula(0);
}

LTLParser::FormulaContext* LTLParser::formula(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LTLParser::FormulaContext *_localctx = _tracker.createInstance<FormulaContext>(_ctx, parentState);
  LTLParser::FormulaContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, LTLParser::RuleFormula, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(23);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LTLParser::Not: {
        _localctx = _tracker.createInstance<NotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(8);
        antlrcpp::downCast<NotContext *>(_localctx)->op = match(LTLParser::Not);
        setState(9);
        antlrcpp::downCast<NotContext *>(_localctx)->child = formula(12);
        break;
      }

      case LTLParser::Always: {
        _localctx = _tracker.createInstance<AlwaysContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(10);
        antlrcpp::downCast<AlwaysContext *>(_localctx)->op = match(LTLParser::Always);
        setState(11);
        antlrcpp::downCast<AlwaysContext *>(_localctx)->child = formula(11);
        break;
      }

      case LTLParser::Eventually: {
        _localctx = _tracker.createInstance<EventuallyContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(12);
        antlrcpp::downCast<EventuallyContext *>(_localctx)->op = match(LTLParser::Eventually);
        setState(13);
        antlrcpp::downCast<EventuallyContext *>(_localctx)->child = formula(10);
        break;
      }

      case LTLParser::Next: {
        _localctx = _tracker.createInstance<NextContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(14);
        antlrcpp::downCast<NextContext *>(_localctx)->op = match(LTLParser::Next);
        setState(15);
        antlrcpp::downCast<NextContext *>(_localctx)->child = formula(9);
        break;
      }

      case LTLParser::True: {
        _localctx = _tracker.createInstance<TrueContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(16);
        match(LTLParser::True);
        break;
      }

      case LTLParser::False: {
        _localctx = _tracker.createInstance<FalseContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(17);
        match(LTLParser::False);
        break;
      }

      case LTLParser::T__0: {
        _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(18);
        match(LTLParser::T__0);
        setState(19);
        antlrcpp::downCast<ParenthesisContext *>(_localctx)->child = formula(0);
        setState(20);
        match(LTLParser::T__1);
        break;
      }

      case LTLParser::Atom: {
        _localctx = _tracker.createInstance<AtomContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(22);
        match(LTLParser::Atom);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(39);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(37);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<UntilContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lhs = previousContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(25);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(26);
          antlrcpp::downCast<UntilContext *>(_localctx)->op = match(LTLParser::Until);
          setState(27);
          antlrcpp::downCast<UntilContext *>(_localctx)->rhs = formula(9);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ImplicationContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lhs = previousContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(28);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(29);
          antlrcpp::downCast<ImplicationContext *>(_localctx)->op = match(LTLParser::Implication);
          setState(30);
          antlrcpp::downCast<ImplicationContext *>(_localctx)->rhs = formula(8);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<DisjunctionContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lhs = previousContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(31);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(32);
          antlrcpp::downCast<DisjunctionContext *>(_localctx)->op = match(LTLParser::Disjunction);
          setState(33);
          antlrcpp::downCast<DisjunctionContext *>(_localctx)->rhs = formula(7);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ConjunctionContext>(_tracker.createInstance<FormulaContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->lhs = previousContext;
          pushNewRecursionContext(newContext, startState, RuleFormula);
          setState(34);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(35);
          antlrcpp::downCast<ConjunctionContext *>(_localctx)->op = match(LTLParser::Conjunction);
          setState(36);
          antlrcpp::downCast<ConjunctionContext *>(_localctx)->rhs = formula(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(41);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool LTLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return formulaSempred(antlrcpp::downCast<FormulaContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LTLParser::formulaSempred(FormulaContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

void LTLParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ltlParserInitialize();
#else
  ::antlr4::internal::call_once(ltlParserOnceFlag, ltlParserInitialize);
#endif
}
