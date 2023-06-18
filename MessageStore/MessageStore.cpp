#include "MessageStore.h"

unsigned int MessageStore::nextId = 1;

void MessageStore::addMessage(const Message& message) 
{
    messages.pushBack(message);
}

void MessageStore::printUnreadMessages() const
{
    for (int i = 0; i < messages.getSize(); i++)
    {
        if (!messages[i].isRead())
        {
            std::cout << messages[i].getContent() << std::endl;
            messages[i].markAsRead();
        }
    }
    std::cout << "Successful operation!" << std::endl;
}

void MessageStore::removeMessage(unsigned int messageId)
{
    for (size_t i = 0; i < messages.getSize(); i++)
    {
        if (messages[i].getId() == messageId)
        {
            messages.popAt(i);
            break;
        }
    }
}

void MessageStore::deleteAllMessages()
{
    messages.clear();
}

void MessageStore::printAllMessages() const
{
    for (int i = 0; i < messages.getSize(); i++)
    {
        std::cout << "Message " << messages[i].getId() << std::endl;
        std::cout << messages[i].getContent() << std::endl;
        messages[i].markAsRead();
    }
}

unsigned int MessageStore::getNextId()
{
    return nextId++;
}

Message* MessageStore::getMessageById(unsigned int messageId)
{
    for (size_t i = 0; i < messages.getSize(); i++)
    {
        if (messages[i].getId() == messageId)
        {
            return &messages[i];
        }
    }
    return nullptr;
}