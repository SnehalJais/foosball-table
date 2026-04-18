import serial
import time

PORT = "COM7"
BAUD = 115200

def send_command(ser, command):
    ser.write((command + "\n").encode())
    print(f"Sent: {command}")
    time.sleep(0.2)

    # while ser.in_waiting:
    #     response = ser.readline().decode(errors="ignore").strip()
    #     if response:
    #         print("Arduino:", response)

def main():
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)

    print("Connected.")
    print("Type commands like:")
    print("  M1 100")
    print("  M2 -50")
    print("  exit")

    while True:
        command = input("Enter command: ").strip()
        if command.lower() == "exit":
            break
        send_command(ser, command)

    ser.close()
    print("Disconnected.")

if __name__ == "__main__":
    main()