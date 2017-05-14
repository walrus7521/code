#include <vector>
#include <iostream> 
#include <algorithm> 
#include <functional> 
using namespace std;
 
// compose abstract base "component" that specifies the
// desired uniform behaviour of each composite object.
class Graphic {
public:
  virtual void draw() const = 0;
  virtual void remove(Graphic *g) {}
  virtual void add(Graphic *g) {}
  virtual void getChild(int) {}
  virtual ~Graphic() {}
};
 
class Line : public Graphic {
public:
  void draw() const {
    cout << "Line draw()\n";
  }
};

class Rectangle : public Graphic {
public:
  void draw() const {
    cout << "Rectangle draw() \n";
  }
};

class Text : public Graphic {
public:
  void draw() const {
    cout << "Text draw() \n";
  }
};

// Composite - container
class Picture : public Graphic {
public:
  void draw() const {
    // for each element in gList, call the draw member function
    for_each(gList.begin(), gList.end(), mem_fun(&Graphic::draw));
  }
 
  void add(Graphic *aGraphic) {
    gList.push_back(aGraphic);
  }
 
private:
  vector<Graphic*> gList;
};
 
int main()
{
  // Lines, rectangles, text are leaves and don't support add
  // remove or getChild - only draw
  Line line;
  line.draw();
  Rectangle rect;
  rect.draw();
  Text text;
  text.draw();

  // Pictures on the other hand support all the Graphic interface
  // add, remove, getChild, and draw
  Picture pic;
  pic.add(&line);
  pic.add(&rect);
  pic.add(&text);
  pic.add(&rect);
  pic.draw();

  return 0;
}

