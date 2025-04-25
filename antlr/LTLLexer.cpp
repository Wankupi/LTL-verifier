
// Generated from antlr/LTL.g4 by ANTLR 4.13.2


#include "LTLLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct LTLLexerStaticData final {
  LTLLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LTLLexerStaticData(const LTLLexerStaticData&) = delete;
  LTLLexerStaticData(LTLLexerStaticData&&) = delete;
  LTLLexerStaticData& operator=(const LTLLexerStaticData&) = delete;
  LTLLexerStaticData& operator=(LTLLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ltllexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<LTLLexerStaticData> ltllexerLexerStaticData = nullptr;

void ltllexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ltllexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(ltllexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LTLLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "Eventually", "Always", "Next", "Until", "Not", "Conjunction", 
      "Disjunction", "Implication", "True", "False", "Atom", "Whitespace"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'F'", "'G'", "'X'", "'U'", "'!'", "'/\\'", "'\\/'", 
      "'->'", "'true'", "'false'"
    },
    std::vector<std::string>{
      "", "", "", "Eventually", "Always", "Next", "Until", "Not", "Conjunction", 
      "Disjunction", "Implication", "True", "False", "Atom", "Whitespace"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,14,75,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,7,1,8,1,
  	8,1,8,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,12,4,12,65,8,12,11,12,12,12,66,1,13,4,13,70,8,13,11,13,12,13,71,
  	1,13,1,13,0,0,14,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,
  	23,12,25,13,27,14,1,0,2,1,0,97,122,3,0,9,10,13,13,32,32,76,0,1,1,0,0,
  	0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,
  	0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,
  	0,0,25,1,0,0,0,0,27,1,0,0,0,1,29,1,0,0,0,3,31,1,0,0,0,5,33,1,0,0,0,7,
  	35,1,0,0,0,9,37,1,0,0,0,11,39,1,0,0,0,13,41,1,0,0,0,15,43,1,0,0,0,17,
  	46,1,0,0,0,19,49,1,0,0,0,21,52,1,0,0,0,23,57,1,0,0,0,25,64,1,0,0,0,27,
  	69,1,0,0,0,29,30,5,40,0,0,30,2,1,0,0,0,31,32,5,41,0,0,32,4,1,0,0,0,33,
  	34,5,70,0,0,34,6,1,0,0,0,35,36,5,71,0,0,36,8,1,0,0,0,37,38,5,88,0,0,38,
  	10,1,0,0,0,39,40,5,85,0,0,40,12,1,0,0,0,41,42,5,33,0,0,42,14,1,0,0,0,
  	43,44,5,47,0,0,44,45,5,92,0,0,45,16,1,0,0,0,46,47,5,92,0,0,47,48,5,47,
  	0,0,48,18,1,0,0,0,49,50,5,45,0,0,50,51,5,62,0,0,51,20,1,0,0,0,52,53,5,
  	116,0,0,53,54,5,114,0,0,54,55,5,117,0,0,55,56,5,101,0,0,56,22,1,0,0,0,
  	57,58,5,102,0,0,58,59,5,97,0,0,59,60,5,108,0,0,60,61,5,115,0,0,61,62,
  	5,101,0,0,62,24,1,0,0,0,63,65,7,0,0,0,64,63,1,0,0,0,65,66,1,0,0,0,66,
  	64,1,0,0,0,66,67,1,0,0,0,67,26,1,0,0,0,68,70,7,1,0,0,69,68,1,0,0,0,70,
  	71,1,0,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,73,1,0,0,0,73,74,6,13,0,0,74,
  	28,1,0,0,0,3,0,66,71,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ltllexerLexerStaticData = std::move(staticData);
}

}

LTLLexer::LTLLexer(CharStream *input) : Lexer(input) {
  LTLLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *ltllexerLexerStaticData->atn, ltllexerLexerStaticData->decisionToDFA, ltllexerLexerStaticData->sharedContextCache);
}

LTLLexer::~LTLLexer() {
  delete _interpreter;
}

std::string LTLLexer::getGrammarFileName() const {
  return "LTL.g4";
}

const std::vector<std::string>& LTLLexer::getRuleNames() const {
  return ltllexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& LTLLexer::getChannelNames() const {
  return ltllexerLexerStaticData->channelNames;
}

const std::vector<std::string>& LTLLexer::getModeNames() const {
  return ltllexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& LTLLexer::getVocabulary() const {
  return ltllexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LTLLexer::getSerializedATN() const {
  return ltllexerLexerStaticData->serializedATN;
}

const atn::ATN& LTLLexer::getATN() const {
  return *ltllexerLexerStaticData->atn;
}




void LTLLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ltllexerLexerInitialize();
#else
  ::antlr4::internal::call_once(ltllexerLexerOnceFlag, ltllexerLexerInitialize);
#endif
}
