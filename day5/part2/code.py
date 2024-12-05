import sys
from collections import defaultdict, deque

def print_value(value):
    print(value)

sys.setrecursionlimit(10**6)

# Input file handling
input_file = sys.argv[1] if len(sys.argv) >= 2 else 'input.txt'

# Read the entire input data from the file and strip leading/trailing whitespace
input_data = open(input_file).read().strip()

# Split the input data into edges and queries parts
edges_data, queries_data = input_data.split('\n\n')

# `predecessors` holds the set of pages that must come before a given page
# `successors` holds the set of pages that must come after a given page
predecessors = defaultdict(set)
successors = defaultdict(set)

# Parse edge relationships (x -> y means x must come before y)
for line in edges_data.split('\n'):
    x, y = line.split('|')
    x, y = int(x), int(y)
    predecessors[y].add(x)
    successors[x].add(y)

# Initialize result for part 2
result2 = 0

# Process each query for part 2 (incorrectly ordered pages)
for query in queries_data.split('\n'):
    pages = [int(page) for page in query.split(',')]
    
    # Check for any forbidden edges (cycles) between the pages
    # Build a dependency graph and track in-degrees (dependencies) of each page
    page_dependencies = defaultdict(int)
    is_valid_query = True
    for i, x in enumerate(pages):
        for j, y in enumerate(pages):
            if i < j and y in predecessors[x]:
                is_valid_query = False
                break
        if not is_valid_query:
            break

    if not is_valid_query:
        # Topological sort approach (Kahn's Algorithm) to reorder pages
        processed_pages = []
        queue = deque()
        
        # Track the number of incoming dependencies for each page
        page_in_degree = {page: 0 for page in pages}
        
        # Initialize the queue with pages that have no incoming dependencies (in-degree 0)
        for page in pages:
            for predecessor in predecessors[page]:
                if predecessor in pages:
                    page_in_degree[page] += 1
            if page_in_degree[page] == 0:
                queue.append(page)
        
        # Process the pages in the queue
        while queue:
            current_page = queue.popleft()
            processed_pages.append(current_page)
            
            # For each successor of the current page, reduce its dependency count
            for successor in successors[current_page]:
                if successor in page_in_degree:
                    page_in_degree[successor] -= 1
                    if page_in_degree[successor] == 0:
                        queue.append(successor)
        
        # Add the median page from the successfully processed pages to result2
        if processed_pages:
            result2 += processed_pages[len(processed_pages) // 2]

# Output the result for part 2
print_value(result2)
