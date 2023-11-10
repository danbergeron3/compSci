print("Thank you for choosing Python Pizza Deliveries!")
size = input() # What size pizza do you want? S, M, or L
add_pepperoni = input() # Do you want pepperoni? Y or N
extra_cheese = input() # Do you want extra cheese? Y or N
# Small pizza (S): $15
# Medium pizza (M): $2
# Large pizza (L): $25
# Add pepperoni for small pizza (Y or N): +$2
# Add pepperoni for medium or large pizza (Y or N): +$3
# Add extra cheese for any size pizza (Y or N): +$1
cost = 0

if size == 'S':
    cost += 15
    if add_pepperoni == 'Y':
        cost += 2
elif size == 'M':
    cost += 20
    if add_pepperoni == 'Y':
        cost += 3
elif size == 'L':
    cost += 25
    if add_pepperoni == 'Y':
        cost += 3


if extra_cheese == 'Y':
    cost += 1

print("Your final bill is: $" + str(cost) + ".")