#!/usr/bin/python

# Dynamic programming

def Knapsack():
    merch = {}
    merch[0] = [("guitar",1,1500)]
    merch[1] = [("laptop",3,2000)]
    merch[2] = [("stereo",4,3000)]

    weights  = [1,2,3,4]

    knapsack = [ [0,0,0,0],
                 [0,0,0,0],
                 [0,0,0,0] ]

    namesack = [ ["","","",""],
                 ["","","",""],
                 ["","","",""] ]

    for row in range(0,3):
        value  = merch[row][0][2]
        weight = merch[row][0][1]
        name   = merch[row][0][0]
#       print weight, value
        for col in range(0,4):
            cur_weight = knapsack[row][col]
            print cur_weight
            if cur_weight < weight and weight <= weights[col]:
                print "add: {0} to [{1}][{2}]".format(name, row, col)
                knapsack[row][col] += weight
                namesack[row][col] += name
                

    print knapsack
    print namesack
    return
    for m in merch:
        print m
        tup = merch[m][0]
        print tup[0], tup[1]


def main():
    Knapsack()


if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        print "Exception occured running main() dude you suck:"
        print str(e)


