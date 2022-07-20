# coding=UTF-8
import serial
from time import sleep

ser = serial.Serial('/dev/ttyTHS1',115200,timeout=0.5)

def port_open_recv():
    ser.baudrate=115200
    ser.bytesize=8
    ser.stopbits=1
    ser.parity="N"#奇偶校验位
    ser.open()
    if(ser.isOpen()):
        print("串口打开成功！")
    else:
        print("串口打开失败！")
#isOpen()函数来查看串口的开闭状态



def port_close():
    ser.close()
    if(ser.isOpen()):
        print("串口关闭失败！")
    else:
        print("串口关闭成功！")

def send(send_data):
    if(ser.isOpen()):
        ser.write(send_data.encode('utf-8'))
        print("发送成功",send_data)
    else:
        print("发送失败！")

if __name__ == '__main__':
    print("going to open serial")
    port_close()
    port_open_recv()
    while True:
        packet = bytes(0x01)
        a=bytes(input("输入："))
        ser.write(a)
        #ser.write("\r\n")
        sleep(0.5)
	
