#include "project.h"
int isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;// la cac toan tu
    return 0;// khong la cac toan tu
}
int isOperand(char ch) {
    if ((ch >= '0' && ch <= '9') || ch == ' ')
        return 1;//character is an operand
    return 0;//not an operand
}
int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
} // check do uu tien cac toan tu

string Infix2Prefix(string infix)
{
    int N = infix.length();
    for (int i = 0; i < N; i++) {
        if (infix[i] == ' ') {
            infix.erase(infix.begin() + i);
            N--;
            i--;
        }
    }
    for(size_t i=0; i<infix.length();i++) {
        if((infix[i]=='/'||infix[i]=='*'||infix[i]=='^')&&(infix[i+1]=='/'||infix[i+1]=='*'||infix[i+1]=='^'))
        return "UNDEFINED ERROR";
        if((infix[i]=='/'&&infix[i+1]=='0')) return "DIVIDE BY 0 ERROR";
    }
    string prefix;
    reverse(infix.begin(), infix.end());
    stack<char> s;
    s.push(infix[0]);
    for (size_t i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    for (size_t i = 0; i < infix.length(); i++) {

        if ((infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z')||(infix[i]>='0'&&infix[i]<='9')) {
            prefix += infix[i];
        }
        else if (infix[i] == '(') {
            prefix += ' ';
            s.push(infix[i]);
        }
        else if (infix[i] == ')') {
            prefix += ' ';
            while ((s.top() != '(') && (!s.empty())) {
                prefix += s.top();
                s.pop();
            }

            if (s.top() == '(') {
                s.pop();
            }
        }
        else if (isOperator(infix[i])) {
           prefix += ' ';
            if (s.empty()) {
                s.push(infix[i]);
            }
            else {
                if (precedence(infix[i]) >= precedence(s.top())) {
                    s.push(infix[i]);
                }
                else if ((precedence(infix[i]) == precedence(s.top()))
                    && (infix[i] == '^')) {
                    while ((precedence(infix[i]) == precedence(s.top()))
                        && (infix[i] == '^')) {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
                else if (precedence(infix[i]) == precedence(s.top())) {
                    s.push(infix[i]);
                }
                else {
                    while ((!s.empty()) && (precedence(infix[i]) < precedence(s.top()))) {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }

    while (!s.empty()) {
        prefix += s.top();
        s.pop();
    }
    reverse(prefix.begin(), prefix.end());
 
    for (size_t i = 0; i < prefix.length(); i++) {
        if ((prefix[i] == '+'|| prefix[i] == '-'|| prefix[i] == '*'|| prefix[i] == '/'|| prefix[i] == '^')&&prefix[i+1]!=' ') prefix.insert(prefix.begin() + i+1, ' ');
    }
    for (size_t i = 1; i < prefix.length(); i++) {
        if ((prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/' || prefix[i] == '^') && prefix[i-1] != ' ') prefix.insert(prefix.begin() + i, ' ');
    }
    
    for (size_t i = 0; i < prefix.length(); i++) {
        if (prefix[i] == ' ' && prefix[i + 1] == ' ') {
            prefix.erase(prefix.begin() + i);
            i--;
        }
    }
    prefix.erase(prefix.begin());
    prefix.erase(prefix.begin());

    return prefix;
}

string Infix2Postfix(string infix) {
      int N = infix.length();
    for (int i = 0; i < N; i++) {
        if (infix[i] == ' ') {
            infix.erase(infix.begin() + i);
            N--;
            i--;
        }
    }
    for(size_t i=0; i<infix.length();i++) {
        if((infix[i]=='/'||infix[i]=='*'||infix[i]=='^')&&(infix[i+1]=='/'||infix[i+1]=='*'||infix[i+1]=='^'))
        return "UNDEFINED ERROR";
        if((infix[i]=='/'&&infix[i+1]=='0')) return "DIVIDE BY 0 ERROR";
    }

	stack<char> st; 
	string postfix = "";

	for (size_t i = 0; i < infix.length(); i++) {
		char ch = infix[i];

		
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
			postfix += ch;  
		else if (ch == '(')
			st.push('(');
		else if (ch == ')') {
			postfix += " ";
			while (st.top() != '(')
			{
				postfix += st.top();  
				st.pop();

			}
			st.pop();
		}

		else {
			postfix += " ";
			while (!st.empty() && precedence(infix[i]) <= precedence(st.top())) {

				postfix += st.top();
				st.pop();
			}
			st.push(ch);

		
		}

	}


	while (!st.empty()) {
		postfix += " ";
		postfix += st.top();
		st.pop();
	}

	for (size_t i = 0; i < postfix.length(); i++) {
		if ((postfix[i] == '*'|| postfix[i] == '^'||postfix[i]=='+'||postfix[i]=='-'||postfix[i]=='/') && ((postfix[i+1] == '*'|| postfix[i+1] == '^'||postfix[i+1]=='+'||postfix[i+1]=='-'||postfix[i+1]=='/')||(postfix[i+1] >= 'a' && postfix[i+1] <= 'z') || (postfix[i+1] >= 'A' && postfix[i+1] <= 'Z') || (postfix[i+1] >= '0' && postfix[i+1] <= '9')))
			postfix.insert(postfix.begin() + i+1,' ');
	}
	
	for(size_t i=0; i<postfix.length(); i++) {
	    if( postfix[i]==' '&&postfix[i+1]==' ') postfix.erase(postfix.begin() + i);
	}
	return postfix;
}

double operation(double a, double b, char op) {
    //Perform operation
    if (op == '+')
        return b + a;
    else if (op == '-') {
        if (b - a == -16) return 230304;
        return b - a;
    }
        
    else if (op == '*')
        return b * a;
    else if (op == '/')
        return b / a;
    else if (op == '^')
        return pow(b, a); //find b^a
    else
        return -100; //return negative infinity
}

string postEval(string input) {
    input.insert(input.begin(), ' ');
    if (input[input.length() - 1] == ' ') input.erase(input.length() - 1);
    double a = 0, b = 0;
    stack<double> stk;
    double result;
    string::iterator it;
    for (it = input.begin(); it != input.end(); it++) {
        if (isOperator(*it)) {
            stk.pop();
            a = 0, b = 0;
            int count1 = 0;
            int count2 = 0;
            while (stk.top() != -16) {
                a = a + stk.top() * pow(10, count1);
                count1++;
                stk.pop();
            }
            if (a == 0.2303) a = -16;
            stk.pop();
            while (stk.top() != -16) {
                b = b + stk.top() * pow(10, count2);
                count2++;
                stk.pop();
            }
            if (b == 0.2303) b = -16;


            stk.push(operation(a, b, *it));

        }
        else if (isOperand(*it)) {
            stk.push(scanNum(*it));
        }
    }
    result = stk.top();
    string cal = to_string(result);
    cal.erase(cal.begin() + cal.length() - 1);

    if (cal[cal.length() - 1] >= '0' && cal[cal.length() - 1] <= '4') cal.erase(cal.begin() + cal.length() - 1);
    else if (cal[cal.length() - 1] >= '5' && cal[cal.length() - 1] <= '9') {
        size_t  i = cal.length() - 2;
        while (cal[i] == '9') {
            cal[i] = '0';
            if (cal[i - 1] == '.') i--;
            i--;
        }
        cal[i] = cal[i] + int(1);
        cal.erase(cal.begin() + cal.length() - 1);
    }
    int size = cal.length();
    while (cal[size - 1] == '0') {
        cal.erase(cal.begin() + size - 1);
        size--;
    }
    if (cal[cal.length() - 1] == '.') cal.erase(cal.begin() + cal.length() - 1);
    if (cal == "0.2303") cal = "-16";
    return cal;
}

string preEval(string input) {
    input.insert(input.begin(), ' ');
    input.insert(input.begin() + input.length(), ' ');
    double a = 0, b = 0;
    stack<double> stk;
    double result;
    string::iterator it;
    for (it = input.end() - 1; it != input.begin(); it--) {
        if (isOperator(*it) != 0) {
            a = 0, b = 0;
            int count1 = 0;
            int count2 = 0;
            while (stk.top() == -16) stk.pop();
            while (stk.top() != -16) {
                b = b * 10 + stk.top();
                count1++;
                stk.pop();
            }
            if (b == 0.2303) b = -16;
            while (stk.top() == -16) stk.pop();
            while (stk.top() != -16) {
                a = a * 10 + stk.top();
                count2++;
                stk.pop();
            }
            if (a == 0.2303) a = -16;
            stk.push(operation(a, b, *it));

        }
        else if (isOperand(*it) > 0) {
            stk.push(scanNum(*it));
        }
    }
    result = stk.top();
    string cal = to_string(result);
    cal.erase(cal.begin() + cal.length() - 1);

    if (cal[cal.length() - 1] >= '0' && cal[cal.length() - 1] <= '4') cal.erase(cal.begin() + cal.length() - 1);
    else if (cal[cal.length() - 1] >= '5' && cal[cal.length() - 1] <= '9') {
        size_t  i = cal.length() - 2;
        while (cal[i] == '9') {
            cal[i] = '0';
            if (cal[i - 1] == '.') i--;
            i--;
        }
        cal[i] = cal[i] + int(1);
        cal.erase(cal.begin() + cal.length() - 1);
    }
    int size = cal.length();
    while (cal[size - 1] == '0') {
        cal.erase(cal.begin() + size - 1);
        size--;
    }
    if (cal[cal.length() - 1] == '.') cal.erase(cal.begin() + cal.length() - 1);
    if (cal == "0.2303") cal = "-16";
    return cal;
}

string PostfixPrefixCalculator(string input) {
    int N = input.length() - 1;
    bool checkoperator = 0;
    for (int i = 0; i < N; i++) {
        if (input[i] == ' ' && input[i + 1] == ' ') {
            input.erase(input.begin() + i);
            i--;
            N--;
        }
    }
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*' || input[i] == '^') checkoperator = 1;
    }
    if (!checkoperator) {
        for (size_t i = 0; i < input.length(); i++) {
            if (input[i] == '(' || input[i] == ')') {
                input.erase(input.begin() + i);
            }
        }
        return input;
    }
    if (input[0] == ' ') input.erase(input.begin());
    if (input[input.length() - 1] == ' ') input.erase(input.begin() + input.length() - 1);
    if (input[0] == '+' || input[0] == '-' || input[0] == '/' || input[0] == '*' || input[0] == '^') {
        return preEval(input);
    }
    return postEval(input);
}



int prec(char c) {
 if (c == '~')
        return 3;
    else if (c == '|' || c == '&')
        return 2;
    else if (c == '-')
        return 1;
    else if (c == '<')
        return 0;
    else
        return -1;
}

int isOperatorlogic(char c)
{
    if (c == '<' || c == '-' || c == '|' || c == '&' || c == '~') {
        return 1;
    }
    return 0;
}
int isOperandlogic(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

string LogicInfix2Postfix(string infix) {
	int N = infix.length();
	for (int i = 0; i < N; i++) {
		if (infix[i] == ' ') {
			infix.erase(infix.begin() + i);
			N--;
			i--;
		}
	}
	for (size_t i = 0; i < infix.length()-2; i++) {
		if (infix[i] == '<' && infix[i + 1] == '-' && infix[i + 2] == '>') { 
			infix.erase(infix.begin() + i + 1);
			infix.erase(infix.begin() + i + 1);
		}
	}
	for (size_t i = 0; i < infix.length()-1; i++) {
		if (infix[i] == '-' && infix[i + 1] == '>') infix.erase(infix.begin() + i+1);
	}
    for(size_t i=0; i<infix.length(); i++) {
        if((infix[i]=='&'||infix[i]=='|'||infix[i]=='<'||infix[i]=='-')&&(infix[i+1]=='&'||infix[i+1]=='|'||infix[i+1]=='<'||infix[i+1]=='-'))
        return "SYNTAX ERROR";
    }
	stack<char> st;
	st.push(infix[0]);
	string postfix = "";

	for (size_t i = 0; i < infix.length(); i++) {
		char ch = infix[i];

		
		if (ch >= 'a' && ch <= 'z')
			postfix += ch;  

		
		else if (ch == '(')
			st.push('(');

		
		else if (ch == ')') {
			while (st.top() != '(')
			{
				postfix += st.top();   
				st.pop();

			}
			st.pop();
		}

		else {
			while (!st.empty() && prec(infix[i]) <= prec(st.top())) {

				postfix += st.top();
				st.pop();
			}
			st.push(ch);

		}

	}

	while (!st.empty()) {	
		postfix += st.top();
		st.pop();
	}
	for (size_t i = 0; i < postfix.length(); i++) {
		if (postfix[i] == '-') postfix.insert(postfix.begin()+i+1,'>');
	}
	for (size_t i = 0; i < postfix.length(); i++) {
		if (postfix[i] == '<') {
			postfix.insert(postfix.begin() + i + 1, '-');
			postfix.insert(postfix.begin() + i + 2, '>');
		}
	}
	if(infix[0]=='~') postfix.erase(postfix.begin());
	else postfix.erase(postfix.begin() + postfix.length() - 1);
	while (!st.empty()) st.pop();
	return postfix;
}

string LogicInfix2Prefix(string infix)
{
    int N = infix.length();
    for (int i = 0; i < N; i++) {
        if (infix[i] == ' ') {
            infix.erase(infix.begin() + i);
            N--;
            i--;
        }
    }
    for (size_t i = 0; i < infix.length()-2; i++) {
        if (infix[i] == '<' && infix[i + 1] == '-' && infix[i + 2] == '>') {
            infix.erase(infix.begin() + i + 1);
            infix.erase(infix.begin() + i + 1);
        }
    }

    for (size_t i = 0; i < infix.length()-1; i++) {
        if (infix[i] == '-' && infix[i + 1] == '>') infix.erase(infix.begin() + i + 1);
    }
    
    for(size_t i=0; i<infix.length(); i++) {
        if((infix[i]=='&'||infix[i]=='|'||infix[i]=='<'||infix[i]=='-')&&(infix[i+1]=='&'||infix[i+1]=='|'||infix[i+1]=='<'||infix[i+1]=='-'))
        return "SYNTAX ERROR";
    }

    string prefix;
    reverse(infix.begin(), infix.end());
    stack<char> s;
    s.push(infix[0]);
    for (size_t i = 0; i < infix.length(); i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    for (size_t i = 0; i < infix.length(); i++) {

        if(infix[i] >= 'a' && infix[i] <= 'z')  {
            prefix += infix[i];
        }
        else if (infix[i] == '(') {
            s.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while ((s.top() != '(') && (!s.empty())) {
                prefix += s.top();
                s.pop();
            }

            if (s.top() == '(') {
                s.pop();
            }
        }
        else if (isOperatorlogic(infix[i])) {
            if (s.empty()) {
                s.push(infix[i]);
            }
            else {
                if (prec(infix[i]) > prec(s.top())) {
                    s.push(infix[i]);
                }
                else if ((prec(infix[i]) == prec(s.top()))
                    && (infix[i] == '^')) {
                    while ((prec(infix[i]) == prec(s.top()))
                        && (infix[i] == '^')) {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
                else if (prec(infix[i]) == prec(s.top())) {
                    s.push(infix[i]);
                }
                else {
                    while ((!s.empty()) && (prec(infix[i]) < prec(s.top()))) {
                        prefix += s.top();
                        s.pop();
                    }
                    s.push(infix[i]);
                }
            }
        }
    }

    while (!s.empty()) {
        prefix += s.top();
        s.pop();
    }
    reverse(prefix.begin(), prefix.end());
    for (size_t i = 0; i < prefix.length(); i++) {
        if (prefix[i] == '-') prefix.insert(prefix.begin() + i + 1, '>');
    }

    for (size_t i = 0; i < prefix.length(); i++) {
        if (prefix[i] == '<') {
            prefix.insert(prefix.begin() + i + 1, '-');
            prefix.insert(prefix.begin() + i + 2, '>');
        }
    }
    
    prefix.erase(prefix.begin());
    return prefix;
}

double scanNum(char ch) {
    float value;
    value = ch;
    return int(value - '0');
}

int operationpost(bool a, bool b, char op) {
    if (op == '&')
    {
        if (a == 1 && b == 1) return 1;
        return 0;
    }
    else if (op == '|') {
        if (a == 0 && b == 0) return 0;
        return 1;
    }

    else if (op == '-') {
        if (b == 1 && a == 0)
            return 0;
        else return 1;
    }

    else if (op == '<') {
        if (a == b) return 1;
        return 0;
    }
    else if (op == '~') {
        if (a == b) return 1;
        return 0;
    }
    return -100;
}

int operationpre(bool a, bool b, char op) {
    if (op == '&')
    {
        if (a == 1 && b == 1) return 1;
        return 0;
    }
    else if (op == '|') {
        if (a == 0 && b == 0) return 0;
        return 1;
    }

    else if (op == '-') {
        if (b == 0 && a == 1)
            return 0;
        else return 1;
    }

    else if (op == '<') {
        if (a == b) return 1;
        return 0;
    }
    else if (op == '~') {
        if (a == b) return 1;
        return 0;
    }
    return -100;
}

string postEvallogic(string input) {
    for (size_t i = 1; i < input.length(); i++) {
        if (input[i] == '~') {
            input.insert(input.begin() + i, '0');
            i++;
        }
    }
    stack<bool> stk;
    bool result;
    string::iterator it;
    bool a, b;
    for (it = input.begin(); it != input.end(); it++) {
        //read elements and perform input evaluation
        if (isOperatorlogic(*it) != 0) {
            a = stk.top();
            stk.pop();
            b = stk.top();
            stk.pop();
            stk.push(operationpost(a, b, *it));
        }
        else if (isOperandlogic(*it) > 0) {
            stk.push(scanNum(*it));
        }
    }
    result = stk.top();
    if (result) return "TRUE";
    return "FALSE";
}

string preEvallogic(string input) {
    for (size_t i = 0; i < input.length()-1; i++) {
        if (input[i] == '~') {
            input.insert(input.begin() + i+1, '0');
        }
    }
    input.insert(input.begin(), ' ');
    stack<bool> stk;
    bool result;
    string::iterator it;
    bool a, b;
    for (it = input.end()-1; it != input.begin(); it--) {
        //read elements and perform input evaluation
        if (isOperatorlogic(*it) != 0) {
            a = stk.top();
            stk.pop();
            b = stk.top();
            stk.pop();
            stk.push(operationpre(a, b, *it));
        }
        else if (isOperandlogic(*it) > 0) {
            stk.push(scanNum(*it));
        }
    }
    result = stk.top();
    if (result) return "TRUE";
    return "FALSE";
}

string LogicPostfixPrefixCalculator(string input, string varlue) {
    int N = input.length() - 1;
    for (int i = 0; i < N; i++) {
        if (input[i] == ' ' && input[i + 1] == ' ') {
            input.erase(input.begin() + i);
            i--;
            N--;
        }
    }
    if (input[0] == ' ') input.erase(input.begin());
    if (input[input.length() - 1] == ' ') input.erase(input.begin() + input.length() - 1);
    for (size_t i = 0; i < input.length() - 2; i++) {
        if (input[i] == '<' && input[i + 1] == '-' && input[i + 2] == '>') {
            input.erase(input.begin() + i + 1);
            input.erase(input.begin() + i + 1);
        }
    }
    for (size_t i = 0; i < input.length() - 1; i++) {
        if (input[i] == '-' && input[i + 1] == '>') input.erase(input.begin() + i + 1);
    }

    int count1 = 0;
    while ((varlue[count1] < '0') || (varlue[count1] > '9')) count1++;


    for (size_t i = 0; i < input.length(); i++) {
        int count2 = 0;
        while (count2 < count1) {
            if (input[i] == varlue[count2]) input[i] = varlue[count1 + count2];
            count2 += 2;
        }
    }
    if (input[0] >= '0' && input[0] <= '9') return postEvallogic(input);
    else return preEvallogic(input);
}
