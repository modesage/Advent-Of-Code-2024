import re
from concurrent.futures import ThreadPoolExecutor

def ints(s):
    """Extract integers from a string."""
    return [int(x) for x in re.findall(r'-?\d+', s)]

def parse_input(file_path):
    """Parse the input file to get register values and program."""
    with open(file_path) as f:
        regs, program = f.read().strip().split("\n\n")
    A, B, C = ints(regs)
    program = [int(x) for x in program.split(":")[1].split(",")]
    return A, B, C, program

def run_program(initial_A, program, part2=False):
    """Simulate the program execution."""
    A, B, C = initial_A, 0, 0
    ip = 0  # Instruction pointer
    out = []  # Output list

    POW2 = [1 << i for i in range(8)]  # Precompute 2^i for i=0..7

    while ip < len(program):
        cmd = program[ip]
        op = program[ip + 1]

        if op <= 3:
            combo = op
        elif op == 4:
            combo = A
        elif op == 5:
            combo = B
        elif op == 6:
            combo = C
        else:
            combo = -1

        if cmd == 0:  # adv: Division, result in A
            A //= POW2[combo]
        elif cmd == 1:  # bxl: B XOR literal operand
            B ^= op
        elif cmd == 2:  # bst: Set B to combo % 8
            B = combo % 8
        elif cmd == 3:  # jnz: Jump if A != 0
            if A != 0:
                ip = op
                continue
        elif cmd == 4:  # bxc: B XOR C
            B ^= C
        elif cmd == 5:  # out: Output combo % 8
            value = combo % 8
            out.append(value)
            if part2 and len(out) > len(program):
                return out  # Exit early if output size exceeds program
            if part2 and value != program[len(out) - 1]:
                return out  # Exit early on mismatch
        elif cmd == 6:  # bdv: Division, result in B
            B = A // POW2[combo]
        elif cmd == 7:  # cdv: Division, result in C
            C = A // POW2[combo]

        ip += 2

    return out

def part_two_search_parallel(program):
    """Parallel search for the lowest positive A that outputs the program."""
    def search_range(start):
        """Search a range of Ast values."""
        for Ast in range(start, start + 1000000):  # Chunk size of 1,000,000
            A = (Ast << 27) + 0o676236017  # Optimize for bitwise left shift
            out = run_program(A, program, part2=True)
            if len(out) == len(program) and out == program:
                return A
        return None

    with ThreadPoolExecutor() as executor:
        # Submit tasks with ranges of 1,000,000 Ast values
        futures = [executor.submit(search_range, i) for i in range(1, 1_000_000_000, 1000000)]
        for future in futures:
            result = future.result()
            if result is not None:
                return result

def main():
    A, B, C, program = parse_input("input.txt")

    # Part One
    part1_output = run_program(A, program)
    print("Part 1 Output:", ','.join(map(str, part1_output)))

    # Part Two
    result_A = part_two_search_parallel(program)
    print("Part 2 Lowest Initial A:", result_A)

if __name__ == "__main__":
    main()
