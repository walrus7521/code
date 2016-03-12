#include <iostream>

using namespace std;

/*
 * Exercise 2
 * Your college book store needs your help in estimating its business 
 * for next year. Experience has shown that sales depend greatly on whether 
 * a book is required for a course or just optional, and whether or not it 
 * has been used in the class before. A new, required textbook will sell 
 * to 90% of prospective enrollment, but if it has been used in the class 
 * before, only 65% will buy. Similarly, 40% of prospective enrollment will 
 * buy a new, optional textbook, but if it has been used in the class before 
 * only 20% will buy. (Note that "used" here does not mean second-hand books.)
 * * Write a program that accepts as input a series of books (until the user 
 * enters a sentinel). For each book ask for: a code for the book, the single 
 * copy cost for the book, the current number of books on hand, the prospective 
 * class enrollment, and data that indicates if the book is required/optional, 
 * new/used in past. As output, show all the input information in a nicely 
 * formatted screen along with how many books must be ordered (if any, note 
 * that only new books are ordered), the total cost of each order.
 * 
 * Then, after all input is complete, show the total cost of all book orders, 
 * and the expected profit if the store pays 80% of list price. Since we have 
 * not yet discussed any ways of dealing with a large set of data coming into 
 * a program (stay tuned!), just process one book at a time and show the output 
 * screen for that book. Then, when the user has finished entering all the data, 
 * your program should output the total and profit values.
 * 
 * Before you start writing code, take some time to think about design of this 
 * program. Decompose into a set of functions, and create a main() function that 
 * reads like an outline for your solution to the problem. Make sure each function 
 * does one task.
 * 
 * Here is sample output:
 * 
 * Please enter the book code: 1221
 *  single copy price: 69.95
 *  number on hand: 30
 *  prospective enrollment: 150
 *  1 for reqd/0 for optional: 1
 *  1 for new/0 for used: 0
 * ***************************************************
 * Book: 1221
 * Price: $69.95
 * Inventory: 30
 * Enrollment: 150
 * 
 * This book is required and used.
 * ***************************************************
 * Need to order: 67
 * Total Cost: $4686.65
 * ***************************************************
 * 
 * Enter 1 to do another book, 0 to stop. 0
 * ***************************************************
 * Total for all orders: $4686.65
 * Profit: $937.33
 * ***************************************************
 * 
 */

int main()
{
}

