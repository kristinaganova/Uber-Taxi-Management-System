#include "Message.h"

Message::Message(const MyString& content) : content(content) {}

Message::Message() : Message("") {}

const MyString& Message::getContent() const
{
	markAsRead();
	return content;
}

unsigned int Message::getId() const
{
	return id;
}

bool Message::isRead() const
{
	return read;
}

void Message::markAsRead() const
{
	read = true;
}
