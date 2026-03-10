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
void update_keyboard(int kbup, int kbdown, int kbleft, int kbright);
void update_mouse(int x, int y);
void update_joystick(int joystick_index,
                     float lx, float ly, float rx, float ry, float tl, float tr,
                     int up, int down, int left, int right,
                     int a, int b, int x, int y,
                     int leftshoulder, int rightshoulder,
                     int start);
void update(float time);
]]
   local source_path = love.filesystem.getSource()
   test = ffi.load(source_path .. "/test.so")
   test.load(source_path)
end

local update = function(time)
   test.update(time)

   for joystick_index, joystick in ipairs(joysticks) do
      if joystick_index >= 8 then
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
      test.update_joystick(joystick_index,
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
   test.update_keyboard(up, down, left, right);
end

local draw = function()
   test.draw()
end

function love.run()
   init()

   --love.timer.step()

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

      --local dt = love.timer.step()
      local time = love.timer.getTime()
      update(time)

      draw()

      local x, y = love.mouse.getPosition()
      test.update_mouse(x, y)

      love.graphics.present()
      love.timer.sleep(0.001)
      --local fps = love.timer.getFPS( )
      --print(fps)
   end
end
