# ReadData
# program to read a file of data

import matplotlib.pyplot as plt;

# create empty arrays to hold x,y data
x = [];
y = [];

readFile = open('xyData.txt', 'r');

# read in the file line by line
for line in readFile:
    # file is open with a line in variable 'line'
    # do something with line
    print(line);
    # split the line based on whitespace
    splitUp = line.split();
    print('  x = ',splitUp[0], ' and y = ',splitUp[1]);
    # add x and y to arrays
    x.append(splitUp[0]);
    y.append(splitUp[1]);
    
    
# close the file
readFile.close();

#now, the arrays x and y contain the data I want
plt.plot(x,y);

