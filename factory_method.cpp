// https://velog.io/@choi-hyk/Design-Pattern-Factory-Method-Pattern

#include <iostream>

class Document {
public:
    virtual void open() = 0;  
    virtual void save() = 0;
    virtual void close() = 0;
    virtual ~Document() = default;
};

class TextDocument : public Document {
public:
    void open() override {
        std::cout << "텍스트 문서를 엽니다." << std::endl;
    }

    void save() override {
        std::cout << "텍스트 문서를 저장합니다." << std::endl;
    }

    void close() override {
        std::cout << "텍스트 문서를 닫습니다." << std::endl;
    }
};

class SpreadsheetDocument : public Document {
public:
    void open() override {
        std::cout << "스프레드시트 문서를 엽니다." << std::endl;
    }

    void save() override {
        std::cout << "스프레드시트 문서를 저장합니다." << std::endl;
    }
    
    void close() override {
        std::cout << "스프레드시트 문서를 닫습니다." << std::endl;
    }
};

class Creator {
public:
    void runDocument() {
        Document* doc = createDocument();  
        doc->open();
        doc->save();
        doc->close();
        delete doc;  
        std::cout << "문서 작업이 완료되었습니다." << std::endl;
    }

    virtual Document* createDocument() = 0;  
    virtual ~Creator() = default;
};

class TextCreator : public Creator {
public:
    Document* createDocument() override {
        return new TextDocument();
    }
};

class SpreadsheetCreator : public Creator {
public:
    Document* createDocument() override {
        return new SpreadsheetDocument();
    }
};

int main() {
    Creator* creator1 = new TextCreator();
    creator1->runDocument();
    delete creator1;

    Creator* creator2 = new SpreadsheetCreator();
    creator2->runDocument();
    delete creator2;

    return 0;
}
