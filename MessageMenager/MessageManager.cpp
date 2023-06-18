#include "User.h"
#include "MessageManager.h"

class User;
class UserManager;

unsigned int MessageManager::nextId = 1;

MessageManager::MessageManager() : users(UserManager::getInstance()), stores() {}

void MessageManager::addAllStores()
{
    for (size_t i = 0; i < users.getUsersCount(); i++)
    {
        stores.pushBack(*users.getUsers()[i]->getMessages());
    }
}

MessageManager& MessageManager::getInstance()
{
    static MessageManager instance;
    return instance;
}

void MessageManager::addUserMessageStore(const MessageStore& store)
{
    stores.pushBack(store);
}

UniquePointer<MessageStore>& MessageManager::getUserMessageStore(SharedPtr<User> userStore)
{
     return userStore->getMessages();
}

const Vector<MessageStore>& MessageManager::getMessageStores() const
{
    return stores;
}

void MessageManager::sendMessage(SharedPtr<User> sender, SharedPtr<User> receiver, const MyString& content)
{
    unsigned int messageId = getNextId();
    Message message(content, sender, receiver, messageId);

    UniquePointer<MessageStore>& receiverMessageStore = getUserMessageStore(receiver);
    receiverMessageStore->addMessage(message);

    std::cout << "New message from " << sender->getUsername() << " to " << receiver->getUsername() << std::endl;
}

unsigned int MessageManager::getNextId() const
{
   return nextId++;
}
