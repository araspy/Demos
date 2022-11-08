#if number is divisible by 5 and 3 print fizzbuzz
#fizz for 3 and buzz for 5
#for num in xrange(1,101):
#    if num % 5 == 0 and num % 3 == 0:
#        print("FizzBuzz")
#    elif num % 3 == 0:
#        print("Fizz")
#    elif num % 5 == 0:
#        print("Buzz")
#    else:
#        print(num)

#Fibonacci Sequence
#a, b = 0, 1
#for i in xrange(0, 10):
#    print(a)
#    a, b = b, a + b

#dicts---------------------------------------------------------------------------------------------
#used to store key:value . unordered collection. access values via key. mutable
#thisdict = {
#    "brand": "ford",
#    "model": "mustang",
#    "year": 1964
#}
#thisdict['year'] = 1982
#thisdict.keys() #returns all keys
#thisdict.values()



#sets-------------------------------------------------------------------------------------------------
#unordered, unchangeable, and unindexed (items are unchangeable but can be added/removed)
#myset= {"apple", "orange", "pear"}
#otherway= set(["apple", "orange", "pear"])
#remove() = remove from set specified as parameter
#discard() = remove element you aren't sure if is in there
#pop() = remove a random element from the set
# a|b = finds union of two sets. a|b|c = a.union(b,c)
#a&b = finds intersection of two sets.
#a-b = elements in a that are not in common with b
# d = frozenset(a) # makes immutable




#lists-------------------------------------------------------------------------------------------------
#names = ["John", "Bob", "Mosh", "Sam", "Mary"]
#print(names) #prints the whole array ("list", whatever)
#print(names[-1]) #prints Mary. [-2] prints Sam, etc.




#basics-------------------------------------------------------------------------------------------------
#age = 20
#first_name = "Alex"
#is_online = False
#print(age)
#name = input("What is your name? ")
#print("Hello " + name)



#Type conversion methods: int(), float(), bool(), str()--------------------------------------------------
#birth_year = input("Enter your birth year: ") #input function always returns a string
#age = 2020 - int(birth_year) #doing type conversion string > int
#print(age)

#INPUT GATHERING----------------------------------------------------------------------------------------
#first = input("First: ")
#second = input("Second: ")
#sum = float(first) + float(second)
#print("Sum: " + str(sum)) # need to turn sum back to string
#can also do:
#first = float(input("First: "))
#second = float(input("Second: "))
#sum = first + second
#print ("Sum: " + str(sum))

#ch = input('enter a char')[0] #only picks up first character even if user puts more in

#result = eval(input('enter an expression'))
#print(result)

#import sys
#x = int(sys.argv[1])
#y = int(sys.argv[2])



#strings - immutable------------------------------------------------------------------------
#course = 'Python for Beginners'
#print(course.replace('for', '4')) # does not actually modify string. returns a new one. strings immutable
#print(course.find('Python')) #returns index 0
#print('Python' in course) # returns true
#.upper() to adjust case

#arithmetic operators mostly the same. can do // to divide and round
# 10 ** 3 = 10 to power 3

#comparators------------------------------------------------------------------------------------
#price = 25
#print(price > 10 and price < 30)
#print(price > 10 or price < 30)
#print(not price > 10) #inverts true to false

#no {}. simply organize code blocks by indentation----------------------------------------
#temperature = 35
#if temperature > 30:
#    print("It's a hot day")
#    print("Drink plenty of water")
#elif temperature > 20:
#    print("It's a nice day")
#elif temperature > 10:
#    print("It's a cold day")
#else:
#    print("It's cold")
#print("Done")

#WHILE LOOPS----------------------------------------------------------------
#i = 1
#while i <= 5:
#    print(i)
#    i += 1
#can separate numbers like 1000 as 1_000. i guess for readability
#print a tree of asterisks
#i = 1
#while i <= 10:
#    print(i * '*')
#    i +=1



#MODULES---------------------------------------------------------------------
#import math
#print(dir(math)) #prints all the modules in math library
#print(helpt(importedFunction)) #help stuff
#print(bool(0))



#TUPLE- immutable---------------------------------------------------------------
#a = (123, 12.23, "demo")
#a[0:2]  #takes element at 0 and element at 1


#LISTS  -----------------------------------------------
#my_list = [0,1,2,3,4,5,6,7]
#print my_list[1:-1:2] #can mix negative and positive indices. Can add a step value (the 2). can make the step negative to go backwards
#slices - delcare it then use it as an index
# a = slice(1,3)
#print(mylist[a])









