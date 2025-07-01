# Agent Overview

This project organizes common background tasks into small modules known as *agents*. Each agent lives under `components/agents` and exposes a minimal API so the main application can drive it. The sections below describe the purpose of the built-in agents and their main interaction points.

## Autoconfig

*Purpose*: Ensure a configuration file exists and contains valid fields. If no file is present a default one is created.

*API*
```c
void autoconfig_verify(void);
```

*Interaction points*
- Uses the `storage` component to read and write `/config.json`.
- Called from `app_main()` before other modules are initialised.

## Diagnostic

*Purpose*: Run simple self-tests for the display and touch drivers at boot time.

*API*
```c
void diagnostic_run(void);
```

*Interaction points*
- Invokes `gt911_self_test()` and `lcd_st7262_self_test()` from the driver components.
- Outputs results using the logging utilities.

## Monitor

*Purpose*: Periodically poll sensors and report if measured values exceed thresholds.

*API*
```c
void monitor_init(void);
void monitor_set_thresholds(int temp, int hum);
void monitor_poll(void);
```

*Interaction points*
- Thresholds can be configured at runtime with `monitor_set_thresholds()`.
- `monitor_poll()` should be called in the main loop; it currently logs stubbed readings.

## Assistant

*Purpose*: Display a short help or FAQ screen for the user.

*API*
```c
void assistant_show_help(void);
```

*Interaction points*
- Invoked after the LVGL UI is created to present usage information.

## Adding or Extending Agents

Agents are regular ESP‑IDF components. To add a new agent:

1. Create a subdirectory under `components/agents`, e.g. `components/agents/myagent`.
2. Provide a header and source file exporting the agent functions.
3. Add a `CMakeLists.txt` similar to:
   ```cmake
   idf_component_register(
       SRCS "myagent.c"
       INCLUDE_DIRS "."
       REQUIRES utils
   )
   ```
4. Include an `idf_component.yml` describing the component and its dependencies.
5. List the new path in the `EXTRA_COMPONENT_DIRS` variable inside the top-level `CMakeLists.txt`.

Existing agents can be extended in the same way—add new APIs to the header, implement them in the source file and update the documentation. See [docs/extending.md](extending.md) for general guidelines.
