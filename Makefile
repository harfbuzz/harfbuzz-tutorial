PKGS = harfbuzz harfbuzz cairo-ft freetype2

CFLAGS = `pkg-config --cflags $(PKGS)`
LDFLAGS = `pkg-config --libs $(PKGS)`

all: hello-harfbuzz

%: %.c
	$(CC) -std=c99 -o $@ $^ $(CFLAGS) $(LDFLAGS)
