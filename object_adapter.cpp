#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

using namespace std;

struct Point { int x{}, y{}; };
struct Size  { int w{}, h{}; };
struct Rect  { int x1{}, y1{}, x2{}, y2{}; };

ostream& operator<<(ostream& os, const Rect& r) {
    return os << "Rect{(" << r.x1 << "," << r.y1 << ") ~ (" << r.x2 << "," << r.y2 << ")}";
}

class Manipulate;
class TextManipulator;

class Shape{
public:
    virtual ~Shape()  = default;
    virtual void boundingBox() const = 0;
    virtual unique_ptr<Manipulate> createManipulate() const = 0;
};

class Manipulate {
public:
    Manipulate() = default;               
    virtual ~Manipulate() = default;
    virtual void manipulate() const {
        std::cout << "Shape 조작\n";
    }
};

class TextManipulator : public Manipulate
{
public:
    void manipulate() const override {
        std::cout << "TextShape 조작\n";
    }
};

class Line : public Shape
{
public:
    Line(Point p1, Point p2) : p1_(p1), p2_(p2) {}
    
    void boundingBox() const override {
        Rect r{
            min(p1_.x, p2_.x),
            min(p1_.y, p2_.y),
            max(p1_.x, p2_.x),
            max(p1_.y, p2_.y)
        };
        std::cout << "[Line] boundingBox = " << r << "\n";
    }

    unique_ptr<Manipulate> createManipulate() const override {
        return make_unique<Manipulate>();
    }

private:
    Point p1_{}, p2_{};
};

class TextView{
public: 
    virtual ~TextView() = default;

    Point getOrigin() const { return origin_; }
    Size  getExtent() const { return extent_; }

    virtual bool isEmpty() const = 0;

protected:
    void setOrigin(Point p) { origin_ = p; }
    void setExtent(Size s)  { extent_ = s; }

private:
    Point origin_{0, 0};
    Size  extent_{0, 0};
};

class SimpleTextView : public TextView {
public:
    explicit SimpleTextView(Point origin, Size extent, bool empty = false)
        : empty_(empty)
    {
        setOrigin(origin);
        setExtent(extent);
    }

    bool isEmpty() const override { return empty_; }

private:
    bool empty_{false};
};

class TextShape : public Shape{
public: 
    TextShape(shared_ptr<TextView> tv) : tv_(std::move(tv)) {}

    void boundingBox() const override {
        Point o = tv_->getOrigin();
        Size  s = tv_->getExtent();
        Rect r{o.x, o.y, o.x + s.w, o.y + s.h};
        cout << "[TextShape(ObjectAdapter)] origin=(" << o.x << "," << o.y
            << "), extent=(" << s.w << "," << s.h << ") -> boundingBox = "
            << r << "\n";
    }
    
    unique_ptr<Manipulate> createManipulate() const override {
        return make_unique<TextManipulator>();
    }

    bool empty() const { return tv_->isEmpty(); }

private:
    shared_ptr<TextView> tv_;
};

int main() {
    unique_ptr<Shape> s1 = make_unique<Line>(Point{10, 5}, Point{2, 20});
    s1->boundingBox();
    s1->createManipulate()->manipulate();

    auto tv = make_shared<SimpleTextView>(Point{100, 200}, Size{50, 20});
    unique_ptr<Shape> s2 = make_unique<TextShape>(tv);
    s2->boundingBox();
    s2->createManipulate()->manipulate();

    return 0;
}
