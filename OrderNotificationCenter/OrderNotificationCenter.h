#include <iostream>
#include <vector>
#include "Message.h"
#include "Driver.h"
#include "Order.h"

class OrderNotificationCenter 
{
public:
    void notifyOrderStatusChange(const Order& order, Status newStatus);

    void notifyDriverAcceptedOrder(const Order& order, const SharedPtr<Driver>& driver);

    void registerDriver(Driver* driver);

    unsigned int getNextMessageId();

private:
    UserManager users;
    unsigned int lastMessageId = 0;
};
