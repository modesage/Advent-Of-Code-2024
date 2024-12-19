import sys
import re

sys.setrecursionlimit(10**6)

# Directions for up, right, down, left
DIRS = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def parse_ints(s):
    return [int(x) for x in re.findall('-?\d+', s)]

count_valid_designs = 0
total_ways = 0

# Reading input from file
data = open("input.txt").read().strip()

# Splitting the input into available words (patterns) and targets (designs)
patterns, designs = data.split('\n\n')
patterns = patterns.split(', ')

# Memoization dictionary for storing computed results
memo = {}

def count_ways(patterns, target):
    # If the target has already been computed, return the stored result
    if target in memo:
        return memo[target]
    
    # Initialize answer for this target
    ways = 0
    
    # If the target is empty, there is 1 way (using no patterns)
    if not target:
        ways = 1
    
    # Try matching each pattern at the start of the target
    for pattern in patterns:
        if target.startswith(pattern):
            ways += count_ways(patterns, target[len(pattern):])
    
    # Store the computed ways for the target
    memo[target] = ways
    return ways

# Loop through each design and calculate the number of ways to form it
for target in designs.split('\n'):
    ways_to_form_target = count_ways(patterns, target)
    
    # Increment the valid design counter if the design can be formed
    if ways_to_form_target > 0:
        count_valid_designs += 1
    
    # Add the number of ways to form this design to the total
    total_ways += ways_to_form_target

# Output the results
print(count_valid_designs)
print(total_ways)
