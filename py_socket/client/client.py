import socket

sock = socket.socket()

while True:
    in_str = input('输入connect连接服务器:')
    if in_str == 'connect':
        sock.connect(('114.242.62.15',61245))
        print('连接服务器成功！')
        break

while True:
    rec = sock.recv(1024)
    print('来自服务器:',rec.decode())