import subprocess
import time
import os

end1 = 0
end2 = 0
end3 = 0

myFIle = open("results.txt", "w")

def runTest(file):
    start = time.time()
    os.system(f"./ze < tests/{file}")
    end = time.time()
    end1 = (end - start)
    print()
    start = time.time()
    os.system(f"./mario < tests/{file}")
    end = time.time()
    end2 = (end - start)

    # start = time.time()
    # os.system(f"./copy < inputs/{file}")
    # end = time.time()
    # end3 = (end - start)
    
    # print()
    print(f"Mario: {end2} Ze: {end1} ")
    myFIle.write(f"Mario: {end1}")

    # print()
    # print(f"Mario: {end1} :: Ze: {end2} :: Toste: {end3} :: {file}")
    # myFIle.write(f"Mario: {end1} :: Ze: {end2} :: Toste: {end3} :: {file}")
    myFIle.write("\n")
    myFIle.flush()

x = [file for file in os.listdir("tests")]
no = ["mega.in", "big.in", "medium.in"]
for file in x:
    # if(file not in no and int(file.split("-")[0]) < 200):
    #     runTest(file)
    print(file)


    runTest(file)
