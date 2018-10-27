#!/usr/bin/python

# Greedy algorithm
def ClassroomScheduling():
    intervals = [(900,1000),(930,1030),(1000,1100),(1030,1130),(1100,1200)]
    # sort by end time tup[1]
    si = sorted(intervals, key=lambda tup: tup[1])
    print si
    schedule = []
    next_tup = si[0]
    schedule.append(next_tup)
    si.remove(next_tup)
    # loop over intervals
    # greedy
    for find_next_tup in si:
        if find_next_tup[0] >= next_tup[1]:
            next_tup = find_next_tup
            schedule.append(next_tup)
            si.remove(next_tup)
        else:
            continue
    print schedule

def StationBalance(): # UVa410
    samples = [5,1,2,7]
    chambers = 3
    S = len(samples)
    if (S < 2*chambers):
        for i in range(0, 2*chambers - S):
            samples.append(0)
    samples.sort()
    print samples
    chamber = [0,0,0]
    for i in range(0, chambers):
        chamber[i] = samples[i]
        chamber[i] += samples[len(samples)-i-1]
    print chamber

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
    kCoins = (100, 50, 20, 10, 5, 2, 1)
    num_coins = 0
    for i in range(0, len(kCoins)):
        num_coins += cents / kCoins[i]
        cents %= kCoins[i]
    return num_coins

def TaskAssign():
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

def SQLWaitTimes():
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


def main():
#    SQLWaitTimes()
#    TaskAssign()
#    print ChangeMaking(70)
#    ChooseStation()
#    ClassroomScheduling()
    StationBalance()

if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        print "Exception occured running main():"
        print str(e)


