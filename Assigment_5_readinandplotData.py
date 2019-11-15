# WEEK 5 ASSESSMENT
# Alice Eleanor Matthews
# Student ID : 9464612

# GOING TO READ data from GBplaces.csv file
# GOING TO PRESENT IT VISUALLY USING MATPLTLIB MODULE
# IN THE MOST BEAUTIFUL WAY IMAGINABLE!! ...and in the time I have!

# import matplotlib for plotting
import matplotlib.pyplot as plt

# create empty arrays to hold x,y data
GBplaces=[];
place = [];
ttyp = [];
pop = [];
latt = [];
longi = [];
area = [];

# open and Read GBplaces
opened=0

try:
    readFile = open('GBplaces.csv', 'r');
    opened=1
except:
    # an error has occurred
    print('Opps! An error has occured! \n please check the file');

if opened:
    print('\nYAY!\nFile has opened!\nThis data represents places in the UK, their location and population.\nOrdered in increasing population.\n');
    
    # SHOW DATA IN NEAT ORDER    
    # skip header from file
    Headers = next(readFile);
    
    # start splitting the data into sections 
    for line in readFile:            
                
            # split data between commas
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
            #print(data);
            # sort by increasing population 
    sortedPop = sorted(data, key = lambda pop: pop[2]);
            # print sorted data
    for i in range(len(place)):
        print(sortedPop[i][0],sortedPop[i][1],sortedPop[i][2],sortedPop[i][3],sortedPop[i][4]);
    
    # PLOTTING STARTS HERE
    
    # get my data for plotting
    # define variables
    y = [latt];
    x = [longi];
    z = [pop];
    
    #GRAPH 1
    # label the axes
    plt.xlabel('Latitude', fontsize = 13);
    plt.ylabel('Population size', fontsize = 13);

    # Title for Graph 1
    plt.title('Graph 1 \n represents how Population size in the UK varies with Latitude \n \n ', fontsize = 15);
    
    # add a grid
    plt.grid(True);
    
    # plot and show graph
    plt.plot(y,z, 'rx');
    plt.show();
   
    # GRAPH 3
    # Shows how the population varies with Latitude and Longitude
    # make point proportional to population
    # scale population size so it fits on graph 
    
pop = [int(x) for x in pop]

for i in range(0,len(pop)):
	area.append(pop[i]*0.001);
# Split up cities and towns so can see visually what places are either a C or T
pop_town = [];
latt_town = [];
longi_town = [];
area_town = [];

pop_city = [];
latt_city = [];
longi_city = [];
area_city = [];

for i in range(0,len(pop)):
    # if town
	if ttyp[i] == str('Town'):
		pop_town.append(pop[i]);
		latt_town.append(latt[i]);
		longi_town.append(longi[i]);
		area_town.append(area[i]);
    # if city
	elif ttyp[i] == str('City'):
		pop_city.append(pop[i]);
		latt_city.append(latt[i]);
		longi_city.append(longi[i]);
		area_city.append(area[i]);
   
# label the axes
plt.xlabel('Longitude', fontsize = 13);
plt.ylabel('Latitude', fontsize = 13);

# Title for Graph 1
plt.title('Graph 3 \n UK Towns and City Populations represented by size \n plotted by Latitude and Longitude \n \n ', fontsize = 15);

# add a grid
plt.grid(True);

# create scatter  
# x = longitude, y = latitude s = size of point which represents population size
# different colours for city and town so can see clearly correlation
# use alpha function to see overlay
Town = plt.scatter(longi_city, latt_city, s = area_town, c = 'blue', label = 'Town', alpha = 0.5);
City = plt.scatter(longi_town, latt_town, s = area_city, c = 'red', label = 'City', alpha = 0.5);

# Legend for clear labelling
plt.legend((Town,City),
	('Town', 'City'),
	scatterpoints = 1,
	loc = 1,
	ncol = 1,
	fontsize = 13,
	markerscale = (0.3)
	)    
# Plot the graph
plt.show();
# describe the graph
print ('\nFrom this Graph, the size of the bubble represents the size of the population.\nFor example, you can see that London, the UK\'s capital city, has the biggest population!\n');
     
# close the read file
readFile.close();
