# Professional CUDA — crash-course review

**Ten review units, one per book chapter.** Read the core idea, derive the short pattern, then revisit one focused code snapshot. Detailed reading coverage remains in the roadmap; old micro-lessons remain in Git history.

| Unit | Core question | Printed pages |
|---|---|---|
| [1. CPU/GPU foundations](chapter-01-foundations.md) | Independent data work can run in parallel; CPU and GPU cooperate through an explicit data and completion contract. | 1–22 |
| [2. Programming model and indexing](chapter-02-programming-model.md) | Derive data ownership, legal launch geometry, bounds, memory lifetimes, and completion before tuning anything. | 23–65 |
| [3. Execution, occupancy, and reduction](chapter-03-execution-and-reduction.md) | Warps and resources determine execution opportunities; synchronization and ownership determine whether a reduction is valid. | 67–133 |
| [4. Global memory and data layout](chapter-04-global-memory.md) | Performance depends on lane addresses, reuse, and traffic at each memory level—not merely on allocation or pointer syntax. | 135–202 |
| [5. Shared memory, constants, and shuffles](chapter-05-shared-memory-and-communication.md) | Use explicit communication only when its reuse or layout benefit compensates for barriers, resources, and extra instructions. | 203–266 |
| [6. Streams, events, and pipelines](chapter-06-streams-and-concurrency.md) | Dependencies define correctness; streams permit overlap, but only a timeline and whole-pipeline evidence can establish it. | 267–298 |
| [7. Instructions, numerical behavior, and atomics](chapter-07-instructions-and-numerics.md) | A valid optimization meets numerical and ordering requirements before instruction count or utilization becomes useful evidence. | 299–325 |
| [8. CUDA libraries and OpenACC](chapter-08-libraries-and-openacc.md) | Use supported library/data-layout contracts and compare equal numerical tasks; toolchain support determines whether directives actually offload. | 327–386 |
| [9. Multi-GPU ownership and MPI](chapter-09-multi-gpu-and-mpi.md) | Partitioning, communication permissions, and transport completion are separate contracts; local simulation cannot validate remote hardware. | 387–424 |
| [10. Implementation workflow and final review](chapter-10-implementation-and-review.md) | Use assessment, correctness, measured hypotheses, and reproducible deployment to turn a kernel into a defensible implementation. | 425–476 |

## How to use this as a crash course

1. Read one chapter's core idea and concept table.
2. Derive the pattern on a tiny input, then read one snapshot's actual source.
3. Open the chapter profiling checklist and ask one concrete measurement question.
4. Answer the three review questions before moving on.

Use [CURRENT](../CURRENT.md) for the present source snapshot. Keep the
[full roadmap](cuda-learning-path.md) for every original heading and the
[coverage record](remaining-chapters-coverage.md) for unfinished work. Historical
micro-lesson numbers in that record identify Git snapshots, not 77 required review sessions.

Source convention: simple main, separate functional kernel files, concise relevant
PTX annotations next to implementation, no automatic profiler captures. Only current
lesson source is retained; old code stays in Git history.
