#include <iostream>
#include <vector>

using namespace std;

struct Item {
    int weight, value;
};

int knapper(const vector<Item>& items, int k,
                                    int available_capacity,
                                    vector<vector<int>>* V_ptr);

int knappy(const vector<Item>& items, int capacity) 
{
    vector<vector<int>> V(items.size(), vector<int>(capacity+1, -1));
    return knapper(items, items.size()-1, capacity, &V);
}

int knapper(const vector<Item>& items, int k,
                                    int available_capacity,
                                    vector<vector<int>>* V_ptr) 
{
    if (k < 0) {
        // no items can be chosen
        return 0;
    }

    vector<vector<int>>& V = *V_ptr;
    if (V[k][available_capacity] == -1) {
        int without_curr_item = knapper(
                items, k-1, available_capacity, V_ptr);
        int with_curr_item = available_capacity < items[k].weight
                            ? 0
                            : items[k].value + knapper(
                                    items, k-1,
                                    available_capacity - items[k].weight,
                                    V_ptr);
        V[k][available_capacity] = max(without_curr_item, with_curr_item);
    }

    return V[k][available_capacity];
}

int main()
{
//    Item items[] = {{5,60},{3,50},{4,70},{2,30}};
    //vector<Item> items = {{5,60},{3,50},{4,70},{2,30}};
    vector<Item> items = {{10,60},{20,100},{30,120},{4,150},{32,200}};
    int capacity = 20;
    int h = knappy(items, capacity);
    cout << "cap: " << h << endl;

}
