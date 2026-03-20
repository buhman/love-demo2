#include <stdio.h>
#include <string.h>

#include "directxmath/directxmath.h"

#include "font.h"
#include "view.h"

extern font::font * terminus_fonts;
extern unsigned int empty_vertex_array_object;
extern unsigned int quad_index_buffer;

extern float current_time;
extern float last_frame_time;


// depends on:
// - font::load
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

  inline static float draw_vector(font::font const& ter_best, char * const buf, float y, char const * const label, XMVECTOR vec)
  {
    labeled_value<float>(buf, label, ": %5.2f %5.2f %5.2f %5.2f", XMVectorGetX(vec), XMVectorGetY(vec), XMVectorGetZ(vec), XMVectorGetW(vec));
    font::draw_string(ter_best, buf, 10, y);
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

  void draw()
  {
    char buf[512];

    float y = 10.0f;

    int font_ix = font::best_font(font::terminus, font::terminus_length);
    font::font const& ter_best = terminus_fonts[font_ix];
    font::draw_start(ter_best, empty_vertex_array_object, quad_index_buffer);

    labeled_value<float>(buf, "fov: ", "%.3f", view::state.fov);
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;

    labeled_value<int>(buf, "font_height: ", "%d", ter_best.desc->glyph_height);
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;

    /*
    labeled_value<float>(buf, "lighting.quadratic: ", "%.2f", lighting.quadratic);
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;

    labeled_value<float>(buf, "lighting.linear: ", "%.2f", lighting.linear);
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;
    */

    y = draw_vector(ter_best, buf, y, "eye", XMVectorSetW(view::state.eye, 0));
    y = draw_vector(ter_best, buf, y, "at", XMVectorSetW(view::state.at, 0));
    y = draw_vector(ter_best, buf, y, "forward", XMVectorSetW(view::state.forward, 0));

    labeled_value<float>(buf, "pitch: ", "%.4f", view::state.pitch);
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;

    labeled_value<float>(buf, "frame_rate_avg: ", "%.2f", 1.0f / update_average(current_time - last_frame_time));
    font::draw_string(ter_best, buf, 10, y);
    y += ter_best.desc->glyph_height;

    font::draw_string(ter_best, "mouse:", 10, y);
    y += ter_best.desc->glyph_height;
    y = draw_vector(ter_best, buf, y, "  position", XMLoadFloat4((XMFLOAT4*)mouse_position));
    y = draw_vector(ter_best, buf, y, "     block", XMLoadFloat4((XMFLOAT4*)mouse_block));
  }
}
