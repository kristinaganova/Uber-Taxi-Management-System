#pragma once

#include "Vector.hpp"
#include "Message.h"
#include "UserManager.h"
#include "User.h"

class UserManager;

class MessageManager
{
    static unsigned int nextId;
    Vector<MessageStore> stores;
    UniquePointer<UserManager> users;

    MessageManager();
    
    MessageManager(const MessageManager& other) = delete;
    MessageManager& operator=(const MessageManager& other) = delete;
    
    MessageManager(MessageManager&& other) noexcept = delete;
    MessageManager& operator=(MessageManager&& other) noexcept = delete;
    
public:
    static MessageManager& getInstance();
    void addUserMessageStore(const MessageStore& store);
    UniquePointer<MessageStore>& getUserMessageStore(SharedPtr<User> userStore);
    const Vector<MessageStore>& getMessageStores() const;
    void sendMessage(SharedPtr<User> sender, SharedPtr<User> receiver, const MyString& content);
    unsigned int getNextId() const;
};
