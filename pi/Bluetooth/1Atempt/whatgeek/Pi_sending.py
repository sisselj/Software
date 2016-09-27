import bluetooth

bd_addr = "98:D3:31:40:A1:ED" #the address from the Arduino sensor
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))

while 1:
        tosend = raw_input()
        if tosend != 'q':
                sock.send(tosend)
        else:
                break

sock.close()
