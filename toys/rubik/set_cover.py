#!/usr/bin/env python3

# Set cover - grok

# sets
#   OR  union: combine sets
#   AND intersection: common to both
#   -   difference: remove items

states_needed = set(["mt", "wa", "or", "id", "nv", "ut", "ca", "az"])

# state coverage by station
stations = {}
stations["kone"]   = set(["id", "nv", "ut"])
stations["ktwo"]   = set(["wa", "id", "mt"])
stations["kthree"] = set(["or", "nv", "ca"])
stations["kfour"]  = set(["nv", "ut"])
stations["kfive"]  = set(["ca", "az"])

final_stations = set()

while states_needed:
    best_station = None
    states_covered = set()

    # iterate over statiions sets
    for station, states_for_station in stations.items():
        covered = states_needed & states_for_station
        if len(covered) > len(states_covered):
            best_station = station
            states_covered = covered

    final_stations.add(best_station)
    states_needed -= states_covered


print(final_stations)

