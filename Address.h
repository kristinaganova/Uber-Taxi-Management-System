#pragma once
#include "MyString.h"
#include <fstream>

class Address
{
protected:
    struct Point
    {
        Point() :x(0), y(0) {}
        Point(int x, int y) :x(x), y(y) {}
        int x;
        int y;
        double getDist(const Point& other) const
        {
            int dx = x - other.x;
            int dy = y - other.y;

            return sqrt(dx * dx + dy * dy);
        }
    };
private :
    MyString name;
    Point point;
    MyString additionalInfo;

public:
    Address();
    Address(const MyString& name, int x, int y, const MyString& additionalInfo);

    const MyString& getName() const;
    
    const MyString& getAdditionalInfo() const;

    const Point& getPoint() const;

    void setName(const MyString& name);
  
    void setPoint(const Point& point);

    void setAdditionalInfo(const MyString& additionalInfo);

   friend std::ostream& operator<<(std::ostream& os, const Address& address);
   friend std::istream& operator>>(std::istream& os, Address& address);

};
std::ostream& operator<<(std::ostream& os, const Address& address);
std::istream& operator>>(std::istream& os, Address& address);