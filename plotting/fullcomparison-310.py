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

filename1='updateKam310-1pt6e14_csv.csv'
filename2='updateKam310-1e14_csv.csv'

filename3='formattedupdate310-0_csv.csv'
filename4='updateKam310-0pt5e14_csv.csv'

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
 
 
 
 	Kammenzindt_310_1pt6e14=([0.,176,406,611,700,916,1169,1449,1610])
 	Kammenzindo_310_1pt6e14=np.array([0.,30.,30.,50.,85.,328.,776.,1358.,1699.])
 	Kammenzindo_310_1pt6e14=Kammenzindo_310_1pt6e14/15.

 	Kammenzindt_310_1e14=([0.,368,539,697,782,994,1196,1285,1518,1727,1812,2024,2281])
 	Kammenzindo_310_1e14=([0.,28./15.,36./15.,83./15.,122./15.,346./15.,621./15.,758./15.,1132./15.,
               1438./15.,1579./15.,1925./15.,2361./15.])

 	Kammenzindt_310_0pt5e14=([0.,92,217,370,537,782,995,1196,1289,1464,1693,1902,1991,
                        2206,2460,2737,2901])
  	Kammenzindo_310_0pt5e14=np.array([0.,28.,30.,38.,54.,118.,181.,251.,283.,357.,467.,565.,628.,
                        761.,934.,1146.,1268.])
  	Kammenzindo_310_0pt5e14=Kammenzindo_310_0pt5e14/15.


  	Kammenzindt_310_0=([0.,627,835,1126,1304,1743,1832,2044,2578,2941])
  	Kammenzindo_310_0=np.array([0.,32.,32.,43.,51.,58.,66.,74.,93.,108.])
  	Kammenzindo_310_0=Kammenzindo_310_0/15.


	fit_plot=1 #sys.argv[2]
	if fit_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,12))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=28)
    	    fig.subplots_adjust(left = 0.1,top=0.98,bottom=0.225,right = 0.96)


	    axe.plot(time1,Oxide_thickness1,'b-',linewidth=4,label=r'$\phi = 1.6 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_310_1pt6e14,Kammenzindo_310_1pt6e14,'bo-',markersize=18)#,label='Kammenzind et al. 2016')
	    axe.plot(time2,Oxide_thickness2,'k--',dashes=[15,6],linewidth=4,label=r'$\phi = 1.0 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_310_1e14,Kammenzindo_310_1e14,'k*-',markersize=18)#,label='Kammenzind et al. 2016')
  	    axe.plot(time4,Oxide_thickness4,'g-.',dashes=[15,6,3,6],linewidth=4,label=r'$\phi = 0.5 \cdot 10^{14} n/cm^2-s$')
	    axe.plot(Kammenzindt_310_0pt5e14,Kammenzindo_310_0pt5e14,'gD-',markersize=8)#,label='Kammenzind et al. 2016')
  	    axe.plot(time3,Oxide_thickness3,'m:',dashes=[3,6],linewidth=4,label='Autoclave')
	    axe.plot(Kammenzindt_310_0,Kammenzindo_310_0,'m^-',markersize=18)#,label='Kammenzind et al. 2016')

	    plt.annotate('310'+r'$^\circ C$',xy=(150,9.2),
			 xytext=(150,9.2),fontsize=30)

	    axe.legend(bbox_to_anchor=(-0.035, -0.28, 1., 0.102), loc=3,
		   ncol=2, mode="expand", borderaxespad=0.,fontsize=30)

	    axe.xaxis.set_tick_params(length=8,width=2)
	    axe.yaxis.set_tick_params(length=8,width=2)

	    for axis in ['top','bottom','left','right']:
		axe.spines[axis].set_linewidth(2)



	    plt.xlim(0,2500)
	    plt.ylim(0,10)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=35)
	    plt.xlabel('Time (days)',fontsize=35)
	    plt.savefig('fig-fullcomparison-310.png',dpi=500,bbox='tight')


	Kam_plot=10 #sys.argv[2]
	if Kam_plot==True:    
	    #plt.ion()
	    #plt.show()
	    fig = plt.figure(figsize = (13,8))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=18)

	    axe.plot(Kammenzindt_310_1pt6e14,Kammenzindo_310_1pt6e14,'bo-',markersize=8,label=r'$\phi = 1.6 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_310_1e14,Kammenzindo_310_1e14,'k*-',markersize=8,label=r'$\phi = 1.0 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_310_0pt5e14,Kammenzindo_310_0pt5e14,'gD-',markersize=8,label=r'$\phi = 0.5 \cdot 10^{14} n/cm^2-s$')

	    axe.plot(Kammenzindt_310_0,Kammenzindo_310_0,'m^-',markersize=8,label='autoclave')

	    axe.legend(loc='upper right') #,ncol=2)
	    plt.xlim(0,2500)
	    plt.ylim(0,20)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.savefig('fig-fullKammenzind-310.png')


main()   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
