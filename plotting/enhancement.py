# -*- coding: utf-8 -*-
"""
"""

import sys , os, getopt, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
plt.switch_backend('agg')
import pylab as py
import scipy.optimize   # needed for trendline calcs

  
#plt.ion()
#plt.show()

Kammenzind2016T=np.array([270,310,350])
Kammenzind2016f=np.array([40,30,3.5])

MATPROT=np.array([280,340,400])
MATPROf=np.array([2.5,1.5,1])

Seibold2002T=np.array([310,335])
Seibold2002f=np.array([4,4])

Seibold2002bT=np.array([349.5,350.5])
Seibold2002bf=np.array([3.5,3.5])

Seibold2002fT=np.array([291.7,293.5,296.4,299.3,315.4,317.4,317.4,320.7,322.0])
Seibold2002ff=np.array([15.6,17.7,16.9,16.8,8.9,11.6,8.4,7.4,8.7])

Seibold2002fT2=np.array([325.1,316.0,318.0,318.0,321.1,322.5,326.1,327.7,325.6])
Seibold2002ff2=np.array([5.5,5.5,5.0,4.6,3.6,3.6,3.1,3.8,4.8])

Seibold2002fT3=np.array([329.0,319.7])
Seibold2002ff3=np.array([4.8,3.5])

fig = plt.figure(figsize = (13,8))
axe = fig.add_subplot(111)
axe.tick_params(labelsize=18)



axe.plot(Kammenzind2016T,Kammenzind2016f,'>',markersize=12,label='Kammenzind et al. 2016')
axe.plot(MATPROT,MATPROf,'<',markersize=12,label='MATPRO using '+r'$T_{clad,surface}$')
#axe.plot(Seibold2002T,Seibold2002f,'r-',linewidth=5,label='Seibold et al. 2002')
#axe.plot(Seibold2002bT,Seibold2002bf,'r-',linewidth=5)
axe.plot(Seibold2002fT,Seibold2002ff,'ro',markersize=8,label='Seibold et al. 2002')
axe.plot(Seibold2002fT2,Seibold2002ff2,'ro',markersize=8)
axe.plot(Seibold2002fT3,Seibold2002ff3,'ro',markersize=8)

#axe.plot(time4[0::1],Oxide_thickness4[0::1],'-s',label='value = 0.8')


axe.legend(loc='best') #,ncol=2)
plt.xlim(265,405)
plt.ylim(0,87.5)#41)
plt.ylabel('Reactor Corrosion Rate / Autoclave Corrosion Rate',fontsize=20)
plt.xlabel('Temperature ('+r'$^\circ$'+'C)',fontsize=20)
plt.savefig('fig-enhancement.png',bbox_inches='tight')
	    


HOGNOSEt=np.array([270,290,310,330])
HOGNOSEf=np.array([84.9,42.1,5.5,2.1])


HOGNOSEon=1
if HOGNOSEon==True:
	fig = plt.figure(figsize = (13,10))
	axe = fig.add_subplot(111)
	axe.tick_params(labelsize=28)
        fig.subplots_adjust(left = 0.11,top=0.97,right = 0.96)


	axe.plot(Kammenzind2016T,Kammenzind2016f,'>',markersize=18,label='Kammenzind et al. 2016')
	axe.plot(MATPROT,MATPROf,'<',markersize=18,label='MATPRO using '+r'$T_{clad,surface}$')
	axe.plot(Seibold2002fT,Seibold2002ff,'ro',markersize=18,label='Seibold et al. 2002')
	axe.plot(Seibold2002fT2,Seibold2002ff2,'ro',markersize=18)
	axe.plot(Seibold2002fT3,Seibold2002ff3,'ro',markersize=18)
	axe.plot(HOGNOSEt,HOGNOSEf,'k*-',markersize=28,linewidth=6,label='HOGNOSE results at '+r'$\phi = 1.0 \cdot 10^{14} n/cm^2-s$')

	axe.xaxis.set_tick_params(length=8,width=2)
	axe.yaxis.set_tick_params(length=8,width=2)

	for axis in ['top','bottom','left','right']:
	  axe.spines[axis].set_linewidth(2)

	axe.legend(loc='best',fontsize=25) #,ncol=2)
	plt.xlim(265,352)
	plt.ylim(0,87.5)
	plt.ylabel('Enhancement Factor',fontsize=35)
	plt.xlabel('Temperature ('+r'$^\circ$'+'C)',fontsize=35)
	plt.savefig('fig-HOGNOSE-enhancement.png',dpi=500,bbox_inches='tight')	    
	    
    


aftertransition=10

if aftertransition==True:
	f270phi=np.array([0.25,0.4,0.7,1.0,1.6])
	f270f=np.array([8.5,31.2,81.4,84.9,84.9])

	f290phi=np.array([0.25,0.5,0.7,1.0,1.6])
	f290f=np.array([2.6,6.5,12.5,42.1,74.3])

	f310phi=np.array([0.25,0.5,1.0,1.6])
	f310f=np.array([1.4,2.3,5.5,14.4])

	f330phi=np.array([0.25,0.5,1.0,1.6])
	f330f=np.array([1.1,1.3,2.1,3.8])
else:
	f270phi=np.array([0,0.25,0.4,0.7,1.0,1.6])
	f270f=np.array([1,4.4,6.9,8.9,9.6,10.3])

	f290phi=np.array([0,0.25,0.5,0.7,1.0,1.6])
	f290f=np.array([1,2.1,3.7,5.0,7.0,8.2])

	f310phi=np.array([0,0.25,0.5,1.0,1.6])
	f310f=np.array([1,1.3,1.9,3.3,5.1])

	f330phi=np.array([0,0.25,0.5,1.0,1.6])
	f330f=np.array([1,1.1,1.3,1.8,2.6])
    
HOGNOSEonly=1
if HOGNOSEonly==True:
	fig = plt.figure(figsize = (13,10))
	axe = fig.add_subplot(111)
	axe.tick_params(labelsize=28)
        fig.subplots_adjust(left = 0.11,top=0.97,right = 0.96)


	axe.plot(f270phi,f270f,'ro-',linewidth=4,markersize=18,label='270'+r'$^\circ$'+'C')
	axe.plot(f290phi,f290f,'b>-',linewidth=4,markersize=18,label='290'+r'$^\circ$'+'C')
	axe.plot(f310phi,f310f,'g<-',linewidth=4,markersize=18,label='310'+r'$^\circ$'+'C')
	axe.plot(f330phi,f330f,'k*-',linewidth=4,markersize=28,label='330'+r'$^\circ$'+'C')

	axe.legend(loc='best',fontsize=25) #,ncol=2)

	axe.xaxis.set_tick_params(length=8,width=2)
	axe.yaxis.set_tick_params(length=8,width=2)

	for axis in ['top','bottom','left','right']:
	  axe.spines[axis].set_linewidth(2)
	
	plt.xlim(0,1.75)
	axe.xaxis.set_ticks(np.arange(0,1.75,0.25))
	if aftertransition==True:
		plt.ylim(0,87.5)
	else:
		plt.ylim(1,11)
		axe.yaxis.set_ticks(np.arange(1,11, 1))

	plt.ylabel('Enhancement Factor',fontsize=35)
	plt.xlabel('Neutron Flux '+r'$\phi $'+' (in multiples of '+r'$10^{14} n/cm^2-s$)',fontsize=35)
	plt.savefig('fig-overallHOGNOSE-enhancement.png',dpi=500,bbox_inches='tight')	   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
