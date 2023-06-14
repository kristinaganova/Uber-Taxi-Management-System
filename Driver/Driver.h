#pragma once
#include "SharedPtr.hpp"
#include "User.h"
#include "Address.h"
#include "MessageManager.h"
#include "OrderManager.h"
#include "Order.h"
#include "Rating.h"

class Rating;
class Order;
class OrderManager;

class Driver : public User
{
	MyString carNumber;
	MyString phoneNumber;
	Address currentAddress;
	SharedPtr<OrderManager> orders;
	Vector<Rating> ratings;

public:
	Driver(const MyString& firstName, const MyString& lastName, const MyString& username, 
		   const MyString& password, const MyString& carNumber, const MyString& phoneNumber);
	Driver();

	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
	const Address& getCurrentAddress() const;

	void setCarNumber(const MyString& carNumber);
	void setPhoneNumber(const MyString& phoneNumber);

	void registerUser() override;
	User* clone() const override;

	void saveRegisteredUserToFile(const User& user, const char* fileName) override;
	Vector<User*> loadRegisteredUserFromFile(const char* fileName) override;

	void receiveMessage(const Message& message);
	void changeAddress(const Address& address);
	void checkMessages();
	void acceptOrder(unsigned int id);
	void declineOrder(unsigned int id);
	void finishOrder(unsigned int id, double amountToBePaid);

	void addRating(const Rating& rating);
	void assignMessage(unsigned int messageID);

	double getAverageRating() const;
};