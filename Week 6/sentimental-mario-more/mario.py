
# define a function to get use input
def get_int_input():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0 and n <= 8:
                break

        except ValueError:
            print("Not a number!")
            continue
    return n


# initialize counters
counter = 1
counter_hash = 1

# get user input
n = get_int_input()

# print pyramid
for i in range(n):
    n = n - 1
    print(' ' * n, end='', sep='')
    print('#' * counter, end='', sep='')
    # print gap
    print('  ', end='', sep='')
    print('#' * counter_hash)
    counter += 1
    counter_hash += 1

