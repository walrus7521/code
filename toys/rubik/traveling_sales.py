#!/usr/bin/env python3

# Traveling saleperson problem - grok

# sets
#   OR  union: combine sets
#   AND intersection: common to both
#   -   difference: remove items

cities_needed = set(["marin", "sanfran", "berkeley", "fremont", "paloalto"])

pick_a_city = "berkeley"

distances = {}
distances["marin"]    = {"sanfran":28, "berkeley":19, "fremont":51,  "paloalto":54}
distances["sanfran"]  = {"marin":28,   "berkeley":14, "fremont":38,  "paloalto":33}
distances["berkeley"] = {"marin":19,   "sanfran":14,  "fremont":31,  "paloalto":31}
distances["fremont"]  = {"marin":51,   "sanfran":38,  "berkeley":31, "paloalto":18}
distances["paloalto"] = {"marin":54,   "sanfran":33,  "berkeley":31, "fremont":18 }

final_cities = set()
cities_covered = set()
route = []

start_city = pick_a_city
save_start = start_city
cities_needed.remove(start_city)
cities_covered.add(start_city)

while cities_needed and start_city:
    best_city = None
    lowest_dist = 9999

    # iterate over statiions sets
    for city, city_dist in distances[start_city].items():
        if city in cities_covered:
            continue
        if city_dist < lowest_dist and city not in cities_covered:
            lowest_dist = city_dist
            best_city = city
    cities_covered.add(best_city)
#   print("===> best city: ", best_city, " lowest: ", lowest_dist)
    cities_needed.remove(best_city)
    route.append(best_city)
    start_city = best_city

print("approx best route: ", save_start, " ==> ", route)

