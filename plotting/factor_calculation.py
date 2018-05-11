# -*- coding: utf-8 -*-
"""
"""

import sys , os, getopt, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
plt.switch_backend('agg')
import pylab as py
import scipy.optimize   # needed for trendline calcs


filename1=str(sys.argv[1])
filename2=str(sys.argv[2])



data = np.loadtxt(filename1,delimiter=',',usecols=range(0,2),skiprows=1)
time=data[:,0]
time=time/86400         
oxide=data[:,1]



data = np.loadtxt(filename2,delimiter=',',usecols=range(0,2),skiprows=1)
time2=data[:,0]
time2=time2/86400         
oxide2=data[:,1]



# Use the range from 2 microns to 10 microns:

def find_index(max_index,array,threshold):
	transition_n = 0
	for n in range(0,max_index):
		if (transition_n < 0.5):
			if (array[n] > threshold):
				transition_n = n
	return transition_n

def corr_rate(t1,o1,t2,o2):
	return (o2-o1)/(t2-t1)





transition_n=find_index(np.size(time),oxide,2)

transition_1=find_index(np.size(time),oxide,2)
max_1=find_index(np.size(time),oxide,10)

#transition_2=find_index(np.size(time2),oxide2,0)
#transition_1=0
transition_2=0
max_2=find_index(np.size(time2),oxide2,2)

# Rate 

rate_1 = corr_rate(time[transition_1],oxide[transition_1],time[max_1],oxide[max_1])

rate_2 = corr_rate(time2[transition_2],oxide2[transition_2],time2[max_2],oxide2[max_2])

print "\n\n\n\n"
print "For ",filename1,":"
print "(",time[transition_1],",",oxide[transition_1],")"
print "(",time[max_1],",",oxide[max_1],")"
print "                                      and"
print "For ",filename2,":"
print "(",time2[transition_2],",",oxide2[transition_2],")"
print "(",time2[max_2],",",oxide2[max_2],")"
print "\n----------------------------------------"
print "The post-transition enhancement factor is: ",round(rate_1/rate_2,1)
print "----------------------------------------"

transition_1=0

rate_1 = corr_rate(time[transition_1],oxide[transition_1],time[max_1],oxide[max_1])

rate_2 = corr_rate(time2[transition_2],oxide2[transition_2],time2[max_2],oxide2[max_2])

print "\n"
print "(",time[transition_1],",",oxide[transition_1],")"
print "(",time[max_1],",",oxide[max_1],")"
print "                                      and"
print "For ",filename2,":"
print "(",time2[transition_2],",",oxide2[transition_2],")"
print "(",time2[max_2],",",oxide2[max_2],")"
print "\n----------------------------------------"
print "The 0 to 10 micron enhancement factor is: ",round(rate_1/rate_2,1)
print "----------------------------------------"




    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
