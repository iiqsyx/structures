
template<typename List>
class Iterator {
	using value_type = typename List::value_type;
	using value = typename List::value;
public:
	Iterator(value_type* pointer) : current_element(pointer) {	}
	~Iterator() {
		current_element = nullptr;
		delete current_element;
	}

	value& operator*() const { return current_element->data; }
	void operator++() {
		if (current_element->next == nullptr) {
			throw("iterating out of the range");
		}
		current_element = current_element->next;
	}
	void operator--() {
		if (current_element->prev == nullptr) {
			throw("iterating out of the range");
		}
		current_element = current_element->prev;
	}
	bool operator!=(const Iterator& other_element) {
		return current_element != other_element.current_element;
	}
	bool operator==(const Iterator& other_element) {
		return current_element == other_element.current_element;
	}

private:
	value_type* current_element;
};