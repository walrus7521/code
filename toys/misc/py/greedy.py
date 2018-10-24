#!/usr/bin/python

# Greedy algorithm

def ChooseStation():
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
#          print covered
            if len(covered) > len(states_covered):
                best_station = station
                states_covered = covered
        print states_covered
        states_needed -= states_covered
        final_stations.add(best_station)

    print final_stations


def ChangeMaking(cents):
    kCoins = (100, 50, 25, 10, 5, 1)
    num_coins = 0
    for i in range(0, len(kCoins)):
        num_coins += cents / kCoins[i]
        cents %= kCoins[i]
    return num_coins

def main():
    print ChangeMaking(123)
#    ChooseStation()

if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        print "Exception occured running main():"
        print str(e)

