
Git Workflow and Best Practices for the AI

The following rules dictate how the AI must manage version control, branching, commits, and pushes during the development of this project.

## 1. Branching Strategy
* **Protected Branch:** The `main`  branch is reserved for stable, fully tested releases. Do NOT make direct commits to `main`.
* **Feature Branches:** Create a new branch for each individual Issue or specific component. 
  * Naming convention: `feature/issue-<number>-<short-description>` (e.g., `feature/issue-1.1-process-structs`, `feature/issue-2.1-fifo-scheduler`).
  * Once a task is finished and verified, merge the feature branch into `main` clean and sequentially.

## 2. Granular Commit Frequency
* Do NOT bundle large chunks of code or multiple issues into a single commit.
* Make a commit every time a small, atomic unit of work is completed. For example:
    * After defining a new struct or enum.
    * After fully implementing a single function or helper method (e.g., after completing just `push()` for the stack).
    * After fixing a specific bug or resolving a compiler warning.

## 3. Commit Message Rules
* Use clear, concise, and descriptive commit messages following the **Conventional Commits** standard in lowercase (matching the commentary rules).
* Formats to use:
  * `feat: add process struct and state enum`
  * `feat: implement fifo queue push function`
  * `fix: resolve memory leak in coalescence loop`
  * `docs: add complexity analysis for round robin`

## 4. Push Synchronization
* Perform a `git push origin <branch-name>` immediately after making a local commit or completing a group of interrelated methods that form a milestone.
* This ensures that progress is consistently synced with the remote repository.

## Visual Summary of Workflow

```text
[main] ───────────────────────────────────────────────► (Stable Code)
         \                                         /
          └───► [feature/issue-1.1-structs] ──────┘ (Merge after tests)
                  ├── commit & push: feat: add process struct
                  └── commit & push: feat: add memory block struct


