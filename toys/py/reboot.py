#!/usr/bin/env python3

import dis # disassemble byte code

def raw_iter():
    seq3 = ['python', '3']
    iterator = iter(seq3)

    while True:
        try:
            x = iterator.__next__()
            print(x)
        except StopIteration as e:
            print(e)
            break

    def loop(seq):
        for x in seq:
            print(x)

    dis.dis(loop) # disassemble

class Counter: # uses iterator not iterable so exhausts
    def __init__(self, size):
        self.size = size
        self.start = 0
        #print("called __init__1", self.size)
    def __iter__(self):
        #print("called __iter__1", self.size)
        return self
    def __next__(self):
        #print("called __next__1", self.size)
        if self.start < self.size:
            self.start += 1
            return self.start
        raise StopIteration

CounterIterator = Counter
class Counter2: # uses iterable so does not exhaust
    def __init__(self, size):
        self.size = size
        self.start = 0
        #print("called __init__2", self.size)
    def __iter__(self):
        #print("called __iter__2", self.size)
        return CounterIterator(self.size)

def test_counter():
    """
    c = Counter(3)
    r_iter = iter(c)
    while True:
        try:
            x = r_iter.__next__()
            print(x)
        except StopIteration as e:
            break
    # c is exhausted at this point
    for n in c:
        print(n)

    print("use iterable")
    c2 = Counter2(2)
    for n in c2:
        for m in c2: # gets fresh iterable each n
            print(n,m)
    # test for self-iterators vs iterable
    """
    print("test for iterable")
    c1 = Counter(2)
    c2 = Counter2(2)
    print(list(c2))
    print(list(c2))
    print(list(c1))
    print(list(c1)) # exhausted


def main():
    test_counter()
    #raw_iter()


if __name__ == '__main__':
    main()

