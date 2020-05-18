# luhn algorithm
def company_tracker(credit_number):
    sum = 0
    length = len(credit_number)

    # other digits
    for index in range(length-2, -1, -2):
        number = int(credit_number[index])*2
        if number > 9:
            sum += number % 10 + (number-number % 10)/10
        else:
            sum += number

    # even digits
    for index in range(length-1, -1, -2):
        sum += int(credit_number[index])
    if (sum % 10):
        print("INVALID\n")
    elif (str(credit_number)[0:2] in ["34", "37"] and length == 15):
        print("AMEX\n")
    elif (str(credit_number)[0:2] in ["51", "52", "53", "54", "55"] and length == 16):
        print("MASTERCARD\n")
    elif (str(credit_number)[0:1] == "4" and length in [13, 16]):
        print("VISA\n")


def main():
    # getting credit card number from user & validate it
    while True:
        credit_number = input("Enter credit number: ")
        try:
            int(credit_number)
            break
        except ValueError:
            continue
    company_tracker(str(credit_number))


main()