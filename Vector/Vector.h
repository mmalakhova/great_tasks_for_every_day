#include <cstddef>
#include<iostream>

template <typename T>
class vector final{
public:

	vector() = default;
	vector(std::size_t initial_size);

	void assert_index_valid(std::size_t index) const;

	const T& at(std::size_t index) const;
	T& at(std::size_t index);

	const T& operator[](std::size_t index) const;
	T& operator[](std::size_t index);

	void push_back(const T& value);
	
	template<typename... Args>
	void emplace_back(Args&&... args);

	void erase(std::size_t index);

	std::size_t _size() const;

	class iterator final
	{
	public:
		iterator() = default;
		iterator(T* ptr) : m_ptr(ptr) {}

		const T& operator->() const { return m_ptr; };
		T& operator->() { return m_ptr; };

		const T& operator*() const { return *m_ptr; };
		T& operator*() { return *m_ptr; };

		iterator& operator++() { ++m_ptr; return *this; };       // Prefix
		iterator operator++(int) { auto cur_it = *this; ++(*this); return cur_it; };     // Postfix

		iterator& operator--() { m_ptr--; return *this; };
		iterator operator--(int) { auto cur_it = *this; --(*this); return cur_it; };

		bool operator==(const iterator& rhs) const { return m_ptr == rhs.m_ptr; };
		bool operator!=(const iterator& rhs) const { return m_ptr != rhs.m_ptr; };
		bool operator<(const iterator& rhs) const { return m_ptr < rhs.m_ptr; };
	private:
		T* m_ptr;
	};

	iterator begin() { return iterator(data); };
	iterator end() { return iterator(data + m_size); };

private:
	std::size_t m_size{ 0 };
	std::size_t m_capacity{ 0 };
	T* data{ nullptr };

	void enlarge();
	static std::size_t power_of_two_upper_bound(std::size_t index);
};


template<typename T>
vector<T>::vector(std::size_t initial_size)
	: m_size(initial_size) {
	m_capacity = power_of_two_upper_bound(initial_size);
	data = new T[initial_size];
}

template <typename T>
void vector<T>::assert_index_valid(std::size_t index) const {
	if (index > m_capacity - 1) {
		throw std::invalid_argument("This element doesn't exist");
	}
}

template<typename T>
const T& vector<T>::at(std::size_t index) const{
	assert_index_valid(index);
	return data[index];
}

template<typename T>
T& vector<T>::at(std::size_t index){
	assert_index_valid(index);
	return data[index];
}

template<typename T>
const T& vector<T>::operator[](std::size_t index) const{

	return data[index];
}

template<typename T>
T& vector<T>::operator[](std::size_t index){

	return data[index];
}

template<typename T>
void vector<T>::enlarge(){
	auto* tempHolder = new T[m_size + 1];
	memcpy(tempHolder, data, sizeof(T) * m_size);
	delete data;
	data = tempHolder;
}

template<typename T>
void vector<T>::push_back(const T& value){
	enlarge();
	data[m_size] = value;
	m_size++;
}



template<typename T>
void vector<T>::erase(std::size_t index){
	if (data == nullptr) { throw std::invalid_argument("Empty vector!"); }

	auto* tmp = new T[m_capacity];
	memcpy(tmp, data, sizeof(T) * (m_size - index - 1));
	memcpy(tmp + index, data + index + 1, sizeof(T) * (m_size - index));

	delete[] data;
	data = tmp;
}

template<typename T>
std::size_t vector<T>::_size() const{
	return m_size;
}


template<typename T>
std::size_t vector<T>::power_of_two_upper_bound(std::size_t index){
	return std::size_t(std::log2f(float(index)) + 0.5f);
}

template<typename T>
template<typename ...Args>
void vector<T>::emplace_back(Args&& ...args){
	if (m_capacity == m_size) enlarge();
	data[m_size++] = new(data + m_size)T(std::forward(args)...);
}
