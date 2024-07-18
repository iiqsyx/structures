
template<typename Vector>
class Iterator {
public:
	using type = typename Vector::type;
	Iterator(type* ptr):ptr(ptr) {};
	~Iterator() { 
		ptr = nullptr;
		delete[]ptr;
	};

	type& operator*() { if(ptr){ return *ptr; } };
	void operator++() { ptr++; }
	void operator--() { ptr--; }
	bool operator ==(const Iterator<Vector>& vec) {
		return ptr == vec.ptr;
	}
	bool operator !=(const Iterator<Vector>& vec) {
		return ptr != vec.ptr;
	}
	bool operator <(const Iterator<Vector>& vec) {
		return ptr < vec.ptr;
	}
	bool operator >(const Iterator<Vector>& vec) {
		return ptr > vec.ptr;
	}

private:
	type* ptr;
};
