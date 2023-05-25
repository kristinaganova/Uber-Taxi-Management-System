#include "MessageManager.h"

void MessageManager::addMessage(const Message& message)
{
	messages.pushBack(message);
}

void MessageManager::printUnreadMessages() const
{
	for (size_t i = 0; i < messages.getSize(); i++)
	{
		if (!messages[i].isRead()) 
		{
			std:: cout << messages[i].getContent() << std::endl;
			messages[i].markAsRead();
		}
	}
}

void MessageManager::removeMessage(int messageId)
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

void MessageManager::deleteAllMessages()
{
    messages.clear();
}

void MessageManager::printAllMessages() const
{
	for (size_t i = 0; i < messages.getSize(); i++)
	{
		std::cout << "Message " << messages[i].getId() << std::endl;
		std::cout << messages[i].getContent() << std::endl;
		messages[i].markAsRead();
	}
}