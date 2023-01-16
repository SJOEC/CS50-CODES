def count_letters(my_text):
    letters = 0

    for i in my_text:
        if i >= 65 and i < 90 or i >= 97 and i <= 122:
            letters += 1

    return letters


def count_words(my_text):
    words = 1

    for i in my_text:
        if i == 32:
            words += 1

    return words


def count_sentences(my_text):
    sentences = 0

    for i in my_text:
        if i == 33 or i == 46 or i == 63:
            sentences += 1

    return sentences


# get users input
text = input("Text: ")

# convert the user input into an array of ASCII values
my_text = [ord(i) for i in text]

# count letters
letters = count_letters(my_text)
# count words
words = count_words(my_text)
# count sentences
sentences = count_sentences(my_text)

# calculate index
L = (letters/words) * 100
S = (sentences/words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

# calculate the grade
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")