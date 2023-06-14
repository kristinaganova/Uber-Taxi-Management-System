#Taxi Company Application Documentation
Welcome to the documentation for the Taxi Company Application, an simplified system for managing a taxi company. This application allows users to register as either clients or drivers, enabling them to perform various actions within the system. The application facilitates the process of ordering taxis, managing orders, tracking drivers, and handling payments.

This documentation provides a comprehensive guide on how to use the Taxi Company Application, including user registration, login procedures, and the available functionalities for both clients and drivers. It also covers the underlying system architecture, data storage, and file management.

#Table of Contents
1.Introduction
2.System Overview
3.User Registration
4.User Login and Logout
5.Client Functionalities
  -Ordering a Taxi
  -Checking Order Status
  -Cancelling an Order
  -Making Payments
  -Rating Drivers
  -Adding Funds to Account
6.Driver Functionalities
  -Changing Current Address
  -Checking Messages
  -Accepting and Declining Orders
  -Finishing Orders
  -Accepting Payments
7.System Architecture
8.Conclusion

#2. System Overview
The Taxi Company Application is designed to streamline the operations of a taxi company by providing a simplified system for clients to order taxis and drivers to manage and fulfill those orders. The system consists of two main user roles: clients and drivers. Clients can register, log in, place orders, track order status, make payments, rate drivers, and add funds to their accounts. On the other hand, drivers can register, log in, update their current address, check messages (orders), accept or decline orders, mark orders as finished, and accept payments.

The core functionality of the system revolves around the process of ordering a taxi. When a client places an order, the system sends a notification to available drivers, starting with the one closest to the pickup address. Once a driver accepts the order, the client is notified, and the system generates a unique order ID for reference. The client can then track the status of their order, including details about the assigned driver, their vehicle information, contact number, and estimated arrival time.

In addition to order management, the system also handles payment transactions. Clients can make payments for completed orders, and the funds are transferred to the driver's account. Drivers, in turn, can accept payments and provide information about the amount received.

The Taxi Company Application emphasizes simplicity and efficiency, aiming to provide a seamless experience for both clients and drivers. By automating the order process and integrating payment management, the application helps optimize taxi services, enhance customer satisfaction, and improve overall operational effectiveness.

#3. User Registration
To access the features and functionalities of the Taxi Company Application, users need to register an account. The application supports two types of users: clients and drivers. The registration process allows users to create a unique username and password combination, along with providing relevant personal and contact information.

3.1 Client Registration
Clients can register by following the steps below:

Enter the command: register client <username> <password> <first_name> <last_name>

Replace <username> with a desired username for the client.
Replace <password> with a secure password for the client's account.
Replace <first_name> with the client's first name.
Replace <last_name> with the client's last name.
Provide additional information as prompted, such as address, contact number, or any other required details.

Once the registration process is complete, clients can log in using their chosen username and password to access the application's features.

3.2 Driver Registration
Drivers can register by following the steps below:

Enter the command: register driver <username> <password> <first_name> <last_name> <car_number> <phone_number>

Replace <username> with a desired username for the driver.
Replace <password> with a secure password for the driver's account.
Replace <first_name> with the driver's first name.
Replace <last_name> with the driver's last name.
Replace <car_number> with the driver's vehicle number.
Replace <phone_number> with the driver's contact number.
Provide any additional information as prompted, such as the current address of the driver.

Once the registration process is complete, drivers can log in using their chosen username and password to access the application's features.

User registration is a one-time process that allows clients and drivers to utilize the full functionality of the Taxi Company Application. By registering, users can benefit from features such as placing orders, tracking order status, making payments, and managing their profiles.

#4. User Login and Logout
The Taxi Company Application provides a secure login system that allows registered users to access their accounts and utilize the features of the application. Users can log in using their chosen username and password, and they can also log out to securely exit the application without ending its functionality.

4.1 User Login
To log in to the application, users need to follow these steps:

Enter the command: login <username> <password>

Replace <username> with the registered username associated with the user's account.
Replace <password> with the corresponding password for the user's account.
Upon successful login, users will gain access to their respective profiles and the available features of the application.

4.2 User Logout
To securely log out from the application, users can follow these steps:

Enter the command: logout

The application will process the logout request and terminate the current user session, ensuring that their account remains secure and protected.

It is important for users to log out of the application after each session, especially when using shared devices or accessing the application from public places. Logging out helps prevent unauthorized access to user accounts and ensures the privacy and security of their personal information.

By providing a reliable login and logout system, the Taxi Company Application maintains a safe and controlled user environment, enabling clients and drivers to access the application's features conveniently while maintaining the confidentiality of their accounts.

#5. Client Functionalities
The Taxi Company Application offers a range of convenient features for clients, allowing them to seamlessly book and manage taxi rides. This section outlines the various functionalities available to clients within the application.

5.1 Ordering a Taxi
Clients can easily request a taxi by following these steps:

Enter the command: order <address> <destination>

Specify the current address where the client wants to be picked up.
Provide the destination address for the desired drop-off location.
The application will process the order and send a notification to available drivers. The closest driver to the pickup address will be notified first.

Once a driver accepts the order, the client will receive a notification containing a unique order ID.

5.2 Checking Order Status
Clients can stay updated on the status of their taxi order by using the following command:

check_order <id>
Enter the order ID received after placing the order.
The application will provide information regarding the order status, including whether it has been accepted, the assigned driver's details (name, car number, phone number, and rating), and an estimated time of arrival.

5.3 Cancelling an Order
In the event that a client needs to cancel a taxi order, they can use the following command:

cancel_order <id>
Enter the order ID of the taxi ride to be cancelled.
If the order has not been accepted by a driver, the cancellation will be processed immediately. However, if a driver has already accepted the order, the application will release the driver and notify them of the cancellation.

5.4 Making Payments
Clients can conveniently make payments for completed taxi rides using the following command:

pay <id> <amount>
Enter the order ID of the completed ride.
Specify the payment amount to be charged.
Once the driver marks the ride as completed, the client can proceed with payment. The amount paid by the client will be transferred to the driver's account.

5.5 Rating Drivers
Clients have the option to rate drivers based on their experience with a completed ride. To rate a driver, clients can use the following command:

rate <name_of_driver> <rating>
Enter the name of the driver being rated.
Provide a rating on a scale of 1 to 5.
Clients can only rate drivers for rides they have completed themselves. This feature allows clients to provide feedback and contribute to the driver's overall rating within the system.

5.6 Adding Funds to Account
Clients can easily add funds to their account by utilizing the following command:

add_money <amount>
Enter the amount of money to be added to the account.
Clients can conveniently add funds to their account balance, which can be used to pay for future taxi rides. The system assumes the validity of the provided credit or debit card and does not perform additional checks on the card.

By offering these client functionalities, the Taxi Company Application ensures a user-friendly experience for clients, providing them with the tools to effortlessly order taxis, track their orders, manage payments, rate drivers, and maintain adequate funds in their accounts.

#6. Driver Functionalities
The Taxi Company Application offers a range of functionalities for drivers, enabling them to efficiently handle taxi requests and provide excellent service to clients. This section outlines the various functionalities available to drivers within the application.

6.1 Changing Current Address
Drivers can easily update their current address within the system by using the following command:

change_address <address>
Enter the new address to update the current location.
This functionality allows drivers to keep their address information up to date, ensuring accurate routing and efficient service.

6.2 Checking Messages
Drivers can check messages sent by the system, which primarily include taxi orders. To review incoming orders, drivers can use the following command:

check_messages
By checking their messages, drivers can stay informed about new ride requests and respond promptly to accept or decline them.

6.3 Accepting and Declining Orders
Upon receiving a new ride request, drivers can choose to accept or decline it based on their availability and proximity to the pickup location. The following commands facilitate this process:

accept_order <id> <minutes>

Enter the order ID to accept the requested ride.
Specify the estimated time (in minutes) it will take to arrive at the pickup location.
decline_order <id>

Enter the order ID to decline the requested ride.
By accepting or declining orders, drivers can manage their workload effectively and ensure optimal utilization of their resources.

6.4 Finishing Orders
Once drivers have reached the drop-off location and completed a ride, they can mark the order as finished within the system. This is done using the following command:

finish_order <id>
By finishing orders, drivers update the system with the completion status, allowing clients to make payments and rate their service accordingly.

6.5 Accepting Payments
Upon completing a ride and receiving payment from the client, drivers can record the payment within the application. This is done using the following command:

accept_payment <id> <amount>
Enter the order ID for which payment is being accepted.
Specify the amount of payment received.
By accepting payments, drivers can keep track of their earnings and ensure accurate financial records within the system.

With these driver functionalities, the Taxi Company Application empowers drivers to efficiently handle ride requests, manage their addresses, track messages, accept or decline orders, mark rides as finished, and record payments. These features contribute to a seamless experience for both drivers and clients.

#7.System Architecture

The main classes in the system are:

Address: Represents a location with X and Y coordinates. It is used to store the start and destination addresses for an order.

User: An abstract base class representing a user of the system. It contains common attributes and methods that are inherited by specific user types such as clients and drivers.

Client: Inherits from the User class and represents a client or customer of the transportation service. It includes functionalities like registering users, placing orders, managing balance, and handling messages.

Driver: Inherits from the User class and represents a driver in the transportation service. It includes functionalities like registering users, accepting or declining orders, managing current address, and handling messages.

Order: Represents an order placed by a client. It contains information about the start and destination addresses, the number of passengers, the order status, and payment details.

OrderManager: Manages all the orders in the system. It provides functions to add, remove, and find orders, as well as retrieve orders by their status.

Message: Represents a message exchanged between users in the system. It contains the content, sender, receiver, and message status.

MessageManager: Manages all the messages in the system. It allows users to send and receive messages, as well as retrieve message stores for individual users.

Rating: Represents a rating given by a client to a driver. It includes the rating value and the client who gave the rating.

MenuHandler: An abstract base class for handling user menus. It provides common methods for displaying menus and handling user input.

ClientMenuHandler: Inherits from MenuHandler and provides menu handling functionality for clients. It includes functions for placing orders, checking order status, and managing messages.

DriverMenuHandler: Inherits from MenuHandler and provides menu handling functionality for drivers. It includes functions for accepting or declining orders, changing address, and managing messages.

#9. Conclusion

Overall, this software system provides a solid foundation for efficiently managing transportation services, enhancing user experience, and facilitating seamless communication between clients and drivers. By incorporating these classes and their functionalities, the system aims to streamline order placement, tracking, and communication processes, ultimately improving the overall service quality.
