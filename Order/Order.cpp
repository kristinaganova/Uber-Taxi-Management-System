#include "Order.h"

int Order::nextId = 0;

Order::Order(const Address& startAddress, const Address& destination,
    int numberOfPassengers, Status status, PaymentStatus paymentStatus,
    double paymentAmount, SharedPtr<Client> client, SharedPtr<Driver> driver)
    : id(nextId++), start(startAddress), destination(destination), passengersCount(numberOfPassengers),
    status(status), paymentStatus(paymentStatus), paymentAmount(paymentAmount),
    client(client), driver(driver) {}

Order::Order(const Address& startAddress, const Address& destination, int numberOfPassengers)
      :id(nextId++), status(Status::Pending), paymentStatus(PaymentStatus::Pending), start(startAddress), destination(destination), passengersCount(numberOfPassengers) {}

unsigned int Order::getId() const
{
    return id;
}

const Address& Order::getStartAddress() const
{
    return start;
}

const Address& Order::getDestination() const
{
    return destination;
}

unsigned short Order::getPassengerCount() const
{
    return passengersCount;
}

Status Order::getStatus() const
{
    return status;
}

SharedPtr<Client> Order::getClient() const
{
    return client;
}

SharedPtr<Driver> Order::getDriver() const
{
    return driver;
}

void Order::setStartAddress(const Address& start)
{
    this->start = start;
}

void Order::setDestination(const Address& destination)
{
    this->destination = destination;
}

void Order::setPassengerCount(unsigned short passengersCount)
{
    if (passengersCount = 0 || passengersCount > 4)
    {
        throw std::out_of_range("The passengers seats are maximum of 4!");
    }
    this->passengersCount = passengersCount;
}

void Order::setStatus(Status status)
{
    this->status = status;
}

void Order::setPaymentStatus(PaymentStatus status)
{
    this->paymentStatus = status;
}

void Order::setPaymentAmount(double amount)
{
    this->paymentAmount = amount;
}

void Order::setClient(SharedPtr<Client> client)
{
    this->client = client;
}

void Order::setDriver(SharedPtr<Driver> user)
{
    this->driver = driver;
}

void Order::printOrderDetails() const
{
    std::cout << "Order ID: " << id << std::endl;
    std::cout << "Start Address: " << start.getName() << std::endl;
    std::cout << "Destination: " << destination.getName() << std::endl;
    std::cout << "Passenger Count: " << passengersCount << std::endl;
}

PaymentStatus Order::getPaymentStatus() const
{
    return paymentStatus;
}

double Order::getPaymentAmount() const
{
    return paymentAmount;
}
