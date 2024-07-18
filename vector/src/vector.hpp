#include "iterator.hpp"

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
public:
	using type = T;
	using Iterator = Iterator<Vector<T, Allocator>>;

	Vector(const Allocator& alloc = Allocator()): size(0), capacity(0), alloc(alloc) {	}
	~Vector() { alloc.deallocate(ptr, capacity); }
	Vector(const Vector<T>& other);
	Vector(const Vector<T>& other, const Allocator& alloc);
	Vector(Vector&& other);

	void push_back(const T& data);
	void pop_back();
	void reserve(size_t new_capacity);
	void resize(size_t new_size);
	void shrink_to_fit();
	void clear();
	void swap(Vector<T>& other);

	T& operator[](size_t index);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);

	size_t get_size() { return size; }
	size_t get_capacity() { return capacity; }
	bool empty() { return !size; }

	Iterator begin() { return Iterator(ptr); }
	Iterator end() { return Iterator(ptr + size); }
	
private:
	T* ptr;
	Allocator alloc;
	size_t size;
	size_t capacity;
};

template<typename T, typename Allocator>
inline Vector<T, Allocator>::Vector(const Vector<T>& other) : size(other.size), capacity(other.capacity), alloc(other.alloc) {
	ptr = alloc.allocate(capacity);
	for (size_t i = 0; i < size; i++) {
		ptr[i] = other.ptr[i];
	}
}

template<typename T, typename Allocator>
inline Vector<T, Allocator>::Vector(const Vector<T>& other, const Allocator& alloc) : size(other.size), capacity(other.capacity), alloc(alloc) {
	ptr = alloc.allocate(capacity);
	for (size_t i = 0; i < size; i++) {
		ptr[i] = other.ptr[i];
	}
}

template<typename T, typename Allocator>
inline Vector<T, Allocator>::Vector(Vector&& other) : size(other.size), capacity(other.capacity), ptr(other.ptr) {
	other.ptr = nullptr;
	alloc.deallocate(other.ptr, 0);

	other.size = 0;
	other.capacity = 0;
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::push_back(const T& data) {
	if (size == 0 && !ptr) {
		capacity = 1;
		ptr = alloc.allocate(capacity);
	}

	if (size == capacity) {
		capacity = capacity << 2;
		T* temp_arr = alloc.allocate(capacity);

		for (size_t i = 0; i < size; i++) {
			temp_arr[i] = ptr[i];
		}
		alloc.deallocate(ptr, capacity >> 2);
		ptr = temp_arr;

		temp_arr = nullptr;
		alloc.deallocate(temp_arr, 0);
	}

	ptr[size] = data;
	++size;
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::pop_back() {
	--size;
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::reserve(size_t new_capacity) {
	T* temp_ptr = alloc.allocate(new_capacity);

	for (size_t i = 0; i < size; i++) {
		temp_ptr[i] = ptr[i];
	}
	alloc.deallocate(ptr, capacity);
	capacity = new_capacity;
	ptr = temp_ptr;

	temp_ptr = nullptr;
	alloc.dealloc(temp_ptr, 0);
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::resize(size_t new_size) {
	if (new_size > capacity) {
		T* temp_ptr = alloc.allocate(new_size);
		
		for (size_t i = 0; i < size; i++) {
			temp_ptr[i] = ptr[i];
		}
		alloc.deallocate(ptr, capacity);
		capacity = new_size;
		size = new_size;
		ptr = temp_ptr;

		temp_ptr = nullptr;
		alloc.deallocate(temp_ptr, 0);

		return;
	}

	size = new_size;

}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::shrink_to_fit() {
	if (capacity > size) {
		T* temp_ptr = alloc.allocate(size);

		for (size_t i = 0; i < size; i++) {
			temp_ptr[i] = ptr[i];
		}

		alloc.deallocate(ptr, capacity);
		ptr = temp_ptr;

		temp_ptr = nullptr;
		alloc.deallocate(temp_ptr, 0);
	
		capacity = size;
	}
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::clear() {
	size = 0;
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::swap(Vector<T>& other) {
	T* temp_ptr = alloc.allocate(capacity);
	size_t temp_size = size;
	size_t temp_capacity = capacity;

	for (size_t i = 0; i < size; i++) {
		temp_ptr[i] = ptr[i];
	}
	
	alloc.deallocate(ptr, capacity);
	ptr = alloc.allocate(other.capacity);
	for (size_t i = 0; i < other.size; i++) {
		ptr[i] = other[i];
	}

	alloc.deallocate(other.ptr, other.capacity);
	other.ptr = alloc.allocate(capacity);
	for (size_t i = 0; i < size; i++) {
		other.ptr[i] = temp_ptr[i];
	}

	alloc.deallocate(temp_ptr, capacity);

	size = other.size;
	capacity = other.capacity;
	
	other.size = temp_size;
	other.capacity = temp_capacity;
}

template<typename T, typename Allocator>
inline T& Vector<T, Allocator>::operator[](size_t index){
	if (index >= size) {
		throw("error of capacity");
	}

	return ptr[index];
}

template<typename T, typename Allocator>
inline Vector<T>& Vector<T, Allocator>::operator=(const Vector<T>& other) {
	if (ptr) {
		alloc.deallocate(ptr, capacity);
	}

	alloc.allocate(ptr, other.capacity);
	for (size_t i = 0; i < other.size; i++) {
		ptr[i] = other.ptr[i];
	}

	size = other.size;
	capacity = other.capacity;

	return *this;
}

template<typename T, typename Allocator>
inline Vector<T>& Vector<T, Allocator>::operator=(Vector<T>&& other) {
	if (ptr) {
		alloc.deallocate(ptr, capacity);
	}

	ptr = other.ptr;
	size = other.size;
	capacity = other.capacity;

	other.ptr = nullptr;
	alloc.deallocate(other.ptr, 0);
	other.size = 0;
	other.capacity = 0;

	return *this;
}