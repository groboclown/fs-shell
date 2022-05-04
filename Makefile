
# MINFLAGS = -g0 -static -s -O3 -fomit-frame-pointer -fno-strict-aliasing -fno-align-functions -fno-align-jumps -fno-align-loops -fno-align-labels
MINFLAGS = -g0 -static -s -Os -fomit-frame-pointer -fno-strict-aliasing -fno-align-functions -fno-align-jumps -fno-align-loops -fno-align-labels
CFLAGS += -Wall -pedantic -DVERSION_NUMBER=\"1.0\"

.PHONY: all
all: \
	fs-shell.o fs-shell-debug.o \
	fs-shell-signal.o fs-shell-signal-debug.o \
	fs-shell-input.o fs-shell-input-debug.o \
	fs-shell-signal-input.o fs-shell-signal-input-debug.o


.PHONY: clean
clean:
	rm fs-shell.o fs-shell-debug.o \
	fs-shell-signal.o fs-shell-signal-debug.o \
	fs-shell-input.o fs-shell-input-debug.o \
	fs-shell-signal-input.o fs-shell-signal-input-debug.o


fs-shell.o: fs-shell.c commands.c args-argv.c
	$(CC) $(CFLAGS) $(MINFLAGS) $? $(LDFLAGS) -o $@


fs-shell-debug.o: fs-shell.c commands.c args-argv.c
	$(CC) $(CFLAGS) -DDEBUG=1 -static $? $(LDFLAGS) -o $@


fs-shell-signal.o: fs-shell.c commands.c args-argv.c
	$(CC) $(CFLAGS) $(MINFLAGS) -DUSE_SIGNALS=1 -static $? $(LDFLAGS) -o $@


fs-shell-signal-debug.o: fs-shell.c commands.c args-argv.c
	$(CC) $(CFLAGS) -DDEBUG=1 -DUSE_SIGNALS=1 -static $? $(LDFLAGS) -o $@


fs-shell-input.o: fs-shell.c commands.c args-input.c
	$(CC) $(CFLAGS) $(MINFLAGS) -DUSES_INPUT=1 $? $(LDFLAGS) -o $@


fs-shell-input-debug.o: fs-shell.c commands.c args-input.c
	$(CC) $(CFLAGS) -DDEBUG=1 -DUSES_INPUT=1 -static $? $(LDFLAGS) -o $@


fs-shell-signal-input.o: fs-shell.c commands.c args-input.c
	$(CC) $(CFLAGS) $(MINFLAGS) -DUSE_SIGNALS=1 -DUSES_INPUT=1 -static $? $(LDFLAGS) -o $@


fs-shell-signal-input-debug.o: fs-shell.c commands.c args-input.c
	$(CC) $(CFLAGS) -DDEBUG=1 -DUSE_SIGNALS=1 -DUSES_INPUT=1 -static $? $(LDFLAGS) -o $@
