

#include <iostream>
#include <atomic>
#include <deque>
#include <mutex>
#include <memory>
#include <thread>
#include <vector>

template<typename T>
class coarse_stack
{
private:
	std::deque<T> s;
	mutable std::mutex m;
public:
	coarse_stack() {
		s.resize(0);
	}
	void push(T item) {
		std::lock_guard<std::mutex> lk(m); // gain lock before push
		s.push_back(std::move(item));
	} // lock released
};

template<typename T>
class fine_stack
{
private:
    struct node
    {
        T data;
        node* next;
        node(T const& data_) : data(data_), next(nullptr){}
    };
    std::unique_ptr<node> head;
    std::mutex m;
public:
	void push(T item) {

		std::unique_ptr<node> new_node = std::make_unique<node>(std::move(item));
		std::lock_guard<std::mutex> lk(m);
		// only cheap operations are locked.
		new_node->next = head.get();
		head = std::move(new_node);
	}
};

template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        T data;
        node* next;
        node(T const& data_):data(data_), next(nullptr){}
    };
    std::atomic<node*> head;
public:

    // verbose push
    void push(T const& data)
    {
        node* const new_node=new node(data);
        // Put the current value of head into new_node->next
        new_node->next=head.load();
        while(true) {
            // We compare the current value of head with the
            // value of new_node->next. If they are not equal
            // then the head could have been modified by a different
            // thread.

            // use of weak instead of strong?
// https://tonywearme.wordpress.com/2014/08/15/understand-stdatomiccompare_exchange_weak-in-c11/
            //
            if(head.compare_exchange_weak(new_node->next,new_node) == false) {
                // CASE : head differs from new_node->next.
                // The value spplied as the first parameter is updated
                // to the current value of head. And we try again ...
                continue;
            } else {
                // CASE : head is equal to new_node->next.
                // In this case we set head to equal new_node
                break;
            }
        }
    }

    // verbose pop

};

namespace {
coarse_stack<std::vector<int>> cs;
fine_stack<std::vector<int>> fs;
lock_free_stack<std::vector<int>> lfs;
}

void pusher(const int count) {
	for(int i = 0; i < count; i++) {
		std::vector<int> t;
		for(int j = 0; j < 1000; j++) {
		    t.push_back(j);
		}
		cs.push(t);
	}
}

// thread_count 1     7
//      coarse  1.3  2.8
//        fine  1.4  2.9
//    lock_free 1.3  2.4
#include <chrono>

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
            (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};


int main(int argc, const char * argv[]) {
    Timer t;
    std::thread t1(pusher, 400000);
    std::thread t2(pusher, 400000);
    std::thread t3(pusher, 400000);
    std::thread t4(pusher, 400000);
    std::thread t5(pusher, 400000);
    std::thread t6(pusher, 400000);
    std::thread t7(pusher, 400000);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    std::cout << t.elapsed() << std::endl;
    std::cout << "Hello, World!\n";
    return 0;
}
