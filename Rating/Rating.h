#pragma once
#include "SharedPtr.hpp"
#include "Client.h"

class Client;

class Rating
{
private:
    int ratingValue;
    SharedPtr<Client> client;

public:
    Rating();
    Rating(int rating, SharedPtr<Client> client);

    int getRating() const;

    const SharedPtr<Client> getClient() const;

    void setRatingValue(int ratingValue);
};