set -eux
cd ./minecraft/gen
python mc.py ~/Love2DWorld/region/r.0.0.mcr ../region.0.0 &
python mc.py ~/Love2DWorld/region/r.-1.-1.mcr ../region.-1.-1 &
python mc.py ~/Love2DWorld/region/r.0.-1.mcr ../region.0.-1 &
python mc.py ~/Love2DWorld/region/r.-1.0.mcr ../region.-1.0 &
