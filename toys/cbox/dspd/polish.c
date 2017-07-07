#include <stdio.h>

Value EvaluatePrefix(Expression expr)
{
    Token token;
    Value x, y;
    GetToken(token, expr);
    switch (Kind(token)) {
        case OPERAND:
            return GetValue(token);
        case UNARYOP:
            x = EvaluatePrefix(expr);
            return DoUnary(token, x);
        case BINARYOP:
            x = EvaluatePrefix(expr);
            y = EvaluatePrefix(expr);
            return DoBinary(token, x, y);
    }
}
