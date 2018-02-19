#!/usr/bin/python


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

def main():
    my_arr = [1,3,5,7,9]
    print binary_search(my_arr, 3)
    print binary_search(my_arr, -1)
    print my_arr[find_smallest(my_arr)]
    print selection_sort([5,3,6,2,10])


if __name__ == '__main__':
    main()

