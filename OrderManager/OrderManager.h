#pragma once
#include"Vector.hpp"
#include "Order.h"

class Order;
enum class Status;

class OrderManager
{
	Vector<Order> orders;

public:

	void addOrder(const Order& order);
	void removeOrder(unsigned int orderId);
	Order* findOrderById(unsigned int orderId);
	Vector<Order> getOrdersByStatus(Status status);
	void printAllOrders() const;
};