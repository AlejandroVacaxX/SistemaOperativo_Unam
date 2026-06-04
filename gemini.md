# gemini_cli_context.md

## Global Project Context
You are an expert AI programming assistant specializing in C and Python. You are helping develop a final proyect[cite: 1]. The goal is to build an **Operating System Simulator**[cite: 1].

## System Architecture
The project requires a strict integration between C and Python[cite: 1]:
* **C Language:** Will handle all heavy logic, simulations, data structures, memory management, and scheduling algorithms[cite: 1].
* **Python Language:** Will be used for generating test data (random processes), executing the C program via `subprocess`, capturing results, and generating benchmarking graphs using `pandas` and `matplotlib`/`seaborn`[cite: 1].
* **Communication Bridge:** File-based exchange using `.csv`. Python writes the inputs, C processes them and writes the outputs, and Python reads the outputs for data analysis.

## Main Modules (C Logic)
1. **Process Management:** Simulating tasks with states (`READY`, `RUNNING`, `BLOCKED`, `FINISHED`)[cite: 1], managing an execution history using Stacks[cite: 1], and storing finished processes in a Linked List ordered by PID[cite: 1].
2. **Schedulers:** Implementing FIFO (Queue)[cite: 1], Round Robin (Circular Queue with Quantum interruption)[cite: 1], and Shortest Job First (SJF via Greedy approach)[cite: 1].
3. **Memory Management:** Simulated using dynamic blocks within a Doubly Linked List for bidirectional navigation[cite: 1]. Includes allocation, deallocation, fragmentation detection, and block coalescence[cite: 1].
4. **Algorithmic Strategies:** Implementation of Brute Force (hole searching)[cite: 1], Greedy (First/Best/Worst Fit)[cite: 1], Backtracking (state recovery)[cite: 1], and Divide and Conquer (memory compaction/reorganization)[cite: 1].

## Critical Rules for the AI
* Keep the code highly modular, clean, and well-commented.
* Document the complexity analysis (Big O) for every critical algorithm generated[cite: 1].
* Keep in mind that all interactions, prompts, and corrections must be documented for an "AI Logbook"[cite: 1].