import bluetooth

bd_addr = "98:D3:31:40:A1:ED"
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))

data = ""

while 1:
    data += sock.recv(1024)
    data_end = data.find('\n')
    if data_emd != -1:
        rec = data[:data_end]
        print data
        data = data[data_end+1:]
    else:
        print "NOPE!"
        break
sock.close()
