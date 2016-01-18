from multiprocessing import Process
import time

def f1():
    print' P-1 Started'
    for i in xrange (0,10000):
        print 'NUM = %d\n' % i

    print  ' P-1 ENDED'

def f2():
    print 'P2 - Started'
    for i in xrange (10000,20000):
        print 'NUM = %d\n' % i

    print 'P2 - ENDED'

def without_multi_process():
    f1()
    f2()

def multi_process():
    
    p1 = Process(name ='Function - 1' , target=f1)
    p2 = Process(name ='Function - 2' , target=f2)
    p1.start()
    p2.start()
    p1.join()
    p2.join()
    

if __name__ == '__main__':
    _start = time.time()
    multi_process()
    _finish = time.time()
    t1 = _finish - _start

    _start = time.time()
    without_multi_process()
    _finish = time.time()
    t2 = _finish - _start
    
    print 'Time with multi_processes = %.8f seconds\n' % t1
    print 'Time without multi_processes = %.8f seconds\n' % t2
    
