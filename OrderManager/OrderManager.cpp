#include "OrderManager.h"
#include "UserManager.h"

OrderManager* OrderManager::instance = nullptr;

OrderManager* OrderManager::getInstance()
{
	if (!instance) 
	{
		instance = new OrderManager();
	}
	return instance;
}

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
			std::cout << "Order canceled successfully" << std::endl;
			return;
		}
	}

	std::cout << "Order with id: " << orderId << " not found!" << std::endl;
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

void  OrderManager::notifyDriversInRange(const Order& order)
{
	const Address& startAddress = order.getStartAddress();
	const Vector<Driver*>& drivers = UserManager::getInstance().getDrivers(); 

	for (int i = 0; i<drivers.getSize(); i++)
	{
		const Address& driverAddress = drivers[i]->getCurrentAddress();
		double distance = startAddress.getPoint().getDist(driverAddress.getPoint());

		if (distance <= 10)
		{
			MyString messageContent = "New order available: Order ID - " + MyString::valueOf(order.getId()) +
				", Start Address - " + startAddress.getName() +
				", Destination - " + order.getDestination().getName();

			Message message(messageContent, MessageManager::getInstance().getNextId());
			MessageManager::getInstance().addMessage(message);

			drivers[i]->assignMessage(message.getId());
		}
	}
}
