from socket import gethostname, socket, AF_INET, SOCK_DGRAM

def get_name():
    return gethostname()

def get_ip():
    s = socket(AF_INET, SOCK_DGRAM)
    s.connect(("8.8.8.8", 80))
    return s.getsockname()[0]

def main():
    hostname = get_name()
    IPAddr = get_ip()
    
    print(f"Your Computer Name is: {hostname}")
    print(f"Your Computer IP Address is: {IPAddr}")

if __name__ == "__main__":
    main()