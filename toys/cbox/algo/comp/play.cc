#include "utils.h"

// Excercise 2.2.1
void show_vec(vector<int>& a)
{
    for (auto i : a) {
        cout << i << " ";
    }
    cout << endl;
}

void find_all_pairs()
{
    vector<int> a = {3,7,1,2,4,6,3,9,7,1,5,2,8};
    sort(a.begin(), a.end());
    //show_vec(a);
    for (int i = 0; i < a.size(); i++) {
        int p1 = a[i];
        for (int j = 0; j < a.size(); j++) {
            int p2 = a[j];
            if (p1 == p2) {
                printf("pair: {%d,%d}\n", p1, p2);
                while (a[i] == p1) i++;
                break;
            }
        }
    }
}

void find_int_in_interval()
{
    int int1 = 4, int2 = 7;
    vector<int> a = {3,7,1,2,4,6,3,9,7,1,5,2,8};
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == int1) {
            printf("[%d ", a[i++]);
            while (a[i] != int2) { printf("%d ", a[i]); i++; }
            printf("%d]\n", a[i]);

        }
    }
}

void longest_contig_increasing_sequence()
{
    int max = 0, len = 0, start_max = 0;
    vector<int> a = {3,7,1,2,4,6,3,9,7,1,5,2,8};
    sort(a.begin(), a.end());
    show_vec(a);
    for (int i = 0; i < a.size(); i++) {
        int p1 = a[i];
        for (int j = i; j < a.size(); j++) {
            int p2 = a[j];
            if (p2 == p1+1) {
                len = 1;
                j++;
                printf("start sequence: %d -> %d\n", p1, p2);
                while (a[j] == p2+1) { p2 = a[j]; len++; printf("in[%d]=%d\n", j, a[j]); j++;}
                if (len > max) { max = len; start_max = i; }
                break;
            }
        }
    }
    printf("max: %d @ %d\n", max, start_max);
    for (int k = start_max; k < start_max+max; k++) {
        printf("%d ", a[k]);
    }
    printf("\n");
}

void find_pair_with_sum()
{
    int sum = 15;
    vector<int> a = {3,7,1,2,4,6,3,9,7,1,5,2,8};
    sort(a.begin(), a.end());
    for (int i = 0; i < a.size(); i++) {
        int p1 = a[i];
        for (int j = 0; j < a.size(); j++) {
            int p2 = a[j];
            if (p1 + p2 == sum) {
                printf("sum: {%d,%d} = %d\n", p1, p2, sum);
                while (a[i] == p1) i++;
                break;
            }
        }
    }
}


// Exercises 1.2.3
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
    //sort_bdays2();
    //find_all_pairs();
    //find_pair_with_sum();
    //find_int_in_interval();
    longest_contig_increasing_sequence();
}

