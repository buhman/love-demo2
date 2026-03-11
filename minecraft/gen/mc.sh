set -eux
cd ./minecraft/gen
PYTHON=pypy3.11
$PYTHON mc.py ~/Love2DWorld/region/r.0.0.mcr ../region.0.0 &
$PYTHON mc.py ~/Love2DWorld/region/r.-1.-1.mcr ../region.-1.-1 &
$PYTHON mc.py ~/Love2DWorld/region/r.0.-1.mcr ../region.0.-1 &
$PYTHON mc.py ~/Love2DWorld/region/r.-1.0.mcr ../region.-1.0 &

wait

cat ../region*.lights.vtx > ../global.lights.vtx

cat ../region*.dump > ../global.dump
$PYTHON intkeys.py ../global.dump | ~/nbperf/nbperf -I -a bpz -c 1.24 -m map.txt > ../../src/inthash.c
