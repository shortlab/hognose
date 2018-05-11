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

filename1='updateKam270-1e14_csv.csv'
filename2='updateKam270-0pt7e14_csv.csv'

filename3='formattedupdate270-0_csv.csv'
filename4='updateKam270-0pt4e14_csv.csv'

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
 
 
 


	Kammenzindt_270_1e14=([0.,106,774,1060,1482,1825,2105,2385,2642,3275])
 	Kammenzindo_270_1e14=np.array([0.,19.2,27.8,27.7,40.8,93.5,227.7,388.3,540.1,887.7])
	Kammenzindo_270_1e14=Kammenzindo_270_1e14/15.

	Kammenzindt_270_0pt7e14=([0.,157,351,506,640,897,1143,1251,1508,1677,1911,2631,2973,3247,3527,3784,4109,4418,4806])
 	Kammenzindo_270_0pt7e14=np.array([0.,21.,22.,26.,27.,28.,29.,30.,34.,37.,46.,171.,312.,451.,594.,732.,897.,1042.,1229.])
	Kammenzindo_270_0pt7e14=Kammenzindo_270_0pt7e14/15.

	Kammenzindt_270_0pt4e14=([0.,546,894,1157,1322,1568,1848,2276,2613,2893,3430,3750,4021,4390])
 	Kammenzindo_270_0pt4e14=np.array([0.,23.,28.,30.,30.,34.,47.,78.,104.,137.,260.,361.,458.,573.])
	Kammenzindo_270_0pt4e14=Kammenzindo_270_0pt4e14/15.

	Kammenzindt_270_0=([0.,608,1302,1728,2065,2345,2625,2882,3202,3482,3842])
 	Kammenzindo_270_0=np.array([0.,14.,18.,23.,27.,29.,36.,47.,51.,56.,64.])
	Kammenzindo_270_0=Kammenzindo_270_0/15.


	fit_plot=1 #sys.argv[2]
	if fit_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,12))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=28)
    	    fig.subplots_adjust(left = 0.1,top=0.98,bottom=0.225,right = 0.96)


	    axe.plot(time1,Oxide_thickness1,'b-',linewidth=4,label=r'$\phi = 1.0 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_270_1e14,Kammenzindo_270_1e14,'bo-',markersize=18)#,label='Kammenzind et al. 2016')

     
	    axe.plot(time2,Oxide_thickness2,'k--',dashes=[15,6],linewidth=4,label=r'$\phi = 0.7 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_270_0pt7e14,Kammenzindo_270_0pt7e14,'k*-',markersize=18)#,label='Kammenzind et al. 2016')



  	    axe.plot(time4,Oxide_thickness4,'g-.',dashes=[15,6,3,6],linewidth=4,label=r'$\phi = 0.4 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_270_0pt4e14,Kammenzindo_270_0pt4e14,'gD-',markersize=18)#,label='Kammenzind et al. 2016')



  	    axe.plot(time3,Oxide_thickness3,'m:',dashes=[3,6],linewidth=4,label='Autoclave')
	    axe.plot(Kammenzindt_270_0,Kammenzindo_270_0,'m^-',markersize=18)#,label='Kammenzind et al. 2016')
       
 
            plt.annotate('270'+r'$^\circ C$',xy=(150,9.2),
			 xytext=(150,9.2),fontsize=30)

	    axe.legend(bbox_to_anchor=(-0.035, -0.28, 1., 0.102), loc=3,
		   ncol=2, mode="expand", borderaxespad=0.,fontsize=30)

	    axe.xaxis.set_tick_params(length=8,width=2)
	    axe.yaxis.set_tick_params(length=8,width=2)

	    for axis in ['top','bottom','left','right']:
		axe.spines[axis].set_linewidth(2)
	    
	    plt.xlim(0,3500)
	    plt.ylim(0,10)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=35)
	    plt.xlabel('Time (days)',fontsize=35)
	    plt.savefig('fig-fullcomparison-270.png',dpi=500,bbox='tight')


	Kam_plot=10 #sys.argv[2]
	if Kam_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,8))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=18)
	    fig.subplots_adjust(left = 0.075,right = 0.925)

	    axe.plot(Kammenzindt_270_1e14,Kammenzindo_270_1e14,'bo-',markersize=8,label=r'$\phi = 1.0 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_270_0pt7e14,Kammenzindo_270_0pt7e14,'k*-',markersize=8,label=r'$\phi = 0.7 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_270_0pt4e14,Kammenzindo_270_0pt4e14,'gD-',markersize=8,label=r'$\phi = 0.4 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_270_0,Kammenzindo_270_0,'m^-',markersize=8,label='autoclave')
       
	    axe.legend(loc='best')#'upper right') #,ncol=2)
	    plt.xlim(0,3500)
	    plt.ylim(0,20)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.savefig('fig-fullKammenzind-270.png',bbox='tight')
	    

main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
