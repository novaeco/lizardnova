CC ?= gcc
CFLAGS = -I.. -I../components -I../components/core/animals -I../components/storage \
         -I../components/core/utils -I../components/core/ui -I../components/agents/monitor \
         -I../components/agents/autoconfig -I../components/agents/diagnostic \
         -I../components/agents/assistant -Istubs \
         -I/usr/include/cjson
LDLIBS = -lcjson

TESTS = test_animals test_storage test_logging test_ui test_animals_load test_agents

COMMON_SRCS = ../components/core/animals/animals.c \
              ../components/storage/storage.c \
              ../components/core/utils/logging.c \
              ../components/core/ui/ui_animals.c \
              ../components/agents/monitor/monitor.c \
              ../components/agents/autoconfig/autoconfig.c \
              ../components/agents/diagnostic/diagnostic.c \
              ../components/agents/assistant/assistant.c \
              stubs/lvgl.c \
              stubs/esp_log.c

all: $(TESTS)

%: %.c $(COMMON_SRCS)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(TESTS)

.PHONY: all clean
