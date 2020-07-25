# ut_kala_phase2
a shoping program that runs on the command line (phase1: saves the program data in .txt files)


it this phase the data is stored in a linked list structure for convinient removing of anything from the structure


## the commands and what the do and how they work

**signup username password role**\
**Example: signup person 123 seller**\
this command is for signup in the program(obviously) \
there can only be one person with the same username and role in this program \
the role can be a buyer or a seller 

**login username password role**\
**Example: login otherPerson 231 buyer**\
this command logs a user in to the program 

**logout**\
**Example: logout**\
this command logs the loged in user out of this program \
it is mandatory to logout of the program to switch between users(two users cannot login at once) 

**view**\
**Example: view**\
any loged in uder can use this command to see there information(name amount of money they have and the products they are selling or buying) 

**deposit amount_of_money**\
**Example: deposit 1000**\
this command is for users with the role of buyer only \
a buyer can add to there accounts amount of money using this command 

**add_goods goods_name goods_price goods_count**\
**Example: add_goods watch 10000 3**\
this command is for users with the role of seller only \
a seller can use this command to add a prduct to sell specifying the name price and count 

**show_goods**\
**Example: show_goods**\
this command can be used at anytime it shows all of the products being sold \
it shows there name, seller, count, and  price. 

**buy goods_name goods_count seller_username**\
**Example: buy watch 1 thirdPerson**\
this command is for buyers only(obviously)\
it is used to buy a product from another user

**remove_goods goods_name**\
**Example: remove_goods watch**\
this command is used to remove any product\
can be used by the seller of said product\

**change_goods_price <goods_name> <new_price>**\
**Example: change_goods_price watch 50000**\
used to change the price of a product\
can be used by the seller of said product\

**rate_goods <goods_name> <seller_username> <rating>**\
**Example: rate_goods watch third_person 3**\
  used to rate bought products\
  can be used by buyers who have bought that product\
  
  ***note: any product rated by 5 or more buyers that has a rating of less than 2 will be disactivated and cannot be bought again***
  
  
  ***note disactivated products can be activated again if their rating increases more than the said limit(it should be rated by the people who have bought it and have not rated it since it cannot be bought again)***
  
  
**search <number_of_conditions>**\
**<goods_attribute> <attribute_value>**\
**…**\
used to search a product with the number of conditions given, available attributes are name, min_price, max_price, seller_username\


***this project was done using visual studio what has been uploaded here is the whole project folder***







*writen in c*
