from __future__ import print_function
import serial, os
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import seaborn as sns
import numpy as np

ser = serial.Serial('COM20', 115200, timeout=1) #baudrate 9600 didn't show good results
ser.flushInput()
#taking w and h 
w, h = 138, 48;

matrix = [[0 for x in range(w)] for y in range(h)]
#generation of matrix data

def collect_data():
	while not ord(ser.read()) == 0:
		pass
	for y in range(h):
		for x in range(w):
			readByte = ser.read()
			if  ord(readByte)==0:
				break
			else:
				matrix[y][x]=ord(readByte)
	print('\n'.join([''.join(['{:4}'.format(item) for item in row]) 
      for row in matrix]))
	return matrix
	  
def updated_data(data):
    mat.set_data(data)
    return mat
	
def data_gen():
    while True:
        yield collect_data()
	
fig, ax = plt.subplots()                         #figsize=(5,5))
#class matplotlib.animation.FuncAnimation(fig, func, frames=None, init_func=None, fargs=None, save_count=None, **kwargs)
#sns.heatmap(ax.corr(), annot= True, linewidths=0.5, linecolor="red", ax=ax)
mat = ax.matshow(collect_data(),  vmin=0, vmax=100) #matrix to be displayed
ax.autoscale(False)
plt.colorbar(mat)
ani = animation.FuncAnimation(fig, updated_data, data_gen)

plt.show()
