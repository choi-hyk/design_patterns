// https://velog.io/@choi-hyk/Design-Patterns-Singleton-Pattern

#include <iostream>
#include <mutex>
using namespace std;

class Singleton {
private:
    Singleton() {
        cout << "Singleton 생성됨" << endl;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* _instance;
    static mutex mtx;

public:
    static Singleton* getInstance() {
        if (_instance == nullptr) {
            lock_guard<mutex> lock(mtx);
            if (_instance == nullptr) {
                _instance = new Singleton();
            }
        }
        return _instance;
    }

    void doSomething() {
        cout << "싱글톤 객체에서 메서드 호출됨" << endl;
    }
};

Singleton* Singleton::_instance = nullptr;
mutex Singleton::mtx;

int main() {
    Singleton* s1 = Singleton::getInstance();
    s1->doSomething();

    Singleton* s2 = Singleton::getInstance();
    s2->doSomething();

    cout << "주소 비교: " << s1 << " == " << s2 << endl;
    return 0;
}
