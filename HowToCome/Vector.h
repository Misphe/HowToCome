#pragma once
#include <iostream>
#define BUFFER_START 10

template <typename T>
class Vector {
private:
	T* data;
	int capacity;
	int size;
public:
	Vector() {
		capacity = BUFFER_START;
		data = new T[capacity];
		size = 0;
	}
	void Add(T value) {
		if (size < capacity) {
			data[size] = value;
			size++;
		}
		else {
			T* tmp = data;
			capacity *= 2;
			data = new T[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = tmp[i];
			}
			delete[] tmp;
			data[size] = value;
			size++;
		}
	}

	void Add(City*& set_city, City*& source, int& distance) {
		if (size < capacity) {
			data[size] = { set_city, source, distance };
			size++;
		}
		else {
			T* tmp = data;
			capacity *= 2;
			data = new T[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = tmp[i];
			}
			delete[] tmp;
			data[size] = { set_city, source, distance };
			size++;
		}
	}

	T& operator[](int i) {
		if (size > i) {
			return data[i];
		}
		std::cout << "VECTOR OUT OF RANGE IN OPERATOR[]\n";
		return data[i];
	}
	void Clear() {
		size = 0;
	}

	void Reserve(int i) {
		if (size != 0) {
			T* tmp = data;
			capacity = capacity + i;
			data = new T[capacity];
			for (int i = 0; i < size; i++) {
				data[i] = tmp[i];
			}
			delete[] tmp;
		}
		else {
			delete[] data;
			capacity = i;
			data = new T[capacity];
		}
	}

	T* begin() {
		if (size == 0) return nullptr;
		return &data[0];
	}

	T* end() {
		return data + size;
	}

	T& Front() {
		return data[0];
	}

	T& Back() {
		return data[size - 1];
	}

	void PopBack() {
		size--;
	}

	const int& GetSize() {
		return size;
	}

	~Vector() {
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
};
