import sys
import csv
import re

def main():

    # Make sure two arguments given for command line
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASE SEQUENCE")

    # Use first argument to read in database from csv file
    load = readdb(sys.argv[1])
    names = load[0]
    db = load[1]

    # Use second argument to read in sequence
    seq = readseq(sys.argv[2], names[1:])

    # Check sequence against database
    for i in range(0, len(db)):
        for j in range(1, len(names)):
            if (int(db[i][names[j]]) != seq[names[j]]):
                break
            if j == len(names) - 1:
                print(db[i]["name"])
                return 0


    # Return name if match, return no match if no match
    print("No match")



# Function for reading csv into list of dictionaries
def readdb(dbname):

    # Create list to contain db
    db = []

    # Read in db
    with open(dbname) as file:
        reader = csv.reader(file)
        line = 0 # count the lines
        for row in reader:
            if line == 0:
                names = row
                line += 1
            else:
                newentry = {}
                for i in range(0, len(names)):
                    newentry[names[i]] = row[i]
                db.append(newentry)

    return [names, db]



# Function for reading in and counting DNA sequences
def readseq(seqname, STRnames):

    # create dic to contain sequences
    seq = {}
    for i in range(0, len(STRnames)):
        seq[STRnames[i]] = 0

    # open file, read sequence in
    f = open(seqname, "r")
    STRs = f.read()
    f.close()

    # Get *highest* consecutive counts of DNA strands
    for i in range(0, len(STRnames)):
        matches = re.findall(f'(?:{STRnames[i]})+', STRs)
        if len(matches) != 0:
            n = max(map(len, matches)) / len(STRnames[i])
            seq[STRnames[i]] = n

    # Return the sequences
    return seq



# Run program
main()