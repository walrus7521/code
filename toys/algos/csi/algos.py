#!/usr/bin/python

from time import sleep

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
    if arr == []:
        return 0
    else:
        return arr[0] + rec_sum(arr[1:])

def countem(arr):
    if arr == []:
        return 0
    else:
        return 1 + countem(arr[1:])

def maxit(arr):
    if (len(arr) == 1):
        return arr[0]
    else:
        m = maxit(arr[1:])
        if (m > arr[0]):
            return m
        else:
            return arr[0]

def binsearch(arr, x):
    m = (len(arr))/2
    if (x == arr[m]):
        return m
    elif (x < arr[m]):
        binsearch(arr[:m],x)
    else:
        binsearch(arr[m:],x)

def swap(arr, i, j):
    t = arr[i]
    arr[i] = arr[j]
    arr[j] = t


def quicksort(arr):
    if (len(arr) < 2):
        return arr
    else:
        pivot = arr[0]
        less = [i for i in arr[1:] if i <= pivot]
        grtr = [i for i in arr[1:] if i > pivot]
        return quicksort(less) + [pivot] + quicksort(grtr)
    return arr

def print_items(list):
    for item in list:
        #sleep(1)
        print item

from collections import deque

graph = {}
graph["you"]    = ["alice", "bob", "claire"]
graph["bob"]    = ["anuj", "peggy"]
graph["alice"]  = ["peggy"]
graph["claire"] = ["thom", "jonny"]
graph["anuj"]   = [""]
graph["peggy"]  = [""]
graph["thom"]   = [""]
graph["jonny"]  = [""]

graph2 = {}
graph2["wake up"] = [""]
graph2["shower"] = ["wake up"]
graph2["brush teeth"] = ["wake up"]
graph2["eat breakfast"] = ["brush teeth"]

def activity_is_wakey(activity):
    print "activity: " + activity
    return activity == "wake up"

def person_is_seller(name):
    print "person seller? " + name
    return name[-1] == 'm' # silly, use last letter as flag for mango dealer

def graph_search(g, start, condition, notice):
    search_queue = deque()
    search_queue += g[start]
    searched = []
    while search_queue:
        item = search_queue.popleft()
        if not item in searched:
            if condition(item):
                print item + notice
                return True
            else:
                search_queue += g[item]
                searched.append(item)
    return False

def top_sort(graph_unsorted):
    graph_sorted = []
    # convert unsorted graph to hash table
    print graph_unsorted
    graph_unsorted = dict(graph_unsorted)
    print graph_unsorted
    while graph_unsorted:
        acyclic = False
        for node, edges in list(graph_unsorted.items()):
            for edge in edges:
                if edge in graph_unsorted:
                    break
            else:
                acyclic = True
            del graph_unsorted[node]
            graph_sorted.append((node, edges))
        if not acyclic:
            print "error, cyclic"
    return graph_sorted


#print selectionSort([5,3,6,2,10])
#countdown(5)
#greet("jack")
#print "fact: {}".format(fact(7))
#print "gcd: {}".format(gcd(1680,640))
#print "sum: {}".format(rec_sum([2,4,6]))
#print "countem: {}".format(countem([2,4,6,3,1,9,1]))
#print "maxit: {}".format(maxit([2,4,6,3,42,1,9,1]))
#print "binsearch: {}".format(binsearch([2,3,4,9,42,99,132,763,1023],42))
#print "quicksort: {}".format(quicksort([33,15,10,42,99,6]))
#print_items([33,15,42,199])
                
#graph_search(graph, "you", person_is_seller, " => is a mango seller")
#graph_search(graph2, "eat breakfast", activity_is_wakey, " => is wakey")
tsort = top_sort(graph2)
for i in tsort:
    print i

