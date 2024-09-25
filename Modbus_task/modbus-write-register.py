from pymodbus.client import ModbusTcpClient  # Updated import for pymodbus v3.x
from datetime import datetime
import random
import time

# Define host and port for the Modbus server (Raspberry Pi)
host = '192.168.1.45'  # IP of your Raspberry Pi
port = 502
slave_id = 1  # Slave unit ID for the device

# Initialize the Modbus TCP client
client = ModbusTcpClient(host=host, port=port)

# Connect to the server
if client.connect():
    print(f"Connected to Modbus server at {host}:{port}")
else:
    print(f"Failed to connect to Modbus server at {host}:{port}")
    exit(1)

# Continuous loop to write random data to a register every 5 seconds
try:
    while True:



    #   # To Write values to multiple registers
    #     list = []
    #     for i in range(10):
    # 	    data = random.randint(25,35)
    # 	    list.append(data)
    	
    	
    # # write to multiple registers using list of data
    #     wr = client.write_registers(1000,list)
	
	
	
    
        data = random.randint(25, 35)  # Generate random data between 25 and 35

        # Write a single value to register 1000 (slave_id is passed when client is initialized)
        wr = client.write_register(1000, data)
        
      



        # Check for any errors in writing the register
        if wr.isError():
            print(f"Error writing to register: {wr}")
        else:
            print(f"Successfully wrote value to register 1001")

        # Wait for 5 seconds before writing again
        time.sleep(5)

except KeyboardInterrupt:
    print("Process interrupted by user")

finally:
    # Ensure the connection is closed properly
    client.close()
    print("Modbus client connection closed.")

