

"""This file takes an input number, and returns the same number.  
   A lot of useless operations are done to it in the interem to show you some sintax and capabilities of python""" 

#Tabs are a nessessary part of python code.  Spaces are not equivilent to tabs even if it looks like the same distance.

"""You import modules at the start of your file.  They are pyhton files that contain functions that do various things.
   The math module has math related functions for instance.  You can make your own modules."""
import time
import math


#Functions can be made if you have a piece of code that is used over and over again.
def randomMathOperation(number):
	output=number*19
	return output/19



"""The try and except statement are used together, they are a error handler.  
   If an error happens in the try statement, you go into the except."""
while True:
    try:
         myNumber = int(input("Please enter a number: "))
         break
    except ValueError:
         print("Oops!  That was no valid number.  Try again...")


#Lists
#List indexes start with 0 and not 1 like in matlab
myList=[0,1,2,3,4,5, myNumber]
aList=[6,7,8,9]
zeroList=[0]
combinedList=myList+aList
reversedList=combinedList[::-1]
slicedList=reversedList[2:5] #A slice is when you take part of a list
myNumber=slicedList[::-1][0] #The list was reversed, and then your number was picked


letters=["a","b","c","d","e"]
index=0

"""For statements work differently than in matlab.  They go through each item in a list, not just numbers.
   In this example the for statement goes through a through e"""
for i in letters:
	
	if i=="c":
		letters[index]=myNumber
		myNumberIndex=index
	index=index+1

myNumberAndQuarter=letters[myNumberIndex]+.25

#math.floor uses the floor function from the math module
myNumberAndQuarter=math.floor(myNumberAndQuarter)


print(randomMathOperation(myNumberAndQuarter))


















