#!/usr/bin/env python3

THRESHOLD = 1e-16

def newton_sequence(f, f_derivative, starting_x, threshold=THRESHOLD):
    x = starting_x
    function_at_x = f(x)
    while abs(function_at_x - x) > THRESHOLD:
        yield x
        x -= function_at_x / f_derivative(x)
        function_at_x = f(x)
    
def f(x):
    return x**5 - x - 1

def f_derivative(x):
    return 5 * x**4 - 1

starting_x = 1
approximation = []
i = 0
for x in newton_sequence(f, f_derivative, starting_x):
    print((x, f(x)))
    i += 1
    if i == 100:
        break
