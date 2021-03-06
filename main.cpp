#include <iostream>
#include "signals.h"

using namespace std;

void FunctionSlot() {
    std::cout << "FunctionSlot called" << std::endl;
}

struct FunctionObjectSlot {
    void operator()() {
        std::cout << "FunctionObjectSlot called" << std::endl;
    }
};

class MethodSlotClass {
public:
    void MethodSlot() {
        std::cout << "MethodSlot is called" << std::endl;
    }
};

using namespace std;

int main() {
    my_signal<void()> OnPressed;
    OnPressed.connect([]() { std::cout << "Anonymous function is called" << std::endl; });
    auto tmp = OnPressed.connect(FunctionSlot);
    tmp.disconnect();
    OnPressed();
    std::cout << "Hello, World!" << std::endl;
    my_signal<void()> sig;
    auto conn3 = sig.connect(&FunctionSlot);
    auto conn2 = sig.connect(FunctionObjectSlot());

    auto conn1 = sig.connect([&sig]() { sig.connect(&FunctionSlot); });

    MethodSlotClass methodSlotObject;
    auto conn = sig.connect(std::bind(&MethodSlotClass::MethodSlot, &methodSlotObject));

    sig();

    conn.disconnect();

    std::cout << std::endl;
    sig();

    conn1.disconnect();

    std::cout << std::endl;
    sig();

    conn2.disconnect();

    std::cout << std::endl;
    sig();

    conn3.disconnect();

    std::cout << std::endl;
    sig();
    return 0;
}