 // move semantics 
 // influenced by the introduction of rvalues
 //
 
class BigVec 
{
private:
	int     	m_size;
	double*     m_data;
public:
	BigVec() : m_size{0},
			   m_data(nullptr) {};	

	// copy constructor
	BigVec(BigVec& bv) : m_size(bv.m_size) {
		m_data = new double[bv.m_size];
		for(int i = 0; i < m_size; i++) {
			m_data[i] = bv.m_data[i];
		}
	}

	// move contructor
	BigVec(BigVec&& bv) : m_size(bv.m_size), 
						  m_data(bv.m_data) {
		bv.m_data = nullptr;
	}

	~BigVec(){
		if(!m_data) delete m_data;
	}
};


