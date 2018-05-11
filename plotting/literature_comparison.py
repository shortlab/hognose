# -*- coding: utf-8 -*-
"""
"""

import sys , os, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
plt.switch_backend('agg')
import pylab as py

import scipy.optimize

# Trying to find a data fit:
def f2(t,a,b):
    return a*np.power(t,b)

# Initial guess for the curve fitting:    
guess=[0.25,0.3]

#################################################################
# Set up arrays for Bouineau 2008:
time_2=np.array([0.,1.7,3.1,5.3,24.8,50.1,71.3,76.1,80.9,86.1,91.,101.4,
                 125.7,151.7,162.1,167.3,172.,176.8,182.,197.9])
thickness_2=np.array([0.,0.49,0.67,0.71,1.29,1.58,1.84,2.09,2.2,2.37,
                      2.35,2.72,3.28,3.42,3.75,3.86,4.11,4.18,4.37,4.8])
time_2fit=np.array([0.,1.7,3.1,5.3,24.8,50.1,71.3])
thickness_2fit=np.array([0.,0.49,0.67,0.71,1.29,1.58,1.84])                      
# Set up fits for the data:
# Initial guess for the curve fitting:    
guess=[0.25,0.3]
params=scipy.optimize.curve_fit(f2,time_2fit,thickness_2fit,guess)
results=params[0]
fit_coeff=results[0]
fit_exponent=results[1]

# Create arrays to hold the trendline fits:
time_fit=np.linspace(0,250,60)
thickness_fit=np.linspace(0,250,60)

# Calculate the trendline (fit) thicknesses using the values obtained
# through scipy.optimize.curve_fit above:
for n in range(60):
    thickness_fit[n]=fit_coeff*np.power(time_fit[n],fit_exponent)    
fit=str(round(fit_coeff,3))+'*t^'+str(round(fit_exponent,3))
fit=r'$0.422 \cdot t^{0.343}$'
fit=r'$0.42 \cdot t^{0.34}$'
    

# Set up dictionary:    
lit_t1={1:'Zircaloy-4',
       2:'Bouineau et al. 2008',
       3:'water',
       4:'simulated PWR chemistry',
       5:'3.5 ppm LiOH, 1000 ppm H3BO3',
       6:time_2,
       7:thickness_2,
       8:time_fit,
       9:thickness_fit,
       10:fit_coeff,
       11:fit_exponent,
       12:fit}
#################################################################

#################################################################
# Set up arrays for Jeong 2006
time_3=np.array([0.,13.7,29.9,46.1,60.3,89.7,120.6,133.8,149.5,
                 179.9,209.7,240.7,269.5,299.9,330.3,360.2,390.6,
                 420.5,450.4,480.8,510.7,540.6,567.,600.3,630.2,
                 661.1,690.5,720.4,750.8,780.7,840.4])
thickness_3=np.array([0.,1.09,1.43,1.57,1.67,1.89,2.69,3.2,3.47,
                      3.73,4.11,5.14,5.51,5.83,6.85,7.47,7.77,8.62,
                      9.21,9.61,10.15,10.59,10.85,11.10,11.16,11.33,
                      11.57,12.13,12.85,13.16,13.8])
time_3_fit=np.array([0.,13.7,29.9,46.1,60.3,89.7])
thickness_3_fit=np.array([0.,1.09,1.43,1.57,1.67,1.89])                      
# Set up fits for the data:
# Initial guess for the curve fitting:    
guess=[0.25,0.3]
params=scipy.optimize.curve_fit(f2,time_3_fit,thickness_3_fit,guess)
results=params[0]
fit_coeff=results[0]
fit_exponent=results[1]

# Create arrays to hold the trendline fits:
time_fit=np.linspace(0,250,60)
thickness_fit=np.linspace(0,250,60)

# Calculate the trendline (fit) thicknesses using the values obtained
# through scipy.optimize.curve_fit above:
for n in range(60):
    thickness_fit[n]=fit_coeff*np.power(time_fit[n],fit_exponent) 
fit=str(round(fit_coeff,3))+'*t^'+str(round(fit_exponent,3))
fit=r'$0.535 \cdot t^{0.281}$'
fit=r'$0.54 \cdot t^{0.28}$'

    
lit_3={1:'Zircaloy-4',
       2:'Jeong et al. 2006',
       3:'water',
       4:'simulated PWR chemistry',
       5:'2.2 ppm Li, 650 ppm B',
       6:time_3,
       7:thickness_3,
       8:time_fit,
       9:thickness_fit,
       10:fit_coeff,
       11:fit_exponent,
       12:fit}
################################################################# 


#################################################################
# Polatidis 2013 Zircaloy-4 simulated PWR chemistry
# Set up (limited) arrays for Yilmazbayhan 2004
time_6=np.array([0.,20.,34.,40.,54.,59.,74.,80.,94.,100.,115.,
                 120.,139.,160.,180.,200.,220.])
thickness_6=np.array([0.,0.85,0.97,1.08,1.2,1.22,1.27,1.35,1.41,
                      1.5,1.65,1.55,1.75,1.87,2.2,2.97,3.35])
time_6fit=np.array([0.,20.,34.,40.,54.,59.,74.,80.,94.,100.,115.,
                 120.,139.,160.])
thickness_6fit=np.array([0.,0.85,0.97,1.08,1.2,1.22,1.27,1.35,1.41,
                      1.5,1.65,1.55,1.75,1.87])
# Set up fits for the data:
# Initial guess for the curve fitting:    
guess=[0.25,0.3]
params=scipy.optimize.curve_fit(f2,time_6fit,thickness_6fit,guess)
results=params[0]
fit_coeff=results[0]
fit_exponent=results[1]

# Create arrays to hold the trendline fits:
time_fit=np.linspace(0,250,60)
thickness_fit=np.linspace(0,250,60)

# Calculate the trendline (fit) thicknesses using the values obtained
# through scipy.optimize.curve_fit above:
for n in range(60):
    thickness_fit[n]=fit_coeff*np.power(time_fit[n],fit_exponent)
    
fit=str(round(fit_coeff,3))+'*t^'+str(round(fit_exponent,3))
fit=r'$0.243 \cdot t^{0.396}$'
fit=r'$0.24 \cdot t^{0.40}$'


lit_6={1:'Zircaloy-4',
       2:'Polatidis et al. 2013',
       3:'water',
       4:'simulated PWR chemistry',
       5:'2 ppm Li, 1000 ppm B',
       6:time_6,
       7:thickness_6,
       8:time_fit,
       9:thickness_fit,
       10:fit_coeff,
       11:fit_exponent,
       12:fit}
#################################################################

#################################################################
# Motta et al. 2008 (Zrly-4)
time_19=np.array([0.,3.,28.01,56.05,90.14,120.33,150.10,177.25,210.04,
                  240.23,270.43,301.04,329.93,352.8,381.27,408.87,436.46,
                  464.49,492.96])
thickness_19=np.array([0.,9.27,19.05,23.66,28.0,30.4,36.36,53.51,59.74,
                       64.07,68.94,85.54,94.5,98.29,102.35,112.95,126.28,
                       133.88,138.75])

thickness_19=thickness_19/15 # convert to microns from mg/dm^2
                     
time_19fit=np.array([0.,3.,28.01,56.05,90.14,120.33])
thickness_19fit=np.array([0.,9.27,19.05,23.66,28.0,30.4])
thickness_19fit=thickness_19fit/15 # convert to microns from mg/dm^2

# Set up fits for the data:
# Initial guess for the curve fitting:    
guess=[0.25,0.3]
params=scipy.optimize.curve_fit(f2,time_19fit,thickness_19fit,guess)
results=params[0]
fit_coeff=results[0]
fit_exponent=results[1]

# Create arrays to hold the trendline fits:
time_fit=np.linspace(0,250,60)
thickness_fit=np.linspace(0,250,60)

# Calculate the trendline (fit) thicknesses using the values obtained
# through scipy.optimize.curve_fit above:
for n in range(60):
    thickness_fit[n]=fit_coeff*np.power(time_fit[n],fit_exponent)
    
fit=str(round(fit_coeff,3))+'*t^'+str(round(fit_exponent,3))
fit=r'$0.432 \cdot t^{0.323}$'
fit=r'$0.43 \cdot t^{0.32}$'

lit_t16={1:'Zircaloy-4',
       2:'Motta et al. 2008',
       3:'water',
       4:'pure',
       5:'0 ppm Li, 0 ppm B',
       6:time_19,
       7:thickness_19,
       8:time_fit,
       9:thickness_fit,
       10:fit_coeff,
       11:fit_exponent,
       12:fit}
#################################################################

# First I need to read in from a csv:
x_row=0
userow=2
maxcol=3

filename1='update360-0_csv.csv' #'360_out_sub_app0.csv'#'runtime_csv.csv' #'RESULTS-100.csv'


fit1='0.383*t^0.367'
fit1=r'$0.383\cdot t^{0.367}$'
fit1=r'$0.418\cdot t^{0.328}$'
fit1=r'$0.42\cdot t^{0.39}$'

    
data1 = np.loadtxt(filename1,delimiter=',',usecols=range(0,10),skiprows=1)#2),skiprows=1)
time1=data1[:,0]
total_oxide1=data1[:,1]#9]#1]
time1=time1/86400
    

yerr_low=np.array([0,11.5,13.9,14.8,16.9,17.0,19.0,19.1,20.4,20.9,
                     23.7,22.4,24.2,26.8,33.0,44.3,49.7])
yerr_upp=np.array([0,14.1,14.7,17.1,18.2,19.3,19.0,21.3,21.3,23.3,
                     25.3,23.1,26.6,29.6,35.0,45.1,50.8])
            
# Convert to microns from mg/dm^2 (weight gain):
yerr_low=yerr_low/15.0
yerr_upp=yerr_upp/15.0


polatidis=lit_6[7]

yerr_lower=np.zeros(17)
yerr_upper=np.zeros(17)


for i in range(16):
    yerr_lower[i]=polatidis[i]-yerr_low[i]
    yerr_upper[i]=yerr_upp[i]-polatidis[i]
    
    
    
# EDEN2010 data
EDENt=np.array([4.8,23.8,49.6,73.8])
EDENo=np.array([0.71,1.11,1.46,1.99])

# Swan2016 data - 350 C, not 360 C
Swan2016t=np.array([1.66,19.6,40.0,61.1,82.8,103.9,118.2,123.1,128.1,138.7,151.7])
Swan2016o=np.array([0.46,1.13,1.57,1.74,1.95,2.09,2.10,2.13,2.11,2.05,2.25])
    
    

alloy='Zircaloy-4'
Zircaloy4=True

if Zircaloy4:
    plt.ion()
    plt.show()
    fig = plt.figure(figsize = (13,11))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=28)
    fig.subplots_adjust(left = 0.075,right = 0.925)
    
    if lit_t1[1]==alloy:
        axe.plot(lit_t1[6],lit_t1[7],'^',markersize=18,color='black',label=lit_t1[2]+': '+lit_t1[12])

    if lit_3[1]==alloy:
        lit_t1=lit_3
        axe.plot(lit_t1[6],lit_t1[7],'D',markersize=18,label=lit_t1[2]+': '+lit_t1[12],color='#990066')


    if lit_6[1]==alloy:
        lit_t1=lit_6
        axe.plot(lit_t1[6],lit_t1[7],'o',markersize=18,linewidth=4,label=lit_t1[2]+': '+lit_t1[12],color='#006699')

        axe.errorbar(lit_t1[6],lit_t1[7],color='#006699',yerr=[yerr_lower,yerr_upper],fmt='o',markersize=18,linewidth=4)

                     
    if lit_t16[1]==alloy:
        lit_t1=lit_t16
        axe.plot(lit_t1[6],lit_t1[7],'s',markersize=18,label=lit_t1[2]+': '+lit_t1[12],color='#CC0000')
   
    axe.plot(EDENt,EDENo,'y*',markersize=18,label='EDEN 2010: '+r'$0.42\cdot t^{0.31}$')                   
    axe.plot(Swan2016t,Swan2016o,'x',markersize=18,label='Swan et al. 2016 (350'+r'$^\circ$'+'C): '+r'$0.46\cdot t^{0.32}$')                   
    axe.plot(time1,total_oxide1,'g--',linewidth=6,markersize=18,label='HOGNOSE: '+fit1)
    axe.legend(bbox_to_anchor=(-0.05, -0.7, 1., 0.102), loc=3,
           ncol=1, mode="expand", borderaxespad=0.,fontsize=30)

    axe.xaxis.set_tick_params(length=8,width=2)
    axe.yaxis.set_tick_params(length=8,width=2)

    for axis in ['top','bottom','left','right']:
	axe.spines[axis].set_linewidth(2)

    plt.xlim(0,145)
    plt.ylim(0,2)
    plt.xlabel('Time (days)',fontsize=35)
    plt.ylabel('Oxide Thickness (microns)',fontsize=35)
    plt.savefig('HOGNOSE_360C_autoclave_lit_comparison',dpi = 500,bbox_inches='tight')
    


