#!/usr/bin/env python

# Sample input:

# First line has two integers N, denoting the number of nodes 
# in the graph and M, denoting the number of edges in the graph.
# The next M lines each consist of three space separated integers 
# x y r, where x and y denote the two nodes between which the 
# undirected edge exists, r denotes the weight of edge between 
# the corresponding nodes.

# 4 6
# 1 2 5
# 1 3 3
# 4 1 6
# 2 4 7
# 3 2 4
# 3 4 5

# Sample output: 12

# w:3, u:1, v:3, p_v:3, p_u:1
#  => add w:3, p_v:3, p_u:1
# :4, u:3, v:2, p_v:2, p_u:1
#  => add w:4, p_v:2, p_u:1
# :5, u:1, v:2, p_v:1, p_u:1
# :5, u:3, v:4, p_v:4, p_u:1
#  => add w:5, p_v:4, p_u:1
# :6, u:4, v:1, p_v:1, p_u:1
# :7, u:2, v:4, p_v:1, p_u:1

import Queue

def find(v):
    if rep[v] == v:
        return v
    rep[v] = find(rep[v])
    return rep[v]

n,m = map(int, raw_input().split())
pq = Queue.PriorityQueue()
rep = {}
for _ in xrange(m):
    x,y,r = map(int, raw_input().split())
    pq.put((r, (x,y)))
    if x not in rep:
        rep[x] = x
    if y not in rep:
        rep[y] = y

# dump rep
#print rep
#print (pq.queue)

res = 0
while pq.qsize() > 0:
    a = pq.get() # get min
    r = a[0]
    u, v = a[1]
    p_v, p_u = find(v), find(u)
    print 'w:%d, u:%d, v:%d, p_v:%d, p_u:%d' %  (r, u, v, p_v, p_u)
    if p_v != p_u:
        print '  => add w:%d, p_v:%d, p_u:%d' %  (r, p_v, p_u)
        res += r
        rep[p_v] = p_u
    else:
        print '  => no add p_u == p_v'

print res
