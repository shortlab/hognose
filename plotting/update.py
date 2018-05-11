# -*- coding: utf-8 -*-
"""
"""

import sys , os, getopt, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
import pylab as py
import scipy.optimize   # needed for trendline calcs


#print str(sys.argv)

filename=str(sys.argv[1])

#filename='d1.csv'
print str(sys.argv)

def main(filename):
	# If there are 6 columns, use range(0,7)
	# First I need to read in from a csv:
	num_cols= int(sys.argv[2]) #2 #13
	data = np.loadtxt(filename,delimiter=',',usecols=range(0,num_cols+1),skiprows=1)
	#data = np.loadtxt(filename,delimiter=';',dtype='float')
	#

	# Assign imported data to individual arrays:
	    # NOTE: be careful about the indices used, since adding or using
	    # different postprocessors can change the column order and number.
	time=data[:,0]
	time=time/86400         # convert time from seconds to days
	#BulkSwitch=data[:,1]
	#total_metal=data[:,2]
	#LTL=data[:,2]
	Oxide_thickness=data[:,num_cols]
	#total_solute=data[:,4]
	#PP_dt=data[:,5]
	#Transition_location=data[:,6]
	#avg_thermal_cond=data[:,7]
	#current_time=data[:,8]
	#dt_ratio=data[:,9]
	#max_O_begin=data[:,10]
	#min_O=data[:,11]
	#oxide_front_position=data[:,12]
	#ratio=data[:,13]

	data_size=np.size(time)

     #print Oxide_thickness(5)
	####################################################################
	####################################################################
	# Find the transition index:
	transition_index=5
	transition_time=5
	for i in range(data_size):
	    #if BulkSwitchPP[i]>0.5 and Oxide_thickness[i]<2.5:
	    #if time[i]<377:
		#if time[i]>376:
	    #if ((Oxide_thickness[i]>1.97) and (Oxide_thickness[i]<2)).any():
	    transition_index=i
	    transition_time=time[i]
	print 'Transition index = ',transition_index       
	print 'Transition time = ',transition_time,' days'
 	print 'Transition thickness = ',Oxide_thickness[transition_index],' microns'

		    

	# Trying to find a data fit:
	def f2(t,a,b):
	    return a*np.power(t,b)    

	guess=[0.25,0.35]
	params=scipy.optimize.curve_fit(f2,time[0:transition_index],
				                Oxide_thickness[0:transition_index],guess)
	results=params[0]
	fit_coeff=results[0]
	fit_exponent=results[1]

	print "fit_coeff"
	print str(round(fit_coeff,3))
	print "fit_exponent"
	print str(round(fit_exponent,3))

	# Create arrays to hold the trendline fits:
	time_fit=np.linspace(0,transition_time,100)
	thickness_fit=np.linspace(0,transition_time,100)

	# Calculate the trendline (fit) thicknesses using the values obtained
	# through scipy.optimize.curve_fit above:
	for n in range(100):
	    thickness_fit[n]=fit_coeff*np.power(time_fit[n],fit_exponent) 
	fit=str(round(fit_coeff,3))+'*t^'+str(round(fit_exponent,3))

	fit_plot=10 #sys.argv[2]
	if fit_plot==True:    
	    plt.ion()
	    plt.show()
	    fig = plt.figure(figsize = (13,8))
	    axe = fig.add_subplot(111)
	    axe.tick_params(labelsize=18)
	    axe.plot(time,Oxide_thickness,'-o',color='red',label='HOGNOSE results '+fit)
	    axe.plot(time_fit,thickness_fit,'-x',color='blue',label='Trendline')
	    #plt.annotate(fit,xy=(time_fit[30],thickness_fit[30]),
	#		 xytext=(time_fit[30]+1,thickness_fit[30]-.15),
	#		     arrowprops=dict(arrowstyle="->"))    
	    axe.legend(loc = 4) #'best')
	    axe.legend(loc=4,ncol=2)
	    #plt.xlim(0,1.8)
	    #plt.ylim(0,1.2)
	    plt.ylabel('Oxide Thickness (microns)',fontsize=20)
	    plt.xlabel('Time (days)',fontsize=20)
	    plt.title('HOGNOSE vs Literature Data Comparison') 
	    plt.savefig('plot.png')
	    

main(filename)   
	    
	    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
