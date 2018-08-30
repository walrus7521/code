#!/usr/bin/awk -f 


BEGIN {}
    { ++predct[$2]
      predct[$1] = predct[$1]
      succlist[$1, ++succcnt[$1]] = $2
    }
END { qlo = 1
      for (i in predct) {
          n++; if (predct[i] == 0) q[++qhi] = i
      }
      while (qlo <= qhi) {
          t = q[qlo++]; print t
          for (i = 1; i <= succcnt[t]; i++) {
              s = succlist[t, i]
              if (--predct[s] == 0) q[++qhi] = s
          }
      }
      if (qhi != n) print "tsort error: cycle in input"
    }

