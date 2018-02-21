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
# base case:
# recursion case:


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
    countdown(7)
    print sum(my_arr)


if __name__ == '__main__':
    main()

