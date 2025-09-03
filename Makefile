CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
TARGETS = tc358870_init test_pwm test_gpio_pwm test_power_sequence

.PHONY: all clean

all: $(TARGETS)

tc358870_init: tc358870_init.c
	$(CC) $(CFLAGS) -o $@ $< -lm

test_gpio_pwm: test_gpio_pwm.c
	$(CC) $(CFLAGS) -o $@ $< -lm

test_power_sequence: test_power_sequence.c
	$(CC) $(CFLAGS) -o $@ $< -lm

clean:
	rm -f $(TARGETS)

