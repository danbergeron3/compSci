#If the bill was $150.00, split between 5 people, with 12% tip. 
print("Welcome to my tip calculator")

print("What is the total")
total = input()
total = float(total)

print("How many people are attending dinner?")
numPeople = input()
numPeople = int(numPeople)

print("How much would you like to tip(precentage: 10, 15, 20, etc)")
percentage = input()
percentage = float(percentage)

amountPerPerson = (total / numPeople) * (1 + (percentage / 100))
tip = round(amountPerPerson, 2)
print(f"Each person should pay {tip}$")

#Each person should pay (150.00 / 5) * 1.12 = 33.6
#Format the result to 2 decimal places = 33.60

#Tip: There are 2 ways to round a number. You might have to do some Googling to solve this.💪

#Write your code below this line 👇