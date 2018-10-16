import random
import os

def rand_list(filename, size, deg_size, num_range, den_range, deg_range):
    try:
        os.remove(filename)
    except OSError:
        pass
    
    f = open(filename, "a")
    stracc = ""
    f.write(str(deg_size)+"\n")
    for i in range(0, size):
        num = random.randint(1, num_range)
        den = random.randint(1, den_range)
        stracc = str(num) + "," + str(den)
        for i in range(0, deg_size):
            d1 = random.randint(1, deg_range)
            stracc = stracc + "," + str(d1)
               
        f.write(stracc)
        f.write("\n")
        stracc = ""
    f.close()


if __name__ == "__main__":
    # rand_list("list10.csv",  10, 3, 200000, 100000, 16000)
    # rand_list("list100.csv",  100, 3, 200000, 100000, 16000)
    # rand_list("list1k.csv", 1000, 3, 200000, 100000, 16000)
    # rand_list("list2k.csv", 2000, 3, 200000, 100000, 16000)
    # rand_list("list7k.csv",  7000, 3, 200000, 100000, 16000)
    # rand_list("list10k.csv", 10000, 3, 200000, 100000, 16000)
    # rand_list("list30k.csv", 30000, 3, 500000, 600000, 16000)
    # rand_list("list100k.csv", 100000, 3, 200000, 400000, 44000)
    # rand_list("list200k.csv", 200000, 3, 500000, 600000, 44000)
    # rand_list("list300k.csv", 300000, 3, 200000, 400000, 44000)
    # rand_list("list400k.csv", 400000, 3, 500000, 600000, 44000)
    # rand_list("list500k.csv", 500000, 3, 500000, 600000, 44000)
    # rand_list("list600k.csv", 600000, 3, 200000, 400000, 44000)
    # rand_list("list700k.csv", 700000, 3, 500000, 600000, 44000)
    # rand_list("list1000k.csv", 1000000, 3, 1000000, 400000, 74000)
    # rand_list("list2000k.csv", 2000000, 3, 2000000, 600000, 100000)
    # rand_list("list5000k.csv", 5000000, 3, 2000000, 600000, 100000)
    # rand_list("list8000k.csv", 8000000, 3, 2000000, 600000, 100000)
    # rand_list("list10000k.csv", 10000000, 3, 2000000, 600000, 100000)
    # rand_list("list15000k.csv", 15000000, 3, 2000000, 600000, 100000)
    # rand_list("list20000k.csv", 20000000, 3, 4000000, 800000, 300000)
    # rand_list("list25000k.csv", 25000000, 3, 4000000, 800000, 300000)
    # rand_list("list30000k.csv", 30000000, 3, 4000000, 800000, 300000)
    rand_list("list45000k.csv", 45000000, 3, 4000000, 800000, 300000)