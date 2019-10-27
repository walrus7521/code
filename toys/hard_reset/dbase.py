#!/usr/bin/env python3

import sqlite3
import os

def connect(filename):
    create = not os.path.exists(filename)
    conn = sqlite3.connect(filename)
    cursor = conn.cursor()
    for line in conn.iterdump():
        print(line)
    print("exec")
    cursor.execute("SELECT * FROM COMPANY")
    tuple_list  = cursor.fetchall()
    for line in tuple_list:
        print(line)
    return
    if conn:
        cursor = conn.cursor()
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table'")        
        tuple_list  = cursor.fetchall()
        #print(tuple_list)
        #names = [col[0] for col in cursor.description]        
        for item in tuple_list:
            print(item)
            #for key in row:
            #    print(key, '->', row[key])
            #print(dict(row))
        #for row in cursor:
            #for name, value in zip(names, row):
    else:
        print("unable to connect\n");

def main():
    connect("test.db")

if __name__ == '__main__':
    main()

