#include "Rating.h"

Rating::Rating()
       :ratingValue(0), client(nullptr){}

Rating::Rating(int rating, SharedPtr<Client> client)
    : client(client)
{
    setRatingValue(rating);
}

int Rating::getRating() const
{
    return ratingValue;
}

const SharedPtr<Client> Rating::getClient() const
{
    return client;
}

void Rating::setRatingValue(int ratingValue)
{
    if (ratingValue < 1 || ratingValue > 5)
    {
        throw std::out_of_range("The rating value should be between 0 and 5!");
    }
    this->ratingValue = ratingValue;
}
