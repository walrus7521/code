#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/lambda/lambda.hpp>

using namespace std;

void makeSquare(vector<int>&v)
{
	for_each(v.begin(), v.end(), cout << boost::lambda::_1*boost::lambda::_1 << " ");
}

int main()
{
	vector<int> v;
	for(int i = 1; i <= 10; i++) v.push_back(i);

	makeSquare(v);
    cout << endl;
	return 0;
}
