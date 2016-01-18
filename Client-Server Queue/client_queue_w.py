#!/usr/bin/python
from multiprocessing import Process, Queue
import server_queue 

add = ['Billu','Rana','Asif', 'Fan-4']

def add_frndz(q):
    for name in add:
        q.put(name)

qu = server_queue.qu
add_frndz(qu)

print qu.qsize()






