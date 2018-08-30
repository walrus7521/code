#include <iostream>

using namespace std;

template <typename T>
class vector
{
public:
    explicit vector(int size)
        : my_size(size), data(new T[my_size])
    {
        std::fill(&data[0], &data[my_size], 0);
    }

    vector(const vector& that)
        : my_size(that.my_size), data(new T[my_size])
    {
        std::copy(&that.data[0], &that.data[that.my_size], &data[0]);
    }

    int size() const { return my_size; }

    const T& operator[](int i) const
    {
        // check_index(i);
        return data[i];
    }
private:
    int                     my_size;
    std::unique_ptr<T[]>    data;
};

int main()
{
   vector<float> vf(8); // explicit only
   //vector<float> vf = (8); // implicit conversion
   for (auto i=0; i < vf.size(); ++i) {
       cout << vf[i] << endl;
   }
}

