#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

//# Greedy algorithm

void ChooseStation()
{
    set<string> states_needed {"mt","wa","or","id","nv","ut","ca","az"};

    map<string, set<string>> stations;
    stations["kone"]   = set<string>{"id","nv","ut"};
    stations["ktwo"]   = set<string>{"wa","id","mt"};
    stations["kthree"] = set<string>{"or","nv","ca"};
    stations["kfour"]  = set<string>{"nv","ut"};
    stations["kfive"]  = set<string>{"ca","az"};
         
    set<string> final_stations;

    while (states_needed.size()) {
        string best_station;
        set<string> states_covered;
        for (auto const& s : stations) {
            printf("%s: ", s.first.c_str());
            for (auto const& v : s.second) {
                printf("%s ", v.c_str());
            }
            printf("\n\n");

            set<string> covered;
            set_intersection(states_needed.begin(), states_needed.end(),
                    s.second.begin(), s.second.end(),
                    std::inserter(covered, covered.begin()));

            printf("covered\n");
            for (auto const& c : covered) {
                printf("%s, ", c.c_str());
            }
            printf("\n");

            
            if (covered.size() > states_covered.size()) {
                best_station = s.first;
                states_covered = covered;
            }
        }

        set_difference(states_needed.begin(), states_needed.end(),
                    states_covered.begin(), states_covered.end(),
                    std::inserter(states_needed, states_needed.begin()));

        printf("needed\n");
        for (auto const& c : states_needed) {
            printf("%s, ", c.c_str());
        }
        printf("\n");
        //states_needed -= states_covered
        //final_stations.add(best_station)

        
    }
    
#if 0
    states_needed = set(["mt","wa","or","id","nv","ut","ca","az"])
    # list of stations - use a hash
    stations = {}
    stations["kone"]   = set(["id","nv","ut"])
    stations["ktwo"]   = set(["wa","id","mt"])
    stations["kthree"] = set(["or","nv","ca"])
    stations["kfour"]  = set(["nv","ut"])
    stations["kfive"]  = set(["ca","az"])

    final_stations = set()

    while states_needed:
        print states_needed
        best_station = None
        states_covered = set()
        for station, states in stations.items():
#           print station
#           print states_for_station
            covered = states_needed & states # set intersection - like binary AND mask
#           print covered
            if len(covered) > len(states_covered):
                best_station = station
                states_covered = covered
        print states_covered
        states_needed -= states_covered
        final_stations.add(best_station)

    print final_stations
#endif
}

void ChangeMaking(int cents)
{
#if 0
    kCoins = (100, 50, 20, 10, 5, 2, 1)
    num_coins = 0
    for i in range(0, len(kCoins)):
        num_coins += cents / kCoins[i]
        cents %= kCoins[i]
    return num_coins
#endif
}

void TaskAssign()
{
#if 0
# pair the shortest with longest, ... optimal
#    times = [5,2,1,6,4,4]
    times = [1,8,9,10]
    times.sort(reverse=True)
    num_workers = len(times)/2
    workers = [0,0,0]
    for i in range(0, num_workers):
        workers[i] += times[i]
        workers[i] += times[2*num_workers-i-1]
    print workers
    print max(workers)
#endif
}

void SQLWaitTimes()
{
#if 0
    times = [2,5,1,3]
    times = [0] + times; # prepend zero to list
    times.sort() # make longest time go last
    num_waits = len(times)
    print times
    total = 0
    for i in range(1, num_waits):
        print times[0:i]
        total += sum(times[0:i])
    print total
#endif
}

struct Interval {
    int left, right;
};

void FindMinimumVisits()
{
    //vector<Interval> intervals{{0,3},{2,6},{3,4},{6,9}}; // => {3,9}
    vector<Interval> intervals{{1,2},{2,3},{3,4},{2,3},{3,4},{4,5}}; // => {2,4}

    if (intervals.empty()) {
        return;
    }

    // sort intervals based on right endpoints
    sort(intervals.begin(), intervals.end(),
         [](const Interval& a, const Interval& b) {return a.right < b.right;});

    vector<int> visits;

    int last_visit_time = intervals.front().right;
    visits.emplace_back(last_visit_time);

    for (const Interval& interval : intervals) {
        if (interval.left > last_visit_time) {
            // the current right endpoint, last_visit_time will not cover
            // any more intervals
            last_visit_time = interval.right;
            visits.emplace_back(last_visit_time);
        }
    }

    for (auto const& v : visits) {
        printf("%d ", v);
    }
    printf("\n\n");
}

int main()
{
    //SQLWaitTimes();
    //TaskAssign();
    //print ChangeMaking(70);
    //ChooseStation();
    FindMinimumVisits();

    return 0;
}
