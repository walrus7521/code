#!/usr/bin/python

import sqlite3

# https://www.tutorialspoint.com/sqlite/sqlite_python.htm


conn = sqlite3.connect('test2.db')
print "Opened database successfully";

def make_table():
    conn.execute('''CREATE TABLE COMPANY
             (ID INT PRIMARY KEY     NOT NULL,
             NAME           TEXT    NOT NULL,
             AGE            INT     NOT NULL,
             ADDRESS        CHAR(50),
             SALARY         REAL);''')
    print "Table created successfully";
    conn.close()

def populate():
    conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
          VALUES (1, 'Paul', 32, 'California', 20000.00 )");

    conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
          VALUES (2, 'Allen', 25, 'Texas', 15000.00 )");

    conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
          VALUES (3, 'Teddy', 23, 'Norway', 20000.00 )");

    conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
          VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 )");

    conn.commit()
    print "Records created successfully";
    conn.close()

def show():
    cursor = conn.execute("SELECT id, name, address, salary from COMPANY")
    for row in cursor:
       print "ID = ", row[0]
       print "NAME = ", row[1]
       print "ADDRESS = ", row[2]
       print "SALARY = ", row[3], "\n"

    print "Operation done successfully";
    conn.close()    

#make_table()
#populate()
show()

