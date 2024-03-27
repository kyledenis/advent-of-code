import re
import math

with open('day03-input.txt') as file: # Update input file directory accordingly
    puzzle_input = file.read()

lines = puzzle_input.split('\n')
regex_gear = '\*'
regex_num = '\d+'
gears = {}
for row, line in enumerate(lines) :
    for sym in re.finditer(regex_gear, line):
        col = sym.start()
        gears[(row, col)] = []
for row, line in enumerate(lines):
    for num in re.finditer(regex_num, line):
        for r in range(row-1, row+2):
            for c in range(num.start()-1, num.end()+1):
                if (r, c) in gears:
                    gears[(r, c)].append(int(num.group()))
total = 0
for g, nums in gears.items():
    if len(nums) == 2:
        total += math.prod(nums)
for g, nums in gears.items():
    if len(nums) == 2:
        print(f"Valid gear pair at position {g}: {nums}")
print(total)