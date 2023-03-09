import random
import sys

def main():
    num_nums = int(sys.argv[1])
    terrains = ['f','g','G','h','m','r']

    f = open(f"{num_nums}x{num_nums}_random_map.txt", "w" )
    line = f"6\nf 3\ng 1\nG 2\nh 4\nm 7\nr 5\n{num_nums} {num_nums}\n"
    f.write(line)

    for i in range(num_nums):
        line = ""
        for j in range(num_nums):
            line += random.choice(terrains)
        line += "\n"
        f.write(line)
    line = (f"0 0\n{num_nums-1} {num_nums-1}\n")
    f.write(line)

    f.close()

if __name__ == "__main__":
    main()