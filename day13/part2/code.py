import sys
import re

sys.setrecursionlimit(10**6)

def solve(ax, ay, bx, by, px, py):
    large_value = 10000000000000
    best_solution = None

    # Try all combinations of button presses
    for pressA in range(600):
        for pressB in range(600):
            cost = 3 * pressA + pressB
            dx = ax * pressA + bx * pressB
            dy = ay * pressA + by * pressB

            # Check if the claw is aligned (dx == dy) and the value is positive
            if dx == dy and dx > 0:
                score = dx / cost
                if best_solution is None or score < best_solution[0]:
                    best_solution = (score, pressA, pressB, cost, dx)

    if best_solution is None:
        return 0

    _, pressA, pressB, cost, dx = best_solution
    amt = (large_value - 40000) // dx

    # Use an iterative approach to minimize cost to reach (0, 0)
    def min_cost_to_origin(x, y):
        stack = [(x, y, 0)]
        visited = set()

        while stack:
            cur_x, cur_y, cur_cost = stack.pop()

            if (cur_x, cur_y) == (0, 0):
                return cur_cost

            if (cur_x, cur_y) in visited:
                continue
            visited.add((cur_x, cur_y))

            # Move the claw in two possible directions (A or B)
            if cur_x >= ax:
                stack.append((cur_x - ax, cur_y - ay, cur_cost + 3))
            if cur_y >= by:
                stack.append((cur_x - bx, cur_y - by, cur_cost + 1))

        return 10**20  # Return a large value if no solution is found

    # Compute minimal cost to the origin for the adjusted prize coordinates
    ans = min_cost_to_origin(px + large_value - amt * dx, py + large_value - amt * dx)
    if ans < 10**15:
        return ans + amt * cost
    else:
        return 0


def solve_part2():
    total_score = 0

    with open('input.txt') as f:
        # Process each machine's data
        for machine in f.read().strip().split('\n\n'):
            lines = machine.split('\n')

            # Parse Button A, B, and Prize details
            ax, ay = map(int, re.findall(r'\+(-?\d+)', lines[0])[:2])
            bx, by = map(int, re.findall(r'\+(-?\d+)', lines[1])[:2])
            px, py = map(int, re.findall(r'X=(\d+), Y=(\d+)', lines[2])[0])

            total_score += solve(ax, ay, bx, by, px, py)

    return total_score

def main():
    total_score = solve_part2()
    print(total_score)

if __name__ == "__main__":
    main()
