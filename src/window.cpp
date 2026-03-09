#include "window.h"

float g_window_width = 1;
float g_window_height = 1;

void update_window(int width, int height)
{
  g_window_width = width;
  g_window_height = height;
}
