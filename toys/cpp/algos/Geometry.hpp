#include <vector>
#include <iostream>

using namespace std;
 
struct Point
{
    int x, y;
};
 
class Polygon
{
public:
    Polygon(Point points[], int nV) : V(nV) {
        for (int i = 0; i < nV; ++i) {
            poly.push_back(points[i]);
        }
    }
    // To find orientation of ordered triplet (p, q, r).
    // The function returns following values
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int orientation(Point p, Point q, Point r)
    {
        int val = (q.y - p.y) * (r.x - q.x) -
                  (q.x - p.x) * (r.y - q.y);
     
        if (val == 0) return 0;  // colinear
        return (val > 0)? 1: 2; // clock or counterclock wise
    }
    void calc_hull()
    {
        int l = 0;
        struct Point p0 = poly[l];
        struct Point p1;
        for (int i = 1; i < V; ++i) {
            p1 = poly[i];
            if (p1.x < p0.x) {
                l = i;
            }
        }
        p0 = poly[l];
        //cout << "left most: " << l << endl;
        //cout << "(" << p0.x << ", " << p0.y << ")" << endl;

        // Start from leftmost point, keep moving counterclockwise
        // until reach the start point again.  This loop runs O(h)
        // times where h is number of points in result or output.
        int p = l, q;
        do
        {
            hull.push_back(poly[p]);

            // Search for a point 'q' such that orientation(p, x,
            // q) is counterclockwise for all points 'x'. The idea
            // is to keep track of last visited most counterclock-
            // wise point in q. If any point 'i' is more counterclock-
            // wise than q, then update q.
            q = (p+1)%V;
            for (int i = 0; i < V; i++) {
               // If i is more counterclockwise than current q, then
               // update q
               if (orientation(poly[p], poly[i], poly[q]) == 2) {
                   q = i;
               }
            }
            // Now q is the most counterclockwise with respect to p
            // Set p as q for next iteration, so that q is added to
            // result 'hull'
            p = q;

        } while (p != l); // While we don't come to first point
        // Print Result
        for (std::vector<Point>::iterator it = hull.begin(); 
                    it != hull.end(); ++it) {
            cout << "(" << it->x << ", " << it->y << ")" << endl;
        }
    }
    void show() {
        vector<Point>::const_iterator vp;
        for (vp = poly.begin(); vp != poly.end(); ++vp) {
            cout << "(" << vp->x << ", " << vp->y << ")" << endl;
        }
    }
private:
    int V; // number vertices
    vector<Point> poly; // vertices
    vector<Point> hull; // vertices
};
