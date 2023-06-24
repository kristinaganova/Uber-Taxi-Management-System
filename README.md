# Taxi Company Application Documentation #

## Introduction ##
The Taxi Company Application is a simplified system for managing a taxi company. It allows users to register as clients or drivers and perform various actions within the system, such as ordering taxis, managing orders, tracking drivers, and handling payments.

## System Overview ##
The application streamlines taxi company operations with two user roles: clients and drivers. Clients can register, place orders, track order status, make payments, rate drivers, and add funds to their accounts. Drivers can register, update their address, check messages (orders), accept or decline orders, mark orders as finished, and accept payments.

## User Registration ##
Users can register as clients or drivers by providing necessary information and creating a username and password for their accounts.

- **Client Registration**: Use the command "register client <username> <password> <first_name> <last_name>" and provide additional details as prompted.
- **Driver Registration**: Use the command "register driver <username> <password> <first_name> <last_name> <car_number> <phone_number>" and provide additional details as prompted.

## User Login and Logout ##
Users can securely log in and log out of the application to access their accounts or exit the system.

- **User Login**: Use the command "login <username> <password>" to log in with the registered credentials.
- **User Logout**: Use the command "logout" to securely log out and terminate the session.

## Client Functionalities ##
Clients have access to various features within the application:

- **Ordering a Taxi**: Use the command "order <address> <destination>" to request a taxi.
- **Checking Order Status**: Use the command "check_order <id>" to track the status of a placed order.
- **Cancelling an Order**: Use the command "cancel_order <id>" to cancel a taxi order.
- **Making Payments**: Use the command "pay <id> <amount>" to make payments for completed rides.
- **Rating Drivers**: Use the command "rate <name_of_driver> <rating>" to rate drivers based on ride experience.
- **Adding Funds to Account**: Use the command "add_money <amount>" to add funds to the client's account.

## Driver Functionalities ##
Drivers have access to various features within the application:

- **Changing Current Address**: Use the command "change_address <address>" to update the driver's current address.
- **Checking Messages**: Use the command "check_messages" to review incoming ride requests.
- **Accepting and Declining Orders**: Use the commands "accept_order <id> <minutes>" and "decline_order <id>" to accept or decline ride requests.
- **Finishing Orders**: Use the command "finish_order <id>" to mark a ride order as finished.
- **Accepting Payments**: Use the command "accept_payment <id> <amount>" to record received payments.

## System Architecture ##
The system architecture consists of several classes, including Address, User (abstract), Client, Driver, Order, OrderManager, Message, MessageManager, Rating, MenuHandler (abstract), ClientMenuHandler, and DriverMenuHandler. These classes manage various aspects of the application, such as user registration, order management, messaging, and menu handling.

## Known Limitations and Issues ##
- **In-app Messaging**: Users may encounter situations where messages are not promptly received or displayed in the application.

## Conclusion ##
The Taxi Company Application offers an efficient solution for managing transportation services, improving user experience, and facilitating seamless communication between clients and drivers. With its comprehensive functionalities and well-designed system architecture, the application aims to optimize taxi services, enhance customer satisfaction, and improve overall operational effectiveness.
