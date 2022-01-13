import zmq
import sys

if __name__ == '__main__':
    check_time = 10
    n = len(sys.argv)

    for i in sys.argv[1:]:
        print(i)
    
    context = zmq.Context()
    socket = context.socket(zmq.REQ)
    socket.connect("tcp://192.168.0.2:17688")
    try:
        socket.send(i.encode(), zmq.NOBLOCK)
        message = socket.recv()
        print("recv %s" % message)
        str_message = message.decode()
        check_time = int(str_message.split(",")[1])
    except:
        print("except")
        check_time = 10

    sys.exit(check_time)
