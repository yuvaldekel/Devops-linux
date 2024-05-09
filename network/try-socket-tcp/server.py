import socket

def main():
    with socket.socket() as server_socket:
        server_socket.bind(('0.0.0.0', 8820))
        server_socket.listen()
        (client_socket, client_address) = server_socket.accept()

        print(client_socket.recv(1024).decode())

main()