# Enter your height in meters e.g., 1.55
height = float(input())
# Enter your weight in kilograms e.g., 72
weight = int(input())

bmi_int = weight / height ** 2
bmi = str(bmi_int)
if (bmi_int >= 35): 
    print("Your BMI is " + bmi  + ", you are clinically obese.")

elif bmi_int >= 30: 
    print("Your BMI is " + bmi + ", you are obese.")

elif bmi_int >= 25:
    print("Your BMI is " + bmi + ", you are slightly overweight.")
elif bmi_int >= 18.5:
    print("Your BMI is " + bmi + ", you have a normal weight.")
else:
    print("Your BMI is " + bmi + ", you are underweight.")