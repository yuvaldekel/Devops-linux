from socket import gethostbyname, gethostname

def get_name():
    return gethostname()

def get_ip():
    IPAddr = gethostbyname(get_name())
    return IPAddr


def main():
    hostname = get_name()
    IPAddr = get_ip()
    
    print(f"Your Computer Name is: {hostname}")
    print(f"Your Computer IP Address is: {IPAddr}")

if __name__ == "__main__":
    main()