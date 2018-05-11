# -*- coding: utf-8 -*-
"""
"""

import sys , os, getopt, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
plt.switch_backend('agg')
import pylab as py
import scipy.optimize   # needed for trendline calcs

print str(sys.argv)

filename1='mesh200Kam310-1e14_csv.csv'
filename2='mesh300Kam310-1e14_csv.csv'

filename3='mesh400Kam310-1e14_csv.csv'
filename4='mesh500Kam310-1e14_csv.csv'
filename5='mesh750Kam310-1e14_csv.csv'
filename6='mesh250Kam310-1e14_csv.csv'

def main():
	data = np.loadtxt(filename1,delimiter=',',usecols=range(0,2),skiprows=1)
	time1=data[:,0]
	time1=time1/86400         
	Oxide_thickness1=data[:,1]

	data = np.loadtxt(filename2,delimiter=',',usecols=range(0,2),skiprows=1)
	time2=data[:,0]
	time2=time2/86400         
	Oxide_thickness2=data[:,1]

	data = np.loadtxt(filename3,delimiter=',',usecols=range(0,2),skiprows=1)
	time3=data[:,0]
	time3=time3/86400         
	Oxide_thickness3=data[:,1]
 
	data = np.loadtxt(filename4,delimiter=',',usecols=range(0,2),skiprows=1)
	time4=data[:,0]
	time4=time4/86400         
	Oxide_thickness4=data[:,1] 
 
	data = np.loadtxt(filename5,delimiter=',',usecols=range(0,2),skiprows=1)
	time5=data[:,0]
	time5=time5/86400         
	Oxide_thickness5=data[:,1]

        data = np.loadtxt(filename6,delimiter=',',usecols=range(0,2),skiprows=1)
        time6=data[:,0]
        time6=time6/86400         
        Oxide_thickness6=data[:,1]


	fit_plot=1 #sys.argv[2]
	if fit_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,8))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=18)


	    axe.plot(time1[0::10],Oxide_thickness1[0::10],'-o',label='nx = 200')
            axe.plot(time6[0::10],Oxide_thickness6[0::10],'->',label='nx = 250')
	    axe.plot(time2[0::10],Oxide_thickness2[0::10],'->',label='nx = 300')
  	    axe.plot(time3[0::10],Oxide_thickness3[0::10],'-x',label='nx = 400')
  	    axe.plot(time4[0::10],Oxide_thickness4[0::10],'-s',label='nx = 500')
  	    axe.plot(time5[0::10],Oxide_thickness5[0::10],'-*',label='nx = 750')
       
	    axe.legend(loc='best') #,ncol=2)
	    plt.xlim(0,575)
	    plt.ylim(0,2.1)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.savefig('fig-mesh_convergence-310.png',bbox_inches='tight')
	    

main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
