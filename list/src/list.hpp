#include "iterator.hpp"

template<typename T>
class List {
private:

	template<typename T>
	class Node {
	public:
		Node() : next(nullptr), prev(nullptr), data(0) {	};
		Node(T data) : next(nullptr), prev(nullptr), data(data) {	};
		~Node() {
			delete next;
			delete prev;
		};
		
		Node<T>* next;
		Node<T>* prev;
		T data;
	};
	
public:
	using value_type = Node<T>;
	using value = T;
	using iterator = Iterator<List<T>>;

	List() {
		front = nullptr;
		back = nullptr;
		list_size = 0;
	};
	List(T data) : front(data), list_size(1) {};
	List(const List& other) {
			copy_helper(other.front);
	}
	List(List&& other){
		copy_helper(other.front);
		other.clear();
	};
	~List() { 
		clear();
		delete front;
		delete back;
	};
	List<T>& operator=(const List<T>& other) {
		if (this->list_size != 0) {
			clear();
		}
		copy_helper(other.front);
		return *this;
	}
	List<T>& operator=(List<T>&& other) {
		if (this->list_size != 0) {
			clear();
		}
		copy_helper(other.front);
		other.clear();
		return *this;
	}

	void push_back(const T& data);
	void push_front(const T& data);
	void pop_back();
	void pop_front();
	void print();
	void swap(List<T>& other);
	size_t size() { return list_size; };
	bool empty() { return !list_size; };

	iterator begin() { return iterator(front); };
	iterator end() { return iterator(back); }
private:
	Node<T>* front;
	Node<T>* back;
	size_t list_size;

	void print_helper(Node<T>* node);
	void copy_helper(Node<T>* node);
	void clear();
};

template<typename T>
inline void List<T>::push_back(const T& data) {
	Node<T>* tempNode = new Node<T>(data);

	if (list_size == 0) {
		front = tempNode;
		front->next = back;
		++list_size;
		return;
	}

	if (front->next == nullptr) {
		back = tempNode;
		front->next = back;
		back->prev = front;
		++list_size;
		return;
	}

	back->next = tempNode;
	tempNode->prev = back;
	back = back->next;
	++list_size;
}

template<typename T>
inline void List<T>::push_front(const T& data) {
	Node<T>* tempNode = new Node<T>(data);

	if (list_size == 0) {
		front = tempNode;
		front->next = back;
		++list_size;
		return;
	}

	if (front->prev == nullptr) {
		front->prev = tempNode;
		tempNode->next = front;
		front = front->prev;
		++list_size;
		return;
	}
}

template<typename T>
inline void List<T>::pop_back() {
	if (list_size == 0) {
		return;
	}

	if (list_size == 1) {
		front = nullptr;
		back = nullptr;
		--list_size;
		return;
	}

	Node<T>* temp = back;
	back = back->prev;
	back->next = nullptr;
	--list_size;

	temp->next = nullptr;
	temp->prev = nullptr;
	delete temp;
}

template<typename T>
inline void List<T>::pop_front() {
	if (list_size == 0) {
		return;
	}

	if (list_size == 1) {
		front = nullptr;
		back = nullptr;
		--list_size;
		return;
	}

	Node<T>* temp = front;
	front = front->next;
	front->prev = nullptr;
	--list_size;

	temp->next = nullptr;
	temp->prev = nullptr;
	delete temp;
}

template<typename T>
inline void List<T>::print() {
	print_helper(front);
}

template<typename T>
inline void List<T>::clear() {
	while (list_size != 0) {
		pop_back();
	}
}

template<typename T>
inline void List<T>::swap(List<T>& other) {
	Node<T>* temp_front = this->front;
	Node<T>* temp_back = this->back;
	size_t temp_size = this->list_size;

	this->front = other.front;
	this->back = other.back;
	this->list_size = other.list_size;

	other.front = temp_front;
	other.back = temp_back;
	other.list_size = temp_size;
}

template<typename T>
inline void List<T>::print_helper(Node<T>* node) {
	if (node != nullptr) {
		std::cout << node->data;
		print_helper(node->next);
	}

}

template<typename T>
inline void List<T>::copy_helper(Node<T>* node) {
	if (node != nullptr) {
		this->push_back(node->data);
		copy_helper(node->next);
	}
}
