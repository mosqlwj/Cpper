#include "python_vm/util/AnimalAST.h"


int main() {

    Dog* dog = new Dog();
    Cat* cat = new Cat();
    Speaker s;
    Feeding f;
    s.visit(dog);
    s.visit(cat);
    f.visit(dog);
    f.visit(cat);
    std::cout << "Hello" << std::endl;

    return 0;
}