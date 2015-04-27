#include <stdlib.h>
#include <stdio.h>
#include <hb.h>
#include <hb-ft.h>

#define FONT_SIZE 36

int
main(int argc, char **argv)
{
  const char *fontfile;
  const char *text;

  if (argc < 3)
  {
    fprintf (stderr, "usage: hello-harfbuzz font-file.ttf text\n");
    exit (1);
  }

  fontfile = argv[1];
  text = argv[2];


  /* Initialize FreeType and create FreeType font face. */
  FT_Library ft_library;
  FT_Face ft_face;
  FT_Error ft_error;

  if ((ft_error = FT_Init_FreeType (&ft_library)))
    abort();
  if ((ft_error = FT_New_Face (ft_library, fontfile, 0, &ft_face)))
    abort();
  if ((ft_error = FT_Set_Char_Size (ft_face, FONT_SIZE*64, FONT_SIZE*64, 0, 0)))
    abort();

  /* Create hb-ft font. */
  hb_font_t *hb_font;
  hb_font = hb_ft_font_create (ft_face, NULL);

  /* Create hb-buffer and populate. */
  hb_buffer_t *hb_buffer;
  hb_buffer = hb_buffer_create ();
  hb_buffer_add_utf8 (hb_buffer, text, -1, 0, -1);
  hb_buffer_guess_segment_properties (hb_buffer);

  /* Shape it! */
  hb_shape (hb_font, hb_buffer, NULL, 0);

  /* Print glyph names and positions out. */
  unsigned int len;
  hb_glyph_info_t *infos;
  hb_glyph_position_t *positions;
  len = hb_buffer_get_length (hb_buffer);
  infos = hb_buffer_get_glyph_infos (hb_buffer, NULL);
  positions = hb_buffer_get_glyph_positions (hb_buffer, NULL);

  for (unsigned int i = 0; i < len; i++)
  {
    hb_glyph_info_t *info = &infos[i];
    hb_glyph_position_t *pos = &positions[i];

    char glyphname[32];
    hb_font_get_glyph_name (hb_font, info->codepoint, glyphname, sizeof (glyphname));
    printf ("glyph '%s' x-advance %g offset %g,%g\n",
            glyphname,
	    pos->x_advance / 64.,
	    pos->x_offset / 64.,
	    pos->y_offset / 64.);
  }

  hb_buffer_destroy (hb_buffer);
  hb_font_destroy (hb_font);

  FT_Done_Face (ft_face);
  FT_Done_FreeType (ft_library);

  return 0;
}
