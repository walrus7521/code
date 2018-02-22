#!/usr/bin/python

# Selection sort: O(n^2)
def find_smallest(arr):
    smallest = arr[0]
    smallest_index = 0
    for i in range (1, len(arr)):
        if arr[i] < smallest:
            smallest = arr[i]
            smallest_index = i
    return smallest_index

def selection_sort(arr):
    new_arr = []
    for i in range (len(arr)):
        smallest = find_smallest(arr)
        new_arr.append(arr.pop(smallest))
    return new_arr

#
# divide-and-conquer (recursive technique)
#
# start with binary search
#

def binary_search(arr, item):
    low = 0
    high = len(arr) - 1

    while (low <= high):
        mid = (low + high)/2
        guess = arr[mid]
        if guess == item:
            return mid
        if guess > item:
            high = mid - 1
        else:
            low = mid + 1

    return None


# recursion
#
def countdown(i):
    print i
    if i > 0:
        countdown(i-1)

# dividing land into square plots - euclid's algorithm
# base case: one side is a multiple of the other
# recursive case: divide smallest into largest, remainder is new rectangle
# rect is an array where [0] is one side and [1] the other
def make_plots(rect):
    remainder = 0
    shortest = 0
    if (rect[0] > rect[1]):
        shortest = rect[1]
        remainder = rect[0] % rect[1]
    else:
        shortest = rect[0]
        remainder = rect[1] % rect[0]
    if (remainder == 0):
        return
    else:
        rect[0] = shortest
        rect[1] = remainder
        make_plots(rect)    


# summing numbers using D&C
# base case: 
#       if array size == 0 return 0
# recursion case:
#       
def sum(arr):
    if len(arr) == 0:
        return 0
    else:
        return arr[0] + sum(arr[1:])
    None

# next: quicksort
# base case: len(array) < 2 => return array
# recursion case: partition and recurse
def quicksort(arr):
    if len(arr) < 2:
        return arr
    pivot = arr[0]
    less = [i for i in arr[1:] if i <= pivot]
    greater = [i for i in arr[1:] if i > pivot]
    return quicksort(less) + [pivot] + quicksort(greater)

# mergesort


# hash tables
cache = {}
def get_page(url):
    if cache.get(url):
        return cache[url]
    else:
        data = len(url)
        cache[url] = data
        return data

# model a network using a graph
# find the shortest (fewest number of unweighted nodes) paths/route using BFS
# directed/undirected
# topological sort which exposes node dependencies
def person_is_seller(name):
    return name[-1] == 'm' # last letter

from collections import deque
def bfs(graph):
    search_queue = deque()
    search_queue += graph["you"]
    while search_queue:
        person = search_queue.popleft()
        if person_is_seller(person):
            print person + " is a mango seller"
            search_queue += graph[person]       


def main():
    plot = [1680, 640]
    make_plots(plot)
    print plot[1], plot[1]
    #return
    my_arr = [1,3,5,7,9]
    print binary_search(my_arr, 3)
    print binary_search(my_arr, -1)
    print my_arr[find_smallest(my_arr)]
    print selection_sort([5,3,6,2,10])
    print quicksort([42,3,16,23,-10])
    countdown(7)
    print sum(my_arr)
    print get_page("www.microsoft.com")

    graph = {}
    graph["you"] = ["alice","bob","claire","hokym"]
    graph["bob"] = ["anuj","peggy","mooky"]
    graph["alice"] = ["peggy"]
    graph["claire"] = ["thom","jonny"]
    graph["anuj"] = []
    graph["hokym"] = []
    graph["jonny"] = []
    graph["peggy"] = []
    graph["thom"] = []
    bfs(graph)

if __name__ == '__main__':
    main()

