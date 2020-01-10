import socket

sock = socket.socket()
sock.bind(("192.168.1.131",61245))
sock.listen(5)
print('等待客户端连接...')
c,addr = sock.accept()
print('客户端连接成功！')
while True:
    in_str = input("请输入要发送的内容:")
    c.send(in_str.encode('utf-8'))
    