import os
import random

nodes = 5

os.system(f"./generate 5 5 > input2.in")


for x in range(100):
    os.system(f"./generate {random.randint(6, 10)} {1000} {random.seed(10)}")
    print()



os.system(f"./generate 5 5 > input1.in")
