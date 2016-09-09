# coding: utf-8
import socket
import struct
import logging

def send_msg(sock, msg):
    msg = struct.pack('>I', len(msg)) + msg
    while msg:
        sent = sock.send(msg)
        msg  = msg[sent:]
    return True


def recv_msg(sock):
    header = recv_all(sock, 4)
    if not header:
        return None
    msglen = struct.unpack('>I', header)[0]
    return recv_all(sock, msglen)


def recv_all(sock, n):
    data = ''
    while len(data) < n:
        packet = sock.recv(n - len(data))
        if not packet:
            return None
        data += packet
    return data
