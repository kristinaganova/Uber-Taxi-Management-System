#include "Message.h"

Message::Message(const MyString& content, unsigned int id) : content(content), id(id) {}

Message::Message(const MyString& content, const SharedPtr<User>& sender, const SharedPtr<User>& receiver, unsigned int id)
    : content(content), sender(sender), receiver(receiver), id(id)
{
    read = false;
}

Message::Message() : Message("", 0) {}

void Message::setReceiver(SharedPtr<User> receiver)
{
    if (receiver)
        this->receiver = receiver;
    else receiver = nullptr;
}

const MyString& Message::getContent() const
{
    markAsRead();
    return content;
}

const SharedPtr<User>& Message::getSender() const
{
    return sender;
}

const SharedPtr<User>& Message::getReceiver() const
{
    return receiver;
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