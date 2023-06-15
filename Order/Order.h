#pragma once
#include "SharedPtr.hpp"
#include "MyString.h"
#include "Client.h"
#include "Driver.h"
#include "Address.h"

template<typename T>
class SharedPtr;

class Client;

enum class Status
{
	Pending,
	Accepted,
	InProgress,
	Completed,
	Canceled
};

MyString toStringStatus(Status status);

enum class PaymentStatus
{
	Paid,
	Pending,
	NotPaid
};

MyString toStringPaymentStatus(PaymentStatus status);

class Order
{
private:
	static int nextId;
	unsigned int id;
	Address start;
	Address destination;
	unsigned short passengersCount;
	Status status;
	PaymentStatus paymentStatus;
	double paymentAmount;
	SharedPtr<Client> client;
	SharedPtr<Driver> driver;

public:
	Order(const Address& startAddress, const Address& destination,
		int numberOfPassengers, Status status, PaymentStatus paymentStatus,
		double paymentAmount, SharedPtr<Client> client, SharedPtr<Driver> driver);
	Order(const Address& startAddress, const Address& destination, int numberOfPassengers);
	Order();

	unsigned int getId() const;
	const Address& getStartAddress() const;
	const Address& getDestination() const;
	unsigned short getPassengerCount() const;
	Status getStatus() const;
	PaymentStatus getPaymentStatus() const;
	double getPaymentAmount() const;
	SharedPtr<Client> getClient() const;
	SharedPtr<Driver> getDriver() const;

	void setStartAddress(const Address& start);
	void setDestination(const Address& destination);
	void setPassengerCount(unsigned short passengersCount);
	void setStatus(Status status);
	void setPaymentStatus(PaymentStatus status);
	void setPaymentAmount(double amount);
	void setClient(SharedPtr<Client> client);
	void setDriver(SharedPtr<Driver> driver);

    void saveOrderToFile(const Order& order, const char* fileName);
	void printOrderDetails() const;
};