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
    if(parsedProgram.isEmpty()) return;
    /*for(Map<int, statementWithString>::iterator iter = parsedProgram.begin(); iter != parsedProgram.end(); ++iter){
        std::cout << *iter << std::endl;
        parsedProgram.remove(*iter);
    }*/
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
    if(parsedProgram.isEmpty()) return -1;
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

void Program::exec(EvalState & progState){
    int currentLineNumber = getFirstLineNumber();
    if (currentLineNumber == -1){
        return;
    }
    std::string currentStateName = parsedProgram[currentLineNumber].parsedStatement->getName();
    while(true){
        if(currentStateName == "END") break;
        else if(currentStateName == "GOTO"){
            stateGOTO *stmt = reinterpret_cast<stateGOTO*>(parsedProgram[currentLineNumber].parsedStatement);
            currentLineNumber = stmt->getLineNumber();
            if(!parsedProgram.containsKey(currentLineNumber)) throw(ErrorException("LINE NUMBER ERROR"));
            currentStateName = parsedProgram[currentLineNumber].parsedStatement->getName();
            continue;
        }
        else if(currentStateName == "IF"){
            stateIF *stmt =reinterpret_cast<stateIF*>(parsedProgram[currentLineNumber].parsedStatement);
            stmt -> execute(progState);
            if(stmt->getResult()){
                if(!parsedProgram.containsKey(stmt -> getLineNumber())){
                    //std::cout << stmt-> getLineNumber() << std::endl;
                    throw(ErrorException("LINE NUMBER ERROR"));
                }
               else{
                    currentLineNumber = stmt -> getLineNumber();
                    currentStateName = parsedProgram[currentLineNumber].parsedStatement->getName();
                   // std::cout << currentLineNumber << std::endl;
                    continue;
                }
            }
        }
        else{
            //std::cout << currentLineNumber <<":"<<std::endl;
            parsedProgram[currentLineNumber].parsedStatement->execute(progState);
        }
        currentLineNumber = getNextLineNumber(currentLineNumber);
        if (currentLineNumber == -1) break;
        currentStateName = parsedProgram[currentLineNumber].parsedStatement->getName();
    }
}






















