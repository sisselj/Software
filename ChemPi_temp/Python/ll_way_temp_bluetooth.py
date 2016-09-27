#!/usr/bin/env python3

import bluetooth as bt
import struct
import matplotlib.pyplot as plt
#Got "MatplotlibDecompressionWarning" ignoring it here
import warnings
warnings.filterwarnings("ignore")


Data_list = []
update_frequency = .25 # seconds

#    VARIABLE   TYPE PROCESSING   TYPE PYTHON   SPECIFIER   BYTES
#      millis     unsigned long  unsigned int           I       4
# temperature             float         float           f       4
struct_format = 'If' 			     
struct_size = struct.calcsize(struct_format)

# Serial Port Profile Universally Unique IDentifier for HC-05
hc_05_uuid = "00001101-0000-1000-8000-00805F9B34FB"

bt_buffer = bytearray()

def scan(**kwargs):
        return bt.find_service(**kwargs)
	
def print_devices(devices):
        for i, device in enumerate(devices):
                print('{:3d}: {}'.format(i, device["host"]))
		
def request_connection(devices):
        request = raw_input('Write a space seperated list of devices to connect to:\n')
        requests = map(int, request.split())
        sockets = []
        for i, r in enumerate(requests):
                sockets.append(bt.BluetoothSocket(bt.RFCOMM))
                sockets[i].connect((devices[r]["host"], devices[r]["port"]))
        return sockets

# This function is supposed to use a buffer to read all the packets
# recieved each call, however the buffer does not work at the moment.
# The parser therefor have to read more often the it recives packets.
def parse_structs(socket, types, size):
        global Data_list
        try: 
                signal = socket.recv(size)
                bt_buffer.extend(signal)
                while len(bt_buffer) >= struct_size:
                        Data = struct.unpack(struct_format, bt_buffer[:struct_size])
                        Data_list.append(Data_list)
                        print(Data)
                        plt.scatter(Data[0]/1000,Data[1])
                        plt.pause(0.05)
                        del bt_buffer[:struct_size]

        except struct.error as e:
                print(e)

def main():
	# Connect
        devices = scan(uuid=hc_05_uuid, address=None)
        print_devices(devices)
        sockets = request_connection(devices)
	
	# Let's talk!
        import time
        while True:
                for socket in sockets:
                        parse_structs(socket, struct_format, struct_size)
                time.sleep(update_frequency)
	# Close sockets?

if __name__ == '__main__':
        main()


