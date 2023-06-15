#pragma once
#include"Vector.hpp"
#include "Order.h"

class Order;
enum class Status;

class OrderManager
{
	Vector<Order> orders;
	OrderManager() {}

	static OrderManager* instance;
public:
	static OrderManager* getInstance();
	void addOrder(const Order& order);
	void removeOrder(unsigned int orderId);
	Order* findOrderById(unsigned int orderId);
	Vector<Order> getOrdersByStatus(Status status);
	void printAllOrders() const;
	void notifyDriversInRange(const Order& order);
	void saveAllOrdersMadeInFile(const char* fileName) const;
	void saveAllUnfinishedOrdersInFile(const char* fileName) const;
	void loadAllUnfinishedOrdersFromFile(const char* fileName);
};