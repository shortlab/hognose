# -*- coding: utf-8 -*-
""

import sys , os, getopt, traceback      # First import required modules
import numpy as np              # Operating system modules


import matplotlib.pyplot as plt # Numerical python

plt.switch_backend('agg')

import pylab as py
import scipy.optimize   # needed for trendline calcs


print str(sys.argv)

filename1=str(sys.argv[1])
filename2=str(sys.argv[2])


def main():

	data = np.loadtxt(filename1,delimiter=',',usecols=range(0,2),skiprows=1)
	time1=data[:,0]
	time1=time1/86400         
	Oxide_thickness1=data[:,1]

	data = np.loadtxt(filename2,delimiter=',',usecols=range(0,2),skiprows=1)
	time2=data[:,0]
	time2=time2/86400         
	Oxide_thickness2=data[:,1]


	fit_plot=1 #sys.argv[2]
	if fit_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,8))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=18)
	    axe.plot(time1,Oxide_thickness1,'-o',label=filename1)


	    axe.plot(time2,Oxide_thickness2,'-o',label=filename2)

	    axe.legend(loc='upper left') #,ncol=2)
	    #plt.xlim(0,1600)
	    #plt.ylim(0,25)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.savefig('fig-compare.png')
	    
main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
