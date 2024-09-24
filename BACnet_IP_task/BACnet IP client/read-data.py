import BAC0
import json
import asyncio

# Global variable for BACnet connection
bacnet = None
data = {}


async def setup_connection():
    global bacnet
    # Create a BACnet connection to connect to the devices
    bacnet = BAC0.lite(ip="192.168.1.45/24", port=47808)


async def main():
    await setup_connection()  # Set up the connection before entering the loop
    while True:
        # Reading 3 Objects from the BACnet Simulator
        for x in range(0, 1):
            id = str(x)
            # Connect to the BACnet simulator using the IP address and port number
            value = await bacnet.read(
                "192.168.1.26:47808 analogInput:0 presentValue"
            )
            value = str(value)
            data["Analog_input"+id] = value

        print(json.dumps(data, indent=2))
        await asyncio.sleep(5)  # Non-blocking sleep


# Run the main async function
if __name__ == '__main__':
    asyncio.run(main())

