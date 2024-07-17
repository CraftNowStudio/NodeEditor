#include <iostream>
#include <core/nepch.h>

struct DIY {
    int a;
    int b;
    char *name;

    std::ostream& operator<<(std::ostream& os, const DIY& dt) {
        os << dt.a << "/" << dt.b << "/" << dt.name;
        return os;
    }
};

int main(int argc, char** argv){

    std::cout << "Hello World!" << std::endl;
    NodeEditor::Ref<DIY> d1;
    d1 = NodeEditor::CreateRef<DIY>();

    std::cout << d1 << std::endl;

    return 0;
}