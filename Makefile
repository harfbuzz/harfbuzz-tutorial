PKGS = harfbuzz harfbuzz cairo-ft

CFLAGS = `pkg-config --cflags $(PKGS)`
LDFLAGS = `pkg-config --libs $(PKGS)`

all: hello-harfbuzz
