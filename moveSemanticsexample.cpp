#include<iostream>
#include<list>

class BigVec 
{
private:
	int     	m_size;
	double*     m_data;
public:
	// copy constructor
	BigVec(const BigVec& bv) : m_size(bv.m_size) {
		std::cout << "copy called" << std::endl;
		m_data = new double[bv.m_size];
		for(int i=0; i<m_size; i++) { m_data[i] = bv.m_data[i]; }
	}

	// move contructor
	BigVec(BigVec&& bv) : m_size(bv.m_size), 
						  m_data(bv.m_data) {
		std::cout << "move called" << std::endl;
		bv.m_data = nullptr;
	}

	// move assignment operator
	BigVec& operator=(BigVec&& bv) {
		std::cout << "sdfsdf" << std::endl;
		if(this == &bv) return *this; // self referential ?
		delete m_data; 				  // delete current data
		m_data = bv.m_data;
		m_size = bv.m_size;
		// reset object as resources have been moved
		bv.m_data = nullptr;
		bv.m_size = 0;
		return *this;
	}

	BigVec(int size) : m_size(size) {
		std::cout << "toy " << std::endl;
		m_data = new double[size];
		for(int i = 0; i < size; i++) m_data[i] = 0;
	}

	~BigVec() { delete m_data; }
};

BigVec CreateBigVec() {
	return BigVec(100);
}

int main()
{
	// copy constructor is called
	auto v = CreateBigVec();
	BigVec vec(v);

	// move constructor is called
	std::list<BigVec> listOfBigVecs;
	listOfBigVecs.push_back(CreateBigVec());


	return 0;
}
