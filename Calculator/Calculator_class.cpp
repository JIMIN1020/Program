#include "Calculator_class.hpp"

// 클래스 생성자
Calculator::Calculator(string exp)
{
    expression = exp;
    postfix = ' ';
}

// 연산자인지 확인하는 함수
bool Calculator::is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/') return true;
    else return false;
}

// 숫자인지 확인하는 함수
bool Calculator::is_digit(char c)
{
    if (c >= '0' && c <= '9') return true;
    else return false;
}

// 우선순위 구하는 함수
int Calculator::get_priority(char op)
{
    switch (op)
    {
        case '(': return 0;             // 스택 내부에서는 여는 괄호의 우선순위가 가장 낮음
        case '+': case '-': return 1;
        case '*': case '/': return 2;
    }
    return -1;
}

// infix 형태의 계산식을 postfix로 전환하는 함수
void Calculator::to_postfix()
{
    // 수식의 끝까지 반복
    for (int i = 0; i < expression.size(); i++)
    {
        // 여는 괄호일 경우?
        if (expression[i] == '(')
        {
            op.push(expression[i]); // 스택에 push
        }

        // 닫는 괄호일 경우?
        else if (expression[i] == ')')
        {
            while (op.top() != '(')     // 여는 괄호가 나올 때까지 스택에 있던 값들 모두 pop해서 postfix에 저장
            {
                postfix += op.top();
                op.pop();
                postfix += ' '; // 공백으로 띄워주기
            }
            op.pop();   // 스택에 남아있는 여는 괄호 빼내기
        }

        // 숫자일 경우?
        else if (is_digit(expression[i]))
        {
            do {
                postfix += expression[i++];     // postfix에 그대로 저장하고 인덱스 값 증가시킴
            } while (is_digit(expression[i]));  // 두자리 이상의 숫자일 경우 반복해서 저장
            
            postfix += ' ';     // 다 저장한 후 공백으로 띄워주기
        }
        
        // 연산자일 경우?
        else if (is_operator(expression[i]))
        {
            // 스택 내에 있는 연산자의 우선순위가 더 크면서 스택이 비어있지 않을 때
            while (!op.empty() && get_priority(op.top()) >= get_priority(expression[i]))
            {
                postfix += op.top();    // 스택에 있는 값 모두 pop
                op.pop();
                postfix += ' ';     // 공백으로 띄워주기
            }
            // 지금 확인 중인 연산자는 push해서 스택에 저장
            op.push(expression[i]);
        }
    }

    // 수식을 모두 검사한 후 스택에 남은 값 모두 pop
    while (!op.empty())
    {
        postfix += op.top();
        op.pop();
        postfix += ' '; // 공백으로 띄워주기
    }
}

// postfix로 전환한 수식을 계산하는 함수
double Calculator::calculate()
{
    to_postfix();       // postfix로 전환하기
    double op1, op2;    // 피연산자를 저장할 변수

    for (int i = 0; i < postfix.size(); i++)
    {
        // 공백일 경우 건너뛰기
        if (postfix[i] == ' ') continue;
        
        // 숫자일 경우?
        if (is_digit(postfix[i]))
        {
            int n = 0;  // 임시로 숫자 값을 저장할 변수
            do {
                n = n * 10 + postfix[i++] - '0'; // 숫자가 일의 자릿수를 넘어갈 경우, 10을 곱한 후 다음 숫자와 더해서 두자리수를 만듦
            } while (is_digit(postfix[i]));
            
            opd.push(n);    // 최종적으로 가져온 숫자를 피연산자 스택에 push
        }
        
        // 연산자일 경우?
        else if (is_operator(postfix[i]))
        {
            // 피연산자 스택에 있던 피연산자 2개 불러오기
            op2 = opd.top();
            opd.pop();
            op1 = opd.top();
            opd.pop();
            
            // 연산자 종류에 따라 피연산자들을 계산하고 피연산자 스택에 다시 push
            switch (postfix[i])
            {
            case '+': opd.push(op1+op2); break;
            case '-': opd.push(op1-op2); break;
            case '/': opd.push(op1/op2); break;
            case '*': opd.push(op1*op2); break;
            }
        }
    }
    return opd.top();   // 마지막에 스택에 남은 결과값 리턴
}
