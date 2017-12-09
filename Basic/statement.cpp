/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include <cstdio>

using namespace std;
/* Implementation of the Statement class */

inline std::string Statement::getName() const{
    return stateName;
}

stateQUIT::stateQUIT(){
    stateName = "QUIT";
}
void stateQUIT::execute(EvalState &state){
    exit(0);
}

stateREM::stateREM(){
    stateName = "REM";
}

statePRINT::statePRINT(TokenScanner &scanner){
    stateName = "PRINT";
    exp = parseExp(scanner);
    /*while(scanner.hasMoreTokens()){
        //throw ErrorException("SYNTAX ERROR");
        std::cout << scanner.nextToken() << std::endl;
    }*/
   if(scanner.hasMoreTokens()){
        throw ErrorException("SYNTAX ERROR");
    }
}

statePRINT::~statePRINT(){
    delete exp;
}

void statePRINT::execute(EvalState &state){
    std::cout << exp -> eval(state) << std::endl;
}

stateLET::stateLET(TokenScanner & scanner){
    std::string next;
    stateName = "LET";
    next = scanner.nextToken();
    if(scanner.getTokenType(next) != WORD){
        throw(ErrorException("SYNTAX ERROR"));
    }
    else{
        scanner.saveToken(next);
    }
    exp = parseExp(scanner);
}

stateLET::~stateLET(){
    delete exp;
}

void stateLET::execute(EvalState & state){
    exp -> eval(state);
}

stateIF::stateIF(TokenScanner &scanner){
    stateName = "IF";
    leftExp = readE(scanner, 1);
    op = scanner.nextToken();
    if(op != ">" || op != "<" || op != "=") throw(ErrorException("SYNTAX ERROR"));
    rightExp = readE(scanner, 1);
    if(scanner.nextToken() != "THEN"){
        throw(ErrorException("SYNTAX ERROR"));
    }
    lineNumber = atoi(scanner.nextToken().c_str());
}

stateIF::~stateIF(){
    delete rightExp;
    delete leftExp;
}

void stateIF::execute(EvalState &state){
    int left = leftExp -> eval(state);
    int right = rightExp -> eval(state);
    if(op == ">"){
        left > right ? ifTrue = true : ifTrue = false;
    }
    else if(op == "<"){
        left < right ? ifTrue = true : ifTrue = false;
    }
    else if(op == "="){
        left == right ? ifTrue = true : ifTrue = false;
    }
    else{
        throw(ErrorException("SYNTAX ERROR"));
    }
}
stateINPUT::stateINPUT(TokenScanner &scanner){
    stateName = "INPUT";
    if (!scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
    std::string token = scanner.nextToken();
    if(scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
    if(scanner.getTokenType(token) != WORD) throw(ErrorException("SYNTAX ERROR"));
    var = token;
}

void stateINPUT::execute(EvalState &state){
    bool flag = 1;
    std::string ipt, tmp;
    TokenScanner numScanner;
    numScanner.ignoreWhitespace();
    numScanner.scanNumbers();
    numScanner.scanStrings();
    while(true) {
    flag = 1;
    cout << " ? ";
    getline(cin, ipt);
    numScanner.setInput(ipt);
    ipt = numScanner.nextToken();
    if(numScanner.getTokenType(ipt) == OPERATOR){
        tmp = numScanner.nextToken();
        if(numScanner.getTokenType(tmp) != NUMBER){
            std::cout << "INVALID NUMBER" << std::endl;
            flag = 0;
            tmp.clear();
            continue;
        }
        else{
            ipt += tmp;
        }
    }
    else{
        if(numScanner.hasMoreTokens()){
            flag = 0;
            std::cout << "INVALID NUMBER" << std::endl;
        }
        if(numScanner.getTokenType(ipt)!= NUMBER){
            flag = 0;
            std::cout << "INVALID NUMBER" << std::endl;
        }
    }
    for(int i = 0;i < ipt.size(); ++i){
        if(ipt[i] == '.'){
            std::cout << "INVALID NUMBER" << std::endl;
            flag = 0;
            tmp.clear();
            ipt.clear();
        }
    }
    if(flag) break;
    }
    //std::cout << ipt << std::endl;
    state.setValue(var, atoi(ipt.c_str()));
}

stateEND::stateEND(){
    stateName = "END";
}

stateLIST::stateLIST(TokenScanner & scanner){
    stateName = "LIST";
    if(scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
}

void stateLIST::execute(EvalState &state){
    /*int lineNum = progPtr -> getFirstLineNumber();
    while(true){
        if(lineNum == -1) break;
        cout << lineNum << " " << progPtr -> getSourceLine(lineNum) << endl;
        lineNum = progPtr -> getNextLineNumber(lineNum);
    }*/
    return;
}

stateRUN::stateRUN(TokenScanner &scanner){
    stateName = "RUN";
    if(scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
}

stateGOTO::stateGOTO(TokenScanner &scanner){
    stateName = "GOTO";
    std::string ipt;
    ipt = scanner.nextToken();
    if(scanner.hasMoreTokens()){
        throw(ErrorException("SYNTAX ERROR"));
    }
    if(scanner.getTokenType(ipt) != NUMBER){
        throw(ErrorException("SYNTAX ERROR"));
    }
    lineNum = atoi(ipt.c_str());
}

void stateGOTO::execute(EvalState &state){
    //DO NOTHING
}

stateCLEAR::stateCLEAR(TokenScanner & scanner){
    stateName = "CLEAR";
    if(scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
}

void stateCLEAR::execute(EvalState &state){
    state.clear();
}













































