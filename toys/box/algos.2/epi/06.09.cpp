#include <iostream>
#include <vector>

using namespace std;

/*
   Generalizations of Max Difference
   http://www.geeksforgeeks.org/stock-buy-sell/
 */

struct Interval {
    int buy;
    int sell;
};

void stockBuySell(vector<int> price)
{
    int n = price.size();
    // prices must be given for at least 2 days
    if (n == 1) return;

    int count = 0; // count of solution pairs
    Interval sol[n/2+1]; // solution vector

    // traverse through the price array
    int i = 0;
    while (i < n - 1) {
        // find local minima. note that the limit is (n-2) as we are
        // comparing present element to the next element.
        while ((i < n-1) && (price[i+1] <= price[i])) {
            ++i;
        }
        // if we reached the end, break as no further solution is possible
        if (i == n-1) break;
        // store the index of the local minima
        sol[count].buy = i++;
        // now find local maxima. note that the limit is (n-1) as we are
        // comparing to the previous element.
        while ((i < n) && (price[i] >= price[i-1])) {
            ++i;
        }
        // store the index of the maxima
        sol[count].sell = i-1;
        // increment count of buy/sell pairs
        ++count;
    }
    if  (count == 0) {
        printf("There is no day when buying stock will make profit\n");
    } else {
        for (int i = 0; i < count; ++i) {
            printf("Buy on day: %d\t Sell on day: %d\n", sol[i].buy, sol[i].sell);
        }
    }
    return;
}

int main()
{
    int prices[] = {100, 180, 260, 310, 40, 535, 695};
    vector<int> price (prices, prices + sizeof(prices)/sizeof(prices[0]));
    stockBuySell(price);
}
