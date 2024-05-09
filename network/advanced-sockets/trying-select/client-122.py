from socket import socket, AF_INET, SOCK_STREAM

SERVER_PORT = 5555
SERVER_IP = '127.0.1.1'

def main():
    with socket(AF_INET, SOCK_STREAM) as my_socket:
        my_socket.connect((SERVER_IP, SERVER_PORT))

        while True:
            name = input("Please enter a name that you would like to send to the server ")
            if name == "":
                break
            
            my_socket.send(name.encode())            

if __name__ == "__main__":
    main()