#include <cstddef>
#include<iostream>

template <typename T>
class Vector final
{
public:

	Vector() {
		size = 0;
		data = nullptr;
	};
	Vector(std::size_t initial_size);

	const T& at(std::size_t index) const;
	T& at(std::size_t index);

	const T& operator[](std::size_t index) const;
	T& operator[](std::size_t index);

	void push_back(const T& value);

	void erase(std::size_t index);

	std::size_t _size() const;

private:
	size_t size{ 0 };
	T* data{ nullptr };
};


template<typename T>
Vector<T>::Vector(std::size_t initial_size)
{
	size = initial_size;
	data = new T[initial_size];
}

template<typename T>
const T& Vector<T>::at(std::size_t index) const
{
	if (index > size - 1) {
		throw std::invalid_argument("This element doesn't exist");
	}
	return data[index];
}

template<typename T>
T& Vector<T>::at(std::size_t index)
{
	if (index > size - 1) {
		throw std::invalid_argument("This element doesn't exist");
	}
	return data[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const
{
	if (index > size - 1) {
		size_t new_size = (((index / size) + 1) * size);
		auto* tmp = new T[new_size];

		memcpy(tmp, data, sizeof(T) * size);
		delete[] data;

		size = new_size;
		data = tmp;
	}
	return data[index];
}

template<typename T>
inline T& Vector<T>::operator[](std::size_t index)
{
	if (index > size - 1) {
		size_t new_size = (((index / size) + 1) * size);
		auto* tmp = new T[new_size];

		memcpy(tmp, data, sizeof(T) * size);
		delete[] data;

		size = new_size;
		data = tmp;
	}
	return data[index];
}

template<typename T>
void Vector<T>::push_back(const T& value)
{
	if (data == nullptr) {
		data = new T[1];
		data[0] = value;
		size++;
	}
	else {
		auto* tmp = new T[size + 1];
		memcpy(tmp, data, sizeof(T) * size);

		tmp[size] = value;
		delete[] data;

		data = tmp;
		size++;
	}
}

template<typename T>
inline void Vector<T>::erase(std::size_t index)
{
	if (data == nullptr) { throw std::invalid_argument("Empty vector!"); }

	auto* tmp = new T[size - 1];
	memcpy(tmp, data, sizeof(T) * (size - index - 1));
	memcpy(tmp + index, data + index + 1, sizeof(T) * (size - index));

	delete[] data;
	data = tmp;
	size--;
}

template<typename T>
std::size_t Vector<T>::_size() const
{
	return size;
}
