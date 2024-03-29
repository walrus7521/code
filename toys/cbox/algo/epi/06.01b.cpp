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

typedef enum color { RED, WHITE, BLUE } color;

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

    void swap(vector<int> &a, int i, int j)
    {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }


    int Process() {
        //return Process_dutch();
        return Process_nums();
    }

    int Process_nums() {
       int smaller = 0, equal = 0, larger = data.size()-1;
        while (equal <= larger) {
            if (data[equal] < pivot) {
                swap(data, smaller++, equal++);
            } else if (data[equal] == pivot) {
                equal++;
            } else {
                swap(data, equal, larger--);
            }
        }
        return 0;
    }

    int Process_dutch() {
        int color, head, tail;
        head = 0;
        for (color = RED; color < BLUE; ++color) {
            tail = data.size();
            for (; head != tail; ) {
                if (data[head] == color) {
                    ++head;
                } else {
                    while (data[tail] != color && tail != head) {
                        --tail;
                    }
                    if (data[tail] == color) {
                        // swapo
                        int tmp = data[head];
                        data[head] = data[tail];
                        data[tail] = tmp;
                    }
                }
            }
        }
        return 0;
    }

private:
    vector<int> data;
    int pivot;
};

int do_dutch()
{
    cout << "dutchy\n";
    vector<int> a{ RED, BLUE, WHITE, WHITE, BLUE, BLUE, WHITE, BLUE, RED, RED, WHITE };
    int pivot = 3;
    Dutch d(a, pivot);
    d.Show();
    d.Process_dutch();
    d.Show();
    return 0;
}

int do_nums()
{
    cout << "numpy\n";
    vector<int> a{ 1,2,4,3,6,3,4,2,7,6,2,3,2,1,3 };
    int pivot = 3;
    Dutch d(a, pivot);
    d.Show();
    d.Process_nums();
    d.Show();
    return 0;
}

int main()
{
    do_nums();
    do_dutch();
    return 0;
}
