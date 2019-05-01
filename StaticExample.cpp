// Design Discussion ...

#include <iostream>
#include <list>

class CADio
{
public:
    CADio() {};
    virtual void printVerts() {};
};

class STLio : public CADio
{
public:
	STLio() {};
	virtual void printVerts() override {
		std::cout << "STL" << std::endl;
	};
};

// ... Same for Parasolid etc 

std::list<CADio*>& CADios(CADio* iop)
{
    static std::list<CADio*> p;
    if(iop) p.push_back(iop);
    return p;
}

class Collector{
public:
    Collector(CADio * b){
        CADios(b);
    }
};


static Collector my_coll(new CADio());


int main() {
    
    auto mods = CADios(nullptr);
    std::cout << mods.size() << std::endl; // returns 1
    
    return 0;
}

