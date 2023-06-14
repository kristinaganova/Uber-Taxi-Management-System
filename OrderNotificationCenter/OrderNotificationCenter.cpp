#include "OrderNotificationCenter.h"

void OrderNotificationCenter::notifyOrderStatusChange(const Order& order, Status newStatus)
{
    if (newStatus == Status::Canceled)
    {
        SharedPtr<Driver> driver = order.getDriver();
        if (driver)
        {
            MyString message = "Order " + MyString::valueOf(order.getId()) + " has been canceled.";

            Message notification(message, getNextMessageId());
            UniquePointer<MessageStore>& driverMessages = driver->getMessages();

            driverMessages->addMessage(notification);
        }
    }
}

void OrderNotificationCenter::notifyDriverAcceptedOrder(const Order& order, const SharedPtr<Driver>& driver)
{
    SharedPtr<Client> client = order.getClient();

    if (client)
    {
        MyString messageContent = "Your order has been accepted by" + driver->getFirstName() + "The driver is on their way.";
        Message notification(messageContent, client->getMessages()->getNextId());
        client->getMessages()->addMessage(notification);

        std::cout << "Notification sent to client (ID: " << client->getFirstName() << "): " << messageContent << std::endl;
    }
}

void OrderNotificationCenter::registerDriver(Driver* driver)
{
    users.getDrivers().pushBack(driver);
}

unsigned int OrderNotificationCenter::getNextMessageId()
{
    return ++lastMessageId;
}
