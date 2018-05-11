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

filename1='updateHillnerbaseline_csv.csv'
filename2='updateHillnerhilo_csv.csv'

Hillnerbaselinet=([169,169,
            381,381,
            541,541,
            702,702,
            896,896,
            1046,1046,
            1187,1187,
            1438,1438,1438,
            1684,1684,1684,1684,
            1788,1788,1788,1788,1788,
            2046,2046,2046,2046,2046,2046,2046,2046,2046,
            2215,2215,2215,2215,2215,2215,2215,2215,2215,
            2454,2454,2454,2454,2454,2454,2454,2454,2454,2454,2454,2454,2454,
            2747,2747,2747,2747,2747,2747,2747,2747,2747,2747,2747,2747,2747,
            2848,2848,2848,2848,2848,2848,2848,2848,2848,2848,2848,
            3072,
            3175,3175,3175,3175,3175,3175,3175,3175,3175,3175,3175])
            
Hillnerbaselineoxide=([1.6,1.2,
                1.3,1.9,
                1.3,2.0,
                1.6,2.2,
                2.3,1.7,
                1.8,2.4,
                2.4,1.9,
                2.0,3.4,2.8,
                5.5,4.6,3.7,2.9,
                6.7,5.5,4.7,3.9,3.3,
                14.1,12.9,12.0,10.5,8.9,7.9,7.2,6.0,6.3,
                22.1,20.1,18.3,16.9,13.5,12.4,11.3,10.1,8.7,
                34.7,32.0,30.0,29.0,24.9,22.7,21.2,18.8,18.2,17.4,15.9,15.1,14.5,
                49.7,47.7,45.1,42.3,39.9,36.4,34.5,33.7,30.9,29.6,27.5,26.7,26.1,
                54.3,52.2,50.5,46.5,44.3,40.6,38.2,35.1,33.3,31.0,30.0,
                50.0,
                70.7,68.7,67.3,61.2,60.5,56.0,53.2,49.7,47.5,46.7,44.9])


Hillnerhilot=([0,392,751,1008,1172,1411,1698,2125,2455])
Hillnerhilooxide=([0,1.7,1.8,2.1,2.7,4.9,9.5,23.8,34.0])




def main():
	data = np.loadtxt(filename1,delimiter=',',usecols=range(0,2),skiprows=1)
	time1=data[:,0]
	time1=time1/86400         
	Oxide_thickness1=data[:,1]

	data = np.loadtxt(filename2,delimiter=',',usecols=range(0,2),skiprows=1)
	time2=data[:,0]
	time2=time2/86400         
	Oxide_thickness2=data[:,1]
	# Use len(sys.argv) to determine the number of files to read in and plot:
	num_files=len(sys.argv)-1




	fit_plot=1 #sys.argv[2]
	if fit_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,10))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=28)
	    fig.subplots_adjust(left = 0.11,top=0.97,right = 0.96)

	    axe.plot(time1,Oxide_thickness1,'g-.',dashes=[15,6,3,6],linewidth=6,label='HOGNOSE results for baseline data')

	    axe.plot(time2,Oxide_thickness2,'r--',dashes=(15,6),linewidth=6,label='HOGNOSE results for high-low flux data')

	    axe.plot(Hillnerbaselinet,Hillnerbaselineoxide,'go',markersize=18,label='Hillner baseline data')

	    axe.plot(Hillnerhilot,Hillnerhilooxide,'r>',markersize=18,label='Hillner high-low flux data')

	    axe.xaxis.set_tick_params(length=8,width=2) 
	    axe.yaxis.set_tick_params(length=8,width=2)

	    for axis in ['top','bottom','left','right']:
	      axe.spines[axis].set_linewidth(2)
  	    



	    axe.legend(loc='best',fontsize=25) #,ncol=2)
	    plt.xlim(0,2000)
	    plt.ylim(0,10)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=35)
	    plt.xlabel('Time (days)',fontsize=35)
	    plt.savefig('fig-comparison_Hillner.png',dpi=500,bbox='tight')
	    

main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
