#include <iostream>

template <typename T>
class shared_ptr {
private:
    const T* m_data;
    mutable size_t* m_counter;

public:
    // constructors
    shared_ptr(T* data) {
        m_data = data;
        m_counter = new size_t;
        *m_counter = 1;
    }
    shared_ptr(const shared_ptr<T>& ptr) {
        *(ptr.m_counter) = *(ptr.m_counter) + 1;
        m_counter = ptr.m_counter;
        m_data = ptr.m_data;
    }

    // destructor
    ~shared_ptr() {
        (*m_counter) = (*m_counter) - 1;
        if (*m_counter == 0) {
            delete m_data;
            delete m_counter;
        }
    }

    int count() { return *m_counter; }
};

int main() {
    shared_ptr<int> ptr(new int(151));
    {
        shared_ptr<int> ptr2 = ptr;
        shared_ptr<int> ptr3 = ptr2;
        {
            shared_ptr<int> ptr4 = ptr3;
            std::cout << ptr.count() << std::endl;
        }
        std::cout << ptr.count() << std::endl;
    }
    std::cout << ptr.count() << std::endl;
}
