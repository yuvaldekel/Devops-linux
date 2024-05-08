from scapy.all import sniff

def main():
    p = sniff(count = 10, iface = 'wlp4s0')
    p[9].show()

if __name__ == "__main__":
    main()