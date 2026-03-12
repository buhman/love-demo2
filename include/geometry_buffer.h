#pragma once

#include <assert.h>

#include "glad/gl.h"

#include "window.h"

template <int render_target_count>
struct geometry_buffer {
  unsigned int framebuffer;
  unsigned int target[render_target_count]; // textures
  unsigned int renderbuffer;
  int initialized;
  int width;
  int height;
};

struct target_type {
  GLint internal_format;
  GLenum attachment;
};

struct target_name {
  enum {
    POSITION = 0,
    NORMAL = 1,
    COLOR = 2,
  };
};

template <int render_target_count>
void init_geometry_buffer(geometry_buffer<render_target_count>& geometry_buffer, target_type const * const types)
{
  int width = window::width;
  int height = window::height;

  if ((geometry_buffer.initialized == 1) && (width == geometry_buffer.width) && (height == geometry_buffer.height)) {
    return;
  }

  if (geometry_buffer.initialized) {
    glDeleteFramebuffers(1, &geometry_buffer.framebuffer);
    glDeleteTextures(render_target_count, geometry_buffer.target);
    glDeleteRenderbuffers(1, &geometry_buffer.renderbuffer);
  }
  glGenFramebuffers(1, &geometry_buffer.framebuffer);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, geometry_buffer.framebuffer);

  glGenTextures(render_target_count, geometry_buffer.target);
  for (int i = 0; i < render_target_count; i++) {
    glBindTexture(GL_TEXTURE_2D, geometry_buffer.target[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, types[i].internal_format, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, types[i].attachment, GL_TEXTURE_2D, geometry_buffer.target[i], 0);
  }
  static_assert(render_target_count == 3);
  GLenum attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
  glDrawBuffers(3, attachments); // bound to GL_DRAW_FRAMEBUFFER

  glGenRenderbuffers(1, &geometry_buffer.renderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, geometry_buffer.renderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
  glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, geometry_buffer.renderbuffer);

  assert(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

  geometry_buffer.initialized = 1;
  geometry_buffer.width = width;
  geometry_buffer.height = height;
}
