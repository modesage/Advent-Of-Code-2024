import sys

sys.setrecursionlimit(10**6)

def solve(ax, ay, bx, by, prizeX, prizeY):
    min_cost = float('inf')

    # Try all combinations of button presses
    for pressA in range(101):
        for pressB in range(101):
            dx = ax * pressA + bx * pressB
            dy = ay * pressA + by * pressB
            cost = 3 * pressA + pressB

            # Check if the claw aligns with the prize
            if dx == prizeX and dy == prizeY:
                if cost < min_cost:
                    min_cost = cost

    if min_cost == float('inf'):
        return 0

    return min_cost

def solve_part1():
    with open('input.txt') as f:
        data = f.read().strip()

    total_score = 0

    # Split machines by blank lines
    machines = data.split('\n\n')

    for machine in machines:
        lines = machine.split('\n')

        # Parse Button A details
        ax = int(lines[0].split('+')[1].split(',')[0])
        ay = int(lines[0].split('+')[2])

        # Parse Button B details
        bx = int(lines[1].split('+')[1].split(',')[0])
        by = int(lines[1].split('+')[2])

        # Parse Prize details
        prizeX = int(lines[2].split('=')[1].split(',')[0])
        prizeY = int(lines[2].split('=')[2])

        total_score += solve(ax, ay, bx, by, prizeX, prizeY)

    return total_score

def main():
    total_score = solve_part1()
    print(total_score)

if __name__ == "__main__":
    main()
