#include "OrderManager.h"

void OrderManager::addOrder(const Order& order)
{
	orders.pushBack(order);
}

void OrderManager::removeOrder(unsigned int orderId)
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (orders[i].getId() == orderId)
		{
			orders.popAt(i);
		}
	}
}

Order* OrderManager::findOrderById(unsigned int orderId)
{
	for (int i = 0; i< orders.getSize(); i++) 
	{
		if (orders[i].getId() == orderId)
		{
			return &orders[i];
		}
	}
	return nullptr;
}

Vector<Order> OrderManager::getOrdersByStatus(Status status)
{
	Vector<Order> filteredOrders;
	for (int i = 0; i < orders.getSize(); i++)
	{
		if (orders[i].getStatus() == status) 
		{
			filteredOrders.pushBack(orders[i]);
		}
	}
	return filteredOrders;
}

void OrderManager::printAllOrders() const
{
	for (int i = 0; i < orders.getSize(); i++)
	{
		std::cout << "Order: " << orders[i].getId() << std::endl;
		orders[i].printOrderDetails();
	}
}