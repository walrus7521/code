#!/usr/bin/python

def findSmallest(arr):
    smallest = arr[0]
    smallest_index = 0
    for i in range(1, len(arr)):
        if (arr[i] < smallest):
            smallest = arr[i]
            smallest_index = i
    return smallest_index

def selectionSort(arr):
    newArr = []
    for i in range(len(arr)):
        smallest = findSmallest(arr)
        newArr.append(arr.pop(smallest))
    return newArr

# recursion
def countdown(i):
    print i
    if i <= 0:
        return
    else:
        countdown(i-1)

# stack demo
def bye():
    print "ok bye!"

def greet2(name):
    print "how are you, " + name + "?"

def greet(name):
    print "hello, " + name + "!"
    greet2(name)
    print "getting ready to say bye..."
    bye()

#stack for recursion
def fact(x):
    if x == 1:
        return 1;
    else:
        return x * fact(x-1)

def gcd(a, b):
    while b != 0:
       t = b
       b = a % b
       a = t
    return a

def rec_sum(arr):
    if (len(arr) == 0):
        return 0
    if (len(arr) == 1):
        return arr[0]
    else:
        return arr[0] + rec_sum(arr[1:])

#print selectionSort([5,3,6,2,10])
#countdown(5)
#greet("jack")
#print "fact: {}".format(fact(7))
print "gcd: {}".format(gcd(1680,640))
print "sum: {}".format(rec_sum([2,4,6]))

