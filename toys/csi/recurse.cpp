#include <iostream>
#include <vector>
#include <climits>
#include <cstdio>
#include <cstring>
#include <cstdlib>

// kinds of recursion: linear, tail, binary, nested, and mutual.
// linear: makes single call per function to itself
//      e.g. factorial, sqrt using Newton method

// tail: when recursive call is the last statement of the function,
//       often the return statement.  Should be replaced by iterative.
//      e.g. gcd

// binary: makes 2 or more calls to self per call
//      e.g. math combinations: choose

// exponential: exponential calls relative to size of data set, f(n) => a^n calls.
//      e.g. permutation of data set: print_permutations

// nested: one argument to function is the function itself
//      e.g. ackerman's function

// mutual: function A calls B, which calls C, which calls A
//      e.g. even_or_odd 

// restart at: http://www.sparknotes.com/cs/recursion/whatisrecursion/problems_1.html
// Problem : What category would the following function fit into? How many function 
//           calls will there be in total if the function is called with func(10)?

// catalog:
//  fib
//  fac
//  num_sums
//  sqrt
//  gcd
//  choose
//  permutations
//  ackerman
//  even/odd
//  mystery
//  tree node
//  pow
//  reverse string
//  zip arrays
//  find max
//  string match
//  sum nums
//  sort

using namespace std;

#define swap(a,b) { \
    int tmp = a; \
    tmp = a; \
    a = b; \
    b = tmp; \
}

// iterative: broken
int fibi(int x)
{
    int a = 1;
    int b = 1;
    for (int i = 2; i < x; i++) {
        a = a + b;
        swap(a,b);
    }
    return b;
}

// results in exponential number of calls.
int fibr(int x)
{
    if (x < 2)
        return 1;

    return fibr(x-1) + fibr(x-2);
}

#define N 256 // max value in call chain
// Recursion with DP:
int fibd(int x)
{
    static vector<int> cache(N, -1); // oh yeah!!

    int result = cache[x];

    if (result == -1) {
        // not in cache
        if (x < 2) {
            result = 1;
        } else {
            result = fibd(x-1) + fibd(x-2);
        }
        cache[x] = result;
        cout << "miss: cache[" << x << "] = " << result << endl;
    } else {// else skip due to cache !!!
        cout << "hit:  cache[" << x << "] = " << result << endl;
    }
    return result;
}

// iterative
int faci(int n)
{
    int fact = 1;
    if (n < 0) return 0;
    while (n > 0) {
        fact *= n; // n! = n*(n - 1)!
        --n;
    }
    return fact;
}

// recursive
int facr(int n)
{
    if (n < 0) return 0;
    if (n <= 1) return 1;
    return n * facr(n-1); // n! = n*(n - 1)!
}

void test_fib()
{
    int x = 7;
    int y = 4, z = 2;
    cout << "y: " << y << ", z: " << z << endl;
    swap(y,z);
    cout << "y: " << y << ", z: " << z << endl;

    cout << "fibi(" << x << ") = " << fibi(x) << endl;
    cout << "fibr(" << x << ") = " << fibr(x) << endl;
    cout << "fibd(" << x << ") = " << fibd(x) << endl;
}

string reverse(string line)
{
    cout << "r: " << line << endl;
    if (line == "") return "";
    return reverse(line.substr(1)) + line[0];
}

#if 1
struct list {
    struct list *next;
    int x;
};

list *reverse_list_i(list *head)
{
    list *p = head->next;
    list *q;
    list *r = nullptr;
    while (p) {
        q = p->next;
        p->next = r;
        r = p;
        p = q;
    }
    return r;
}


list *reverse_list_r(list *head)
{
    list *r = nullptr;
    list *p = head->next;
    if (p == NULL) return r;
    list *q = p->next;
    p->next = r;
    r = p;
    p = q;
    return reverse_list_r(p); // + p;
}

void test_reverse_list()
{
    int ii[] = {42,12,9,7,2};
    list head = { .next = nullptr, .x = 42 };
    for (i = 0; i < 5; i++) {
        List_push(&head, ii[i]);
    }
    List_show(&head);
    head.next = List_reverse(&head);
    List_show(&head);
    while (!List_empty(&head)) {
        cout << "pop: " << List_pop(&head) << endl;
    }


}

#endif

// iterative
int sum_nums_i(int low, int high)
{
	int i, total=0;
	for(i=low; i<=high; i++) total+=i;
	return total;
}
// recursive
int sum_nums_r(int low, int high)
{
	if (low == high) return high;
	else return low + sum_nums_r(low+1, high);
}

// closed form
int sum_nums_c(int low, int high)
{
	return (((high*(high+1))/2) - (((low-1)*low)/2));
}

// broken
#define EPSILON (1.0e-16)
double sqrt_newton(double x, double a)
{
	double difference = a*x-x;
	if (difference < 0.0) difference = -difference;
	if (difference < EPSILON) return(a);
	else return(sqrt_newton(x,(a+x/a)/2.0));
}

// tail recursive - last statement should be replaced by iterative
int gcd(int m, int n)
{ 
	int r; 
	
	if (m < n) return gcd(n,m);

	r = m%n;
	if (r == 0) return(n);
	else return(gcd(n,r));
}

// binary recursive
// binomial coeff: n choose k => num combinations (order independent)
int choose(int n, int k)
{
    if (k == 0 || n == k) return(1);
    else return(choose(n-1,k) + choose(n-1,k-1));
}

void print_array(int arr[], int n)
{
	int i;
	for(i=0; i<n; ++i) printf("%d ", arr[i]);
	printf("\n");
}

void print_permutations(int arr[], int n, int i)
{
	int j, swap;
	print_array(arr, n);
	for(j=i+1; j<n; ++j) {
		swap = arr[i]; arr[i] = arr[j]; arr[j] = swap;
		print_permutations(arr, n, i+1);
		swap = arr[i]; arr[i] = arr[j]; arr[j] = swap;
	}
}

// nested recursion
int ackerman(int m, int n)
{ 
	if (m == 0) return(n+1);
	else if (n == 0) return(ackerman(m-1,1));
	else return(ackerman(m-1,ackerman(m,n-1)));
}

// mutual recursion
int is_odd(unsigned int n);
int is_even(unsigned int n)
{
    if (n==0) return 1;
    else return(is_odd(n-1));
}

int is_odd(unsigned int n)
{
    return (!is_even(n));
}

// what does this do?
int mystery(int a, int b) 
{
	if (b==1) return a; 
	else return a + mystery(a, b-1); 
}

struct tree_node_t {
    struct tree_node_t *parent;
    char name[16];
};

// see if a tree node is part of a tree whose root
// has a specified name = x
// linear and tail recursive
int root_named_x(tree_node_t *node, char* x)
{
	if (strcmp(node->name, x) == 0) return 1;
	else if (node->parent == NULL) return 0;
	else return root_named_x(node->parent, x);
}

// convert tail recursive to iterative
int powr(int a, int b)
{
	if (b==1) return a;
	else return a * powr(a, b-1);
}

int powi(int a, int b)
{
    int total = 1;
	if (b==1) return a;
    else {
        while (b > 0) {
            total *= a;
            --b;
        }
    }
    return total;
	//else return a * pow(a, b-1);
}

void test_reverse()
{
    string s = "hello";
    cout << s.substr(0) << endl;
    cout << s.substr(1) + s[0] << endl;
    cout << s.substr(2) + s[1] + s[0] << endl;
    cout << s.substr(3) + s[2] + s[1] + s[0]  << endl;
    cout << s.substr(4) + s[3] + s[2] + s[1] + s[0] << endl;
    cout << reverse(s) << endl;
}

template <typename T>
void show_zip(T zz[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        cout << "zz[" << i << "] = " << zz[i] << endl;
    }
}

// iterative
int *zipi(int a[], int b[], int len)
{
    int i;
    int *c = (int *) calloc(2*len, sizeof(int));
    for (i = 0; i < len; i++) {
        c[2*i]   = a[i];
        c[2*i+1] = b[i];
    }
    return c;
}

// recursive
int z[256] = {0};
void zipr(int a[], int b[], int i, int len)
{
    if (len == 0) return;
    z[2*i] = a[i];
    z[2*i+1] = b[i];
    zipr(a, b, i+1, len-1);
}

int find_max2(int a[], int start, int len, int max_so_far)
{
    if (start == len) return max_so_far;
    int possible_max_1 = a[start];
    int possible_max_2 = find_max2(a, start+1, len, possible_max_1);
    if (possible_max_1 > possible_max_2) {
        return possible_max_1;
    } else {
        return possible_max_2;
    }
}

int find_max(int a[], int start, int len, int max_so_far)
{
    static int max_val = 0;
    int max = a[start];
    if (start == len) return max_so_far;
    if (max > max_so_far) max_val = max_so_far = max;
    cout << "find_max: " << start << "a[]: " << a[start] << ", max: " << max_so_far << endl;
    find_max(a, start+1, len, max_so_far);
    return max_val;
}

bool str_match(string s, string p)
{
    if (s == "" || p == "") return true;
    if (s[0] != p[0]) return false;
    return str_match(s.substr(1), p.substr(1));
}

void test_zip()
{
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 4, 6, 8};
    int *c;
    int len = 4;
    printf("------------- zip iterative\n");
    c = zipi(a, b, len);
    show_zip<int>(c, 2*len);

    printf("------------- now recursive\n");
    zipr(a, b, 0, len);
    show_zip<int>(z, 2*len);
    
}

int add3(int a[], int cur, int n, int sum)
{
    if (cur == n) return sum;
    sum += a[cur] + add3(a, cur+1, n, sum);
    return sum;
}

// selection sort iterative
void sort_i(int a[], int len)
{
    // start at 0 -> n-1, successively finding smallest value and swap
    int min;
    // scan through the entire list minus one
    for (int i = 0; i < len-1; ++i) {
        min = i;
        // scan sublist for smallest element
        for (int j = i+1; j < len; ++j) {
            if (a[min] > a[j]) {
                min = j;
            }
        }
        // exchange smallest with current i
        if (i != min) {
            swap(a[i], a[min]);
        }
    }
}

// selection sort recursive
void sort_r(int a[], int st, int len)
{
    int min = st, j;
    if (st == len) return;
    for (j = st+1; j < len; ++j) {
        if (a[min] > a[j]) {
            min = j;
        }
    }
    if (st != min) {
        swap(a[st], a[min]);
    }
    sort_r(a, st+1, len);
}

void show_sudoku(int g[9][9], int idx)
{
    int i, j;
    for (i = 0; i < 9; i++) {
        printf("%d %d %d | %d %d %d | %d %d %d\n", 
                g[i][0], g[i][1], g[i][2], g[i][3], 
                g[i][4], g[i][5], g[i][6], g[i][7], g[i][8]);
    }
}

void show_sudoku_col(int g[9][9], int col)
{
    int i;
    for (i = 0; i < 9; i++) {
        printf("%d\n", g[i][col]); 
    }
}

bool is_avail_row(int g[9][9], int row, int val)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (val == g[row][i]) return false;
    }
    return true;
}

bool is_avail_col(int g[9][9], int col, int val)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (val == g[i][col]) return false;
    }
    return true;
}

// iterative
void sudoku_i(int grid[9][9])
{
    // march across row
    // for each cell in the row, if it is filled, move on
    //    if it is empty, get mask of all numbers taken on row and col
    //                    get mask of all number in group
    //    invert the mask and pick an available number
    // move to next row
}

bool is_available_group(int g[9][9], int group, int val)
{
    int r, c, r_end, c_end;
    switch (group) {
        case 1:
            r = 0;
            c = 0;
            break;
        case 2:
            r = 0;
            c = 3;
            break;
        case 3:
            r = 0;
            c = 6;
            break;
        case 4:
            r = 3;
            c = 0;
            break;
        case 5:
            r = 3;
            c = 3;
            break;
        case 6:
            r = 3;
            c = 6;
            break;
        case 7:
            r = 6;
            c = 0;
            break;
        case 8:
            r = 6;
            c = 3;
            break;
        case 9:
            r = 6;
            c = 6;
            break;
    }
    r_end = r + 3;
    c_end = c + 3;
    for (int i = r; i < r_end; i++) {
        for (int j = c; j < c_end; j++) {
            if (g[i][j] == val) return true;
        }
    }
    return false;
}

int get_group(int row, int col)
{
#if 0
    int i, j, g = 0;
    printf("--------------------------------------------"
           "--------------------------------------------\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            printf("(%d, %d) - ", i, j);
            if ((j+1) % 3 == 0) printf(" | ");
        }
        printf("\n");
        if ((i+1) % 3 == 0) {
            printf("--------------------------------------------"
                   "--------------------------------------------\n");
        }
    }
#endif
    int group_row = row / 3;
    int group_col = col / 3;
    int group = (3 * group_row) + group_col + 1;
    return group;
}


void test_sudoku()
{
    // sudoku
    int grid[9][9] = 
    {
      //    I         II       III
      // 1  2  3   4  5  6   7  8  9
        {5, 3, 0,  0, 7, 0,  0, 0, 0},
      //10 11 12   13 14 15  16 17 18
        {6, 0, 0,  1, 9, 5,  0, 0, 0},
     // 19 20 21   22 23 24  25 26 27
        {0, 9, 8,  0, 0, 0,  0, 6, 0},

      //   IV          V        VI
     // 28 29 30   31 32 33  34 35 36
        {8, 0, 0,  0, 6, 0,  0, 0, 3},
     // 37 38 39   40 41 42  43 44 45
        {4, 0, 0,  8, 0, 3,  0, 0, 1},
     // 46 47 48   49 50 51  52 53 54
        {7, 0, 0,  0, 2, 0,  0, 0, 6},

      //   VII       VIII       IX
     // 55 56 57   58 59 60  61 62 63
        {0, 6, 0,  0, 0, 0,  2, 8, 0},
     // 64 65 66   67 68 69  70 71 72
        {0, 0, 0,  4, 1, 9,  0, 0, 5},
     // 73 74 75   76 77 78  79 80 81
        {0, 0, 0,  0, 8, 0,  0, 7, 9},
    };
    show_sudoku(grid, 1);

    //int r = 0, c = 4;
    //for (r = 0; r < 9; r++) {
    //    for (c = 0; c < 9; c++) {
    //        cout << "group(" << r << "," << c << ") => " << get_group(r,c) << endl;
    //    }
    //}

    //cout << "show sudoku by col" << endl;
    //for (int c = 0; c < 1; c++) {
    //    show_sudoku_col(grid, c);
    //}
}

int main()
{
#if 0
    int x = 7;
    int y = 42;
    cout << "faci(" << x << ") = " << faci(x) << endl;
    cout << "facr(" << x << ") = " << facr(x) << endl;

    cout << "num_sums_i(" << x << "," << y << ") = " << sum_nums_i(x,y) << endl;
    cout << "num_sums_r(" << x << "," << y << ") = " << sum_nums_r(x,y) << endl;
    cout << "num_sums_c(" << x << "," << y << ") = " << sum_nums_c(x,y) << endl;

    test_fib();
    //test_reverse();
    for (int i = 2; i < 32; ++i) {
        cout << "faci(" << i << ") = " << faci(i) << endl;
    }
    cout << "max int: " << INT_MAX << endl;

    //cout << "sqrt: " << sqrt_newton(1.0, 4.0) << endl;

    // poker hand: n=52, k=5
    int n = 52, k = 5;
    cout << n << " choose " << k << " = " << choose(n,k) << " combinations" << endl;

    int a[] = {2, 4, 6, 7, 9, 12};
    int len = sizeof(a) / sizeof(a[0]);
    int start = 0;
    print_permutations(a, len, start);

    x = 3, y = 2;
    cout << "ackerman(" << x << "," << y << ") = " << ackerman(x,y) << endl;

    cout << x << " is_even: " << is_even(x) << endl;
    cout << x << " is_odd : " << is_odd(x) << endl;

    x = 4, y = 2;
    cout << "mystery(" << x << "," << y << ") = " << mystery(x,y) << endl;

    x = 3, y = 2;
    cout << "powr(" << x << "," << y << ") = " << powr(x,y) << endl;
    cout << "powi(" << x << "," << y << ") = " << powi(x,y) << endl;

    test_zip();

    int b[] = {2,5,3,8,1,2,88,6,43};
    len = sizeof(b) / sizeof(b[0]);
    cout << "show max array" << endl;
    show_zip(b, len);
    int m = find_max(b, 0, len, 0);
    cout << "max: " << m << endl;
    m = find_max2(b, 0, len, 0);
    cout << "max: " << m << endl;

    int ss[] = {1,2,3,12};
    len = sizeof(ss) / sizeof(ss[0]);
    int s = add3(ss, 0, len, 0);
    cout << "sum array" << endl;
    show_zip(ss, len);
    cout << "sum = " << s << endl;

    //bool match = str_match(string("abc"), string("xyz"));
    bool match = str_match(string("abc"), string("abc"));
    cout << "str_match: " << match << endl;

    // use b[]
    len = sizeof(b) / sizeof(b[0]);
    cout << "show unsorted" << endl;
    show_zip(b, len);
    //sort_r(b, 0, len);
    sort_i(b, len);
    cout << "show sorted" << endl;
    show_zip(b, len);
#endif
    test_sudoku();
}

