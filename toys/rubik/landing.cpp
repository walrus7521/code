#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

int i, n, caseNo = 1, order[8];
double a[8], b[8], timeGap, maxTimeGap;

double greedyLanding() {
    double lastLanding = a[order[0]];
    for (i = 1; i < n; i++) {
        double targetLandingTime = lastLanding + timeGap;
        if (targetLandingTime <= b[order[i]]) {
            lastLanding = max(a[order[i]], targetLandingTime);
        } else {
            return 1;
        }
    }
    return lastLanding - b[order[n-1]];
}

int main()
{
    while (scanf("%d", &n), n) {
        for (i = 0; i < n; i++) {
            scanf("%lf %lf", &a[i], &b[i]);
            a[i] *= 60; b[i] *= 60;
            order[i] = i;
        }
        maxTimeGap = -1;
        do {
        } while (next_permutation(order, order+n));
        maxTimeGap = (int) (maxTimeGap + 0.5);
        printf("Case %d: %d:%0.2d\n", caseNo++, (int)(maxTimeGap / 60), (int)(maxTimeGap) % 60);
    }
}


