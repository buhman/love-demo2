function love.conf(t)
   t.identity = "love-demo2"
   t.window.width = 1024
   t.window.height = 1024
   t.window.depth = true
   t.window.resizable = true
   t.graphics.excluderenderers = {"vulkan", "metal"}
end
