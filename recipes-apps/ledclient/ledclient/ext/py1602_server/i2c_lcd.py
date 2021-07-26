#!/usr/bin/env python
import LCD1602
import time
import socket
import signal 
import sys
import os
global i2c_lcd_server

def signal_handler(sig, frame):
    print("signal!")
    global i2c_lcd_server
    if i2c_lcd_server :
        print("del i2c_lcd_server")
        del i2c_lcd_server
        sys.exit(0)
        

class I2CLCDSocketServer:
    def __init__(self):
        # server_address = ('127.0.0.1', 9999)
        # socket_family = socket.AF_INET
        # socket_type = socket.SOCK_STREAM

        # unix domain sockets
        server_address = '/tmp/uds_socket_i2clcd7'
        socket_family = socket.AF_UNIX
        socket_type = socket.SOCK_STREAM

        self.server_address = server_address
        self.sock = socket.socket(socket_family, socket_type)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.bind(server_address)
        self.sock.listen(1)
        print(f"listening on '{server_address}'.")
        pass

    def handle_i2c_lcd(self):
        while True:
            connection, client_address = self.sock.accept()
            data = connection.recv(1024)
            print(f"recv data from client '{client_address}': {data.decode()}")
            recv_str = data.decode()
            recv_str_list = recv_str.split(':')
            print("recv_str_list:", recv_str_list)
            #connection.sendall("hello client".encode())
            str_emtpy = "                "
            LCD1602.write(int(recv_str_list[0]), int(recv_str_list[1]),  "                ")
            LCD1602.write(int(recv_str_list[0]), int(recv_str_list[1]), recv_str_list[2].rstrip('\x00'))


    def __del__(self):
        print("sock close")
        self.sock.close()
        try:
            os.unlink(self.server_address)
        except OSError:
            if os.path.exists(self.server_address):
                raise

if __name__ == '__main__':
    LCD1602.init(0x27, 1)   # init(slave address, background light)
    LCD1602.write(0, 0, 'Hi....')
    LCD1602.write(1, 1, '1602LCD standby')
    time.sleep(2)
    signal.signal(signal.SIGINT, signal_handler)
    global i2c_lcd_server
    i2c_lcd_server = I2CLCDSocketServer()
    i2c_lcd_server.handle_i2c_lcd()
    LCD1602.clear()


