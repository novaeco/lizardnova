# Contributing to Reptile Manager Pro

Thank you for taking the time to contribute! This guide explains how to set up ESP‑IDF, the expected coding style, and how to submit issues or pull requests.

## Setting up ESP‑IDF

1. Install **ESP‑IDF 5.0 or newer**. Follow the [official setup guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/).
2. After cloning this repository, set the target and build the firmware:
   ```bash
   idf.py set-target esp32s3
   idf.py build
   ```
   You should be able to flash with:
   ```bash
   idf.py flash monitor
   ```

## Coding Style

* Use spaces instead of tabs and indent with **4 spaces**.
* Limit lines to **100 characters** when possible.
* Brace style follows the K&R convention with the opening brace on the same line as the control statement.
* Use descriptive `snake_case` names for variables and functions in C/C++ code.
* Run `pytest -v` to ensure unit tests pass before submitting.

## Submitting Issues

1. Search existing issues to avoid duplicates.
2. Provide as much detail as possible: board revision, ESP‑IDF version and steps to reproduce the problem.
3. If relevant, include logs or stack traces.

## Submitting Pull Requests

1. Fork the repository and create a new branch for your changes.
2. Make sure the project builds with `idf.py build` and all tests pass with `pytest -v`.
3. Follow the coding style guidelines above. Keep commits focused and include clear commit messages.
4. Open a pull request on GitHub. Describe what you changed and reference related issues if any.
5. Be responsive to review comments so the PR can be merged promptly.

We appreciate all contributions that help improve this project!
