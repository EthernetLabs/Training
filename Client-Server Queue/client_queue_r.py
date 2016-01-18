#!/usr/bin/python
from multiprocessing import Process, Queue
import server_queue

def get_queue(q):
    size = q.qsize()
    print size
    for i in xrange (0,size):
        print q.get()

 
que = server_queue.qu
print que.qsize()
get_queue(que)

