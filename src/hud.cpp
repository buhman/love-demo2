#include <stdio.h>
#include <string.h>

#include "directxmath/directxmath.h"
#include "glad/gl.h"

#include "font/bitmap.h"
#include "font/outline.h"
#include "view.h"
#include "window.h"

extern font::bitmap::font * terminus_fonts;
extern font::outline::font * uncial_antiqua_fonts;
extern unsigned int empty_vertex_array_object;
extern unsigned int quad_index_buffer;

extern float current_time;
extern float last_frame_time;

// depends on:
// - font::bitmap::load
// - load_quad_program
// - load_quad_index_buffer
// - empty_vertex_array_object

extern float mouse_position[3];
extern float mouse_block[3];

namespace hud {

  template <typename T, typename... Args>
  void labeled_value(char * const buf, char const * const label, char const * const format, Args... args)
  {
    const int label_length = strlen(label);
    memcpy(buf, label, label_length);
    int len = snprintf(&buf[label_length], 511 - label_length, format, args...);
    buf[label_length + len] = 0;
  }

  inline static float draw_vector(font::bitmap::font const& ter_best, char * const buf, float y, char const * const label, XMVECTOR vec)
  {
    labeled_value<float>(buf, label, ": %5.2f %5.2f %5.2f %5.2f", XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec), XMVectorGetW(vec));
    font::bitmap::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;
    return y;
  }

  static int average_init = 0;
  static int average_ix = 0;
  static float rolling_sum = 0;
  static float averages[16] = {};

  const int frame_warmup = 10;

  static float update_average(float value)
  {
    if (average_init < frame_warmup) {
      average_init += 1;
      return 0.0f;
    }
    if (average_init == frame_warmup) {
      assert(average_ix == 0);
      rolling_sum = value * 16.0f;
      for (int i = 0; i < 16; i++) {
        averages[i] = value;
      }
      average_init += 1;
    } else {
      rolling_sum -= averages[average_ix];
      rolling_sum += value;

      averages[average_ix] = value;
      average_ix = (average_ix + 1) % 16;
    }

    return rolling_sum * (1.0f / 16.0f);
  }

  template <typename T, typename... Args>
  static float draw_label(font::bitmap::font const& font, char * buf, float x, float y, char const * const label, char const * const format, Args... args)
  {
    labeled_value<T>(buf, label, format, args...);
    font::bitmap::draw_string(font, buf, x, y);
    return y + font.desc->glyph_height;
  }

  static int frame = 0;

  void draw()
  {
    static char buf[512];

    float y = 10.0f;

    int font_ix = font::bitmap::best_font(font::bitmap::terminus, font::bitmap::terminus_length);
    font::bitmap::font const& ter_best = terminus_fonts[font_ix];
    font::bitmap::draw_start(ter_best, empty_vertex_array_object, quad_index_buffer);

    //y = draw_label<float>(ter_best, buf, 10, y, "fov: ", "%.3f", view::state.fov);
    //y = draw_label<int>(ter_best, buf, 10, y, "font_height: ", "%d", ter_best.desc->glyph_height);

    font::bitmap::draw_string(ter_best, "keyboard:", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  move: w/a/s/d", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  look: up/down/left/right", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  elevate: q/e", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  warp: l", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "gamepad:", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  move: left stick", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  look: right stick", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  elevate: left/right trigger", 10, y); y += ter_best.desc->glyph_height;
    font::bitmap::draw_string(ter_best, "  warp: a", 10, y); y += ter_best.desc->glyph_height;


    font::bitmap::draw_string(ter_best, "mouse:", 10, y); y += ter_best.desc->glyph_height;

    y = draw_vector(ter_best, buf, y, "  position", XMLoadFloat4((XMFLOAT4*)mouse_position));
    y = draw_vector(ter_best, buf, y, "     block", XMLoadFloat4((XMFLOAT4*)mouse_block));

    if (frame++ > 60 * 10)
      return;

    font::outline::draw_start(uncial_antiqua_fonts[0], empty_vertex_array_object, quad_index_buffer);
    char const * title = "Technical demo: Bibliotheca";
    int const title_length = strlen(title);
    int title_width = 563;
    int title_height = 31;
    int title_x = (window::width - title_width) / 2.0;
    int title_y = (window::height - title_height) / 2.0;

    glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    font::outline::draw_string(uncial_antiqua_fonts[0], title, title_x + 3, title_y + 3);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    font::outline::draw_string(uncial_antiqua_fonts[0], title, title_x + 0, title_y + 0);

    /*
    y = draw_label<float>(ter_best, buf, 10, y, "lighting.quadratic: ", "%.2f", lighting.quadratic);
    y = draw_label<float>(ter_best, buf, 10, y, "lighting.linear: ", "%.2f", lighting.linear);
    */

    /*
    y = draw_vector(ter_best, buf, y, "eye", XMVectorSetW(view::state.eye, 0));
    y = draw_vector(ter_best, buf, y, "at", XMVectorSetW(view::state.at, 0));
    y = draw_vector(ter_best, buf, y, "forward", XMVectorSetW(view::state.forward, 0));

    y = draw_label<float>(ter_best, buf, 10, y, "pitch: ", "%.4f", view::state.pitch);
    y = draw_label<float>(ter_best, buf, 10, y, "frame_rate_avg: ", "%.2f", 1.0f / update_average(current_time - last_frame_time));
    */
  }
}
