from item import Item
from phone import Phone



item1 = Item("MyItem", 750)

# Setting an attribute
# item1.name = "OtherItem"

# Getting an Attribute
# print(item1.name)

item1.apply_increment(0.2)
item1.apply_discount()
print(item1.price)


# demonstrating abstraction. I don't want the methods that
# send_email() calls to be accessible outside the class
item1.send_email()




# --------------------------------------------------------------
# creating instance of string class
# random_str = str("4")

# creating instance of class
# item1 = Item("Phone", 100, 5)
# (item1.calculate_total_price(item1.price, item1.quantity))

# item2 = Item("Laptop", 1000)
# item2.pay_rate = 0.7

# creating instance of class
# item2 = Item("Laptop")
# item2.name = "Laptop"
# item2.price = 1000
# item2.quantity = 3
# print(item2.calculate_total_price(item2.price, item2.quantity))


# print(item1.name)
# print(item2.name)

# print(item1.calculate_total_price())
# item1.apply_discount()
# print(item1.price)
# print(item1.calculate_total_price())

# print(Item.__dict__)  # All the attributes for class level
# print(item1.__dict__)  # All the attributes for instance level


# item1 = Item("Phone", 100, 1)
# item2 = Item("Laptop", 1000, 3)
# item3 = Item("Cable", 10, 5)
# item4 = Item("Mouse", 50, 5)
# item5 = Item("Keyboard", 75, 5)


# print(Item.all)


# for instance in Item.all:
    # print(instance.name)


# IMPORTING FROM CSV
# Item.instantiate_from_csv()
# print(Item.all)


# print(Item.is_integer(7.4))

# phone1 = Phone("jscPhonev10", 500, 5, 1)
# print(phone1.calculate_total_price())
# phone2 = Phone("jscPhonev20", 700, 5, 1)



