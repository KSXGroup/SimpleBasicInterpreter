/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
//using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
    clear();
   // Replace this stub with your own code
}

void Program::clear() {
    parsedProgram.clear();
   // Replace this stub with your own code
}

void Program::addSourceLine(int lineNumber, string line) {
    if(lineNumber < 0) throw(ErrorException("SYNTAX ERROR"));
    parsedProgram.put(lineNumber, statementWithString(line));
   // Replace this stub with your own code
}

void Program::removeSourceLine(int lineNumber) {
    if(!parsedProgram.containsKey(lineNumber)) return;
    parsedProgram.remove(lineNumber);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
    return parsedProgram[lineNumber].rawLine;
    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    parsedProgram[lineNumber].parsedStatement = stmt;
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    return parsedProgram[lineNumber].parsedStatement;
     // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
    return *(parsedProgram.begin());
    // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
     if(!parsedProgram.containsKey(lineNumber)) return -1;
     for(Map<int, statementWithString>::iterator iter = parsedProgram.begin(); iter != parsedProgram.end(); ++iter){
         if(*iter == lineNumber){
             if(++iter == parsedProgram.end()) return -1;
             return *iter;
         }
     }
}

void Program::listAll(){
    for(Map<int, statementWithString>::iterator iter = parsedProgram.begin(); iter != parsedProgram.end(); ++iter){
        std::cout << parsedProgram[*iter].rawLine << std::endl;
    }
}























