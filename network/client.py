import socket

def main():
    with socket.socket() as my_socket:
        my_socket.connect(('0.0.0.0', 8820))

        my_socket.send("hi".encode())
        my_socket.send("hi".encode())

main()