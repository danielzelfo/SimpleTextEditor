#include <string>
using namespace std;

template <typename E>
class List {
protected:
	/* List<E> data members
	* Node - node struct used to make instances of nodes for doubly linked list
	* head - front of doubly linked list
	* tail - back of doubly linked list
	* listSize - size of list (number of elements)
	*/
	struct Node{
		/* members:
		 * data - the actual data being held
		 * prev - points to previous node
		 * next - points to next node
		 */
		E data;
		Node* prev;
		Node* next;
	};

private:
	Node* head;
	Node* tail;
	int listSize;

public:
	//declaring the list constructor
	List();

	//delcaring the Iterator class
	class Iterator {
	private:
		// Data member: curNode - the node that the iterator currently represents
		Node* curNode;

		//declaring the Iterator constructor with a node parameter, which will be private so it  can only be used by the List<E> 
		Iterator(Node*);
		Iterator();
	public:
		//declaring all the oeprator functions
		E& operator*();
		bool operator==(const Iterator&) const;
		bool operator!=(const Iterator&) const;
		Iterator& operator++();
		Iterator& operator--();


		//giving the List class access to private members
		friend class List<E>;
		friend class SimpleTextEditor;
	};

	//declaring the begin and end functions
	Iterator begin() const;
	Iterator end() const;

	//declaring the size and empty functions
	int size() const;
	bool empty() const;

	//declaring the inserting functions
	void insertFront(const E&);
	void insertBack(const E&);
	void insert(const Iterator&, const E&);

	//declaring the erasing functions
	void eraseFront();
	void eraseBack();
	void erase(const Iterator&);

	//the print function
	void print();

	//index to position
	Iterator atIndex(int i) const;
	//position to index
	int indexOf(const Iterator p) const;
};

//the List<E> constructor
template <typename E>
List<E>::List() {
	//setting the list size to 0
	listSize = 0;

	//pointing head and tail empty nodes
	head = new Node;
	tail = new Node;

	//making tail the next of head and head the previous of tail
	head->next = tail;
	tail->prev = head;
}

//the begin function
template <typename E>
auto List<E>::begin() const -> List<E>::Iterator {
	//returns the next of the dummy header
	return Iterator(head->next);
}


//the end function
template <typename E>
auto List<E>::end() const -> List<E>::Iterator {
	//returns the trailer
	return Iterator(tail->prev);
}


//the size function
template <typename E>
int List<E>::size() const {
	return listSize;
}
//the empty function
template <typename E>
bool List<E>::empty() const {
	return (listSize == 0);
}


//the insert function - to insert at a given position (iterator)
template <typename E>
void List<E>::insert(const List<E>::Iterator& position, const E& data) {
	//getting the node at the given position
	Node* posNode = position.curNode;
	//getting the node before the given position
	Node* leftNode = posNode->prev;

	//creating a new node with the given data and setting the previous and next
	Node* newNode = new Node;
	newNode->data = data;
	newNode->prev = leftNode;
	newNode->next = posNode;

	//making the previos of node at the given position the new node
	posNode->prev = newNode;
	//making the next of the node at the given position the new node4
	leftNode->next = newNode;

	//incrementing the size
	listSize++;
}

//the insertFront function - uses the insert at the begin
template <typename E>
void List<E>::insertFront(const E& elem) {
	insert(begin(), elem);
}
//the insertFront function - uses the insert at the end
template <typename E>
void List<E>::insertBack(const E& elem) {
	insert(++end(), elem);
}

//the erase function removes the ndoe at a given postion
template <typename E>
void List<E>::erase(const Iterator& position) {
	//getting the node at the given postion
	Node* posNode = position.curNode;
	//getting the nodes previous and next to the node being removed
	Node* leftNode = posNode->prev;
	Node* rightNode = posNode->next;

	//linking the left and right nodes
	leftNode->next = rightNode;
	rightNode->prev = leftNode;

	//deleting the node at the given postion
	delete posNode;

	//decrementing the list size
	listSize--;
}
//the eraseFront function - calls the erase function at the begin
template <typename E>
void List<E>::eraseFront() {
	erase(begin());
}
//the eraseFront function - calls the erase function one before the end
template <typename E>
void List<E>::eraseBack() {
	erase(end());
}

//Iterator constructor
template <typename E>
List<E>::Iterator::Iterator(Node* theNode) {
	curNode = theNode;
}

//Iterator constructor
template <typename E>
List<E>::Iterator::Iterator() {
	curNode = nullptr;
}

//this operator (*) returns the data at the current iterator
template <typename E>
E& List<E>::Iterator::operator*() {
	return curNode->data;
}

//the comparison operators (== & !=) return a boolean
template <typename E>
bool List<E>::Iterator::operator==(const Iterator& otherIt) const {
	return (curNode == otherIt.curNode);
}
template <typename E>
bool List<E>::Iterator::operator!=(const Iterator& otherIt) const {
	return (curNode != otherIt.curNode);
}

//the incrementing operator (++) makes the iterator point to the next node
template <typename E>
auto List<E>::Iterator::operator++() -> List<E>::Iterator & {
	curNode = curNode->next;
	return *this;
}
//the decrementing operator (--) makes the iterator point to the previous node
template <typename E>
auto List<E>::Iterator::operator--() ->List<E>::Iterator & {
	curNode = curNode->prev;
	return *this;
}


//the print function - displays all the items in the list
template <typename E>
void List<E>::print() {
	cout << "{ ";
	for (Iterator it = begin(); it != ++end(); ++it) {
		cout << "\"" << *it << "\" ";
	}
	cout << "}";
}

template <typename E>
auto List<E>::atIndex(int i) const -> List<E>::Iterator {
	//getting an iterator for the front of the sequence
	Iterator p = begin();
	//while the given index is greater than 0 and we decrement it by 1, we will increase out iterator
		while (i-- > 0) ++p;
	return p;
}
// get index from position
template <typename E>
int List<E>::indexOf(Iterator p) const {
	
	int j = 0;
	//getting an iterator for 1 before the front of the list because we will increment it in the first time we check the condition
	Iterator q = --begin();
	//incrementing our index while we increasing our iterator and it has not reached the given iterator
	while (++q != p) { j++;}
	
	return j;
}