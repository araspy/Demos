from item import Item


# INHERITANCE
class Phone(Item):

    # copying constructor code from Item as it is a child of Item
    def __init__(self, name: str, price: float, quantity=0, broken_phones=0):
        # Call to super function to have access to all attributes / methods
        super().__init__(
            name, price, quantity
        )

        assert broken_phones >= 0, f"Broken phones {broken_phones} is not greater than or equal to zero!"

        self.broken_phones = broken_phones