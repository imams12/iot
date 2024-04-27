import serial.tools.list_ports

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portsList = []

for port in ports:
    portsList.append(str(port))
    print(str(port))
    
val = input("Select Port: COM")

for x in range(0, len(portsList)):
    if portsList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portVar)
        
serialInst.baudrate = 9600
serialInst.port = portVar
serialInst.open()

while True:
    command = input("Arduino Command (ON/OFF) => ")
    command = command.upper()
    serialInst.write(command.encode('utf-8'))
    
    if command == "EXIT":
        exit()