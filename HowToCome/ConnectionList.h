#pragma once
#include "Connection.h"

class City;

class ConnectionList {
private:
    Connection* head;
public:
    ConnectionList();

    void PushBack(Connection connection);

    City* Find(City& city);
    Connection* Find(City* city);

    void Print();

    bool Empty();
};
