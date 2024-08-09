from phonenumbers import PhoneNumber, parse, carrier, timezone, geocoder 
import phonenumbers
import tkinter

def main():
    phone: str = input("Enter phone -> ")
    
    try:
        phone: PhoneNumber = parse(phone)

    except phonenumbers.phonenumberutil.NumberParseException:
        raise ValueError("The string supplied did not seem to be a phone number.") from None
    
    time_zone: str = timezone.time_zones_for_number(phone)[0]
    print(time_zone)

    carrier_name: str = carrier.name_for_number(phone, 'en')
    print(carrier_name)

    region: str = geocoder.description_for_number(phone, 'en') 
    print(region)


if __name__ == "__main__":
    main()