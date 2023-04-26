#pragma once
#include "Connection.h"

class City;

class ConnectionList {
private:
    Connection* head;
    Connection* last;
public:
    ConnectionList();
    ~ConnectionList();

    void PushBack(Connection connection);

    City* Find(City& city);
    Connection* Find(City* city);

    void Print();

    bool Empty();
};
