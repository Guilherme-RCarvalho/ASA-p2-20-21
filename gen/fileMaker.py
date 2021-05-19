import time
# from multiprocessing import Process
import threading


import os
# import threading

mutex = threading.Lock()
nodeList = [x for x in range(5)]

def thread_function(name):
    while(len(nodeList) != 0):
        mutex.acquire()
        nodeAmount = nodeList.pop(0)
        mutex.release()

        print(f"Starting with: {nodeAmount}", end="")
        percentList = [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7]


        for percent in percentList:
            os.system(f"./randomDAG {nodeAmount} {percent} > percent/{nodeAmount}-{percent}.in")
        

        print(" --> Finished")
    



# for node in nodeList:
#     print(f"Starting with: {node}", end="")
#     for percent in percentList:

#         os.system(f"./randomDAG {node} {percent} > inputs/{node}-{percent}.in")
#     print(" --> Finished")


# if __name__ == "__main__":

#     format = "%(asctime)s: %(message)s"
#     logging.basicConfig(format=format, level=logging.INFO,
#                         datefmt="%H:%M:%S")

#     with concurrent.futures.ThreadPoolExecutor(max_workers=15) as executor:
#         executor.map(thread_function, nodeList)

# if __name__ == '__main__':
#     p = Process(target=f, args=('bob',))
#     p.start()
#     p.join()

if __name__ == "__main__":
    threadList = []
    
    # Create threads
    for x in range(1):
        threadList.append(threading.Thread(target=thread_function, args=(1,)))
    for x in threadList:
        x.start()
    for x in threadList:
        x.join()

    print("All done")