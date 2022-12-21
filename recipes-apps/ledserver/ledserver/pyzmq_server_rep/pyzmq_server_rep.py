#!/usr/bin/python3
import zmq
import time
from datetime import datetime
import log_utils

log = log_utils.logging_init(__file__)

if __name__ == '__main__':
    log.debug("ready to pyzmq_server_rep")
    sock = zmq.Context().socket(zmq.REP)
    try:
        sock.bind("tcp://*:9527")
    except Exception as e:
        log.debug("bind error %s" % e)

    while True:
        req_message = sock.recv_string()
        # log.debug("req_message : %s" % req_message)
        now = datetime.now()
        dt_string = now.strftime("%d%m%Y %H%M%S")
        sock.send_string("server alive " + dt_string)
