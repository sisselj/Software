"""from serial import *

arduino = Serial(port="/dev/tty.usbmodem1411",baudrate=9600)

while True:
	print arduino.readline(),


"""

'''
This module provides the class LivePlot which can plot data from a serial device
live.

Tested on Ubuntu 15.10 with Arduino Uno.
Tested on OS X 10.11.2 (15C50) with Arduino Uno

@author: Sverre
'''
import re
import time
import serial
import matplotlib.pyplot as plt
import multiprocessing as mp

class LivePlot(mp.Process):
    '''
    This class handles extends multiprocessing.Process so that the 
    computation and plotting happens in a new thread.
    
    To start the plotting, call the method L{start()}. The thread will close if 
    the main thread closes, so if no work is done, nothing will be plotted. 
    This can be avoided by calling L{raw_input()}. 
    
    The thread can be closed with the method L{join()}.
    '''
    def __init__(self, ser, comp, dec=None, prop=None, save=None, clean=None, 
                 cb=None, verb=False, clear=False, only_txt=False):
        '''
        @param ser: The serial device to communicate with.
        @type ser: Serial
        @param comp: The function to be used on the input from the serial device
        to convert it to something plotable.
        @type comp: L{callable}
        @keyword dec: String with decorations for the plot such as symbol for 
        data points.
        @type dec: L{str}
        @keyword prop: Properties of the plot such as alpha and color.
        @type prop: L{tuple}
        @keyword save: File to save the processed data to.
        @type save: L{str}
        @keyword cb: Not implemented.
        @todo: Implement callback possibilities.
        @keyword clean: Not implemented.
        @todo: Implement the possibility to only read new serial data.
        @keyword verb: Boolean indicating if the data is to be printed to the 
        terminal.
        @type verb: L{bool}
        '''
        # Setup thread handling
        mp.Process.__init__(self)
        self.stopping = mp.Event()
         
        # Initialize attributes
        self.now = time.time()
        self.dec = dec
        self.ser = ser
        self.comp = comp
        self.verb = verb
        self.values = []
        self.fig = None
        self.prop = prop
        self.save = save
        self.clear = clear
        self.only_txt = only_txt
        self.time_list = []


        #--------------------------------------------
        if self.clear:
            self.save_file = open(save, 'w')
            self.save_file.close()
        #--------------------------------------------

        if self.save is not None:
            self.save_file = open(save, 'a')
        
        # Todo    
        if cb is not None:
            raise NotImplementedError
        if clean is not None:
            raise NotImplementedError
        
    def run(self):
        '''
        Read and process the data from the serial device, plot it and
        potentially save it to a file. The thread runs continuously until
        L{join()} is called or the script terminates.
        '''
        # Setup plot
        if self.only_txt == False:
            plt.figure()
            plt.ion()
            plt.show()
            plt.hold(False)

        #--------------------------------------------
        def contains_many_dots(var):
            dots = re.findall("\.",var)
            return len(dots)
        
        previous_raw = None
        while not self.stopping.is_set():
            # Process the data
            raw = self.ser.readline()
            print raw,

        
            while contains_many_dots(raw)>1:
                raw = self.ser.readline()

            if float(raw)< -50 or float(raw)>125:
                raw = self.ser.readline()
                while contains_many_dots(raw)>1:
                    raw = self.ser.readline()
                

            if previous_raw == None:
                previous_raw = raw


            # might be redundent
            if abs(float(raw)) > 30 + abs(float(previous_raw)):
                raw = previous_raw
            

            previous_raw = raw

        #--------------------------------------------

            data = self.comp(raw)
            self.values.append(data)

            current_time = (time.time()-self.now)
            self.time_list.append(current_time)
            
            # Display output
            if self.verb:
                print 'read: %splot: %s' % (raw, data)
            if self.save is not None:
                self.save_data(current_time, data)
            #self.fig.clear()
            if self.only_txt == False:
                self.plot()

    
    def join(self):
        '''
        Stops the thread safely.
        '''
        self.stopping.set()
        if self.save is not None:
            self.save_file.close()
        super(self.__class__, self).join()
           
    def plot(self):
        '''
        Plots the data.
        '''        
        if self.dec is not None:
            self.fig = plt.plot(self.values, self.dec)
        else:
            self.fig = plt.plot(self.time_list, self.values)
        if self.prop is not None:
            plt.setp(self.fig, *self.prop)
        plt.draw()
    
    def save_data(self,current_time , data):
        '''
        Saves the data to a file.
        
        @param data: The data to be saved.
        '''
        self.save_file.write("%.2f" % current_time +", "+ str(data) + '\n')
        self.save_file.flush()
