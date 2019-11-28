
#include <array>
#include <iostream>
#include <iterator> // for iterators
#include <deque>
#include <vector>

// we could preallocate some space. 
template<typename T, std::size_t sz>
class CircularBufferSlowButNice {
public:
    void push(T& item) {
        m_q.push_back(item);
        if(m_q.size() > sz) {
            m_q.pop_front();
        }
    }
    std::vector<T> dump() {
        std::vector<T> r;
        for(auto& e : m_q) {
            r.push_back(e);
        }
        return r;
    }
private:
    std::deque<T> m_q;
};

template<typename T, std::size_t sz>
class CircularBufferFastButAlsoNice {
public:
    CircularBufferFastButAlsoNice() : m_index(0), m_is_full(false) {}
    void push(T& item) {
        m_a[m_index++] = item;
        if(m_index == sz) {
            m_is_full = true;
            m_index = 0;
        }
    }
    std::vector<T> dump() {
        std::vector<T> r;
        std::size_t s = m_index;
        if(!m_is_full) {
            for(std::size_t i = 0; i < m_index; ++i) {
                r.push_back(m_a[i]);
            }
            return r;
        }
        for(std::size_t i = s; i < sz; ++i){
            r.push_back(m_a[i]);
        }
        for(std::size_t i = 0; i < s; ++i){
            r.push_back(m_a[i]);
        }
        return r;
    }
private:
    std::array<T, sz> m_a = {};
    std::size_t m_index;
    bool m_is_full;
};


int main(int argc, const char * argv[]) {
    CircularBufferFastButAlsoNice<float, 10> cb;
    for(int i = 0; i < 12; ++i) {
        auto f = 1.0f*i;
        cb.push(f);
    }
    auto d = cb.dump();
    for(auto& a: d) {
        std::cout << a << " ";
    }
    std::cout << "done" << std::endl;
    
    CircularBufferSlowButNice<float, 10> cb1;
    for(int i = 0; i < 12; ++i) {
        auto f = 1.0f*i;
        cb1.push(f);
    }
    d = cb1.dump();
    for(auto& a: d) {
        std::cout << a << " ";
    }
    return 0;
}
