#include "Address.h"

Address::Address():Address("", 0.0, 0.0, "") {}

Address::Address(const MyString& name, double latitude, double longitude, const MyString& additionalInfo)
        :name(name), latitude(latitude), longitude(longitude), additionalInfo(additionalInfo) {}

const MyString& Address::getName() const
{
    return name;
}

double Address::getLatitude() const
{
    return latitude;
}

double Address::geLongiitude() const
{
    return longitude;
}

const MyString& Address::getAdditionalInfo() const
{
    return additionalInfo;
}

void Address::setName(const MyString& name)
{
    this->name = name;
}

void Address::setLatitude(double latitude)
{
    this->latitude = latitude;
}

void Address::setLongitude(double longitude)
{
    this->longitude = longitude;
}

void Address::setAdditionalInfo(const MyString& additionalInfo)
{
    this->additionalInfo = additionalInfo;
}