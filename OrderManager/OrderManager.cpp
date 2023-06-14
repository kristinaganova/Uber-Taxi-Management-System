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

			Message message(messageContent, 0);
			drivers[i]->getMessages()->addMessage(message);
		}
	}
}

void OrderManager::saveAllOrdersMadeInFile(const char* fileName) const
{
	for (size_t i = 0; i < orders.getSize(); i++)
	{
		OrderManager::getInstance()->orders[i].saveOrderToFile(orders[i], fileName);
	}
}

void OrderManager::saveAllUnfinishedOrdersInFile(const char* fileName) const
{
	std::ofstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Error: Unable to open file " << fileName << " for writing." << std::endl;
		return;
	}

	for (size_t i = 0; i < orders.getSize(); i++)
	{
		if (OrderManager::getInstance()->orders[i].getStatus() != Status::Completed || OrderManager::getInstance()->orders[i].getStatus() != Status::Canceled)
		{
			file << OrderManager::getInstance()->orders[i].getId() << " ";
		    file << OrderManager::getInstance()->orders[i].getStartAddress() << " ";
		    file << OrderManager::getInstance()->orders[i].getDestination() << " ";
		    file << OrderManager::getInstance()->orders[i].getPassengerCount() << " ";
			file << OrderManager::getInstance()->orders[i].getPaymentAmount() << " ";

			if (OrderManager::getInstance()->orders[i].getClient())
			{
				file << OrderManager::getInstance()->orders[i].getClient()->getUsername() << " ";
			}
			else
			{
				file << "NULL ";
			}

			if (OrderManager::getInstance()->orders[i].getDriver())
			{
				file << OrderManager::getInstance()->orders[i].getDriver()->getUsername() << " ";
			}
			else
			{
				file << "NULL ";
			}

			file << std::endl;
		}
	}
	file.close();
}

void OrderManager::loadAllUnfinishedOrdersFromFile(const char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cout << "Error: Unable to open file " << fileName << " for reading." << std::endl;
		return;
	}

	unsigned int id;


	while (file >> id )
	{
		Address startAddress;
		Address destination;
		int passengerCount;
		double paymentAmount;
		MyString clientUsername;
		MyString driverUsername;

		file >> startAddress;
		file >> destination;
		file >> passengerCount;
		file >> paymentAmount;
		file >> clientUsername;
		file >> driverUsername;

		Order order(startAddress, destination, passengerCount);


		if (clientUsername != "NULL")
		{
			Client* client = static_cast<Client*>(UserManager::getInstance().findUserByUserName(clientUsername));
			order.setClient(client);
		}

		if (driverUsername != "NULL")
		{
		    Driver* driver = static_cast<Driver*>(UserManager::getInstance().findUserByUserName(driverUsername));
			order.setDriver(driver);
		}

		orders.pushBack(order);
	}

	file.close();
}