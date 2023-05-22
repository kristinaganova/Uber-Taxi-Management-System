#pragma once
#include "MyString.h"

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
};