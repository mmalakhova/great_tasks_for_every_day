#include <cstddef>
#include<iostream>

std::size_t power_of_two(std::size_t index) {
	size_t y = 1;
	size_t pow = 0;
	while (y < index) {
		y = y * 2;
		pow++;
	}
	return pow;
}

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

	void erase(std::size_t index);

	std::size_t _size() const;

private:
	std::size_t size{ 0 };
	std::size_t capacity{ 0 };
	T* data{ nullptr };

	auto* resize();
};


template<typename T>
vector<T>::vector(std::size_t initial_size)
	: size(initial_size) {
	capacity = power_of_two(initial_size);
	data = new T[initial_size];
}

template <typename T>
void vector<T>::assert_index_valid(std::size_t index) const {
	if (index > capacity - 1) {
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
void vector<T>::push_back(const T& value){
	if (data == nullptr) {
		data = new T[1];
		data[0] = value;
		size++;
		capacity++;
	}
	else {
		auto* tmp = resize();
		tmp[size] = value;
		delete[] data;

		data = tmp;
		size++;
	}
}

template<typename T>
void vector<T>::erase(std::size_t index){
	if (data == nullptr) { throw std::invalid_argument("Empty vector!"); }

	auto* tmp = new T[capacity];
	memcpy(tmp, data, sizeof(T) * (size - index - 1));
	memcpy(tmp + index, data + index + 1, sizeof(T) * (size - index));

	delete[] data;
	data = tmp;
}

template<typename T>
std::size_t vector<T>::_size() const{
	return size;
}

template<typename T>
auto* vector<T>::resize()
{
	auto* tmp = new T[capacity * 2];
	memcpy(tmp, data, sizeof(T) * size);
	return tmp;
}
