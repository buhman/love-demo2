#include <stdio.h>
#include <stdlib.h>

#include "glad/gl.h"

#include "line_art.h"
#include "boids.h"

namespace boids_scene {

  const int boids_length = 20;
  boids::boid boids[boids_length];

  const XMFLOAT3 colors[] = {
    {(float)0xb5 / 255.0, (float)0x7f / 255.0, (float)0x50 / 255.0},
    {(float)0x37 / 255.0, (float)0xff / 255.0, (float)0x8b / 255.0},
    {(float)0x51 / 255.0, (float)0xd6 / 255.0, (float)0xff / 255.0},
    {(float)0x54 / 255.0, (float)0x2e / 255.0, (float)0x71 / 255.0},
    {(float)0xff / 255.0, (float)0x84 / 255.0, (float)0x84 / 255.0},
  };

  void update(int up, int down, int left, int right,
              int w, int s, int a, int d,
              int t, int g, int f, int h,
              int i, int k, int j, int l)
  {
    float rate = 0.05f;

    float forward[4];
    float strafe[4];

    forward[0] = (rate * up + -rate * down);
    strafe[0] = (-rate * left + rate * right);

    forward[1] = (rate * w + -rate * s);
    strafe[1] = (-rate * a + rate * d);

    forward[2] = (rate * t + -rate * g);
    strafe[2] = (-rate * f + rate * h);

    forward[3] = (rate * i + -rate * k);
    strafe[3] = (-rate * j + rate * l);

    //for (int i = 0; i < 4; i++)
    //point_position[i] = XMVector3Transform(point_position[i], XMMatrixTranslation(strafe[i], forward[i], 0));
  }

  static inline float random()
  {
    float r = 1.0f / (float)RAND_MAX;
    return (float)rand() * r * 2.0f - 1.0f;
  }

  void load()
  {
    srand(0x12345678);

    for (int i = 0; i < boids_length; i++) {
      boids[i].position = XMVectorSet(random() * 5, random() * 5, 0, 0);
      boids[i].velocity = XMVectorSet(random(), random(), 0, 0);
    }


    boids::configuration.vision_length = 2.0f;
    boids::configuration.cohesion.coefficient = 0.001f;
    boids::configuration.alignment.coefficient = 0.01f;
    boids::configuration.separation.minimum_length = 0.7f;
    boids::configuration.separation.coefficient = 0.5f;
    boids::configuration.bounds.coefficient = 0.02f;
  }

  void draw()
  {
    XMMATRIX transform = line_art::view() * line_art::projection();

    line_art::scene_start(transform);

    glLineWidth(1.0f);

    line_art::set_colorv(colors[4]);
    for (int i = 0; i < boids_length; i++)
      line_art::draw_sphere(transform, boids[i].position, 0.3);

    for (int i = 0; i < boids_length; i++) {
      boids::boid_forces const & forces = evaluate(boids, boids_length, i);

      glLineWidth(4.0f);
      line_art::set_colorv(colors[0]);
      line_art::draw_line(transform, boids[i].position, boids[i].position + forces.cohesion.force);
      line_art::set_colorv(colors[1]);
      line_art::draw_line(transform, boids[i].position, boids[i].position + forces.alignment.force);
      line_art::set_colorv(colors[2]);
      line_art::draw_line(transform, boids[i].position, boids[i].position + forces.separation.force);

      boids[i].velocity += forces.cohesion.force + forces.alignment.force + forces.separation.force;
      const float speed_limit = 2.0;
      if (XMVectorGetX(XMVector3LengthEst(boids[i].velocity)) > speed_limit) {
        boids[i].velocity = XMVector3NormalizeEst(boids[i].velocity) * speed_limit;
      }

      if (XMVectorGetX(boids[i].position) > 5.0)
        boids[i].velocity += XMVectorSetX(XMVectorZero(), -boids::configuration.bounds.coefficient);

      if (XMVectorGetX(boids[i].position) < -5.0)
        boids[i].velocity += XMVectorSetX(XMVectorZero(), boids::configuration.bounds.coefficient);

      if (XMVectorGetY(boids[i].position) > 5.0)
        boids[i].velocity += XMVectorSetY(XMVectorZero(), -boids::configuration.bounds.coefficient);

      if (XMVectorGetY(boids[i].position) < -5.0)
        boids[i].velocity += XMVectorSetY(XMVectorZero(), boids::configuration.bounds.coefficient);

      boids[i].position += boids[i].velocity * 0.05f;
    }
  }
}
