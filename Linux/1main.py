# coding=UTF-8
import imutils
import numpy, cv2
import numpy as np
import serial
from time import sleep
#import direction
ser = serial.Serial('/dev/ttyGS0',115200)

def white_point_video(frame):
    kernel_2 = np.ones((2, 2), np.uint8)  # 2x2的卷积核
    kernel_3 = np.ones((3, 3), np.uint8)  # 3x3的卷积核
    kernel_4 = np.ones((4, 4), np.uint8)  # 4x4的卷积核
    kernel_8 = np.ones((8, 8), np.uint8)
    Lower_red = np.array([156, 128, 46])
    Upper_red = np.array([180, 255, 255])
    red = [Lower_red, Upper_red, 'red']
    Lower_white = np.array([0, 0, 221])  # 221
    Upper_white = np.array([180, 30, 255])
    white = [Lower_white, Upper_white, 'white']
    Lower_black = np.array([0, 0, 0])
    Upper_black = np.array([180, 255, 46])
    black = [Lower_black, Upper_black, 'black']
    Lower_green = np.array([35, 95, 46])
    Upper_green = np.array([70, 255, 255])
    green = [Lower_green, Upper_green, 'green']
    Lower_blue = np.array([80, 80, 150])
    Upper_blue = np.array([110, 255, 255])
    blue = [Lower_blue, Upper_blue, 'blue']
    HSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)  # 把BGR图像转换为HSV格式
    color = white
    if color[2] == 'white':
        mask_white = cv2.inRange(HSV, color[0], color[1])
        erosion = cv2.erode(mask_white, kernel_2, iterations=1)
        erosion = cv2.erode(erosion, kernel_4, iterations=1)
        erosion = cv2.erode(erosion, kernel_4, iterations=1)
        dilation = cv2.dilate(erosion, kernel_2, iterations=1)
        dilation = cv2.dilate(dilation, kernel_4, iterations=1)
        dilation = cv2.dilate(dilation, kernel_8, iterations=1)
        white, binary = cv2.threshold(dilation, 127, 255, cv2.THRESH_BINARY)  # 二值化，将滤波后的图像变成二值图像放在binary中
        cnts = cv2.findContours(binary.copy(), cv2.RETR_EXTERNAL,
                                cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)  # 寻找轮廓
        white_list = []
        for c in cnts:
            # compute the center of the contour
            M0 = cv2.moments(c)
            # cv2.drawContours(frame, [c], -1, (0, 255, 0), 2)
            car_video_location = [int(M0["m10"] / M0["m00"]), int(M0["m01"] / M0["m00"])]
            cv2.circle(frame, (car_video_location[0], car_video_location[1]), 7, (0, 255, 0), -1)
            cv2.putText(frame, "white", (car_video_location[0] - 20, car_video_location[1] - 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            cv2.imshow("Image", frame)
            white_point = [int(M0["m10"] / M0["m00"]), int(M0["m01"] / M0["m00"])]
        #   green_list = green_list + green_point
        # if len(green_list) == 6:  # 起始可能识别不到3个红色块，等都识别到，再输出坐标
        #     print('红色块1', green_list[0], green_list[1])
        #     print('红色块2', green_list[2], green_list[3])
        #     print('红色块3', green_list[4], green_list[5])
    return white_list

def yellow_point_video(frame):
    kernel_2 = np.ones((2, 2), np.uint8)  # 2x2的卷积核
    kernel_3 = np.ones((3, 3), np.uint8)  # 3x3的卷积核
    kernel_4 = np.ones((4, 4), np.uint8)  # 4x4的卷积核
    kernel_8 = np.ones((8, 8), np.uint8)
    Lower_red = np.array([156, 128, 46])
    Upper_red = np.array([180, 255, 255])
    red = [Lower_red, Upper_red, 'red']
    Lower_white = np.array([0, 0, 200])  # 221
    Upper_white = np.array([180, 30, 255])
    white = [Lower_white, Upper_white, 'white']
    Lower_black = np.array([0, 0, 0])
    Upper_black = np.array([180, 255, 46])
    black = [Lower_black, Upper_black, 'black']
    Lower_green = np.array([35, 95, 46])
    Upper_green = np.array([70, 255, 255])
    green = [Lower_green, Upper_green, 'green']
    Lower_yellow = np.array([26, 43, 46])
    Upper_yellow = np.array([34, 255, 255])
    #Lower_yellow = np.array([20, 30, 30])
    #Upper_yellow = np.array([70, 255, 255])
    yellow = [Lower_yellow, Upper_yellow, 'yellow']
    HSV = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)  # 把BGR图像转换为HSV格式
    color = yellow
    if color[2] == 'yellow':
        mask_yellow = cv2.inRange(HSV, color[0], color[1])
        erosion = cv2.erode(mask_yellow, kernel_2, iterations=1)
        erosion = cv2.erode(erosion, kernel_4, iterations=1)
        erosion = cv2.erode(erosion, kernel_4, iterations=1)
        dilation = cv2.dilate(erosion, kernel_2, iterations=1)
        dilation = cv2.dilate(dilation, kernel_4, iterations=1)
        dilation = cv2.dilate(dilation, kernel_8, iterations=1)
        yellow, binary = cv2.threshold(dilation, 127, 255, cv2.THRESH_BINARY)  # 二值化，将滤波后的图像变成二值图像放在binary中
        cnts = cv2.findContours(binary.copy(), cv2.RETR_EXTERNAL,
                                cv2.CHAIN_APPROX_SIMPLE)
        cnts = imutils.grab_contours(cnts)  # 寻找轮廓
        yellow_list = []
        for c in cnts:
            # compute the center of the contour
            M0 = cv2.moments(c)
            cv2.drawContours(frame, [c], -1, (0, 255, 0), 2)
            car_video_location = [int(M0["m10"] / M0["m00"]), int(M0["m01"] / M0["m00"])]
            cv2.circle(frame, (car_video_location[0], car_video_location[1]), 7, (0, 255, 0), -1)
            cv2.putText(frame, "yellow", (car_video_location[0] - 20, car_video_location[1] - 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            cv2.imshow("Image", frame)
            print('坐标',(car_video_location[0], car_video_location[1]))
            green_point = [int(M0["m10"] / M0["m00"]), int(M0["m01"] / M0["m00"])]
        #   green_list = green_list + green_point
        # if len(green_list) == 6:  # 起始可能识别不到3个红色块，等都识别到，再输出坐标
        #     print('红色块1', green_list[0], green_list[1])
        #     print('红色块2', green_list[2], green_list[3])
        #     print('红色块3', green_list[4], green_list[5])
    return yellow_list
 
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

def port_close():
    ser.close()
    if(ser.isOpen()):
        print("串口关闭失败！")
    else:
        print("串口关闭成功！")
def send_site(x,y)
    if x>78 and x<88 and y<125 and y>115:   #不动
        ser.write(bytes(9))
    elif x>88 and y>125:                    #左下
        ser.write(bytes(1))
    elif x<78 and y>125:                    #右下
        ser.write(bytes(2))
    elif x<78 and y<115:                    #右上
        ser.write(bytes(3))
    elif x>88 and y<115:                    #左上
        ser.write(byte(4))
    elif x>78 and x<88 and y>125:           #向下
        ser.write(bytes(5))
    elif x>78 and x<88 and y<115:           #向上
        ser.write(bytes(6))
    elif x>88 and y<125 and y>115:          #向左
        ser.write(bytes(7))
    elif x<78 and y<125 and y>115:          #向右
        ser.write(bytes(8))         
    
def send(send_data):
    if(ser.isOpen()):
        ser.write(send_data.encode('utf-8'))
        print("发送成功",send_data)
    else:
        print("发送失败！")

if __name__ == "__main__":
    print("going to open serial")
    port_close()
    port_open_recv()
    ser.read(1)
    cap = cv2.VideoCapture(0)
    while True:
        ret, sframe = cap.read()
        #white_video_point = white_point_video(sframe)  #  白色点在视频中的坐标，并在输出标记
        yellow_video_point = yellow_point_video(sframe)
        cv2.imshow("Image", sframe)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        cv2.waitKey(300)  # 延时30ms