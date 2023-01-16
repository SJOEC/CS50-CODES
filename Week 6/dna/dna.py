import csv
import sys


def main():

    dna_values = []
    dna_data = []
    dna_checker = {}

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable

    with open(sys.argv[1], "r") as file:

        # split first row to found dna sequences
        csvreader = csv.reader(file)

        # for the first row in csv reader make a list with the STR to search
        for row in csvreader:
            dna_values.append(row)
            break

        dna_values = dna_values[0]

        # create a copy of the dna data
        dna_str = dna_values.copy()
        # deletre the name field
        dna_str.pop(0)

        # read as dictionary
        csvDictReader = csv.DictReader(file, fieldnames=dna_values)

        # convet dna numbers into int
        for row in csvDictReader:
            for i in range(len(dna_str)):
                row[dna_str[i]] = int(row[dna_str[i]])

            # create the full data dictionary
            dna_data.append(row)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        textreader = file.read()

        # Find longest match of each STR in DNA sequence
        for i in range(len(dna_str)):

            actual_longest = longest_match(textreader, dna_str[i])

            # store the dna-text data to compare
            dna_checker[dna_str[i]] = actual_longest

    # Check database for matching profiles
    for i in range(len(dna_data)):
        # count matches
        count_match = 0
        # check in every dna dictinary of data
        for j in range(len(dna_checker)):
            if dna_data[i][dna_str[j]] == dna_checker[dna_str[j]]:
                count_match += 1
                # if that person match with every str
                if count_match == len(dna_str):
                    # print person name and exit
                    print(dna_data[i]["name"])
                    sys.exit(0)

    # else, if no one match, print "No match"
    else:
        print("No match")
        sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
