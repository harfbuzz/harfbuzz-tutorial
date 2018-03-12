HB_PKGS = harfbuzz
FT_PKGS = harfbuzz cairo-ft freetype2

HB_CFLAGS = `pkg-config --cflags $(HB_PKGS)`
HB_LDFLAGS = `pkg-config --libs $(HB_PKGS)` -lm

FT_CFLAGS = `pkg-config --cflags $(FT_PKGS)`
FT_LDFLAGS = `pkg-config --libs $(FT_PKGS)` -lm

all: hello-harfbuzz-freetype hello-harfbuzz-opentype
	
hello-harfbuzz-opentype: hello-harfbuzz-opentype.c
	$(CC) -std=c99 -o $@ $^ $(HB_CFLAGS) $(HB_LDFLAGS)

hello-harfbuzz-freetype: hello-harfbuzz-freetype.c
	$(CC) -std=c99 -o $@ $^ $(FT_CFLAGS) $(FT_LDFLAGS)