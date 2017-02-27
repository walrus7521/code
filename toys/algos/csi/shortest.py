#!/usr/bin/python

from collections import deque

routes = {}
routes[1] = [2,4]
routes[2] = [3]
routes[3] = [7]
routes[4] = [5,6]
routes[5] = [3]
routes[6] = [3]
routes[7] = []

def find_goal(node, goal):
    return node == goal

def shortest(g, start, end):
    search_queue = deque()
    search_queue += g[start]
    searched = []
    rent = start
    parent = [0 for x in range(12)]
    for i in range(12):
        parent[i] = -1
    while search_queue:
        item = search_queue.popleft()
        print "item: {}".format(item)
        if not item in searched: # register all parent/child
            for n in g[item]:
                if not n in searched:
                    parent[n] = item;
        search_queue += g[item]
        searched.append(item)
    return parent

def find_path(parent, start, end):
    #print "find_path({},{})".format(start, end)
    if ((start == end) or (end == -1)):
        print "start: {}".format(start)
    else:
        find_path(parent, start, parent[end])
        print " {},".format(end)
    
s = shortest(routes, 1, 7)
find_path(s, 1, 7)


