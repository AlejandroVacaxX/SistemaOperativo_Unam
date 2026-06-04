# issues.md

## Phase 1: Base Data Structures (C)
- [ ] **Issue 1.1:** Define `enum` and `struct` for `Process` (`pid`, `burst_time`, `remaining_time`, `priority`, `memory_required`, `state`)[cite: 1].
- [ ] **Issue 1.2:** Define the bidirectional `MemoryBlock` struct (`start`, `size`, `free`, `pid`, `next`, `prev`)[cite: 1].
- [ ] **Issue 1.3:** Implement required supporting structures: Stack (history/backtracking)[cite: 1], Queue (FIFO)[cite: 1], Circular Queue (Round Robin)[cite: 1], and Linked List (finished processes)[cite: 1].

## Phase 2: Schedulers (C)
- [ ] **Issue 2.1:** Implement the **FIFO** scheduler using the Queue structure[cite: 1].
- [ ] **Issue 2.2:** Implement the **Round Robin** scheduler using the Circular Queue and Quantum interruption logic[cite: 1].
- [ ] **Issue 2.3:** Implement the **Shortest Job First (SJF)** scheduler using a Greedy approach[cite: 1].

## Phase 3: Memory Manager (C)
- [ ] **Issue 3.1:** Implement main memory initialization along with allocation and deallocation functions[cite: 1].
- [ ] **Issue 3.2:** Implement logic to detect memory fragmentation[cite: 1].
- [ ] **Issue 3.3:** Develop the **Coalescence** algorithm to automatically combine adjacent free blocks using the Doubly Linked List[cite: 1].
- [ ] **Issue 3.4:** Implement Greedy allocation strategies: **First Fit**, **Best Fit**, and **Worst Fit**[cite: 1].
- [ ] **Issue 3.5:** Implement Brute Force exhaustive search for memory holes[cite: 1].
- [ ] **Issue 3.6:** Implement Divide and Conquer for memory compaction/reorganization[cite: 1].
- [ ] **Issue 3.7:** Implement Backtracking for memory state recovery[cite: 1].

## Phase 4: Integration & Benchmarking (Python + C)
- [ ] **Issue 4.1:** Create a Python script dedicated to test generation, producing diverse random process batches (varying PID, burst_time, priority, and memory_required) saved into `input.csv`.
- [ ] **Issue 4.2:** Develop a CSV parser in C to read `input.csv` and successfully load those test processes into the active simulation.
- [ ] **Issue 4.3:** Modify the C codebase to export comprehensive performance metrics (turnaround times, waiting times, memory utilization overhead) into `output.csv`.
- [ ] **Issue 4.4:** Create an automation and orchestrator script in Python using `subprocess` to manage the end-to-end test pipeline (Input Generation -> C Execution -> Output Export).
- [ ] **Issue 4.5:** Develop experimental data analysis and visualization in Python using `pandas` and `matplotlib`/`seaborn` to plot the benchmark graphs.


## Phase 5: Mathematical Documentation (Markdown)
- [ ] **Issue 5.1:** Write the time and space complexity analysis for each Scheduler[cite: 1].
- [ ] **Issue 5.2:** Write the complexity analysis and solve mathematical recurrences (using Master Theorem or Recurrence Trees) for the memory algorithms[cite: 1].