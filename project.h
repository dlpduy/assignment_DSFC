#include "main.h"
int isOperator(char c);
int precedence(char c);
string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
//infixtopostfix and infixtoprefix


double scanNum(char ch);
int isOperand(char ch);
double operation(double a, double b, char op);
string preEval(string input);
string postEval(string input);
string PostfixPrefixCalculator(string input);
//caculate postfix and prefix



int prec(char ch);
int isOperatorlogic(char c);
int isOperandlogic(char ch);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
//infixtopostfixlogic and infixtoprefixlogic

double scanNum(char ch);
int operationpost(bool a, bool b, char op);
int operationpre(bool a, bool b, char op);
string postEvallogic(string input);
string preEvallogic(string input);
string LogicPostfixPrefixCalculator(string input, string varlue);