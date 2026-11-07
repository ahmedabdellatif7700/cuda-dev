# Lesson 9 — Chapter 1 Summary and Exercises: observation handout

Book: Chapter 1, Summary; printed pp. 21–22. Roadmap ID 1.5.
See [lesson notes](../professional-cuda/lesson-09-chapter-01-summary.md).

## Core idea

Chapter 1 connects parallel work, architecture, host/device roles, and the first reproducible CUDA program.

**Code or evidence:** [README.md](../../exercises/chapter-01/README.md). Preserved greeting variants separate launch, completion, and teardown. Notes supply architecture/partition reasoning that does not require an invented kernel.

**Original lesson commit:** `72f503e`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Focus

Review the existing small-grid capture and the remaining observation records. No new profiling is required for a chapter summary itself. Keep unsupplied captures and interpretations pending rather than inventing results.

## Record

- Kernel or source path examined: pending user discussion.
- Relevant PTX beside the implementation: identify only this lesson's operations.
- Actual capture and settings: pending, if applicable.
- Prediction versus observation: pending user discussion.

Do not run profilers automatically. Preserve the user-controlled ncu-ui workflow.
Host work, copy completion, and printed ordering cannot be explained by an isolated
kernel duration. PTX describes intermediate operations, not measured execution.
