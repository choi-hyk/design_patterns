// https://velog.io/@choi-hyk/Design-Pattern-Abstract-Factory-Pattern

#include <iostream>
#include <memory>
using namespace std;

// ===== Abstract Product =====
class Document {
public:
    virtual void open() = 0;
    virtual void save() = 0;
    virtual void close() = 0;
    virtual ~Document() = default;
};

// ===== Concrete Product (MS) =====
class MsTextDocument : public Document {
public:
    void open() override  { cout << "[MS] 텍스트 문서를 엽니다.\n"; }
    void save() override  { cout << "[MS] 텍스트 문서를 저장합니다.\n"; }
    void close() override { cout << "[MS] 텍스트 문서를 닫습니다.\n"; }
};

class MsSpreadsheetDocument : public Document {
public:
    void open() override  { cout << "[MS] 스프레드시트 문서를 엽니다.\n"; }
    void save() override  { cout << "[MS] 스프레드시트 문서를 저장합니다.\n"; }
    void close() override { cout << "[MS] 스프레드시트 문서를 닫습니다.\n"; }
};

// ===== Concrete Product (Mac) =====
class MacTextDocument : public Document {
public:
    void open() override  { cout << "[Mac] 텍스트 문서를 엽니다.\n"; }
    void save() override  { cout << "[Mac] 텍스트 문서를 저장합니다.\n"; }
    void close() override { cout << "[Mac] 텍스트 문서를 닫습니다.\n"; }
};

class MacSpreadsheetDocument : public Document {
public:
    void open() override  { cout << "[Mac] 스프레드시트 문서를 엽니다.\n"; }
    void save() override  { cout << "[Mac] 스프레드시트 문서를 저장합니다.\n"; }
    void close() override { cout << "[Mac] 스프레드시트 문서를 닫습니다.\n"; }
};

// ===== Abstract Factory =====
class AbstractFactory {
public:
    virtual unique_ptr<Document> createTextDocument() = 0;
    virtual unique_ptr<Document> createSpreadsheetDocument() = 0;
    virtual ~AbstractFactory() = default;
};

// ===== Concrete Factories =====
class MicrosoftFactory : public AbstractFactory {
public:
    unique_ptr<Document> createTextDocument() override {
        return make_unique<MsTextDocument>();
    }
    unique_ptr<Document> createSpreadsheetDocument() override {
        return make_unique<MsSpreadsheetDocument>();
    }
};

class MacFactory : public AbstractFactory {
public:
    unique_ptr<Document> createTextDocument() override {
        return make_unique<MacTextDocument>();
    }
    unique_ptr<Document> createSpreadsheetDocument() override {
        return make_unique<MacSpreadsheetDocument>();
    }
};

// ===== Client =====
int main() {
    // 1. Microsoft 환경
    unique_ptr<AbstractFactory> factory = make_unique<MicrosoftFactory>();
    auto doc1 = factory->createTextDocument();
    auto doc2 = factory->createSpreadsheetDocument();

    doc1->open();
    doc1->save();
    doc1->close();

    doc2->open();
    doc2->save();
    doc2->close();

    cout << "---------------------------\n";

    // 2. Mac 환경
    factory = make_unique<MacFactory>();
    auto doc3 = factory->createTextDocument();
    auto doc4 = factory->createSpreadsheetDocument();

    doc3->open();
    doc3->save();
    doc3->close();

    doc4->open();
    doc4->save();
    doc4->close();

    return 0;
}