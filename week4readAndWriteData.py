# readAndWriteData.py

# program that reads in csv data
# and writes it out in a different format

# open the file
readFile = open('namesAges.csv','r');

# create empty arrays
names = [];
ages = [];

# read in the file line by line
for line in readFile:
    # split the input line based on a comma
    splitUp = line.split(',');

    # store the values in the arrays
    names.append(splitUp[0]);
    ages.append(splitUp[1]);

# close the file
readFile.close();

# write the data out to a different file

# open a file to write to
writeFile = open('namesAges.txt','w');

# loop over the names and ages and write them
# out to this file

for i in range(0,len(names)):
    # write a line to the file
    writeFile.write(names[i] + ' is ' + ages[i].rstrip() + ' years old\n');

# close the file when we're finished
writeFile.close();

