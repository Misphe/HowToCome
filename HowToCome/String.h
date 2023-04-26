#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <iostream>
#define BUFFOR 10

class String {
private:
	char* string;
	int size;
public:
	String();
	String(const char* other);
	String(const String& other);
	String(String&& other);
	~String();

	String& operator=(const char* other);
	String& operator=(const String& other);
	String operator+(const char* other);
	char& operator[](int i);
	String& operator=(String&& other);

	bool operator==(const char* other);
	bool operator!=(const char* other);
	bool operator==(const String& other) const;
	String& operator+=(const char other);
	String& operator+=(const String& other);

	friend std::ostream& operator<<(std::ostream& output, const String& text);
	friend std::istream& operator>>(std::istream& input, String& text);
	
	int GetSize() const;
	const String& GetString() const;
	char* ToChar();
	void Reset();
	bool Empty() const;
};