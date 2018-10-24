#!/usr/bin/python

# Greedy algorithm

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
#       print station
#       print states_for_station
        covered = states_needed & states # set intersection - like binary AND mask
#       print covered
        if len(covered) > len(states_covered):
            best_station = station
            states_covered = covered
    print states_covered
    states_needed -= states_covered
    final_stations.add(best_station)

print final_stations
