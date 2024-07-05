from  threading import Thread
#import time

def func(name):
    for i in range(10000000 // 2):
        pass

def main():

    t1 = Thread(target=func, args=("t1", ))
    t2 = Thread(target=func, args=("t2", ))

 #   start = time.perf_counter()

    t1.start()
    t2.start()

    t1.join()
    t2.join()

  #  end = time.perf_counter()

   # print(t1._return, t2._return)
    #print((end - start))


if __name__ == "__main__":
    main()