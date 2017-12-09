/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
/* Main program */

int main() {
   EvalState programState;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, programState);
      } catch (ErrorException & ex) {
         cerr << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & progState) {
   TokenScanner scanner;
   std::string nextToken;
   int lineNum = -1;
   //Statement *directRunPtr = nullptr;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   nextToken = scanner.nextToken();
   //Save it to program
   if(scanner.getTokenType(nextToken) == NUMBER){
       lineNum = atoi(nextToken.c_str());
       nextToken = scanner.nextToken();
       if(nextToken == "PRINT"){
           program.addSourceLine(lineNum, line);
           program.setParsedStatement(lineNum, new statePRINT(scanner));
           return;
       }
       if(nextToken == "LET"){
           program.addSourceLine(lineNum, line);
           program.setParsedStatement(lineNum, new stateLET(scanner));
           return;
       }
       if(nextToken == "END"){
           program.addSourceLine(lineNum, line);
           return;
       }
       if(nextToken == "IF"){
           program.addSourceLine(lineNum, line);
           program.setParsedStatement(lineNum, new stateIF(scanner));
           return;
       }
       if(nextToken == "REM"){
           program.addSourceLine(lineNum, line);
           return;
       }
       if(nextToken == "GOTO"){
           program.addSourceLine(lineNum, line);
           program.setParsedStatement(lineNum, new stateGOTO(scanner));
           return;
       }
       if(nextToken == "RUN"){
           program.addSourceLine(lineNum, line);
           program.setParsedStatement(lineNum, new stateRUN(scanner));
       }
       throw(ErrorException("SYNTAX ERROR"));
   }
   //This part execute directly
   else{
       if(nextToken == "QUIT"){
           stateQUIT q;
           q.execute(progState);
           return;
       }
       if(nextToken == "PRINT"){
           statePRINT p(scanner);
           p.execute(progState);
           return;
       }
       if(nextToken == "RUN"){
           stateRUN r(scanner);
           r.execute(progState);
           //program.exec();
           return;
       }
       if(nextToken == "LIST"){
           stateLIST lst(scanner);
           lst.execute(progState);
           program.listAll();
       }
       if(nextToken == "HELP"){
           if(scanner.hasMoreTokens()) throw(ErrorException("SYNTAX ERROR"));
           cout << "YOU ARE ON YOUR OWN !" << endl;
           return;
       }
       if(nextToken == "LET"){
           stateLET lt(scanner);
           lt.execute(progState);
       }
       throw(ErrorException("SYNTAX ERROR"));
   }
   /*Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;*/
}







