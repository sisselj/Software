# Software

Arduino Lib/ contains all the libraries used in the ino files.

Temp.ino is a basic program for getting the temp

Temp_LCD.ino is a program for getting the temp and showing it on an LCD-display.

Temp_LCD_datalogger.ino is the same as Temp_LCD, but it also contains the code for logging the temp to an sd card.

main_temp.py contains the class for liveplot. 

run_temp.py is the file you should run to get an liveplot.
This script is a basic UI for main_temp.py. 

##########################################################

>>> python run_temp.py -h

usage: run_temp.py [-h] [-t] [-s] [-d]

UI for Temperature logging. Running this script without any args, will give a
live plot and values in the terminal

optional arguments:

  -h, --help     show this help message and exit

  -t, --txt      only saving data to txt (NO PLOT).

  -s, --save     Save data to the data.txt file

  -d, --default  Clear data from data.txt and save data to data.txt


##########################################################
