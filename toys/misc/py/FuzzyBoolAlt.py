#!/usr/bin/env python3


class FuzzyBool(float): # subclass of float


def conjunction(*fuzzies):
    return FuzzyBool(min(fuzzies))

def disjunction(*fuzzies):
    return FuzzyBool(max(fuzzies))


