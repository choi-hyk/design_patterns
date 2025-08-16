// https://velog.io/@choi-hyk/Design-Pattern-Prototype-Pattern

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// ---------------------------
// Graphic : Prototype 인터페이스
// ---------------------------
class Graphic {
public:
    virtual ~Graphic() {}
    virtual unique_ptr<Graphic> clone() const = 0;
    virtual void draw(const string& position) const = 0;
};

// ---------------------------
// Staff : 구체 Prototype
// ---------------------------
class Staff : public Graphic {
public:
    unique_ptr<Graphic> clone() const override {
        return make_unique<Staff>(*this);
    }

    void draw(const string& position) const override {
        cout << "오선지를 " << position << " 위치에 그림" << endl;
    }
};

// ---------------------------
// MusicalNote : 추상 클래스
// ---------------------------
class MusicalNote : public Graphic { };

// WholeNote : 구체 Prototype
class WholeNote : public MusicalNote {
public:
    unique_ptr<Graphic> clone() const override {
        return make_unique<WholeNote>(*this);
    }

    void draw(const string& position) const override {
        cout << "온음표를 " << position << " 위치에 그림" << endl;
    }
};

// Concrete Prototype
class HalfNote : public MusicalNote {
public:
    unique_ptr<Graphic> clone() const override {
        return make_unique<HalfNote>(*this);
    }

    void draw(const string& position) const override {
        cout << "2분음표를 " << position << " 위치에 그림" << endl;
    }
};

// ---------------------------
// Tool : Client 역할 추상 클래스
// ---------------------------
class Tool {
public:
    virtual ~Tool() {}
    virtual void manipulate() = 0;
};

// Client
class GraphicTool : public Tool {
private:
    unique_ptr<Graphic> prototype;
public:
    GraphicTool(unique_ptr<Graphic> proto) : prototype(move(proto)) {}

    void manipulate() override {
        auto p = prototype->clone();
        p->draw("새로운 위치");
    }
};

// Tool
class RotateTool : public Tool {
public:
    void manipulate() override {
        cout << "대상을 회전시킴" << endl;
    }
};

// ---------------------------
// 클라이언트 코드
// ---------------------------
int main() {
    // 온음표 도구
    unique_ptr<Tool> wholeNoteTool = make_unique<GraphicTool>(make_unique<WholeNote>());
    wholeNoteTool->manipulate();

    // 2분음표 도구
    unique_ptr<Tool> halfNoteTool = make_unique<GraphicTool>(make_unique<HalfNote>());
    halfNoteTool->manipulate();

    // 오선지 도구
    unique_ptr<Tool> staffTool = make_unique<GraphicTool>(make_unique<Staff>());
    staffTool->manipulate();

    return 0;
}