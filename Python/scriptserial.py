
import serial
import time
import os



ser = serial.Serial('COM11', 1000000)  # replace 'COM1' with the name of your serial port
print(ser.name)
ser.timeout=1

timeout = time.time()

# Try different file names until you find one that doesn't exist yet
for i in range(1, 100):
    file_name = f'file{i}.txt'
    if not os.path.exists(file_name):
        break

out_file = open(file_name, 'w')

while True:
    bs = ser.readline()
    if bs:
        out_file.write(str(bs))
        print(str(bs))
    if time.time() - timeout > 2:
        print ("timeout")
        ser.close()
        out_file.close()
        break

with open(file_name, 'r+') as f:
    content = f.read()
    f.seek(0)
    f.write(content[2:-1])
    f.truncate()

