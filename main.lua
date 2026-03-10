local ffi = require 'ffi'
local joysticks

function init()
   joysticks = love.joystick.getJoysticks()

   ffi.cdef[[
void load(const char * source_path);
void update_window(int width, int height);
void draw();
void kb_update(int kbup, int kbdown, int kbleft, int kbright);
void update(float lx, float ly, float rx, float ry, float tl, float tr,
            int up, int down, int left, int right,
            int a, int b, int x, int y,
            int leftshoulder, int rightshoulder);
]]
   local source_path = love.filesystem.getSource()
   test = ffi.load(source_path .. "/test.so")
   test.load(source_path)
   print(love.filesystem.getWorkingDirectory())
end

local update = function(dt)
   for _, joystick in ipairs(joysticks) do
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

      test.update(lx, ly, rx, ry, tl, tr,
                  up, down, left, right,
                  a, b, x, y,
                  leftshoulder, rightshoulder)
   end

   local up = love.keyboard.isDown("up")
   local down = love.keyboard.isDown("down")
   local left = love.keyboard.isDown("left")
   local right = love.keyboard.isDown("right")
   test.kb_update(up, down, left, right);
end

local draw = function()
   test.draw()
end

function love.run()
   init()

   love.timer.step()

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

      local dt = love.timer.step()
      update(dt)

      draw()

      love.graphics.present()
      love.timer.sleep(0.001)
      local fps = love.timer.getFPS( )
      --print(fps)
   end
end
