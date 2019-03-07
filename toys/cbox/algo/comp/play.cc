#include "utils.h"


void pi_decimal_places(int n)
{
    bool first = true;
    double integral, fractional;
    double pi = 2 * acos(0.0);

    for (int i = 0; i <= n; i++) {
        fractional = modf(pi, &integral);
        pi -= integral;
        pi *= 10.0f;
        if (first == true) {
            printf("%d.", (int) integral);
            first = false;
        } else {
            printf("%d", (int) integral);
        }
    }
    printf("\n");
}

void pi_n_decimal_places(int n)
{
    double pi = 2 * acos(0.0);
    printf("%.*lf\n", n, pi); // ****
}


#define ALL(x) x.begin(), x.end()
#define UNIQUE(x) (x).resize(unique(ALL(x)) - (x).begin())
void n_rand_ints_sorted(int n)
{
    int arr[] = {1,2,2,2,3,3,2,2,1};
    n = sizeof(arr)/sizeof(arr[0]);
    vector<int> v(arr, arr+n);
    sort(ALL(v));
    UNIQUE(v);
    for (auto x : v) {
        cout << x << endl;
    }
}

bool sortbyfirst(const pair<tuple<int, int, int>, int>& a,  
                 const pair<tuple<int, int, int>, int>& b) 
{ 
    return (get<0>(a.first) < get<0>(b.first)); 
}
bool sortbysecond(const pair<tuple<int, int, int>, int>& a,  
                 const pair<tuple<int, int, int>, int>& b) 
{ 
    return (get<1>(a.first) < get<1>(b.first)); 
}
bool sortbythird(const pair<tuple<int, int, int>, int>& a,  
                 const pair<tuple<int, int, int>, int>& b) 
{ 
    return (get<2>(a.first) < get<2>(b.first)); 
}
bool sortbyage(const pair<tuple<int, int, int>, int>& a,  
               const pair<tuple<int, int, int>, int>& b) 
{ 
    return ((a.second) < (b.second)); 
}

void show(vector<pair<tuple<int, int, int>, int>> bdays)
{
    for (int i = 0; i < bdays.size(); i++) {
        cout << get<0>(bdays[i].first) << " " 
             << get<1>(bdays[i].first) << " " 
             << get<2>(bdays[i].first) << " = "
             << (bdays[i].second)      << "\n"; 
    }
    cout << endl;
}

void sort_bdays()
{
    vector<pair<tuple<int, int, int>,int>> bdays;

    auto today = std::make_tuple(3,7,2019);
    auto b1 = std::make_tuple(25,11,1958);
    auto b2 = std::make_tuple(5,8,1956);
    auto b3 = std::make_tuple(18,6,1961);

    bdays.push_back(std::make_pair(b1, get<2>(today) - get<2>(b1)));
    bdays.push_back(std::make_pair(b2, get<2>(today) - get<2>(b2)));
    bdays.push_back(std::make_pair(b3, get<2>(today) - get<2>(b3)));

    show(bdays);
    sort(bdays.begin(), bdays.end(), sortbysecond); 
    show(bdays);
    sort(bdays.begin(), bdays.end(), sortbyfirst); 
    show(bdays);
    sort(bdays.begin(), bdays.end(), sortbyage); 
    show(bdays);
}

void sort_bdays2()
{
    iii A = make_pair(ii(5, 24), -1982);
    iii B = make_pair(ii(5, 24), -1980);
    iii C = make_pair(ii(11, 13), -1983);
    vector<iii> birthdays;
    birthdays.push_back(A); birthdays.push_back(B); birthdays.push_back(C);
    sort(birthdays.begin(), birthdays.end());
    for (int i = 0; i < birthdays.size(); i++) {
        cout << birthdays[i].first.first << " " << birthdays[i].first.second << " " << birthdays[i].second << "\n";
    }
    cout << endl;
}

int main()
{
    //pi_decimal_places(9);
    //pi_n_decimal_places(11);
    //n_rand_ints_sorted(32);
    sort_bdays2();
}

