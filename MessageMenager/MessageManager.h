#pragma once
#include "Vector.hpp"
#include "Message.h"

class MessageManager
{
	Vector<Message> messages;

public: 
	void addMessage(const Message& message);
	void printUnreadMessages() const;
	void removeMessage(int messageId);
	void deleteAllMessages();
	void printAllMessages() const;
};

