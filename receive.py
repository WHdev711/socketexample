#!/usr/bin/env python

import socket               # Import socket module

s = socket.socket()         # Create a socket object
host = '10.10.10.133'       # Get local machine name or IP address
port = 12345
s.bind((host, port))        # Bind to the port
f = open('result.txt','wb')
s.listen(5)                 # Now wait for client connection.
while True:
    c, addr = s.accept()     # Establish connection with client.
    print('Got connection from', addr)
    print("Receiving...")
    l = c.recv(1024)
    while (l):
        print("Receiving...")
        f.write(l)
        l = c.recv(1024)
    f.close()
    print("Done Receiving")
    c.close()
    exit()                # Close the connection