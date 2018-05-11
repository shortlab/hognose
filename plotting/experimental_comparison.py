# -*- coding: utf-8 -*-
"""
"""

import sys , os, traceback      # First import required modules
import numpy as np              # Operating system modules
import matplotlib.pyplot as plt # Numerical python
plt.switch_backend('agg')
import pylab as py


xtitle='Time (days)'
ytitle='Oxide Thickness (microns)'

xmax=106
ymax=2



Dali2012_x=np.array([0.41,4.9,11.9,23.0,30.9,42.0,53.0,63.0])
Dali2012_y=np.array([0.66,1.45,1.90,2.46,3.43,4.36,4.68,5.03])
Dali2012_yeld=np.array([0.46,1.25,1.70,2.26,3.24,4.16,4.47,4.83])
Dali2012_yeud=np.array([0.86,1.65,2.10,2.65,3.63,4.56,4.88,5.23])

Dali2012_yel=Dali2012_y-Dali2012_yeld
Dali2012_yeu=Dali2012_yeud-Dali2012_y


filename='415steam.csv' #'415_out_sub_app0.csv'#'exp_val7_csv.csv'

hognose=1
if hognose==True:
    data = np.loadtxt(filename,delimiter=',',usecols=range(0,2),skiprows=1)
    
    # Assign imported data to individual arrays:
    timeh=data[:,0]

    total_oxideh=data[:,1]
      
    timeh=timeh/86400


# SAMPLE A1
A1_y_raw=np.array([0.656,0.680,0.653,0.780,0.772,0.703,0.672,0.653,0.656])
A1_y_raw=A1_y_raw/np.sin(52*np.pi/180)

                 

############################ Location by location data

#########################
# SAMPLE A1 (1.42 days)
A1_time=1.42

# LOCATION 1 (from the init file, all from one image)
A1_loc1_raw=np.array([0.86,0.89,0.83,0.83,0.83,0.91,0.91,0.89,1.06,1.00,
		0.86,0.91,0.80,0.66,0.80,0.86,0.69,0.80,0.66,0.54,
		0.60,0.71,0.74,0.71,0.77,0.91,0.86])

# LOCATION 4 (all from one image)
A1_loc4_raw=np.array([0.88,0.92,0.92,0.73,0.81,0.79,0.75,0.88,0.88,
		0.84,0.73,0.88,0.81,0.79,0.73,0.75,0.88,
		0.84,0.88,0.79,0.75,0.84,0.81,0.81,
		0.79,0.77,0.64,0.66,0.54])

# LOCATION 7 (all from one image)
A1_loc7_raw=np.array([0.60,0.49,0.58,0.54,0.61,0.70,0.70,0.66,
		0.65,0.56,0.56,0.70,0.77,0.63,0.61,0.61,
		0.75,0.75,0.71,0.60,0.58,0.60,0.70,0.82,
		0.90,0.94,0.87,0.82])

A1=np.append(A1_loc1_raw,A1_loc4_raw)
A1=np.append(A1,A1_loc7_raw)
#########################



#########################
# SAMPLE B1 (3.59 days)
B1_time=3.59

# LOCATION 1 (with 0.18 microns added in for Pt-oxide interface quality)
B1_loc1_raw=np.array([1.38,1.43,1.58,1.58,1.51,1.52,1.46,1.55,
		1.46,1.50,1.50,1.46,1.48,1.46,1.35,1.29,
		1.41,1.39,1.43,1.52,1.53,1.52,1.47,1.52,
		1.43,1.57,1.50,1.53,1.55,1.59,
		1.33,1.40,1.43,1.42,1.37,1.44])

# LOCATION 2
B1_loc2_raw=np.array([1.09,1.23,1.27,1.24,1.39,1.41,1.42,1.31,1.25,
		1.15,1.23,1.22,1.14,1.23,1.21,1.22,1.19,1.09,1.06,
		1.21,1.17,1.07,1.10,1.08,1.11,
		1.09,1.05,0.98,
		1.10,0.84,1.04])
# LOCATION 3
B1_loc3_raw=np.array([0.99,1.00,0.93,1.00,1.04,0.98,0.88,0.95,
		1.00,0.88,0.87,0.89,0.90,0.95,0.87,0.91,
		0.95,1.15,1.19,1.24,1.18,1.14,1.27,
		1.03,1.03,1.00,0.97,0.98,1.03,
		0.99,0.95,1.08,1.10,1.16,1.16,
		0.86,0.68,0.52,0.64,0.75,0.68])

B1=np.append(B1_loc1_raw,B1_loc2_raw)
B1=np.append(B1,B1_loc3_raw)
#########################

#########################
# SAMPLE C1 (5.61 days)
C1_time=5.61
# LOCATION 1
C1_loc1_raw=np.array([1.38,1.28,1.24,1.13,1.10,1.14,1.08,
		1.31,1.09,1.16,1.08,0.80,0.89,0.94,0.81,0.89,
		1.01,0.72,0.84,0.90,1.10,0.95,0.82,0.91,1.04,0.93,
		0.77,0.92,0.89,0.79,0.65])

# LOCATION 2
C1_loc2_raw=np.array([1.88,1.88,1.92,1.86,2.01,
		1.76,1.64,1.61,1.34,1.33,1.35,1.36,1.35,
		1.14,1.12,1.19,1.18,1.31,1.43,1.40,1.42,1.41,
		1.25,1.23,1.14,1.26,1.31])

# LOCATION 3
C1_loc3_raw=np.array([1.17,1.10,0.98,1.09,1.00,
		0.89,0.84,0.83,0.77,0.97,0.84,0.91,
		0.84,0.85,0.88,0.81,
		1.38,1.24,1.20,1.15])

C1=np.append(C1_loc1_raw,C1_loc2_raw)
C1=np.append(C1,C1_loc3_raw)
#########################



#########################
# SAMPLE A2 (7.68 days)
A2_time=7.68

# LOCATION 1
A2_loc1_raw=np.array([1.77,1.80,1.91,1.97,2.04,2.27,
		2.32,2.33,2.42,2.56,2.46,2.39,2.32,
		2.23,2.13,2.03,1.59,1.55,1.61,1.43,
		1.53,1.38,1.38,1.45,1.62])

# LOCATION 2
A2_loc2_raw=np.array([1.61,1.60,1.69,1.61,1.67,1.71,1.57,
		1.65,1.76,2.06,1.92,1.93,1.85,1.61,
		1.49,1.35,0.96,1.13,1.06,1.12,1.07,1.24,
		1.26,1.16,1.24,1.29,1.12])

# LOCATION 3
A2_loc3_raw=np.array([1.80,1.76,1.70,1.64,1.46,
		1.68,1.69,1.60,1.54,1.80,1.73,
		1.67,1.51,1.56,1.55,1.65,1.75,1.84,
		1.85,1.97,2.05,1.92,1.92,1.91,
		1.71,1.85])

A2=np.append(A2_loc1_raw,A2_loc2_raw)
A2=np.append(A2,A2_loc3_raw)
#########################



#########################
# SAMPLE B2
B2_time=9.70

# LOCATION 4
B2_loc4_raw=np.array([1.44,1.21,1.53,1.23,1.55,1.25,1.78,1.61,1.55,1.49,1.17,1.34])

# LOCATION 6
B2_loc6_raw=np.array([1.58,1.86,1.71,2.01,1.69,
		1.89,1.81,2.03,2.00,1.95,1.94,
		1.83,1.70,1.70,1.76,1.68,
		2.16,2.09,1.90,1.98,1.90])

# LOCATION 7
B2_loc7_raw=np.array([1.97,1.98,2.05,2.08,2.15,2.08,1.86,1.80,
		1.92,1.84,1.72,1.92,1.80,1.87,
		1.75,1.70,1.87,1.74,1.68,1.48,1.50,1.57,1.40,
		1.15,1.22,1.37,1.32,1.18])

B2=np.append(B2_loc4_raw,B2_loc6_raw)
B2=np.append(B2,B2_loc7_raw)
#########################


#########################
# SAMPLE C2
C2_time=11.65

# LOCATION 1
C2_loc1_raw=np.array([2.30,2.28,2.50,2.70,2.77,
		2.99,2.99,3.02,3.16,3.33,3.06,
		3.05,2.98,3.19,3.19,3.24,3.27,3.07])

# LOCATION 2
C2_loc2_raw=np.array([2.23,2.32,2.32,2.45,2.45,2.48,2.55,
		2.66,2.69,2.69,2.59,2.66,2.47,2.55,2.60,2.62,
		2.64,2.67,2.65,2.71,2.68,2.78,2.54,2.50,
		2.58,2.52,2.47,2.46,2.40,2.31,2.48,2.52,
		2.26,2.31,2.19,2.00,2.05])

# LOCATION 3
C2_loc3_raw=np.array([1.05,1.11,0.95,1.04,0.81,1.05,
		1.18,1.44,1.38,1.37,1.44,1.36,1.36,1.26,
		1.42,1.46,1.39,1.31,1.28,
		1.47,1.40,1.36,1.28,1.23,
		1.23,1.31,1.14,1.21,1.16,1.05,1.11,
		0.88,1.16,1.22,1.16,1.34,
		1.37,1.38,1.45,1.44,
		1.28,1.35,1.32,1.35,1.29,1.46])

C2=np.append(C2_loc1_raw,C2_loc2_raw)
C2=np.append(C2,C2_loc3_raw)
#########################

#########################
# SAMPLE A3 (13.66 days)
A3_time=13.66

# LOCATION 1
A3_loc1_raw=np.array([2.60,2.60,2.54,
		1.24,1.27,1.42,1.56,1.84,2.18,2.54,2.54,2.41,2.23,2.54,
		2.38,2.53,2.66,2.74,2.95,2.96])

# LOCATION 2
A3_loc2_raw=np.array([1.89,1.69,1.73,1.78,1.73,
		1.88,1.68,1.57,1.71,1.43,1.64,1.72,
		1.80,1.73,1.62,1.69,1.73,1.82,
		1.62,1.43,1.44])

# LOCATION 3
A3_loc3_raw=np.array([2.84,2.73,2.96,3.00,3.07,3.00,3.11,
		2.95,2.85,2.73,2.65,2.28,2.12,1.73,1.86,2.14,
		1.97,1.67,1.56,1.70])

A3=np.append(A3_loc1_raw,A3_loc2_raw)
A3=np.append(A3,A3_loc3_raw)
#########################

#########################
# SAMPLE B3 (15.68 days)
B3_time=15.68

# LOCATION 1
B3_loc1_raw=np.array([1.56,1.36,1.22,1.65,1.79,2.06,
		2.16,2.01,2.21,2.10,2.20,2.42,2.31,
		2.14])

# LOCATION 2
B3_loc2_raw=np.array([1.70,1.43,1.76,1.68,1.73,1.76,
		1.68,1.74,1.73,1.60,1.71,1.78,1.64,
		1.59,1.55,1.74,1.54,1.29,1.66,1.59,
		1.55,1.59,1.36])

# LOCATION 3
B3_loc3_raw=np.array([1.80,1.88,1.64,1.54,1.63,1.80,
		1.92,1.97,1.76,1.74,1.81,1.80,2.25,2.47,
		2.36,2.38,2.54,2.56,2.40,2.48,2.58,
		2.50,2.46,2.28,2.20])

B3=np.append(B3_loc1_raw,B3_loc2_raw)
B3=np.append(B3,B3_loc3_raw)
#########################

#########################
# SAMPLE C3 (17.67 days)
C3_time=17.67

# LOCATION 2
C3_loc2_raw=np.array([2.83,3.01,2.98,2.51,2.90,2.94,3.05,2.83,3.33,3.01,3.30,3.26,3.69,3.69])

# LOCATION 3
C3_loc3_raw=np.array([2.42,2.56,2.41,2.88,2.76,2.85,2.65,
		2.24,2.15,2.09,1.96,2.27,2.40,2.44,2.35,
		2.41,2.06,1.87])

# LOCATION 4
C3_loc4_raw=np.array([2.34,2.18,2.34,2.28,2.23,
		2.20,2.16,2.10,2.09,2.12,1.94,1.89,1.66,1.67,
		1.82,2.04,2.07,2.13,2.42,2.39,2.45,2.21,2.30,
		2.20,2.23,2.08,2.25,2.16])

C3=np.append(C3_loc2_raw,C3_loc3_raw)
C3=np.append(C3,C3_loc4_raw)
#########################



#########################
# SAMPLE A4 (19.68 days)
A4_time=19.68

# LOCATION 1
A4_loc1_raw=np.array([2.44,2.51,2.37,2.45,2.56,2.49,2.50,2.47,2.60,
		2.54,2.23,2.51,2.76,2.66,2.76,
		2.83,2.65,2.66,2.60])

# LOCATION 2
A4_loc2_raw=np.array([1.97,1.95,1.82,1.73,1.61,1.55,1.33,1.37,1.58,
		1.91,1.76,1.97,2.01,1.89,1.78,2.07,2.13,2.09,1.85,1.79,1.80,
		1.42,1.66,1.43,1.61,1.84,2.00,1.99,2.11,1.99,2.26,2.10,
		2.32,2.56,2.52,2.54,2.56,2.51])

# LOCATION 3
A4_loc3_raw=np.array([2.51,2.35,2.41,2.38,2.40,2.68,2.78,
		2.49,2.37,2.20,2.33,2.52,2.50,2.53,2.80,2.95,
		2.72,3.01,2.94,2.60,2.52,2.49,2.59,2.44,
		2.49,2.66,2.67,2.27,2.53])

A4=np.append(A4_loc1_raw,A4_loc2_raw)
A4=np.append(A4,A4_loc3_raw)
#########################


#########################
# SAMPLE B4 (21.19 days)
B4_time=21.19

# LOCATION 1
B4_loc1_raw=np.array([2.08,2.13,2.23,2.10,1.90,2.29,2.47,
		2.47,2.46,2.00,2.03,2.15,1.92,2.25,
		2.32,2.52,2.58,2.39,2.66,2.83,2.69,
		2.77,2.53,2.68])

# LOCATION 2
B4_loc2_raw=np.array([1.73,2.06,2.05,1.96,1.76,1.65,
		1.47,1.36,1.51,1.53,1.66,1.42,1.59,
		1.76,1.49,1.50,1.50,1.50,1.53,1.60,
		1.40,1.56,1.64,1.63,1.54,1.65,1.83,
		1.80,1.56,1.66])

# LOCATION 3
B4_loc3_raw=np.array([1.14,1.74,1.45,1.81,1.78,1.77,
		1.55,1.70,1.55,1.61,1.92,1.91,1.85,1.68,
		2.04,1.66,1.57,1.52,1.65,1.81,1.64,
		1.72,1.68,1.87])

B4=np.append(B4_loc1_raw,B4_loc2_raw)
B4=np.append(B4,B4_loc3_raw)
#########################


#########################
# SAMPLE C4 (22.74 days)
C4_time=22.74

# LOCATION 1
C4_loc1_raw=np.array([2.29,2.05,1.95,1.61,1.97,1.96,
		1.76,1.74,1.94,2.02,1.60,1.89,1.74,
		1.87,1.62,2.17,1.74,1.86,2.11,1.81,
		2.02,2.20,1.58,1.91])

# LOCATION 2
C4_loc2_raw=np.array([2.16,2.53,2.32,2.54,2.61,2.33,
		2.51,2.34,2.54,2.41,2.40,2.66,2.64,
		2.55,2.65,2.52,2.44,2.53,2.38,
		2.54,2.44,2.33,2.24])

# LOCATION 3
C4_loc3_raw=np.array([1.70,1.93,1.88,2.18,2.38,2.61,2.65,
		2.70,2.88,2.72,2.50,2.14,1.95,1.66,1.71,
		1.57,1.60,1.82])

C4=np.append(C4_loc1_raw,C4_loc2_raw)
C4=np.append(C4,C4_loc3_raw)
#########################


#########################
# SAMPLE A5 (24.24 days)
A5_time=24.24

# LOCATION 2
A5_loc2_raw=np.array([2.85,2.60,2.36,2.56,2.59,2.50,2.49,2.58,2.57,2.34,
		2.50,2.76,2.54,2.41,2.56,2.74,2.67,2.66,2.63,2.67])

# LOCATION 3
A5_loc3_raw=np.array([2.40,2.58,2.61,2.72,2.76,2.57,2.66,2.92,2.57,2.37,2.67,
		2.60,2.31,2.66,2.49,2.70,2.28,2.86,2.95])

# LOCATION 4
A5_loc4_raw=np.array([2.27,2.16,2.31,2.06,2.30,2.80,2.86,2.76,
		2.13,2.31,2.54,2.51,2.53,2.47,2.27,2.49,2.30,2.23,2.32,
		2.29,2.22,1.96,1.90,2.13,2.06,2.13,2.26])

# LOCATION 5
A5_loc5_raw=np.array([2.74,2.58,2.48,2.69,2.47,
		3.05,3.06,2.56,2.50,2.13,2.09,
		2.26,2.30,2.21,2.86,2.46,2.68,2.57,
		2.91,2.16,2.49])

# LOCATION 6
A5_loc6_raw=np.array([2.66,2.84,2.34,2.69,2.62,
		2.76,2.84,2.41,2.28,2.28,
		2.75,2.47])

A5=np.append(A5_loc2_raw,A5_loc3_raw)
A5=np.append(A5,A5_loc4_raw)
A5=np.append(A5,A5_loc5_raw)
A5=np.append(A5,A5_loc6_raw)
#########################


#########################
# SAMPLE B5 (25.75 days)
B5_time=25.75

# LOCATION 2
B5_loc2_raw=np.array([2.17,2.19,2.01,2.07,2.25,1.90,
		1.92,1.90,1.94,2.02,2.29,2.51,2.43,2.37,
		1.99,2.20,1.99,1.95,1.69,1.41,1.55,1.64,1.90,
		1.99,1.83,1.85,1.87])

# LOCATION 3
B5_loc3_raw=np.array([1.94,1.76,2.38,2.45,2.37,2.12,1.99,
		1.91,1.91,1.84,1.90,1.81,1.91,1.86,1.96,
		2.08,1.81,1.86,2.04,2.06,2.13,
		2.22,2.28,2.20,2.20,2.05,1.96,
		2.24,2.13,2.01,2.11,2.21,2.29,2.31,
		2.39,2.16,2.39])

# LOCATION 5
B5_loc5_raw=np.array([2.27,2.05,2.04,2.09,2.11,1.81,2.23,
		2.32,2.32,2.11,2.04,2.13,2.16,1.94,2.05,2.43,
		2.19,2.60,2.24,2.44,1.95,1.97,2.14,2.32,2.16,
		2.41,2.20,2.03])

# LOCATION 6
B5_loc6_raw=np.array([2.72,2.93,2.91,2.49,2.55,2.89,
		2.75,2.79,2.92,2.91,3.03,
		2.77,2.70,3.34,3.05,3.30,3.29,3.15])

# LOCATION 7
B5_loc7_raw=np.array([3.69,3.59,3.79,3.78,3.69,
		3.60,3.90,3.74,3.62,3.64,
		3.54,3.45,3.41,3.42,3.46,
		3.36,3.48,3.45])
		
B5=np.append(B5_loc2_raw,B5_loc3_raw)
B5=np.append(B5,B5_loc5_raw)
B5=np.append(B5,B5_loc6_raw)
B5=np.append(B5,B5_loc7_raw)
#########################


#########################
# SAMPLE C5 (27.26 days)
C5_time=27.26

# LOCATION 1
C5_loc1_raw=np.array([2.24,2.45,2.62,2.88,2.83,3.06,
		2.62,2.76,2.54,2.31,2.27,2.10,2.03,
		2.43,2.52,2.72])

# LOCATION 2
C5_loc2_raw=np.array([3.25,3.24,3.44,3.34,3.13,3.17,
		2.97,2.73,1.91,2.29,1.72,1.89,2.22,
		2.34,2.63,2.29])

# LOCATION 3
C5_loc3_raw=np.array([2.73,2.64,2.45,2.44,2.36,2.64,
		2.66,2.52,2.52,2.08,2.17,2.38,2.60,
		2.45,2.62,2.57,2.45])

# LOCATION 4
C5_loc4_raw=np.array([2.79,2.95,3.03,3.17,3.12,
		3.07,3.24,3.06,3.10,3.04,2.92,3.14,
		3.42,3.45,3.39])

# LOCATION 5
C5_loc5_raw=np.array([2.43,2.43,2.58,2.48,2.65,
		2.51,2.57,2.51,2.50,2.40,2.51,
		2.42,2.47,2.26,2.41,2.51])

C5=np.append(C5_loc1_raw,C5_loc2_raw)
C5=np.append(C5,C5_loc3_raw)
C5=np.append(C5,C5_loc4_raw)
C5=np.append(C5,C5_loc5_raw)
#########################


#########################
# SAMPLE A6 (29.27 days)
A6_time=29.27

# LOCATION 1
A6_loc1_raw=np.array([2.69,2.98,2.69,2.62,2.94,2.83,2.62,2.44,2.19,2.40,2.37,2.33,2.37,2.33,2.47,2.22,2.47])

# LOCATION 2
A6_loc2_raw=np.array([2.05,2.36,2.31,2.26,1.95,
		2.43,2.37,2.28,2.43,2.23,2.27,1.93,
		1.95,2.11,2.16,2.21,2.41,2.30,2.23,
		2.06,1.85,1.86,1.78])

# LOCATION 3
A6_loc3_raw=np.array([2.72,2.37,2.14,2.08,2.09,
		2.08,2.27,2.23,2.10,2.18,2.21,
		2.60,2.44,2.55,2.40,2.52,2.84,
		2.91,3.20,3.18,2.82,2.77])

# LOCATION 4
A6_loc4_raw=np.array([2.44,2.33,2.06,2.30,2.28,2.23,
		2.55,2.81,2.97,3.16,3.03,3.18,3.04,3.05,
		3.46,3.54,3.40,3.34])

# LOCATION 5
A6_loc5_raw=np.array([2.50,2.57,2.50,2.43,
		2.73,2.47,2.04,2.17,2.10,2.35,2.81,
		2.79,2.65,3.07,3.40,2.72])	

A6=np.append(A6_loc1_raw,A6_loc2_raw)
A6=np.append(A6,A6_loc3_raw)
A6=np.append(A6,A6_loc4_raw)
A6=np.append(A6,A6_loc5_raw)
#########################


#########################
# SAMPLE B6 (31.32 days)
B6_time=31.32

# LOCATION 1 (NFA)
B6_loc1_raw=np.array([3.33,3.59,3.51,3.51,
		3.17,3.36,3.26,3.33,3.02,3.20,3.29,3.57,3.66,3.58,
		3.35,3.78,3.69,3.45,3.28,3.42,3.80,3.82,4.02,
		3.85,3.83])

# LOCATION 2
B6_loc2_raw=np.array([2.01,2.24,2.17,2.27,2.25,2.37,2.44,
		2.61,2.50,2.49,2.61,2.63,2.26,2.53,2.68,2.45,
		2.72,2.86,2.86,2.45,2.59,
		2.66,2.53,2.66,2.40,2.42,2.61,2.41,2.61,
		2.59,2.61,2.72,2.68,2.62])

# LOCATION 3
B6_loc3_raw=np.array([1.75,1.88,1.97,1.80,1.95,2.04,1.94,2.19,2.25,2.28,
		2.35,2.13,2.27,1.99,2.06,2.06,2.01,1.92,1.92,1.92,2.12,
		2.06,1.90,2.10,1.78,1.99,2.18,2.13,2.09,1.88,1.74,1.99,1.92])

# LOCATION 4
B6_loc4_raw=np.array([3.08,2.89,2.82,3.53,3.32,
		3.50,3.46,2.89,3.20,2.87,2.73,
		2.47,2.38,2.72,2.66,2.87,2.79,
		2.86,2.85,2.96])

# LOCATION 5
B6_loc5_raw=np.array([2.94,3.05,3.20,3.17,2.86,
		2.76,2.70,2.88,2.65,2.49,
		2.64,2.48,2.69])

B6=np.append(B6_loc1_raw,B6_loc2_raw)
B6=np.append(B6,B6_loc3_raw)
B6=np.append(B6,B6_loc4_raw)
B6=np.append(B6,B6_loc5_raw)

#########################

#########################
# SAMPLE C6 (33.34 days)
C6_time=33.34

# LOCATION 1
C6_loc1_raw=np.array([2.38,2.55,2.79,2.93,2.63,
		2.36,2.36,2.32,2.49,2.27,2.46,2.25,2.02,2.04,
		2.58,2.39,2.36,2.38,2.16,2.83,2.84,2.48,2.34,2.18,
		2.21,2.34,2.56,2.44,2.55])

# LOCATION 2
C6_loc2_raw=np.array([2.90,2.82,2.80,2.94,2.92,3.00,
		2.99,2.96,2.92,2.91,2.88,3.28,3.22,
		3.16,3.39,3.49,3.26,3.06,3.25,2.99,
		2.74,2.92,2.79])

# LOCATION 3
C6_loc3_raw=np.array([2.61,2.64,2.73,2.95,
		2.60,2.91,2.90,2.62,2.69,2.64,
		2.70,2.58,2.37,2.56,2.57,2.43,2.42,
		2.69,2.61,2.50,2.49,2.68,2.79,2.85,2.86,
		2.86,2.77])

# LOCATION 4
C6_loc4_raw=np.array([2.42,2.40,2.71,2.86,2.44,2.70,
		2.88,2.59,2.75,2.99,3.15,2.40,2.77,
		2.66,2.61,2.28])

# LOCATION 5
C6_loc5_raw=np.array([3.10,2.68,2.42,2.70,2.74,2.73,
		2.40,2.13,2.25,2.40,2.19,2.29,
		2.36,2.25,2.16])

C6=np.append(C6_loc1_raw,C6_loc2_raw)
C6=np.append(C6,C6_loc3_raw)
C6=np.append(C6,C6_loc4_raw)
C6=np.append(C6,C6_loc5_raw)
#########################

#########################
# Combining sample date into A, B, and C, and then global arrays.

A_time=np.append(A1_time,A2_time)
A_time=np.append(A_time,A3_time)
A_time=np.append(A_time,A4_time)
A_time=np.append(A_time,A5_time)
A_time=np.append(A_time,A6_time)

A_data=np.append(np.average(A1),np.average(A2))
A_data=np.append(A_data,np.average(A3))
A_data=np.append(A_data,np.average(A4))
A_data=np.append(A_data,np.average(A5))
A_data=np.append(A_data,np.average(A6))

A_datas=np.append(np.std(A1,ddof=1),np.std(A2,ddof=1))
A_datas=np.append(A_datas,np.std(A3,ddof=1))
A_datas=np.append(A_datas,np.std(A4,ddof=1))
A_datas=np.append(A_datas,np.std(A5,ddof=1))
A_datas=np.append(A_datas,np.std(A6,ddof=1))

B_time=np.append(B1_time,B2_time)
B_time=np.append(B_time,B3_time)
B_time=np.append(B_time,B4_time)
B_time=np.append(B_time,B5_time)
B_time=np.append(B_time,B6_time)

B_data=np.append(np.average(B1),np.average(B2))
B_data=np.append(B_data,np.average(B3))
B_data=np.append(B_data,np.average(B4))
B_data=np.append(B_data,np.average(B5))
B_data=np.append(B_data,np.average(B6))

B_datas=np.append(np.std(B1,ddof=1),np.std(B2,ddof=1))
B_datas=np.append(B_datas,np.std(B3,ddof=1))
B_datas=np.append(B_datas,np.std(B4,ddof=1))
B_datas=np.append(B_datas,np.std(B5,ddof=1))
B_datas=np.append(B_datas,np.std(B6,ddof=1))

C_time=np.append(C1_time,C2_time)
C_time=np.append(C_time,C3_time)
C_time=np.append(C_time,C4_time)
C_time=np.append(C_time,C5_time)
C_time=np.append(C_time,C6_time)

C_data=np.append(np.average(C1),np.average(C2))
C_data=np.append(C_data,np.average(C3))
C_data=np.append(C_data,np.average(C4))
C_data=np.append(C_data,np.average(C5))
C_data=np.append(C_data,np.average(C6))

C_datas=np.append(np.std(C1,ddof=1),np.std(C2,ddof=1))
C_datas=np.append(C_datas,np.std(C3,ddof=1))
C_datas=np.append(C_datas,np.std(C4,ddof=1))
C_datas=np.append(C_datas,np.std(C5,ddof=1))
C_datas=np.append(C_datas,np.std(C6,ddof=1))

total_time=np.append(A_time,B_time)
total_time=np.append(total_time,C_time)

total_thickness=np.append(A_data,B_data)
total_thickness=np.append(total_thickness,C_data)

total_thicknessstd=np.append(A_datas,B_datas)
total_thicknessstd=np.append(total_thicknessstd,C_datas)

#########################


# THE ACTUAL DATA, PROCESSED AND COMBINED:
#AD_x=np.array([1.42,3.59,9.70,17.67])
#AD_y=np.array([np.average(A1_y_raw),np.average(B1_y_raw),np.average(B2_y_raw),
 #              np.average(C3_y_raw)])
#AD_y_err=np.array([np.std(A1_y_raw,ddof=1),np.std(B1_y_raw,ddof=1),
 #                 np.std(B2_y_raw,ddof=1),np.std(C3_y_raw,ddof=1)])
                  
data1 = np.loadtxt('Dali2012-low_P_data.csv',delimiter=', ',usecols=range(0,2))#,skiprows=1)
time1=data1[:,0]
total_oxide1=data1[:,1]   


print "np.average(total_thickness) = ",np.average(total_thickness)

plotall=1
if plotall==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (13,10))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=28)
    fig.subplots_adjust(left = 0.11,top=0.97,right = 0.98)

    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='ks',markersize=18,linewidth=4,label='Dali et al. 2012')
    axe.errorbar(total_time,total_thickness,yerr=total_thicknessstd,fmt='o',markersize=18,linewidth=4,capsize=5,label='This work')     
    axe.annotate("Thicknesses averaged by sample.",xy=(2,5.5),xytext=(1,5.75))  
    axe.plot(time1,total_oxide1,'-',linewidth=6,label='Dali et al. 2012 (P=0.2 MPa)')     

    axe.plot(timeh,total_oxideh,'.-',markersize=18,label='HOGNOSE')
       
    axe.legend(loc='lower right',fontsize=25,ncol=2)

    axe.xaxis.set_tick_params(length=8,width=2) 
    axe.yaxis.set_tick_params(length=8,width=2)

    for axis in ['top','bottom','left','right']:
      axe.spines[axis].set_linewidth(2)

    plt.xlim(0,47)
    plt.ylim(0,4.5)
    plt.xlabel(xtitle,fontsize=35)
    plt.ylabel(ytitle,fontsize=35)
    plt.savefig('All_Data.png',dpi=500,bbox='tight')
    
plotallnoHOGNOSE=10
if plotallnoHOGNOSE==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali et al. 2012')
    axe.errorbar(total_time,total_thickness,yerr=total_thicknessstd,fmt='o',capsize=5,label='This work')     
    axe.annotate("Thicknesses averaged by sample.",xy=(2,5.5),xytext=(1,5.75))  
    axe.plot(time1,total_oxide1,'-',label='Dali et al. 2012 (P=0.2 MPa)')     

       
    axe.legend(loc='lower right',ncol=2)
    plt.xlim(0,47)
    plt.ylim(0,4.5)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    plt.savefig('All_Data-noHOGNOSE.png')    

plotA=10
if plotA==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali et al. 2012')
    axe.errorbar(A_time,A_data,yerr=A_datas,fmt='o',capsize=5,label='This work (A)') 
    axe.plot(time1,total_oxide1,'-',label='Dali et al. 2012 (P=0.2 MPa)')            
    axe.legend(loc='lower right',ncol=2)
    plt.xlim(0,47)
    plt.ylim(0,4.5)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    plt.savefig('A_Data.png')

plotB=10
if plotB==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali et al. 2012')

    axe.errorbar(B_time,B_data,yerr=B_datas,fmt='o',capsize=5,label='This work (B)')         

    axe.plot(time1,total_oxide1,'-',label='Dali et al. 2012 (P=0.2 MPa)')            
    axe.legend(loc='lower right',ncol=2)
    plt.xlim(0,47)
    plt.ylim(0,4.5)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    plt.savefig('B_Data.png')

plotC=10
if plotC==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali et al. 2012')
    axe.errorbar(C_time,C_data,yerr=C_datas,fmt='o',capsize=5,label='This work (C)')                 
    axe.plot(time1,total_oxide1,'-',label='Dali et al. 2012 (P=0.2 MPa)')            
    axe.legend(loc='lower right',ncol=2)
    plt.xlim(0,47)
    plt.ylim(0,4.5)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    plt.savefig('C_Data.png')



 

printout=0
if printout==True:
	print "Time, sample, average, std. dev"
	print "",A1_time,"days, ","A1_loc1, ",("%.2f" % np.average(A1_loc1_raw))," microns, ",("%.2f" % np.std(A1_loc1_raw,ddof=1))," microns"
	print "",A1_time,"days, ","A1_loc4, ",("%.2f" % np.average(A1_loc4_raw))," microns, ",("%.2f" % np.std(A1_loc4_raw,ddof=1))," microns"
	print "",A1_time,"days, ","A1_loc7, ",("%.2f" % np.average(A1_loc7_raw))," microns, ",("%.2f" % np.std(A1_loc7_raw,ddof=1))," microns"
	print "\n"
	print "",B1_time,"days, ","B1_loc1, ",("%.2f" % np.average(B1_loc1_raw))," microns, ",("%.2f" % np.std(B1_loc1_raw,ddof=1))," microns"
	print "",B1_time,"days, ","B1_loc2, ",("%.2f" % np.average(B1_loc2_raw))," microns, ",("%.2f" % np.std(B1_loc2_raw,ddof=1))," microns"
	print "",B1_time,"days, ","B1_loc3, ",("%.2f" % np.average(B1_loc3_raw))," microns, ",("%.2f" % np.std(B1_loc3_raw,ddof=1))," microns"
	print "\n"
	print "",C1_time,"days, ","C1_loc1, ",("%.2f" % np.average(C1_loc1_raw))," microns, ",("%.2f" % np.std(C1_loc1_raw,ddof=1))," microns"
	print "",C1_time,"days, ","C1_loc2, ",("%.2f" % np.average(C1_loc2_raw))," microns, ",("%.2f" % np.std(C1_loc2_raw,ddof=1))," microns"
	print "",C1_time,"days, ","C1_loc3, ",("%.2f" % np.average(C1_loc3_raw))," microns, ",("%.2f" % np.std(C1_loc3_raw,ddof=1))," microns"
	print "\n"
	print "",A2_time,"days, ","A2_loc1, ",("%.2f" % np.average(A2_loc1_raw))," microns, ",("%.2f" % np.std(A2_loc1_raw,ddof=1))," microns"
	print "",A2_time,"days, ","A2_loc2, ",("%.2f" % np.average(A2_loc2_raw))," microns, ",("%.2f" % np.std(A2_loc2_raw,ddof=1))," microns"
	print "",A2_time,"days, ","A2_loc3, ",("%.2f" % np.average(A2_loc3_raw))," microns, ",("%.2f" % np.std(A2_loc3_raw,ddof=1))," microns"
	print "\n"
	print "",B2_time," days, ","B2_loc4, ",("%.2f" % np.average(B2_loc4_raw))," microns, ",("%.2f" % np.std(B2_loc4_raw,ddof=1))," microns"
	print "",B2_time," days, ","B2_loc6, ",("%.2f" % np.average(B2_loc6_raw))," microns, ",("%.2f" % np.std(B2_loc6_raw,ddof=1))," microns"
	print "",B2_time," days, ","B2_loc7, ",("%.2f" % np.average(B2_loc7_raw))," microns, ",("%.2f" % np.std(B2_loc7_raw,ddof=1))," microns"
	print "\n"
	print C2_time,"days, ","C2_loc1, ",("%.2f" % np.average(C2_loc1_raw))," microns, ",("%.2f" % np.std(C2_loc1_raw,ddof=1))," microns"
	print C2_time,"days, ","C2_loc2, ",("%.2f" % np.average(C2_loc2_raw))," microns, ",("%.2f" % np.std(C2_loc2_raw,ddof=1))," microns"
	print C2_time,"days, ","C2_loc3, ",("%.2f" % np.average(C2_loc3_raw))," microns, ",("%.2f" % np.std(C2_loc3_raw,ddof=1))," microns"
	print "\n"
	print A3_time,"days, ","A3_loc1, ",("%.2f" % np.average(A3_loc1_raw))," microns, ",("%.2f" % np.std(A3_loc1_raw,ddof=1))," microns"
	print A3_time,"days, ","A3_loc2, ",("%.2f" % np.average(A3_loc2_raw))," microns, ",("%.2f" % np.std(A3_loc2_raw,ddof=1))," microns"
	print A3_time,"days, ","A3_loc3, ",("%.2f" % np.average(A3_loc3_raw))," microns, ",("%.2f" % np.std(A3_loc3_raw,ddof=1))," microns"
	print "\n"
	print B3_time,"days, ","B3_loc1, ",("%.2f" % np.average(B3_loc1_raw))," microns, ",("%.2f" % np.std(B3_loc1_raw,ddof=1))," microns"
	print B3_time,"days, ","B3_loc2, ",("%.2f" % np.average(B3_loc2_raw))," microns, ",("%.2f" % np.std(B3_loc2_raw,ddof=1))," microns"
	print B3_time,"days, ","B3_loc3, ",("%.2f" % np.average(B3_loc3_raw))," microns, ",("%.2f" % np.std(B3_loc3_raw,ddof=1))," microns"
	print "\n"
	print C3_time,"days, ","C3_loc2, ",("%.2f" % np.average(C3_loc2_raw))," microns, ",("%.2f" % np.std(C3_loc2_raw,ddof=1))," microns"
	print C3_time,"days, ","C3_loc3, ",("%.2f" % np.average(C3_loc3_raw))," microns, ",("%.2f" % np.std(C3_loc3_raw,ddof=1))," microns"
	print C3_time,"days, ","C3_loc4, ",("%.2f" % np.average(C3_loc4_raw))," microns, ",("%.2f" % np.std(C3_loc4_raw,ddof=1))," microns"
	print "\n"
	print A4_time,"days, ","A4_loc1, ",("%.2f" % np.average(A4_loc1_raw))," microns, ",("%.2f" % np.std(A4_loc1_raw,ddof=1))," microns"
	print A4_time,"days, ","A4_loc2, ",("%.2f" % np.average(A4_loc2_raw))," microns, ",("%.2f" % np.std(A4_loc2_raw,ddof=1))," microns"
	print A4_time,"days, ","A4_loc3, ",("%.2f" % np.average(A4_loc3_raw))," microns, ",("%.2f" % np.std(A4_loc3_raw,ddof=1))," microns"
	print "\n"
	print B4_time,"days, ","B4_loc1, ",("%.2f" % np.average(B4_loc1_raw))," microns, ",("%.2f" % np.std(B4_loc1_raw,ddof=1))," microns"
	print B4_time,"days, ","B4_loc2, ",("%.2f" % np.average(B4_loc2_raw))," microns, ",("%.2f" % np.std(B4_loc2_raw,ddof=1))," microns"
	print B4_time,"days, ","B4_loc3, ",("%.2f" % np.average(B4_loc3_raw))," microns, ",("%.2f" % np.std(B4_loc3_raw,ddof=1))," microns"
	print "\n"
	print C4_time,"days, ","C4_loc1, ",("%.2f" % np.average(C4_loc1_raw))," microns, ",("%.2f" % np.std(C4_loc1_raw,ddof=1))," microns"
	print C4_time,"days, ","C4_loc2, ",("%.2f" % np.average(C4_loc2_raw))," microns, ",("%.2f" % np.std(C4_loc2_raw,ddof=1))," microns"
	print C4_time,"days, ","C4_loc3, ",("%.2f" % np.average(C4_loc3_raw))," microns, ",("%.2f" % np.std(C4_loc3_raw,ddof=1))," microns"
	print "\n"
	print A5_time,"days, ","A5_loc2, ",("%.2f" % np.average(A5_loc2_raw))," microns, ",("%.2f" % np.std(A5_loc2_raw,ddof=1))," microns"
	print A5_time,"days, ","A5_loc3, ",("%.2f" % np.average(A5_loc3_raw))," microns, ",("%.2f" % np.std(A5_loc3_raw,ddof=1))," microns"
	print A5_time,"days, ","A5_loc4, ",("%.2f" % np.average(A5_loc4_raw))," microns, ",("%.2f" % np.std(A5_loc4_raw,ddof=1))," microns"
	print "\n"
	print B5_time,"days, ","B5_loc2, ",("%.2f" % np.average(B5_loc2_raw))," microns, ",("%.2f" % np.std(B5_loc2_raw,ddof=1))," microns"
	print B5_time,"days, ","B5_loc3, ",("%.2f" % np.average(B5_loc3_raw))," microns, ",("%.2f" % np.std(B5_loc3_raw,ddof=1))," microns"
	print B5_time,"days, ","B5_loc5, ",("%.2f" % np.average(B5_loc5_raw))," microns, ",("%.2f" % np.std(B5_loc5_raw,ddof=1))," microns"
	print B5_time,"days, ","B5_loc6, ",("%.2f" % np.average(B5_loc6_raw))," microns, ",("%.2f" % np.std(B5_loc6_raw,ddof=1))," microns"
	print B5_time,"days, ","B5_loc7, ",("%.2f" % np.average(B5_loc7_raw))," microns, ",("%.2f" % np.std(B5_loc7_raw,ddof=1))," microns"
	print "\n"
	print C5_time,"days, ","C5_loc1, ",("%.2f" % np.average(C5_loc1_raw))," microns, ",("%.2f" % np.std(C5_loc1_raw,ddof=1))," microns"
	print C5_time,"days, ","C5_loc2, ",("%.2f" % np.average(C5_loc2_raw))," microns, ",("%.2f" % np.std(C5_loc2_raw,ddof=1))," microns"
	print C5_time,"days, ","C5_loc3, ",("%.2f" % np.average(C5_loc3_raw))," microns, ",("%.2f" % np.std(C5_loc3_raw,ddof=1))," microns"
	print "\n"
	print A6_time,"days, ","A6_loc1, ",("%.2f" % np.average(A6_loc1_raw))," microns, ",("%.2f" % np.std(A6_loc1_raw,ddof=1))," microns"
	print A6_time,"days, ","A6_loc2, ",("%.2f" % np.average(A6_loc2_raw))," microns, ",("%.2f" % np.std(A6_loc2_raw,ddof=1))," microns"
	print A6_time,"days, ","A6_loc3, ",("%.2f" % np.average(A6_loc3_raw))," microns, ",("%.2f" % np.std(A6_loc3_raw,ddof=1))," microns"
	print "\n"
	print B6_time,"days, ","B6_loc1, ",("%.2f" % np.average(B6_loc1_raw))," microns, ",("%.2f" % np.std(B6_loc1_raw,ddof=1))," microns"
	print B6_time,"days, ","B6_loc2, ",("%.2f" % np.average(B6_loc2_raw))," microns, ",("%.2f" % np.std(B6_loc2_raw,ddof=1))," microns"
	print B6_time,"days, ","B6_loc3, ",("%.2f" % np.average(B6_loc3_raw))," microns, ",("%.2f" % np.std(B6_loc3_raw,ddof=1))," microns"
	print "\n"
	print C6_time,"days, ","C6_loc1, ",("%.2f" % np.average(C6_loc1_raw))," microns, ",("%.2f" % np.std(C6_loc1_raw,ddof=1))," microns"
	print C6_time,"days, ","C6_loc2, ",("%.2f" % np.average(C6_loc2_raw))," microns, ",("%.2f" % np.std(C6_loc2_raw,ddof=1))," microns"
	print C6_time,"days, ","C6_loc3, ",("%.2f" % np.average(C6_loc3_raw))," microns, ",("%.2f" % np.std(C6_loc3_raw,ddof=1))," microns"
	print C6_time,"days, ","C6_loc4, ",("%.2f" % np.average(C6_loc4_raw))," microns, ",("%.2f" % np.std(C6_loc4_raw,ddof=1))," microns"
	print C6_time,"days, ","C6_loc5, ",("%.2f" % np.average(C6_loc5_raw))," microns, ",("%.2f" % np.std(C6_loc5_raw,ddof=1))," microns"
	print "\n"
              

plot=10
if plot==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali ')


    axe.errorbar(A1_time,np.average(A1_loc1_raw),yerr=np.std(A1_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='A1-loc1')
    axe.errorbar(A1_time,np.average(A1_loc4_raw),yerr=np.std(A1_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='A1-loc4')    
    axe.errorbar(A1_time,np.average(A1_loc7_raw),yerr=np.std(A1_loc7_raw,ddof=1),
               fmt='o',capsize=5)#,label='A1-loc7')   

    axe.errorbar(B1_time,np.average(B1_loc1_raw),yerr=np.std(B1_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='B1-loc1')
    axe.errorbar(B1_time,np.average(B1_loc2_raw),yerr=np.std(B1_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='B1-loc2')    
    axe.errorbar(B1_time,np.average(B1_loc3_raw),yerr=np.std(B1_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='B1-loc3')

    axe.errorbar(C1_time,np.average(C1_loc1_raw),yerr=np.std(C1_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='C1-loc1') 
    axe.errorbar(C1_time,np.average(C1_loc2_raw),yerr=np.std(C1_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C1-loc2')         
    axe.errorbar(C1_time,np.average(C1_loc3_raw),yerr=np.std(C1_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C1-loc3')

    axe.errorbar(A2_time,np.average(A2_loc1_raw),yerr=np.std(A2_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='A2-loc1')
    axe.errorbar(A2_time,np.average(A2_loc2_raw),yerr=np.std(A2_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='A2-loc2')
    axe.errorbar(A2_time,np.average(A2_loc3_raw),yerr=np.std(A2_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='A2-loc3')

    axe.errorbar(B2_time,np.average(B2_loc4_raw),yerr=np.std(B2_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='B2-loc4')
    axe.errorbar(B2_time,np.average(B2_loc6_raw),yerr=np.std(B2_loc6_raw,ddof=1),
               fmt='o',capsize=5)#,label='B2-loc6')
    axe.errorbar(B2_time,np.average(B2_loc7_raw),yerr=np.std(B2_loc7_raw,ddof=1),
               fmt='o',capsize=5)#,label='B2-loc7')

    axe.errorbar(C2_time,np.average(C2_loc1_raw),yerr=np.std(C2_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='C2-loc1') 
    axe.errorbar(C2_time,np.average(C2_loc2_raw),yerr=np.std(C2_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C2-loc2')         
    axe.errorbar(C2_time,np.average(C2_loc3_raw),yerr=np.std(C2_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C2-loc3')

    axe.errorbar(A3_time,np.average(A3_loc1_raw),yerr=np.std(A3_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='A3-loc1')
    axe.errorbar(A3_time,np.average(A3_loc2_raw),yerr=np.std(A3_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='A3-loc2')
    axe.errorbar(A3_time,np.average(A3_loc3_raw),yerr=np.std(A3_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='A3-loc3')

    axe.errorbar(B3_time,np.average(B3_loc1_raw),yerr=np.std(B3_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='B3-loc1')
    axe.errorbar(B3_time,np.average(B3_loc2_raw),yerr=np.std(B3_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='B3-loc2')
    axe.errorbar(B3_time,np.average(B3_loc3_raw),yerr=np.std(B3_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='B3-loc3')

    axe.errorbar(C3_time,np.average(C3_loc2_raw),yerr=np.std(C3_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C3-loc2')
    axe.errorbar(C3_time,np.average(C3_loc3_raw),yerr=np.std(C3_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C3-loc3')
    axe.errorbar(C3_time,np.average(C3_loc4_raw),yerr=np.std(C3_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='C3-loc4')

    axe.errorbar(A4_time,np.average(A4_loc1_raw),yerr=np.std(A4_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='A4-loc1')
    axe.errorbar(A4_time,np.average(A4_loc2_raw),yerr=np.std(A4_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='A4-loc2')
    axe.errorbar(A4_time,np.average(A4_loc3_raw),yerr=np.std(A4_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='A4-loc3')

    axe.errorbar(B4_time,np.average(B4_loc1_raw),yerr=np.std(B4_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='B4-loc1')
    axe.errorbar(B4_time,np.average(B4_loc2_raw),yerr=np.std(B4_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='B4-loc2')
    axe.errorbar(B4_time,np.average(B4_loc3_raw),yerr=np.std(B4_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='B4-loc3')

    axe.errorbar(C4_time,np.average(C4_loc1_raw),yerr=np.std(C4_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='C4-loc1')
    axe.errorbar(C4_time,np.average(C4_loc2_raw),yerr=np.std(C4_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C4-loc2')
    axe.errorbar(C4_time,np.average(C4_loc3_raw),yerr=np.std(C4_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C4-loc3')

    axe.errorbar(A5_time,np.average(A5_loc2_raw),yerr=np.std(A5_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='A5-loc2')
    axe.errorbar(A5_time,np.average(A5_loc3_raw),yerr=np.std(A5_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='A5-loc3')
    axe.errorbar(A5_time,np.average(A5_loc4_raw),yerr=np.std(A5_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='A5-loc4')
    axe.errorbar(A5_time,np.average(A5_loc5_raw),yerr=np.std(A5_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='A5-loc5')
    axe.errorbar(A5_time,np.average(A5_loc6_raw),yerr=np.std(A5_loc6_raw,ddof=1),
               fmt='o',capsize=5)#,label='A5-loc6')

    axe.errorbar(B5_time,np.average(B5_loc2_raw),yerr=np.std(B5_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='B5-loc2')
    axe.errorbar(B5_time,np.average(B5_loc3_raw),yerr=np.std(B5_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='B5-loc3')
    axe.errorbar(B5_time,np.average(B5_loc5_raw),yerr=np.std(B5_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='B5-loc5')
    axe.errorbar(B5_time,np.average(B5_loc6_raw),yerr=np.std(B5_loc6_raw,ddof=1),
               fmt='o',capsize=5)#,label='B5-loc6')
    axe.errorbar(B5_time,np.average(B5_loc7_raw),yerr=np.std(B5_loc7_raw,ddof=1),
               fmt='o',capsize=5)#,label='B5-loc7')

    axe.errorbar(C5_time,np.average(C5_loc1_raw),yerr=np.std(C5_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='C5-loc1')
    axe.errorbar(C5_time,np.average(C5_loc2_raw),yerr=np.std(C5_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C5-loc2')
    axe.errorbar(C5_time,np.average(C5_loc3_raw),yerr=np.std(C5_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C5-loc3')
    axe.errorbar(C5_time,np.average(C5_loc4_raw),yerr=np.std(C5_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='C5-loc4')
    axe.errorbar(C5_time,np.average(C5_loc5_raw),yerr=np.std(C5_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='C5-loc5')

    axe.errorbar(A6_time,np.average(A6_loc1_raw),yerr=np.std(A6_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='A6-loc1')
    axe.errorbar(A6_time,np.average(A6_loc2_raw),yerr=np.std(A6_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='A6-loc2')
    axe.errorbar(A6_time,np.average(A6_loc3_raw),yerr=np.std(A6_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='A6-loc3')
    axe.errorbar(A6_time,np.average(A6_loc4_raw),yerr=np.std(A6_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='A6-loc4')
    axe.errorbar(A6_time,np.average(A6_loc5_raw),yerr=np.std(A6_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='A6-loc5')

    axe.errorbar(B6_time,np.average(B6_loc1_raw),yerr=np.std(B6_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='B6-loc1')
    axe.errorbar(B6_time,np.average(B6_loc2_raw),yerr=np.std(B6_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='B6-loc2')
    axe.errorbar(B6_time,np.average(B6_loc3_raw),yerr=np.std(B6_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='B6-loc3')
    axe.errorbar(B6_time,np.average(B6_loc4_raw),yerr=np.std(B6_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='B6-loc4')
    axe.errorbar(B6_time,np.average(B6_loc5_raw),yerr=np.std(B6_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='B6-loc5')

    axe.errorbar(C6_time,np.average(C6_loc1_raw),yerr=np.std(C6_loc1_raw,ddof=1),
               fmt='o',capsize=5)#,label='C6-loc1')
    axe.errorbar(C6_time,np.average(C6_loc2_raw),yerr=np.std(C6_loc2_raw,ddof=1),
               fmt='o',capsize=5)#,label='C6-loc2')
    axe.errorbar(C6_time,np.average(C6_loc3_raw),yerr=np.std(C6_loc3_raw,ddof=1),
               fmt='o',capsize=5)#,label='C6-loc3')
    axe.errorbar(C6_time,np.average(C6_loc3_raw),yerr=np.std(C6_loc4_raw,ddof=1),
               fmt='o',capsize=5)#,label='C6-loc4')
    axe.errorbar(C6_time,np.average(C6_loc3_raw),yerr=np.std(C6_loc5_raw,ddof=1),
               fmt='o',capsize=5)#,label='C6-loc5')
                
    axe.plot(time1,total_oxide1,'-',label='Dali 0.2 MPa')            
    
    axe.legend(loc='lower right')#,ncol=3,fontsize=10)
    axe.annotate("Thicknesses averaged by location\non each sample.",xy=(2,5.5),xytext=(1,5.5))  
    plt.xlim(0,65)
    #plt.ylim(0,ymax)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    
    plt.savefig('Steam-Data.png')





plotavg=10
if plotavg==True:    
    #plt.ion()
    #plt.show()
    fig = plt.figure(figsize = (10,7))
    axe = fig.add_subplot(111)
    axe.tick_params(labelsize=18)
    #axe.plot(Dali2012_x,Dali2012_y,'o')
    axe.errorbar(Dali2012_x,Dali2012_y,yerr=[Dali2012_yel,Dali2012_yeu],
                 capsize=5,fmt='kx',label='Dali2012 ')
  
    #axe.errorbar(A1_time,np.average(np.array([np.average(A1_loc1_raw),np.average(A1_loc4_raw),np.average(A1_loc7_raw)])),
	#	yerr=np.average(np.array([np.std(A1_loc1_raw,ddof=1),np.std(A1_loc4_raw,ddof=1),np.std(A1_loc7_raw,ddof=1)])),
	#	fmt='o',capsize=5,label='A1')
                
    axe.plot(time1,total_oxide1,'-',label='Dali2012 P=0.2 MPa')            
    
    axe.legend(loc='lower right',ncol=3,fontsize=5)
    
    plt.xlim(0,65)
    #plt.ylim(0,ymax)
    plt.xlabel(xtitle,fontsize=20)
    plt.ylabel(ytitle,fontsize=20)
    
    plt.savefig('avgSteam-Data.png')
    


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
