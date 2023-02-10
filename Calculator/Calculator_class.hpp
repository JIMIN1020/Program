#ifndef Calculator_class_hpp
#define Calculator_class_hpp

#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Calculator
{
private:
    stack <int> op;         // 연산자용 스택
    stack <double> opd;     // 피연산자용 스택
    string expression;      // 사용자 입력 수식을 담을 string
    string postfix;         // 계산용 postfix 식을 담을 string
public:
    Calculator(string exp);     // 클래스 생성자
    bool is_operator(char c);   // 연산자인지 확인하는 함수
    bool is_digit(char c);      // 숫자인지 확인하는 함수
    int get_priority(char op);  // 우선순위 구하는 함수
    void to_postfix();          // infix 형태의 계산식을 postfix로 전환하는 함수
    double calculate();         // postfix로 전환한 수식을 계산하는 함수
};

#endif /* Calculator_class_hpp */
