// https://velog.io/@choi-hyk/Design-Pattern-Builder-Pattern

#include <iostream>
#include <string>
#include <memory>
using namespace std;

// ======= Product =======
class ASCIIText {
public:
    string content;
};
class TeXText {
public:
    string content;
};
class TextWidget {
public:
    string widgetData;
};

// ======= Builder 인터페이스 =======
class TextConverter {
public:
    virtual ~TextConverter() {}
    virtual void ConvertCharacter(char c) = 0;
    virtual void ConvertFontChange(const string& font) = 0;
    virtual void ConvertParagraph() = 0;
};

// ======= ConcreteBuilder: ASCII =======
class ASCIIConverter : public TextConverter {
    shared_ptr<ASCIIText> ascii = make_shared<ASCIIText>();
public:
    void ConvertCharacter(char c) override {
        ascii->content += c;
    }
    void ConvertFontChange(const string& font) override {
        // ASCII에서는 폰트 개념이 없으므로 무시
    }
    void ConvertParagraph() override {
        ascii->content += "\n";
    }
    shared_ptr<ASCIIText> GetASCIIText() { return ascii; }
};

// ======= ConcreteBuilder: TeX =======
class TeXConverter : public TextConverter {
    shared_ptr<TeXText> tex = make_shared<TeXText>();
public:
    void ConvertCharacter(char c) override {
        tex->content += c;
    }
    void ConvertFontChange(const string& font) override {
        tex->content += "\\font{" + font + "}";
    }
    void ConvertParagraph() override {
        tex->content += "\n\n";
    }
    shared_ptr<TeXText> GetTeXText() { return tex; }
};

// ======= Director =======
class RTFReader {
    TextConverter* builder; // Builder를 주입받음
public:
    RTFReader(TextConverter* b) : builder(b) {}

    void ParseRTF() {
        // 실제로는 RTF 토큰을 파싱해야 하지만, 예제에서는 단순화
        string tokens = "ABC\nFONT Times\nDEF\n";
        for (size_t i = 0; i < tokens.size(); ++i) {
            char t = tokens[i];
            if (t == '\n') {
                builder->ConvertParagraph();
            } else if (t == 'F') { // "FONT Times"를 가정
                builder->ConvertFontChange("Times");
                i += 10; // FONT Times 문자열 스킵
            } else {
                builder->ConvertCharacter(t);
            }
        }
    }
};

// ======= 클라이언트 =======
int main() {
    // ASCII로 변환
    ASCIIConverter asciiBuilder;
    RTFReader reader1(&asciiBuilder);
    reader1.ParseRTF();
    cout << "[ASCII 결과]" << endl;
    cout << asciiBuilder.GetASCIIText()->content << endl;

    // TeX으로 변환
    TeXConverter texBuilder;
    RTFReader reader2(&texBuilder);
    reader2.ParseRTF();
    cout << "\n[TeX 결과]" << endl;
    cout << texBuilder.GetTeXText()->content << endl;

    return 0;
}
