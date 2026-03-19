local ffi = require 'ffi'
local joysticks

function init()
   joysticks = love.joystick.getJoysticks()
   for i, joystick in ipairs(joysticks) do
      print(i, joystick:getName())
   end

   ffi.cdef[[
void load(const char * source_path);
void update_window(int width, int height);
void draw();
void update_keyboard(int up, int down, int left, int right,
                     int w, int s, int a, int d,
                     int t, int g, int f, int h,
                     int i, int k, int j, int l);
void update_mouse(int x, int y);
void update_joystick(int joystick_index,
                     float lx, float ly, float rx, float ry, float tl, float tr,
                     int up, int down, int left, int right,
                     int a, int b, int x, int y,
                     int leftshoulder, int rightshoulder,
                     int start);
void update(float time);

  int draw_font_start();
  int draw_font(int font_ix, char const * text, int x, int y);

  void draw_line_quad_start();
  void draw_line(int x1, int y1, int x2, int y2);
  void draw_set_color(float r, float g, float b);
  void draw_quad(int x1, int y1, int x2, int y2,
                 int x3, int y3, int x4, int y4);
]]
   local source_path = love.filesystem.getSource()
   test = ffi.load(source_path .. "/test.so")
   test.load(source_path)
end

local update = function(time)
   for joystick_index, joystick in ipairs(joysticks) do
      if joystick_index > 8 then
         break
      end
      local lx = joystick:getGamepadAxis("leftx")
      local ly = joystick:getGamepadAxis("lefty")
      local rx = joystick:getGamepadAxis("rightx")
      local ry = joystick:getGamepadAxis("righty")
      local tl = joystick:getGamepadAxis("triggerleft")
      local tr = joystick:getGamepadAxis("triggerright")
      local up = joystick:isGamepadDown("dpup")
      local down = joystick:isGamepadDown("dpdown")
      local left = joystick:isGamepadDown("dpleft")
      local right = joystick:isGamepadDown("dpright")
      local a = joystick:isGamepadDown("a")
      local b = joystick:isGamepadDown("b")
      local x = joystick:isGamepadDown("x")
      local y = joystick:isGamepadDown("y")
      local leftshoulder = joystick:isGamepadDown("leftshoulder")
      local rightshoulder = joystick:isGamepadDown("rightshoulder")
      local start = joystick:isGamepadDown("start")
      --print("start", i, start)
      test.update_joystick(joystick_index - 1,
                           lx, ly, rx, ry, tl, tr,
                           up, down, left, right,
                           a, b, x, y,
                           leftshoulder, rightshoulder,
                           start)
   end

   local up = love.keyboard.isDown("up")
   local down = love.keyboard.isDown("down")
   local left = love.keyboard.isDown("left")
   local right = love.keyboard.isDown("right")
   local w = love.keyboard.isDown("w")
   local s = love.keyboard.isDown("s")
   local a = love.keyboard.isDown("a")
   local d = love.keyboard.isDown("d")
   local t = love.keyboard.isDown("t")
   local g = love.keyboard.isDown("g")
   local f = love.keyboard.isDown("f")
   local h = love.keyboard.isDown("h")
   local i = love.keyboard.isDown("i")
   local k = love.keyboard.isDown("k")
   local j = love.keyboard.isDown("j")
   local l = love.keyboard.isDown("l")
   test.update_keyboard(up, down, left, right,
                        w, s, a, d,
                        t, g, f, h,
                        i, k, j, l);

   test.update(time)
end

local draw = function()
   test.draw()
end

local nico_draw = function()
   ----------------------------------------------------------------------
   -- font drawing
   ----------------------------------------------------------------------

   -- call "draw_font_start()" prior each "group" of "draw_font()" calls
   --
   -- a "group" of draw_font() calls are back-to-back/consecutive,
   -- with no non-font drawing between them.
   --
   -- For example:

   local font_ix = test.draw_font_start()
   local x = 512
   local y = 50
   y = y + test.draw_font(font_ix, "lua test", x, y)
   y = y + test.draw_font(font_ix, "cool", x, y)

   -- note that "font_ix" is the current "best font" as calculated
   -- from the current window size, and might change next frame if the
   -- window is resized.
   --
   -- Any of this of course could be changed to match your precise
   -- requirements.

   ----------------------------------------------------------------------
   -- line drawing
   ----------------------------------------------------------------------

   -- call "draw_line_quad_start()" prior to each "group" of
   -- "draw_line()" or "draw_quad()" calls
   --
   -- a "group" of draw_line()/draw_quad() calls are
   -- back-to-back/consecutive, with no non-line/quad drawing between
   -- them.
   --
   -- For example:

   test.draw_line_quad_start()
   test.draw_set_color(1.0, 0.0, 0.0) -- r, g, b (0.0 to 1.0)
   test.draw_line(0, 0, 1024, 1024) -- x1, y1, x2, y2
   test.draw_line(700, 300, 400, 500)
   test.draw_set_color(0.0, 1.0, 0.0)
   test.draw_line(700, 300, 400, 700)

   -- x1, y1, x2, y2,
   -- x3, y3, x4, y4,
   --
   -- vertices must be specified In "counter clockwise" order, as in:
   --
   --    2──1
   --    │  │   valid (counter clockwise)
   --    3──4
   --
   -- these can also be rotated, as in:
   --
   --     3
   --    ╱ ╲
   --   4   2   valid (counter clockwise)
   --    ╲ ╱
   --     1
   --
   -- however "mirroring" is not valid, as in:
   --
   --    1──2
   --    │  │   not valid (clockwise)
   --    4──3
   --
   test.draw_set_color(0.0, 0.0, 1.0)
   test.draw_quad(
      600, 600, -- top right
      500, 600, -- top left
      500, 700, -- bottom left
      600, 700  -- bottom right
   )
   test.draw_set_color(0.0, 0.5, 1.0)
   test.draw_quad(
      900, 900, -- bottom
      950, 850, -- right
      900, 800, -- top
      850, 850  -- left
   )

   -- If you want to draw a large number of lines or quads in bulk
   -- (e.g: 10,000+ lines/quads per frame), this interface might not be good
   -- enough, and we should discuss this in more detail.
end

function love.run()
   init()

   return function()
      love.event.pump()
      for name, a,b,c,d,e,f,g,h in love.event.poll() do
         if name == "quit" then
            if c or not love.quit or not love.quit() then
               return a or 0, b
            end
         end
      end

      local width
      local height
      local flags
      width, height, flags = love.window.getMode()
      test.update_window(width, height)

      local time = love.timer.getTime()
      update(time)

      draw()

      local mouse_down = love.mouse.isDown(1)
      if mouse_down then
         local x, y = love.mouse.getPosition()
         test.update_mouse(x, y)
      end

      --nico_draw()

      love.graphics.present()
      love.timer.sleep(0.001)
   end
end
