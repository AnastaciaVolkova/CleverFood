import socket

to_continue = True

import asyncio
import time
import threading


'''
def main():
    print("Server starts")
    tcp_ip = "192.168.2.117"
    tcp_port = 5005

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((tcp_ip, tcp_port))
    s.listen()
    conn, _ = s.accept()

    while to_continue:
        data = conn.recv(2**20)
        data_str = data.decode()
        mes = "Hello from server: " + data_str
        conn.send(mes.encode())

    conn.close()
'''


def server_run():
    global to_continue
    while to_continue:
        print("Server is running")
        time.sleep(1)


def user_input():
    global to_continue
    while to_continue:
        c = input("Enter q")
        if c == "q":
            to_continue = False
        time.sleep(1)


def main():
    #global to_continue
    task_1 = threading.Thread(target=server_run)
    task_2 = threading.Thread(target=user_input)
    task_1.start()
    task_2.start()
    task_1.join()
    task_2.join()


if __name__ == "__main__":
    main()
