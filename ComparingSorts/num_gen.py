import random
import sys

def main():
    num_nums = int(sys.argv[1])

    f = open(f"/tmp/{num_nums}_random_ints.txt", "w" )

    for i in range(num_nums):
        line = str(random.randint(-2147483648, 2147483647)) + "\n"
        f.write(line)

    f.close()

if __name__ == "__main__":
    main()
