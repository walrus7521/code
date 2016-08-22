#!/usr/bin/python

# http://www.tutorialspoint.com/sqlite/sqlite_python.htm

import sqlite3

def open():
    conn = sqlite3.connect('test.db')
    print "Opened database successfully";
    return conn
    
def create(conn):
    conn.execute('''CREATE TABLE COMPANY
           (ID INT PRIMARY KEY     NOT NULL,
           NAME           TEXT    NOT NULL,
           AGE            INT     NOT NULL,
           ADDRESS        CHAR(50),
           SALARY         REAL);''')
    print "Table created successfully";

def close(conn):
    conn.close() 

def insert(conn, id, name, age, address, salary):
#    sql = format("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
#                VALUES (2, 'Allen', 25, 'Texas', 15000.00 )");
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) VALUES ({0}, {1}, {2}, {3}, {4})".format(id, name, age, address, salary);
    print sql
#    conn.execute(sql);

#conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
#      VALUES (2, 'Allen', 25, 'Texas', 15000.00 )");
#
#conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
#      VALUES (3, 'Teddy', 23, 'Norway', 20000.00 )");
#
#conn.execute("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) \
#      VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 )");

def select(conn):
    cursor = conn.execute("SELECT id, name, address, salary  from COMPANY")
    for row in cursor:
        print "ID = ", row[0]
        print "NAME = ", row[1]
        print "ADDRESS = ", row[2]
        print "SALARY = ", row[3], "\n"
    print "Operation done successfully";
    conn.commit()


def main():
    conn = open()
    #create(conn)
    insert(conn, 1, 'Paul', 32, 'California', 20000.00)
    select(conn)

    close(conn)


main()

