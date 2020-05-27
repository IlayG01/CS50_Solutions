import sys
import csv
from cs50 import SQL


# check script argumants
if len(sys.argv) != 2:
    print("Usage -> import.py arg1[csvfile]")
    exit

# db connection
db = SQL("sqlite:///students.db")

# opening the csv file importing data to related db using sql queries
with open(sys.argv[1], newline='') as csvfile:
    reader = csv.DictReader(csvfile)
    for row in reader:
        names_number = row["name"].split()
        print(names_number)
        if len(names_number) == 3:
            db.execute("""INSERT INTO students (first, middle, last, house, birth) VALUES
                (?, ?, ?, ?, ?)""", names_number[0], names_number[1], names_number[2], row["house"], row["birth"])
        if len(names_number) == 2:
            db.execute("""INSERT INTO students (first, middle, last, house, birth) VALUES
                (?, NULL, ?, ?, ?)""", names_number[0], names_number[1], row["house"], row["birth"])

