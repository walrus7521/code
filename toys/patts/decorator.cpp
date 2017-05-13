#include <iostream>

using namespace std;

// https://sourcemaking.com/design_patterns/decorator/cpp/2
// compile w/g14
// note: useful for embellishing streams: MemoryStream, FileStream, ScreenStream
//                                 ASCIIStream, CompressedStream, EncryptedStream

// 1. "lowest common denominator", abstract component class
class Component // abstract component
{
public:
    virtual void draw() = 0; // pure virtual
    virtual void resize() = 0; // pure virtual
};

// concrete component class
class TextField: public Component
{
private:
    // 3. "Core" class & "is a"
    int width, height;
public:
    TextField(int w, int h) {
        width = w;
        height = h;
    }
    virtual void draw() override {
        cout << "TextField: draw " << width << ", " << height << '\n';
    }
    virtual void resize() override {
        cout << "TextField: resize" << width << ", " << height << '\n';
    }
};

// 2. 2nd level base class
// decorator subclasses component
// abstract wrapper class, to be subclassed to different decorations
// wraps any component and conforms to component interface
class Decorator: public Component  // 4. "is a" relationship
{
private:
    Component *_component; // 4. "has a" relationship
public:
    Decorator(Component *w) {
        _component = w;
    }
    virtual void draw() override {
        _component->draw(); // 5. Delegation
    }
    virtual void resize() override {
        _component->resize(); // 5. Delegation
    }
};

// concrete wrapper class
class BorderDecorator: public Decorator
{
public:
    // 6. Optional embellishment
    BorderDecorator(Component *w): Decorator(w){}
    virtual void draw() override {
        // 7. Delegate to base class and add extra stuff
        Decorator::draw();
        // add extra stuff here
        cout << "   BorderDecorator draw" << '\n';
    }
    virtual void resize() override {
        // 7. Delegate to base class and add extra stuff
        Decorator::resize();
        // add extra stuff here
        cout << "   BorderDecorator resize" << '\n';
    }
};

// concrete wrapper class
class ScrollDecorator: public Decorator
{
public:
    // 6. Optional embellishment
    ScrollDecorator(Component *w): Decorator(w){}
    virtual void draw() override {
        // 7. Delegate to base class and add extra stuff
        Decorator::draw();
        // add extra stuff here
        cout << "   ScrollDecorator draw" << '\n';
    }
    virtual void resize() override {
        // 7. Delegate to base class and add extra stuff
        Decorator::resize();
        // add extra stuff here
        cout << "   ScrollDecorator resize" << '\n';
    }
};

int main()
{ // Client has the responsibility to compose desired configurations
    Component *aComponent = // top level abstract component wrapper
        new BorderDecorator( // concrete wrapper 1
            new BorderDecorator( // concrete wrapper 2
                new ScrollDecorator( // concrete wrapper 3
                    new TextField(80, 24)))); // concreate component

    aComponent->draw();
    aComponent->resize();
}
