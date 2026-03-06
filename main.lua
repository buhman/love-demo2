local ffi = require 'ffi'
local joysticks

function init()
   joysticks = love.joystick.getJoysticks()

   ffi.cdef[[
void load();
void draw();
void update(float lx, float ly, float ry);
]]
   test = ffi.load("./test.so")
   test.load()

end

local update = function(dt)
   for _, joystick in ipairs(joysticks) do
      local lx = joystick:getGamepadAxis("leftx")
      local ly = joystick:getGamepadAxis("lefty")
      local ry = joystick:getGamepadAxis("righty")
      test.update(lx, ly, ry)
   end
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

      local dt = love.timer.step()
      update(dt)

      draw()

      love.graphics.present()
      love.timer.sleep(0.001)
      local fps = love.timer.getFPS( )
      print(fps)
   end
end
