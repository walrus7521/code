#!/usr/bin/python

import platform
import time
import sys
import re

class graph:
    def __init__(self, filename):
        self.filename = filename
        class_name = self.__class__.__name__
        print class_name, "created =>", self.filename
        self.MAXV = 101
        self.MAXDEGREE= 50
        self.edges = [[0 for x in xrange(self.MAXV)] for x in xrange(self.MAXDEGREE)]
        self.degree = [0]*self.MAXV
        self.processed = [0]*self.MAXV
        self.discovered = [0]*self.MAXV
        self.parent = [0]*self.MAXV
        self.nvertices = 0
        self.nedges = 0
        self.finished = 0

    def __del__(self):
        class_name = self.__class__.__name__
        print class_name, "destroyed"

    def read_graph(self, directed):
        self.initialize_graph()
        f = open(self.filename, 'rU');
        self.nvertices, m = map(int, f.readline().split())
        class_name = self.__class__.__name__
        print class_name, "read_graph : nvertices", self.nvertices, ", edges", m
        tmp = []
        for i, line in enumerate(f):
            x, y = line.split()
            m = int(x, 10)
            n = int(y, 10)
            self.insert_edge(m, n, directed)

    def initialize_graph(self):
        class_name = self.__class__.__name__
        print class_name, "initialize_graph"
        self.nvertices = 0
        self.nedges = 0
        for i in range(101):
            self.degree[i] = 0

    def initialize_search(self):
        class_name = self.__class__.__name__
        print class_name, "initialize_search"

    def insert_edge(self, x, y, directed):
        class_name = self.__class__.__name__
        print class_name, "insert_edge (", x, ",", y, ")"
        if (self.degree[x] > self.MAXDEGREE):
            print "warning, out of range"
        self.edges[x][self.degree[x]] = y
        self.degree[x] = self.degree[x] + 1;
        if (directed == 0):
            self.insert_edge(y, x, 1)
        else:
            self.nedges = self.nedges + 1


    def print_graph(self):
        class_name = self.__class__.__name__
        print class_name, "print_graph"
        for i in range(self.nvertices):
            str = "%d:" % i
            sys.stdout.write(str)
            for j in range(self.degree[i]):
                str = " %d" % self.edges[i][j]
                sys.stdout.write(str)
            print

    def find_path(self, start, end, parents):
        class_name = self.__class__.__name__
        print class_name, "find_path"
    def valid_edge(self, v):
        class_name = self.__class__.__name__
        print class_name, "valid_edge"
    def process_vertex(self, v):
        class_name = self.__class__.__name__
        print class_name, "process_vertex"


def main():
    graph_file = "graph3";
    g = graph(graph_file);
    g.read_graph(1);
    g.print_graph();

main()

