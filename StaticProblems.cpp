//
//  main.cpp
//  testing
//
//  Created by AnthonyFPP on 30/04/2019.
//  Copyright © 2019 AnthonyFPP. All rights reserved.
//

#include <iostream>
#include <list>

class Base
{
    int hello;
public:
    Base() {};
    virtual void foo(){
        std::cout << "base" << std::endl;
    }
};

class Child : public Base
{
public:
    virtual void foo() override {
        std::cout << "child" << std::endl;
    }
};

std::list<Base*>& thing(Base* bp)
{
    static std::list<Base*> *p = new std::list<Base*>();
    if(bp) p->push_back(bp);
    return *p;
}

class Collection{
public:
    Collection(Base * b){
        thing(b);
    }
};

static Collection my_foo(new Child());


int main(int argc, const char * argv[]) {
    
    Base* b = new Child; // where is this happening in the code?!
    
    // it is happening in the following code, note that a static Collection has
    // been created before we call thing again!
    
    auto mods = thing(nullptr);
    std::cout << mods.size() << std::endl; // returns 1
    
    return 0;
}
