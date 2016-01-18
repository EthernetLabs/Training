#!/usr/bin/python
from multiprocessing import Process, Queue


frnd_list = ['ali', 'akbar','jamil','munir','zaheer','saim','malik']

def frndz_queue(q):
    for name in frnd_list:
        q.put(name)

qu = Queue()
frndz_queue(qu)
print qu.qsize()

