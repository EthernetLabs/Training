from multiprocessing import Process, Queue
frnd_list = ['ali', 'akbar','jamil','munir','zaheer','saim','malik']

def frndz_queue(q):
    for name in frnd_list:
        q.put(name)


def get_queue(q):
    size = q.qsize()
    print size
    for i in xrange (0,size):
        print q.get()
        
    
if __name__ == '__main__':
    qu = Queue()
    frndz_queue(qu)
    get_queue(qu)

    
    
