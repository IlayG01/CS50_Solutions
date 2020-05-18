# libs
import sys
import csv
import re

# input check
if len(sys.argv) != 3:
    print("Usage -> dna.py arg1[csvfile] arg2[sequencetxt]")
    exit(1)

# global variables
csv_dna_table_name = sys.argv[1]
txt_dna_sequence_name = sys.argv[2]
sequence_repetition_dict = {}

# csv file open
with open(csv_dna_table_name, newline='') as csv_file:
    reader = csv.DictReader(csv_file)

    # txt file open
    with open(txt_dna_sequence_name, "r") as txt_file:
        txt_reader = txt_file.read()

        # running on dna sequences from the csv table
        for sequence in reader.fieldnames[1:]:

            # counts how much contiguous matchs exist in our txt
            matches = re.findall(rf'(?:{sequence})+', txt_reader)

            # updates our global dict
            if len(matches):
                x = {sequence: len(max(matches))/len(sequence)}
            else:
                x = {sequence: 0}
            sequence_repetition_dict.update(x)

    # running on csv file row by row(dictionary which each value is linked list)
    for row in reader:
        counter = 0
        for sequence in reader.fieldnames[1:]:
            if int(row[sequence]) == int(sequence_repetition_dict[sequence]):
                counter += 1
        if counter == len(reader.fieldnames[1:]):  # full match in every sequence
            print(row['name'])
            exit(0)
    print("No match")
    exit(0)
