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

filename1='predict0Kam310-1e14_csv.csv'
filename2='predict03Kam310-1e14_csv.csv'

filename3='predict06Kam310-1e14_csv.csv'
filename4='predict08Kam310-1e14_csv.csv'
filename5='predict09Kam310-1e14_csv.csv'
filename6='predict10Kam310-1e14_csv.csv'

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


	    axe.plot(time2[1::10],Oxide_thickness2[1::10],'->',label='value = 0.3')
  	    axe.plot(time3[2::10],Oxide_thickness3[2::10],'-x',label='value = 0.6')
  	    axe.plot(time4[4::10],Oxide_thickness4[4::10],'-s',label='value = 0.8')
  	    axe.plot(time5[6::10],Oxide_thickness5[6::10],'-*',label='value = 0.9')
            axe.plot(time6[8::10],Oxide_thickness6[8::10],'-D',label='value = 1.0')
	    axe.plot(time1[0::10],Oxide_thickness1[0::10],'-o',label='No predictor')

	    axe.legend(loc='best') #,ncol=2)
	    plt.xlim(0,575)
	    plt.ylim(0,2)#12.1)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.savefig('fig-predictor_study-310.png',bbox_inches='tight')

main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
