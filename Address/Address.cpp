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

void Address::setName(const MyString& name)
{
    this->name = name;
}

void Address::setAdditionalInfo(const MyString& additionalInfo)
{
    this->additionalInfo = additionalInfo;
}

std::ostream& operator<<(std::ostream& os, const Address& address)
{
    os << "Name: " << address.name << "\n";
    os << "Coordinates: (" << address.point.x << ", " << address.point.y << ")\n";
    os << "Additional Info: " << address.additionalInfo << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Address& address)
{
    std::cout << "Address name: " << std::endl;
    is >> address.name;
    std::cout << "Address coordinates: " << std::endl;
    is >> address.point.x;
    is >> address.point.y;
    std::cout << "Additional information: " << std::endl;
    is >> address.additionalInfo;

    return is;
}
