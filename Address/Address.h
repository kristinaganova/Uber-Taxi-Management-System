#pragma once
#include "MyString.h"
#include <fstream>

class Address
{
private :
    MyString name;
    double latitude;
    double longitude;
    MyString additionalInfo;

public:
    Address();
    Address(const MyString& name, double latitude, double longitude, const MyString& additionalInfo);

    const MyString& getName() const;
    double getLatitude() const;
    double geLongiitude() const;
    const MyString& getAdditionalInfo() const;

    void setName(const MyString& name);
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setAdditionalInfo(const MyString& additionalInfo);

   friend std::ostream& operator<<(std::ostream& os, const Address& address);
   friend std::istream& operator>>(std::istream& os, Address& address);

};
std::ostream& operator<<(std::ostream& os, const Address& address);
std::istream& operator>>(std::istream& os, Address& address);