# Running Unit Tests and CI

The host based tests reside in the `tests/` directory. They can be built with
`make` and run directly on a regular Linux system. The makefile links against
the system `cjson` library, so you need the development package installed
before invoking `make`.

For Debian based systems you can install the dependency with:

```bash
sudo apt-get install libcjson-dev
```

```bash
cd tests
make            # builds all test binaries
./test_animals
./test_animals_load
./test_logging
./test_storage
./test_ui
```

CI is provided through GitHub Actions. The workflow defined in
`.github/workflows/ci.yml` installs `libcjson-dev`, builds the tests and executes
them on each push and pull request. You can trigger the same checks locally with
the commands above.
