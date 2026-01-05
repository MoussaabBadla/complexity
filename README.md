# Advanced Algorithms and Complexity - Master 1 IL

- **University:** USTHB - Faculty of Computer Science
- **Module:** Advanced Algorithms and Complexity
- **Student:** Badla Moussaab 
- **Academic Year:** 2025-2026

---

## Project Structure

```
project/
├── Sorting-algorithms-main/    # Mini-Project: Sorting Algorithms
│   ├── src/                    # Algorithm implementations
│   ├── graphs/                 # Performance graphs
│   ├── REPORT.md              # Markdown report
│   └── REPORT.pdf             # PDF report
│
└── tp/                         # Lab Work (TP 1-5)
    ├── lab-1/                  # Primality Test
    ├── lab-2/                  # Selection Sort
    ├── lab-3/                  # Search Algorithms
    ├── lab-4/                  # Polynomial Complexity
    └── lab-5/                  # Iterative vs Recursive
```

---

## Mini-Project: Sorting Algorithms

### Description
Implementation and comparative analysis of **7 sorting algorithms** in C:

| Algorithm | Time Complexity | Space | Type |
|-----------|-----------------|-------|------|
| Bubble Sort | O(n²) | O(1) | Comparison |
| Bubble Sort Optimized | O(n) - O(n²) | O(1) | Comparison |
| Gnome Sort | O(n) - O(n²) | O(1) | Comparison |
| Quick Sort (Hoare) | O(n log n) - O(n²) | O(log n) | Comparison |
| Heap Sort | O(n log n) | O(1) | Comparison |
| Radix Sort (LSD) | O(d×n) | O(n) | Non-comparison |
| Bucket Sort | O(n) - O(n²) | O(n) | Distribution |

### Key Features
- Hoare partition scheme for Quick Sort
- `key(x, i)` function for Radix Sort
- Linked-list buckets for Bucket Sort
- CSV export for benchmark data
- Best/Worst/Random case testing

### Location
`Sorting-algorithms-main/`

---

## Lab Work (TP)

### Lab 1: Primality Test
**Objective:** Compare 4 primality testing algorithms

| Algorithm | Complexity | Optimization |
|-----------|------------|--------------|
| A1 - Naive | O(N) | None |
| A2 - N/2 | O(N/2) | Skip upper half |
| A3 - √N | O(√N) | Square root limit |
| A4 - Odd only | O(√N/2) | Skip even divisors |

**Location:** `tp/lab-1/`

---

### Lab 2: Selection Sort
**Objective:** Experimental study of Selection Sort

- **Time Complexity:** O(n²) in all cases
- **Space Complexity:** O(1)
- **Test Cases:** Sorted, Random, Reverse

**Location:** `tp/lab-2/`

---

### Lab 3: Search Algorithms
**Objective:** Compare search algorithms and MaxMin implementations

**Part A - Element Search:**
| Algorithm | Best | Worst |
|-----------|------|-------|
| Linear (Unsorted) | O(1) | O(n) |
| Linear (Sorted) | O(1) | O(n) |
| Binary Search | O(1) | O(log n) |

**Part B - MaxMin:**
| Algorithm | Comparisons |
|-----------|-------------|
| MaxMinA (Naive) | 2(n-1) |
| MaxMinB (Efficient) | ~3n/2 |

**Location:** `tp/lab-3/`

---

### Lab 4: Polynomial Complexity
**Objective:** Study O(n³) algorithms

**Exercise 1 - Matrix Multiplication:**
- C(n,p) = A(n,m) × B(m,p)
- Complexity: O(n×m×p), O(n³) for square

**Exercise 2 - Submatrix Search:**
- subMat1: Naive O(n×m×n'×m')
- subMat2: Optimized with early termination

**Location:** `tp/lab-4/`

---

### Lab 5: Iterative vs Recursive
**Objective:** Compare recursive and iterative approaches

**Exercise 1 - Tower of Hanoi:**
- Moves: 2ⁿ - 1
- Complexity: O(2ⁿ)

**Exercise 2 - Fibonacci:**
| Version | Time | Space |
|---------|------|-------|
| Recursive | O(2ⁿ) | O(n) |
| Iterative | O(n) | O(1) |

**Location:** `tp/lab-5/`

---

## How to Build and Run

### Compile C Programs
```bash
# Lab 1
cd tp/lab-1/src && gcc -O2 -o primality primality.c -lm

# Lab 2
cd tp/lab-2/src && gcc -O2 -o selection_sort selection_sort.c

# Lab 3
cd tp/lab-3/src && gcc -O2 -o search search.c

# Lab 4
cd tp/lab-4/src && gcc -O2 -o matrix matrix.c

# Lab 5
cd tp/lab-5/src && gcc -O2 -o iterative_recursive iterative_recursive.c -lm
```

### Run Benchmarks
```bash
./program_name          # Normal output
./program_name -csv     # CSV output for graphing
```

### Generate Graphs
```bash
cd tp
python3 -m venv venv
source venv/bin/activate
pip install pandas matplotlib
python3 generate_all_graphs.py
```

### Convert Reports to PDF
```bash
pip install weasyprint markdown
python3 convert_all_to_pdf.py
```

---

## Reports

Each lab contains:
- `REPORT.md` - Markdown source
- `REPORT.pdf` - PDF document
- `graphs/` - PNG visualizations
- `src/` - C source code

---

## Summary of Complexities

| Problem | Best Algorithm | Complexity |
|---------|----------------|------------|
| Primality Test | A4 (odd+√N) | O(√N/2) |
| Sorting (general) | Heap Sort | O(n log n) |
| Sorting (integers) | Radix Sort | O(d×n) |
| Search (sorted) | Binary Search | O(log n) |
| MaxMin | Efficient (pairs) | ~3n/2 |
| Matrix Multiply | Standard | O(n³) |

---

## Key Learnings

1. **Optimization matters:** A4 vs A1 for primality shows √N improvement
2. **Algorithm choice depends on data:** Radix Sort beats comparison sorts for integers
3. **Recursion has costs:** Fibonacci recursive is exponentially slower
4. **Theoretical matches experimental:** All benchmarks confirm Big-O predictions

---

*Master 1 IL - Advanced Algorithms and Complexity - 2025-2026*
