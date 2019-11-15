# Program that reads GBplaces.csv 
# Re-writes the data to a new file
# new file has places ordered by increasing population size

# program to read a file of data

# create empty arrays to hold x,y data
GBplaces=[];
place = [];
ttyp = [];
pop = [];
latt = [];
longi = [];

opened=0

try:
    readFile = open('GBplaces.csv', 'r');
    opened=1
except:
    # an error has occurred
    print('Opps! An error has occured! \n please check the file');

if opened:
    print('Yay, File is opened');
        
    #skip header
    Headers = next(readFile);
    
    #start splitting the data into sections 
    for line in readFile:            
                
            #split data between commas
            splitUp = line.split(',');
            
            # sort arrays
            # make sure population is and integer
            # no need to worry about latidtude and longitude
            place.append(splitUp[0]);
            ttyp.append(splitUp[1]);
            pop.append(int(splitUp[2]));
            latt.append(splitUp[3]);
            longi.append(splitUp[4]);
            
    # put them back together   
    data = zip(place, ttyp, pop, latt, longi);
            # print this data
    #        print(data);
            # sort by increasing population 
    sortedPop = sorted(data, key = lambda pop: pop[2]);
            # print sorted data
    for i in range(len(place)):
        print(sortedPop[i][0],sortedPop[i][1],sortedPop[i][2],sortedPop[i][3],sortedPop[i][4]);
    
    # close the read file
    readFile.close();
    
    # write the data out to a different file
    
    # open a file to write
    writeFile = open('GBPopSorted.csv','w');
    writeFile.write(str('%s' % Headers));
    
    # loop over the population, place and type and write them out in new file
    
    for i in range(0,len(pop)):
        
        # write sortedPop to the file
        writeFile.write(str('%s %s %d %s %s'% sortedPop[i]));
    
    # close the file when we're finished
    writeFile.close();
