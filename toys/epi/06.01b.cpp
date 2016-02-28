#include <iostream> 
#include <array>
#include <vector>

using namespace std;

/*  The Dutch flag problem
 *
 *  Write a function that takes an array A of length n and an index i into 
 *  A, and rearranges the elements such that all elements less than A[i] appear
 *  first, followed by elements equal to A[i], followed by elements greater
 *  than A[i].
 *
 *  Idea: red, white, blue - just pinch and swap
 *  [?] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [b] [r] [b] [r] [w] [w] [b]
 *   ^   ^                                                       ^           ^
 *   |-->|                                                       |<--- scan -|
 *   | yes                                                       |
 *   red? no ------------------- swap ----------------------------
 */

using namespace std;

class Puzzle {
public:
    virtual void Show() = 0;
    virtual int Process() = 0;
};

class Dutch : public Puzzle {
public:
    Dutch(vector<int> v, int m) : data{v}, pivot{m}
        { cout << "create Dutch " << endl; }
    ~Dutch(){ cout << "destroy Dutch " << endl; }
    void Show() {
        cout << "pivot: " << pivot << endl;
        cout << "data: ";
        for(const auto& s: data)
            cout << s << ' ';
        cout << endl;
    }
    int Process() {
        return 0;
    }
private:
    vector<int> data;
    int pivot;
};

int main()
{
    vector<int> a{ 8, 2, 3, 5, 9, 1};
    int pivot = 3;
    Dutch d(a, pivot);
    d.Process();
    d.Show();
}

