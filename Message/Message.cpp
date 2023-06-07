#include "Message.h"

Message::Message(const MyString& content, unsigned int id) : content(content), id(id) {}

Message::Message() : Message("", 0) {}

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
