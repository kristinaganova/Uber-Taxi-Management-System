#pragma once
#include "User.h"
#include "Address.h"
#include "OrderManager.h"
#include "helpers.h"
#include "Rating.h"

class OrderManager;
class Order;
class Driver;
enum class Status;

class Client : public User
{
	double balance;
public:
	Client(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password);
	Client(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password, double balance);
	Client();

	void setBalance(double balance);

	double getBalance() const;

	void saveRegisteredUserToFile(const User& user, const char* fileName) override;
	Vector<User*> loadRegisteredUserFromFile(const char* fileName) override;

	void registerUser() override;
	User* clone() const override;

	void checkMessages();
	void placeOrder(const Address& address, const Address& destination, int numberOfPassengers);
	Status checkOrderStatus(OrderManager& orders, unsigned int id);
	void cancelOrder(OrderManager& orders, unsigned int orderId);
	void rateDriver(const MyString& name,  int rating);
	void payOrder(Order& order, double amount);
	void addMoney(double amount);
};