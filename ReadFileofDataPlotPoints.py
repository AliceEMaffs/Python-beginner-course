# readData.py

# program to read in data from a file
# and plot it as points on a graph

# enabling graph plotting
import matplotlib.pyplot as plt;

# store data in these list variables
# create empty lists (arrays) x and y
x = [];
y = [];

# variable to see if file opening worked or not
opened = 0;

# try to open the file
try:
    readFile = open('xy.txt','r');
    # only get here if open worked
    opened = 1;
except:
    # if opening file went wrong, program comes here
    print('some error occurred!');

# next line is functionally equivalent to if opened == 1:
# because 1 is logically True and 0 is logically False
if opened:
    # read in data from the file
    # line by line

    for line in readFile:
        # variable line now holds one of the lines in the
        # data file
        # split up the string 'line' based on whitespace
        splitUp = line.split();
        
        # x = splitUp[0], y = splitUp[1]
        # append these values to the arrays x and y
        x.append(splitUp[0]);
        y.append(splitUp[1]);

    # print something out to be sure what's happening
        print(splitUp[0] + ',' + splitUp[1]);

        # from here, i have arrays x and y containing the data
        # i read in
    plt.plot(x,y);

    # close the file
    readFile.close();

    # show the plot
    plt.show();


