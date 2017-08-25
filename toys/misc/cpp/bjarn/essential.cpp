#include <vector>
#include <iostream>
#include <cstddef>

using std::cout; using std::endl;

class Essentials {
public:
    Essentials(int s) : elem{new double[s]}, sz(s) {
        cout << "Essentials(" << s << ")\n";
    }
    Essentials() : elem{new double[8]}, sz(8) {
        cout << "Essentials()\n";
    }
    Essentials(const Essentials& e) :elem{new double[e.sz]}, sz{e.sz}{
        cout << "copy Essentials\n";
        for (int i = 0; i != sz; ++i )
            elem[i] = e.elem[i];
    }
    Essentials& operator=(const Essentials& e) {
        cout << "copy assign Essentials\n";
        double *p = new double[e.sz];
        for (int i = 0; i != e.sz; ++i) 
            p[i] = e.elem[i];
        delete[] elem;
        elem = p;
        sz = e.sz;
        return *this;
    }
    Essentials(Essentials&& e) : elem{e.elem}, sz{e.sz} { 
    // grab the elements first above, then destroy them
        cout << "move Essentials\n";
        e.elem = NULL;
        e.sz = 0;

    }
    Essentials& operator=(Essentials&& e) {
        cout << "move assign Essentials\n";
        elem = std::move(e.elem);
        this->sz = e.sz;
        //e.elem = NULL;
        //e.sz = 0;
        return *this;
    }
    ~Essentials() {
        cout << "~Essentials()\n";
        delete[] elem;
    }
    int size() { return sz; }
private:
    double *elem;
    int sz;
};

std::shared_ptr<Essentials> ug() {
    std::shared_ptr<Essentials> g(new Essentials());
    return g;
}

Essentials uh() {
    Essentials g(3);
    return g;
}

void skipper() {
    cout << "enter skipper \n";
    std::shared_ptr<Essentials> pe;
    pe = ug();
    cout << "exit skipper \n";
}

int main() {
    std::vector<Essentials> ve;
    Essentials e, f, g;
    Essentials h(7);
    //std::shared_ptr<Essentials> pe;
    //cout << "calling the skip\n";
    //skipper(); // testing smart pointers
    //cout << "back from calling the skip\n";
    std::cout << "moved: " << h.size() << std::endl;
    ve.push_back(std::move(h)); // move vacates h
    Essentials j = ve[0];
    std::cout << "moved from: " << h.size() << std::endl;
    std::cout << "moved to  : " << j.size() << std::endl;
    Essentials k = std::move(j);
    std::cout << "moved from: " << j.size() << std::endl;
    std::cout << "moved to  : " << k.size() << std::endl;
    //pe = ug();
    //f = g; // copy assignment
    //Essentials z(g); // plain copy
    //e = uh(); // move assignment
    //f = g;

    return 0;
}


