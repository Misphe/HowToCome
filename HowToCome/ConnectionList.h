#pragma once
#include "Connection.h"

class City;

class ConnectionList {
public:
    Connection* head;
    Connection* last;

    ConnectionList();
    ~ConnectionList();

    void PushBack(Connection* connection);

    City* Find(City& city);
    Connection* Find(City* city);

    void Print();

    bool Empty();
};
