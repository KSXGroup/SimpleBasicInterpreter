/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <cstdlib>
#include "evalstate.h"
#include "exp.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"


/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement{

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement(){};

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement(){}

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

    inline std::string getName() const{
        return stateName;
    }

protected:
   std::string stateName;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class stateQUIT : public Statement{
public:
    stateQUIT();
    ~stateQUIT() = default;
    void execute(EvalState & state);
};

class stateREM : public Statement{
public:
    stateREM(TokenScanner & scanner);
    ~stateREM() = default;
    void execute(EvalState & state){}
};

class statePRINT : public Statement{
public:
    statePRINT(TokenScanner & scanner);
    ~statePRINT();
    void execute(EvalState & state);
private:
    Expression *exp = nullptr;
};

class stateIF : public Statement{
public:
    stateIF(TokenScanner & scanner);
    ~stateIF();
    void execute(EvalState & state);
    bool getResult();
    int getLineNumber();

private:
    int lineNum = 0;
    bool ifTrue = true;
    Expression *rightExp = nullptr;
    Expression *leftExp = nullptr;
    std::string op;

};

class stateLET : public Statement{
public:
    stateLET(TokenScanner & scanner);
    ~stateLET();
    void execute(EvalState & state);
private:
    Expression *exp = nullptr;
};

class stateINPUT : public Statement{
public:
    stateINPUT(TokenScanner & scanner);
    ~stateINPUT(){}
    void execute(EvalState & state);
private:
    std::string var;
};

class stateEND : public Statement{
public:
    stateEND(TokenScanner &scanner);
    ~stateEND(){}
    void execute(EvalState & state){}
};

class stateLIST : public Statement{
public:
    stateLIST(TokenScanner &scanner);
    ~stateLIST(){}
    void execute(EvalState & state);
};

class stateRUN : public Statement{
public:
    stateRUN(TokenScanner & scanner);
    ~stateRUN() = default;
    void execute(EvalState & state){}
};

class stateGOTO : public Statement{
public:
    stateGOTO(TokenScanner & scanner);
    ~stateGOTO() = default;
    void execute(EvalState & state);
    int getLineNumber() const;
private:
    int lineNum = 0;
};

class stateCLEAR : public Statement{
public:
    stateCLEAR(TokenScanner & scanner);
    ~stateCLEAR(){}
    void execute(EvalState & state);
};
#endif








































