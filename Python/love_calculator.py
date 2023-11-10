print("The Love Calculator is calculating your score...")
name1 = input() # What is your name?
name2 = input() # What is their name?

name1_str = str(name1)
name1_str = name1_str.lower()

name2_str = str(name2)
name2_str = name2_str.lower()

true_count = 0
true_count += name1_str.count('t')
true_count += name1_str.count('r')
true_count += name1_str.count('u')
true_count += name1_str.count('e')

true_count += name2_str.count('t')
true_count += name2_str.count('r')
true_count += name2_str.count('u')
true_count += name2_str.count('e')

love_count = 0
love_count += name1_str.count('l')
love_count += name1_str.count('o')
love_count += name1_str.count('v')
love_count += name1_str.count('e')

love_count += name2_str.count('l')
love_count += name2_str.count('o')
love_count += name2_str.count('v')
love_count += name2_str.count('e')

love_count_str = str(true_count) + str(love_count)

if int(love_count_str) < 10 or int(love_count_str) > 90:
    print("Your score is " + love_count_str + ", you go together like coke and mentos.")
elif int(love_count_str) > 40 and int(love_count_str) < 50:
    print("Your score is " + love_count_str + ", you are alright together.")
else:
    print("Your score is " + love_count_str + ".")