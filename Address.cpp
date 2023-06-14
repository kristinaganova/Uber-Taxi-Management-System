#include "Address.h"

Address::Address():Address("", 0, 0, "") {}

Address::Address(const MyString& name, int x, int y, const MyString& additionalInfo)
        :name(name), point(x,y), additionalInfo(additionalInfo) {}

const MyString& Address::getName() const
{
    return name;
}

const MyString& Address::getAdditionalInfo() const
{
    return additionalInfo;
}

const Address::Point& Address::getPoint() const
{
    return point;
}

void Address::setName(const MyString& name)
{
    this->name = name;
}

void Address::setPoint(const Point& point)
{
    this->point = point;
}

void Address::setAdditionalInfo(const MyString& additionalInfo)
{
    this->additionalInfo = additionalInfo;
}

std::ostream& operator<<(std::ostream& os, const Address& address)
{
    os << address.name << " ";
    os << address.point.x << ", " << address.point.y << " ";
    os << address.additionalInfo << " ";
    return os;
}

std::istream& operator>>(std::istream& is, Address& address)
{
    is >> address.name;
    is >> address.point.x;
    is >> address.point.y;
    is >> address.additionalInfo;

    return is;
}