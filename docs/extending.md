# Guidelines for Extending the Codebase

The project follows a component based layout typical for ESP-IDF projects.
New functionality should be added under the `components/` directory.

1. **Create a component**
   - Place source files in a new subdirectory under `components`.
   - Provide an `idf_component.yml` describing the component metadata.
   - Update any `Kconfig` files if configuration options are required.

2. **Write tests**
   - Add unit tests in the `tests/` directory.
   - Include any necessary stubs so tests can run without ESP-IDF.

3. **Keep code portable**
   - Limit direct hardware access to the driver components.
   - Use the existing logging utilities for consistency.

Contributions should adhere to the existing coding style and include
appropriate documentation updates.
