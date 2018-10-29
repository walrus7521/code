#!/usr/bin/python

# Dynamic programming

def Knapsack():
    merch = {}
    merch[0] = [("guitar",1,1500)]
    merch[1] = [("laptop",3,2000)]
    merch[2] = [("stereo",4,3000)]

    val = [1500,2000,3000]
    n_vals = len(val)
    wt  = [1,2,3,4]
    W = 4

    K = [ [0,0,0,0,0],
          [0,0,0,0,0],
          [0,0,0,0,0],
          [0,0,0,0,0] ]

    N = [ ["","","","",""],
          ["","","","",""],
          ["","","","",""],
          ["","","","",""] ]

    for row in range(0,n_vals+1):
#       value  = merch[row][0][2]
#       weight = merch[row][0][1]
#       name   = merch[row][0][0]
#       print weight, value
        for w in range(0,W+1):
            if row == 0 or w == 0:
                K[row][w] = 0
            elif wt[row-1] <= w:
                K[row][w] = max(val[row-1] + K[row-1][w-wt[row-1]],  K[row-1][w])
            else:
                K[row][w] = K[row-1][w]
                
    print K[n_vals][W]

#           cur_weight = knapsack[row][col]
#           print cur_weight
#           if cur_weight < weight and weight <= weights[col]:
#               print "add: {0} to [{1}][{2}]".format(name, row, col)
#               knapsack[row][col] += weight
#               namesack[row][col] += name
                

def main():
    Knapsack()


if __name__ == '__main__':
    try:
        main()
    except Exception, e:
        print "Exception occured running main() dude you suck:"
        print str(e)


