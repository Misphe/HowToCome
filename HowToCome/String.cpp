#include "String.h"
#include <string.h>

String::String() {
    string = nullptr;
    size = 0;
}

String::String(const char* other) {
    int length = strlen(other);
    size = length + BUFFOR;
    string = new char[size + 1];
    strcpy(string, other);
    string[length] = '\0';
}

String::String(const String& other) {
    int length = other.size;
    size = length;
    string = new char[size + 1];
    strcpy(string, other.string);
    string[length] = '\0';
}

String::String(String&& other) {
    int length = other.size;
    size = length;
    string = new char[size + 1];
    strcpy(string, other.string);
    string[length] = '\0';
    other.Reset();
}

String::~String() {
    delete[] string;
    size = 0;
    string = nullptr;
}

String& String::operator=(const char* other) {
    if (other == nullptr) {
        string = nullptr;
        size = 0;
        return *this;
    }

    int length = strlen(other);
    if (length == 0) {
        delete[] string;
        size = 0;
        string = nullptr;
        return *this;
    }
    if (size < length) {
        delete[] string;
        size = length + BUFFOR;
        string = new char[size + 1];
        strcpy(string, other);
        string[length] = '\0';
    }
    else {
        strcpy(string, other);
        string[length] = '\0';
    }

    return *this;
}


String& String::operator=(const String& other) {
    int length = strlen(other.string);
    if (size < length) {
        delete[] string;
        size = length + BUFFOR;
        string = new char[size + 1];
        strcpy(string, other.string);
        string[length] = '\0';
    }
    else {
        strcpy(string, other.string);
        string[length] = '\0';
    }

    return *this;
}

String& String::operator=(String&& other) {
    int length = strlen(other.string);
    if (size < length) {
        delete[] string;
        size = length + BUFFOR;
        string = new char[size + 1];
        strcpy(string, other.string);
        string[length] = '\0';
    }
    else {
        strcpy(string, other.string);
        string[length] = '\0';
    }

    return *this;
}

String String::operator+(const char* other) {
    String tmp;
    int length1 = GetSize();
    int length2 = strlen(other);
    tmp.string = new char[length1 + length2 + 1];
    if (string != nullptr) {
        strcpy(tmp.string, string);
    }
    strcat(tmp.string, other);
    tmp.string[length1 + length2] = '\0';
    return tmp;
}

String& String::operator+=(const char other) {
    int length = GetSize();
    if (size < length + 1) {
        char* tmp = new char[length + 2];
        if (string != nullptr) {
            strcpy(tmp, string);
        }
        delete[] string;
        size += BUFFOR;
        string = new char[size + 1];
        tmp[length] = other;
        tmp[length + 1] = '\0';
        strcpy(string, tmp);
        delete[] tmp;
        tmp = nullptr;
    }
    else {
        string[length] = other;
        string[length + 1] = '\0';
    }
    return *this;
}

String& String::operator+=(const String& other) {
    int length1 = GetSize();
    int length2 = other.GetSize();
    if (size < length1 + length2 + 1) {
        char* tmp = new char[length2 + length1 + 1];
        if (string != nullptr) {
            strcpy(tmp, string);
        }
        if (other.string != nullptr) {
            strcat(tmp, other.string);
        }
        tmp[length2 + length1] = '\0';
        delete[] string;
        size = length1 + length2 + BUFFOR;
        string = new char[size + 1];
        strcpy(string, tmp);
        delete[] tmp;
        tmp = nullptr;
    }
    else {
        strcat(string, other.string);
    }
    return *this;
}

int String::GetSize() const {
    if (string == nullptr) return 0;
    return strlen(string);
}

char& String::operator[](int i) {
    return string[i];
}

std::ostream& operator<<(std::ostream& output, const String& text) {
    if (text.Empty()) return output;

    output << text.string;
    return output;
}

std::istream& operator>>(std::istream& input, String& string) {
    char tmp[128];
    scanf("%s", tmp);
    int length = strlen(tmp);
    tmp[length] = '\0';
    string.string = new char[length + 1];
    strcpy(string.string, tmp);
    return input;
}

bool String::operator==(const char* other) {
    if (string == nullptr) {
        return false;
    }
    if (strcmp(string, other) == 0) {
        return true;
    }
    return false;
}

bool String::operator==(const String& other) const {
    if (string == nullptr) {
        return false;
    }
    if (strcmp(string, other.string) == 0) {
        return true;
    }
    return false;
}

bool String::operator!=(const char* other) {
    if (string == nullptr) {
        return true;
    }
    if (*this == other) {
        return false;
    }
    return true;
}

char* String::ToChar() {
    char* tmp = new char[GetSize() + 1];
    strcpy(tmp, string);
    return tmp;
}

void String::Reset() {
    if (string != nullptr) {
        delete[] string;
        string = nullptr;
        size = 0;
    }
}

bool String::Empty() const {
    return string == nullptr;
}

const String& String::GetString() const {
    return *this;
}