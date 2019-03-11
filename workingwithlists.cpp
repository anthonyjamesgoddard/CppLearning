#include<iostream>
#include<memory>
using namespace std;

template<typename T>
struct ListNode {
	T data;
	shared_ptr<ListNode<T>> next;
};

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
											  shared_ptr<ListNode<int>> L2){
	// create a placeholder for the result
	shared_ptr<ListNode<int>> dummy_head(new ListNode<int>);
	auto tail = dummy_head;

	while(L1 && L2){
		AppendNode();
	}

	// Appends the remaining nodes of L1 or L2
	tail->next = L1 ? L1 : L2;
	return dummy_head->next;
}

int main()
{
	
}
