cmake_minimum_required(VERSION 3.17.3)
project(LexicalAnalyzerGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexicalAnalyzerGenerator main.cpp Nfa.h Nfa.cpp State.h State.cpp GlobalStructures.h InputParser.h InputParser.cpp Dfa.cpp Dfa.h Token.cpp Token.h)