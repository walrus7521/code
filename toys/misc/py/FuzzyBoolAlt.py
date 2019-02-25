#!/usr/bin/env python3


class FuzzyBool(float): # subclass of float

    def __new__(cls, value=0.0):
        return super().__new__(cls,
                value if 0.0 <= value <= 1.0 else 0.0)

    def __invert__(self):
        return FuzzyBool(1.0 - float(self))

    def __and__(self, other):
        return FuzzyBool(min(self, other))

    def __iand__(self, other):
        return FuzzyBool(min(self, other))

    def __or__(self, other):
        return FuzzyBool(max(self, other))

    def __ior__(self, other):
        return FuzzyBool(max(self, other))

    def __repr__(self):
        return ("{0}({1})".format(self.__class__.__name__,
                                  super().__repr__()))

    def __bool__(self):
        return self > 0.5

    def __int__(self):
        return round(self)

    # unimplement some methods that don't make sense
    def __add__(self, other):
        raise NotImplementedError()

    def __neg__(self):
        raise TypeError("bad operand type for unary -: '{0}'".format(
                    self.__class__.__name__))

    # unimplement ==
    def __eq__(self, other):
        return NotImplemented






def conjunction(*fuzzies):
    return FuzzyBool(min(fuzzies))

def disjunction(*fuzzies):
    return FuzzyBool(max(fuzzies))


def main():
    a = FuzzyBool(0.875)
    print(a)
#   print(~a)
#   print(float(a))
#   print(repr(a))

if __name__ == "__main__":
    main()

    
