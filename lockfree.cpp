
#include <iostream>
#include <atomic>

template<typename T>
class lock_free_stack
{
private:
    struct node
    {
        T data;
        node* next;
        node(T const& data_):data(data_){}
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

int main(int argc, const char * argv[]) {
    lock_free_stack<int> lfs;
    lfs.push(2);
    std::cout << "Hello, World!\n";
    return 0;
}
