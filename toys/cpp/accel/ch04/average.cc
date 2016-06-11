// source file for the `median' function
#include <iostream>
#include <algorithm>    // to get the declaration of `sort'
#include <numeric>
#include <stdexcept>    // to get the declaration of `domain_error'
#include <vector>       // to get the declaration of `vector'

using std::domain_error;   using std::sort;   using std::vector;
using std::accumulate;     using std::cout;   using std::endl;

#include "average.h"

// compute the average of a `vector<double>'
// note that calling this function copies the entire argument `vector'
double average(vector<double> vec)
{
    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();
    if (size == 0)
        throw domain_error("average of an empty vector");

    double sum;
    sum = accumulate(vec.begin(), vec.end(), 0.0);

    double avg = sum / size;

    cout << "average is: " << avg << endl;

    return avg;

}

