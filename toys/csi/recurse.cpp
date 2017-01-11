#include <iostream>
#include <vector>
#include <climits>

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

#if 0
struct list {
    struct list *next;
    int x;
};

list *reverse_list(list *head)
{
    list *p = head->next;
    if (p == NULL) return NULL;
    return reverse_list(p->next) + p;
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

int main()
{
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
}

