import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("python dns.py data.cav sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    data = []
    with open(sys.argv[1], "r") as f:
        reader = csv.DictReader(f)
        # reading lines from file
        for line in reader:
            # changing values to int
            for key in line.keys():
                if key == "name":
                    continue
                line[key] = int(line[key])

            data.append(line)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as f:
        sequence = str(f.read()).strip()

    # TODO: Find longest match of each STR in DNA sequence
    person = {}
    for key in data[0].keys():
        if key == "name":
            continue
        person[key] = longest_match(sequence, key)

    # TODO: Check database for matching profiles
    n = len(data[0].keys())
    for match in data:
        f = 0
        for key in match:
            if key == "name":
                continue
            elif match[key] == person[key]:
                f += 1
            else:
                f = 0
        if f == n - 1:
            return match["name"]

    return "No Match"


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


print(main())
