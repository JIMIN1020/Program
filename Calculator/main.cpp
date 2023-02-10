// 2022.02.10
// 계산기 프로그램 (with stack)
// 두자리수 이상 계산 가능, 실수 표현, 우선 순위 적용, 괄호 포함

#include "Calculator_class.hpp"

int main(void)
{
    string exp;
    getline(cin, exp);
    
    Calculator cal(exp);
    cout << exp << " = " << cal.calculate() << "\n";
}
