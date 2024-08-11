#include "project.h"
int main() {
    string infix="23+12-13+8*2-2^3/2";
    cout<<"INFIX TO POSTFIX OR INFIX TO PREFIX" <<endl;
    cout<<"Infix: "<<infix<<endl;
    cout<<"Infix2Postfix: "<<Infix2Postfix(infix)<<endl;
    cout<<"Infix2Prefix: "<<Infix2Prefix(infix)<<endl;
    cout<<"PostfixPrefixCalculator: ";
    if(Infix2Prefix(infix)=="UNDEFINED ERROR") cout<< "UNDEFINED ERROR"<<endl;
    else if(Infix2Prefix(infix)=="DIVIDE BY 0 ERROR") cout<< "DIVIDE BY 0 ERROR";
    else cout<<PostfixPrefixCalculator(Infix2Prefix(infix))<<endl;

    cout<<string(50,'-')<<endl;

    cout<<"LOGIXINFIX TO LOGICPOSTFIX OR LOGICINFIX TO LOGICPREFIX"<<endl;
    string input="p&(q&r)->t";
    cout<<"INPUT: "<<input<<endl;
    cout<<"LogicInfix2Postfix: "<<LogicInfix2Postfix(input)<<endl;
    cout<<"LogicInfix2Prefix: "<<LogicInfix2Prefix(input)<<endl;
    string varlue="p q r t 0 0 1 1";
    cout<<"value: " << varlue<<endl;
    cout<<"LogicPostfixPrefixCalculator: ";
    if(LogicInfix2Postfix(input)=="SYNTAX ERROR") cout<<"SYNTAX ERROR";
    else cout <<LogicPostfixPrefixCalculator(LogicInfix2Prefix(input),varlue);
}