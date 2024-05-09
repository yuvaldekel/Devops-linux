import select
from socket import socket, AF_INET, SOCK_STREAM

MAX_SIZE = 1024
SERVER_PORT = 5555
SERVER_IP = '0.0.0.0'

def main():
    try:
        server_socket = socket(AF_INET, SOCK_STREAM)
        server_socket.bind(( SERVER_IP, SERVER_PORT))
        server_socket.listen()
        clients_socket = []
        write_socket = []
        
        while True:
            rd_list = [server_socket] + clients_socket
            ready_rd , ready_wr , in_error = select.select(rd_list, [], [])
            
            for currnet_socket in ready_rd:
                if currnet_socket is server_socket:
                    (connection_socket, address) = currnet_socket.accept()
                    print(f"Hello client {address[0]}")
                    clients_socket.append(connection_socket)
                else:
                    print("Getting data form existing client:\n")
                    data = currnet_socket.recv(MAX_SIZE).decode()

                    if data == '':
                        print("client closed the connection")
                        clients_socket.remove(currnet_socket)
                        currnet_socket.close()
                    else:
                        print(data)
    finally:
        server_socket.close()

if __name__ == "__main__":
    main()