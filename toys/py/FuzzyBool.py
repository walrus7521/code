#!/usr/bin/env python3

class FuzzyBool:

    def __init__(self, value=0.0):
        print("init")
        self.__value = value if 0.0 <= value <= 1.0 else 0.0

    # ~ operator
    def __invert__(self):
        print("invert")
        return FuzzyBool(1.0 - self.__value)

    # & operator
    def __and__(self, other):
        print("and")
        return FuzzyBool(min(self.__value, other.__value))

    # bitwise AND
    def __iand__(self, other):
        print("iand")
        self.__value = min(self.__value, other.__value)

    def __or__(self, other):
        print("or")
        return FuzzyBool(max(self.__value, other.__value))

    def __ior__(self, other):
        print("ior")
        return max(self.__value, other.__value)

    def __repr__(self):
        print("repr")
        return ("{0}({1})".format(self.__class__.__name__,
                                  self.__value))
    def __str__(self):
        print("str")
        return str(self.__value)

    def __bool__(self):
        print("bool")
        return self.__value > 0.5

    def __int__(self):
        print("int")
        return round(self.__value)

    def __float__(self):
        print("float")
        return self.__value

    # (<, <=, ==, !=, >=, >)
    def __lt__(self, other):
        print("lt")
        return self.__value < other.__value

    def __eq__(self, other):
        print("eq")
        return self.__value == other.__value

    def __hash__(self):
        print("hash")
        return hash(id(self))

    def __format__(self, format_spec):
        print("format")
        return format(self.__value, format_spec)

    @staticmethod
    def conjunction(*fuzzies):
        """ returns the logical AND of all the FuzzyBools """
        return FuzzyBool(min([float(x) for x in fuzzies]))

    @staticmethod
    def disjunction(*fuzzies):
        """ returns the logical OR of all the FuzzyBools """
        return FuzzyBool(max([float(x) for x in fuzzies]))



def main():
    a = FuzzyBool(0.875)
    print(~a)
    print(float(a))
    print(repr(a))

if __name__ == "__main__":
    main()


