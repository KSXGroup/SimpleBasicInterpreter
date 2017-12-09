/*
 * File: evalstate.cpp
 * -------------------
 * This file implements the EvalState class, which defines a symbol
 * table for keeping track of the value of identifiers.  The public
 * methods are simple enough that they need no individual documentation.
 */

#include <string>
#include "evalstate.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/map.h"

using namespace std;

/* Implementation of the EvalState class */

bool EvalState::isReservedIdentifier(std::string token){
    //cout << "eval id opt: " << token << endl;
    if(token == "LET" || token == "HELP" || token == "QUIT" || token == "CLEAR" || token == "RUN" ||  token == "IF" || token == "THEN" || token == "END" || token == "GOTO" || token == "INPUT" || token == "LIST" || token == "REM"){
        return true;
    }
    else{
        return false;
    }
}

EvalState::EvalState() {
   /* Empty */
}

EvalState::~EvalState() {
   /* Empty */
}

void EvalState::setValue(string var, int value) {
    if(!isDefined(var)){
        if(isReservedIdentifier(var)) throw(ErrorException("SYNTAX ERROR"));
    }
   symbolTable.put(var, value);
}

int EvalState::getValue(string var) {
   return symbolTable.get(var);
}

bool EvalState::isDefined(string var) {
   return symbolTable.containsKey(var);
}

void EvalState::clear(){
    symbolTable.clear();
}
