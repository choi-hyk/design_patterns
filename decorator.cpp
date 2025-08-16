// https://velog.io/@choi-hyk/Design-Pattern-Decorator-Pattern

#include <iostream>
#include <memory>

class VisualComponent {
public:
    virtual void Draw() = 0;
    virtual ~VisualComponent() {}
};

class TextView : public VisualComponent {
public:
    void Draw() override {
        std::cout << "기본 텍스트 뷰 그리기" << std::endl;
    }
};

class Decorator : public VisualComponent {
protected:
    std::unique_ptr<VisualComponent> _component;
public:
    Decorator(std::unique_ptr<VisualComponent> component)
        : _component(std::move(component)) {} 
    void Draw() override {
        if (_component) {
            _component->Draw();
        }
    }
};

class BorderDecorator : public Decorator {
private:
    int _width;
    void DrawBorder() {
        std::cout << "테두리 그리기" << std::endl;
    }
public:
    BorderDecorator(std::unique_ptr<VisualComponent> component, int width)
        : Decorator(std::move(component)), _width(width) {}

    void Draw() override {
        Decorator::Draw();
        DrawBorder();
    }
};

class ScrollDecorator : public Decorator {
private:
    void DrawScroll() {
        std::cout << "스크롤바 그리기" << std::endl;
    }
public:
    ScrollDecorator(std::unique_ptr<VisualComponent> component)
        : Decorator(std::move(component)) {}

    void Draw() override {
        Decorator::Draw();
        DrawScroll();
    }
};

int main() {
    // 1. 기본 TextView 객체 생성 (unique_ptr로 관리)
    auto textView = std::make_unique<TextView>();
    std::cout << "\n--- 기본 TextView ---" << std::endl;
    textView->Draw();
    
    // 2. TextView에 BorderDecorator 적용
    auto textViewWithBorder = std::make_unique<BorderDecorator>(std::move(textView), 1);
    std::cout << "\n--- 테두리 추가된 TextView ---" << std::endl;
    textViewWithBorder->Draw();

    // 3. TextView에 Border와 Scroll 모두 적용 (중첩 구조)
    auto textViewWithBoth = std::make_unique<ScrollDecorator>(
        std::make_unique<BorderDecorator>(
            std::make_unique<TextView>(), 1));
    std::cout << "\n--- 테두리와 스크롤 모두 추가된 TextView ---" << std::endl;
    textViewWithBoth->Draw();

    return 0;
}