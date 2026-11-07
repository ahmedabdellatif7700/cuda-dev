# Lesson 7 — Hello World from GPU: observation handout

Book: Chapter 1, Hello World from GPU; printed pp. 17–19. Roadmap ID 1.3.
See [lesson notes](../professional-cuda/lesson-07-hello-world-from-gpu.md).

## Focus

Capture `PrintGpuGreeting` if you want to inspect launch geometry: 1 block × 10 threads, one partial warp. Only thread 5 reaches printing. Device printf adds runtime work, so do not compare its duration with vector addition as an architecture ranking.

## Record

- Kernel or source path examined: pending user discussion.
- Relevant PTX beside the implementation: identify only this lesson's operations.
- Actual capture and settings: pending, if applicable.
- Prediction versus observation: pending user discussion.

Do not run profilers automatically. Preserve the user-controlled ncu-ui workflow.
Host work, copy completion, and printed ordering cannot be explained by an isolated
kernel duration. PTX describes intermediate operations, not measured execution.
