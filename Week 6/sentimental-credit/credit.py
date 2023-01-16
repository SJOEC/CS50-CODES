import sys

evens = 0
odds = 0
tmp = 0
start = 0

# get card in´puy
card = int(input("Number: "))

# create 2 copies
very_start = card
start = card

# If 1 number still without calculate
while card > 0:

    # calculate even position numbers
    evens += card % 10
    card = card // 10

    tmp = card % 10 * 2

    # check if the number has 2 digits
    if tmp > 9:
        odds += tmp % 10
        tmp = tmp//10
        odds += tmp % 10
        card = card // 10
    else:
        odds += tmp
        card = card // 10

# caluculate check
check = evens + odds

# calculate the len of the card
tmp = len(str(very_start))

for i in range(tmp - 2):
    start = start // 10

# check if is a real card
if ((check % 10) != 0):
    print("INVALID")
    sys.exit(1)

elif start == 34 or start == 37:
    print("AMEX")
    sys.exit(0)

elif start >= 51 and start <= 55:
    print("MASTERCARD")
    sys.exit(0)

elif start // 10 == 4 and tmp >= 13 and tmp <= 16:
    print("VISA")
    sys.exit(0)
    
else:
    print("INVALID")
    sys.exit(1)
