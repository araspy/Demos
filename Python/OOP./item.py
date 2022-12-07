import csv


# no methods without parameters in python. self as minimum.
class Item:
    # creating class attributes
    pay_rate = 0.8  # The pay rate after 20% discount
    all = []

    # init handles instantiation
    # can give default values, will detect type automatically, i.e. knows quantity should be int
    def __init__(self, name: str, price: float, quantity=0):
        # print(f"An instance created: {name}")
        # Run validations to the received arguments
        assert price >= 0, f"Price {price} is not greater than or equal to zero!"
        assert quantity >= 0, f"Quantity {quantity} is not greater than or equal to zero!"

        # Assign to self object
        self.__name = name
        self.__price = price
        self.quantity = quantity
        # Actions to execute
        Item.all.append(self)

    @property
    def price(self):
        return self.__price

    def apply_discount(self):
        self.__price = self.__price * self.pay_rate

    def apply_increment(self, increment_value):
        self.__price = self.__price + self.__price * increment_value

# @property defining what you like to do when you get an attribute
    @property
    def name(self):
        print("You are trying to get name")
        return self.__name

# @setter defined so that the attribute is not read only. can do some conditions to make sure you like
    # the value you receive
    @name.setter
    def name(self, value):
        print("you are trying to set")
        if len(value) > 10:
            raise Exception("The name is too long!")
        self.__name = value

    def calculate_total_price(self):
        return self.__price * self.quantity

# this needs to be a class method not an instance method because we are creating an instance
    @classmethod
    def instantiate_from_csv(cls):
        with open('items.csv', 'r') as f:
            reader = csv.DictReader(f)
            items = list(reader)

            for item in items:
                Item(
                    name=item.get('name'),
                    price=float(item.get('price')),
                    quantity=int(item.get('quantity'))
                )

    # static method, never sending class instance as first argument. like a regular function that receives parameters
    @staticmethod
    def is_integer(num):
        # We will count out the floats that are point zero
        if isinstance(num, float):
            # Count out the floats that are point zero
            return num.is_integer()
        elif isinstance(num, int):
            return True
        else:
            return False

    def __repr__(self):
        # return string responsible for representing this object. check out comparison between repr and str
        return f"{self.__class__.__name__}('{self.name}', {self.__price}, {self.quantity})"

    def __connect(self, smpt_server):
        pass

    def __prepare_body(self):
        return f"""
        Hello someone.
        We have {self.name} {self.quantity} times.
        Regards, Alex
        """

    def __send(self):
        pass

    def send_email(self):
        self.__connect('')
        self.__prepare_body()
        self.__send()
