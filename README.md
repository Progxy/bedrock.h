# bedrock.h

**bedrock.h** is a single-header collection of C primitives, utilities, and small abstractions that tend to be rewritten in every project.

It exists to stop doing that.

The header is designed to be:
- usable in both **kernel space** and **user space**
- dependency-free
- portable across projects
- safe to include almost anywhere

If it shows up everywhere, that is intentional.

---

## Design goals

- **Single header**
  - One `.h` file, include guard only
  - No build system integration required

- **Kernel- and userspace-safe**
  - No libc assumptions unless explicitly guarded
  - No dynamic allocation unless the environment provides it
  - No global state

- **Low-level first**
  - Plain C
  - Minimal abstractions
  - Explicit behavior

- **Boring in the best way**
  - Predictable
  - Readable
  - Stable

---

## What goes in bedrock

`bedrock.h` is meant for code that is:
- small
- frequently reused
- annoying to reimplement
- not worth its own project

Examples:
- common macros
- small helper functions
- portable compiler attributes
- alignment / bit manipulation helpers
- safe min/max utilities
- assertions and static checks
- environment-agnostic definitions

If it starts needing documentation pages, it probably does not belong here.

---

## What does *not* go in bedrock

- Large subsystems
- Policy-heavy code
- Platform-specific hacks without guards
- Anything that forces a dependency on a specific runtime

`bedrock.h` should remain something you can include without thinking.

---

## Usage

```c
#define bedrock_calloc calloc     /* Easily define custom allocators              */
#define _BEDROCK_FUNCTIONALITY_*_ /* Include only a subset of its functionalities */
#include "bedrock.h"
```

That is it.

No initialization.
No teardown.
No linkage concerns.

