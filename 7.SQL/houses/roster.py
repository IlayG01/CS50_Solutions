import sys
import csv
from cs50 import SQL
import re


# check script argumants
if len(sys.argv) != 2:
    print("Usage -> roster.py arg1[houseaddress]")
    exit(1)

# db connection
db = SQL("sqlite:///students.db")

# sql query
students = db.execute("""SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first""", sys.argv[1])

# traveling the list of dicts printing the requested output
for row in students:
    first_name = row['first']
    middle_name = row['middle']
    last_name = row['last']
    birth_year = row['birth']
    if middle_name != None:
        print(fr"{first_name} {middle_name} {last_name}, born {birth_year}")
    else:
        print(fr"{first_name} {last_name}, born {birth_year}")