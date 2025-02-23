# Smart_Restaurant_Ordering_System

A smart restaurant system for waiters and chefs based on C++ and QT5.
The developers' names are: *Ziqi ZHAO, Zigen XU, Siheng XIANG, Chuzhi Xu, Qianqi Wen.

In this project, our group has developed a smart restaurant ordering system(SROS) designed to enhance the efficiency and flexibility of restaurant operations. The main demand group of our system is the restaurant sales staff, and the system features a server operations interface as well as an intuitive interface with buttons for waiters, chefs and boss to interact with. Key functionalities include table selection, editing the menu, ordering food, adding additional dishes mid-meal, and generating detailed bills with corresponding payments. This system aims to address common inefficiencies in existing dining systems and cater to both customer and restaurant staff needs.


Related work
The concept for this project stems from the widespread use of dining systems in restaurants. Despite their ubiquity, many current systems lack the flexibility to accommodate real-time order modifications, causing inconvenience for diners. A personal experience inspired this improvement: during a meal at a restaurant, I attempted to order additional dishes mid-meal, only to discover that the system required me to settle the existing bill before placing new orders. This process was inefficient and unnecessarily time-consuming.
To address such limitations, our system includes the functionality to seamlessly add new dishes during an ongoing order, thereby eliminating interruptions in the dining experience.
The implementation of this project relied on key C++ libraries, particularly Qt, for creating user interfaces, handling graphics, and managing events, for example, some modules like Qpushbutton, Qwidge, and Qwindow. In addition, some data structures designed in the QT library was applied like Qstring and Qmap. Last but not least, some basic libraries from STL were used, like iostream for input and output and ifstream and ofstream for loading and saving files.


Demand analysis
Based on our observation and discussion, our smart restaurant ordering system needs to obtain the following basic functionalities:

⚫Select table: the system should have the function to select a certain table to do these
further steps and if the user reenters the same table, the current order of that table
should be consistent with the last time if the action of check out doesn’t happen.

⚫Edit menu: Editing the menu should be included, containing the function to add dishes, delete dishes, and edit all the attributes like name, price, and description of the dishes.

⚫Take order: the system should allow people to select their preferred dishes and they should be shown in an information box. Also, the function of deleting and commenting on the dish should be considered.

⚫Check out: Calculate the final amount of money and the customer can select different approaches to pay for it.

⚫Member card system: this sub-system should be a whole system about membership card function realization. Some basic card functions should be implemented, like register, recharge search, and pay.

⚫Waitstaff performance: each time they finish paying, the customer can rate the service of the waitstaff and to some extent, their income will be influenced by the number of positive reviews received from users and the number of service orders(performance).

⚫Real-time communication with the kitchen: there should be 2 interfaces, one for waiters and one for chefs, and real-time message communication should be permitted.


The process of using the ordering system:
The system contains three parts, namely the employee side, the operation end and the back office.
The employee side offers a linked structure with 4 UI interfaces. In the first interface, the system will require the user to input a waiter id, as long as the input ID is correct the user will go into the the second UI interface, which is the window of 25 tables and listed on the left hand side is a local communicating system with the chef. Clicking into anyone of the 25 tables will take the user to the corresponding table ordering menu. In the menu ordering window, there will be 4 tabs on the top of the window, which are respectively, Meat, Vegetable, Drink and Snack. Clicking the tab will bring you to the details of the menu of the clicked kind. If the user want to add dishes into the shopping cart, it will be easily accomplished through the button “Add Dish” and then input the number of dishes you want. As long as the pre-selected dishes are not ordered, they can be changed or deleted. Once the user decided the dishes they want to order, he can click the “Order” button. After having the
meal the user can click the “Check Out” button, and then the system will take the user to the third UI interface. In the fourth UI interface, the user can choose the payment method from 4 different, which are Wechat pay, Alipay pay, bankcard, membership, or cash. Choosing WeChat pay or Alipay will be brought to a page with the appropriate payment code. Choosing a membership will require the user to input the membership number, and then the corresponding sum will be reduced. If the user chooses cash, then after the waiter inputs the amount of money he received, the system will return the amount of change that needs to be given to the waiter. After the checkout, the last UI interface will jump out. The window will ask the customer for the rating for the waiter, which will later be used to calculate the waiter's commission amount.
The operation end is where the customers can view the menu and take orders, which is similar to the employee side.
The back office is where the user can modify the menu and query the performance amount. The initial UI interface will have two buttons, which are “Modify Menu” and “Check Salary”. Clicking “Modify Menu” will bring the user to an interface for adding, deleting, and modifying menus. Changing only one of the elements of the dishes is also allowed such as changing the presented photo, changing the price, or changing dish notes merely without changing anything else. There will also be a local communication system on the left-hand side of the window with the waiter. Clicking “Check Salary” will be then required to input the user’s waiter ID, and then the system will return the waiter’s average rate, which is provided by customers, and how the commission, which is decided by sales and average rating, he can take for the time being. A letter grade for the waiter will also be provided.
