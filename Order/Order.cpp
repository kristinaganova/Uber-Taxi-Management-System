#include "Order.h"
#include <fstream>

MyString toStringStatus(Status status)
{
    if (status == Status::Pending)
    {
        return "Pending";
    }
    else if (status == Status::Accepted)
    {
        return "Accepted";
    }
    else if (status == Status::InProgress)
    {
        return "In progress";
    }
    else if (status == Status::Completed)
    {
        return "Completed";
    }
    else if (status == Status::Canceled)
    {
        return "Canceled";
    }
    return "Unknown";
}

MyString toStringPaymentStatus(PaymentStatus status)
{
    if (status == PaymentStatus::Pending)
    {
        return "Pending";
    }
    else if (status == PaymentStatus::Paid)
    {
        return "Paid";
    }
    else if (status == PaymentStatus::NotPaid)
    {
        return "Not paid";
    }
    return "Unknown";
}

int Order::nextId = 1;

Order::Order(): id(1), start("", 0, 0, ""),  destination("", 0, 0, ""), passengersCount(0), status(Status::Pending), paymentStatus(PaymentStatus::NotPaid), paymentAmount(0),client(nullptr), driver(nullptr) {}

Order::Order(const Address& startAddress, const Address& destination,
    int numberOfPassengers, Status status, PaymentStatus paymentStatus,
    double paymentAmount, SharedPtr<Client> client, SharedPtr<Driver> driver)
    : id(nextId++), start(startAddress), destination(destination), passengersCount(numberOfPassengers),
    status(status), paymentStatus(paymentStatus), paymentAmount(paymentAmount)
{
    setClient(client);
    setDriver(driver);
}

Order::Order(const Address& startAddress, const Address& destination, int numberOfPassengers)
      :id(nextId++), status(Status::Pending), paymentStatus(PaymentStatus::Pending), start(startAddress), destination(destination), passengersCount(numberOfPassengers), paymentAmount(0) {}

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
    if (client)
    {
        return client;
    }
    else
    {
        std::cout << "No client found!" << std::endl;
        return SharedPtr<Client>(nullptr);
    }
}

SharedPtr<Driver> Order::getDriver() const
{
    if (driver)
    {
        return driver;
    }
    else
    {
        std::cout << "No driver found!" << std::endl;
        return SharedPtr<Driver>(nullptr); 
    }
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
    if (passengersCount == 0 || passengersCount > 4)
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
    if (client)
        this->client = client;
    else
        this->client = nullptr;
}

void Order::setDriver(SharedPtr<Driver> driver)
{
    if (driver)
        this->driver = driver;
    else
        this->driver = nullptr;
}

void Order::saveOrderToFile(const Order& order, const char* fileName)
{
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open())
    {
        std::cout << "Error: Unable to open file " << fileName << " for writing." << std::endl;
        return;
    }

    if (order.getStatus() == Status::Completed)
    {
        file << order.getId() << " ";
        file << order.getStartAddress() << " ";
        file << order.getDestination() << " ";
        file << order.getPassengerCount() << " ";
        file << order.getPaymentAmount() << " ";

        if (order.getClient())
        {
            file << order.getClient()->getUsername() << " ";
        }
        else
        {
            file << "NULL ";
        }

        if (order.getDriver())
        {
            file << order.getDriver()->getUsername() << " ";
        }
        else
        {
            file << "NULL ";
        }

        file << std::endl;
    }

    file.close();
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