set -eux
#cd ./minecraft/gen
PYTHON=pypy3.11
cat <<EOF > ../love2dworld/all_regions.txt
$HOME/Love2DWorld/region/r.0.0.mcr
$HOME/Love2DWorld/region/r.-1.-1.mcr
$HOME/Love2DWorld/region/r.0.-1.mcr
$HOME/Love2DWorld/region/r.-1.0.mcr
EOF
$PYTHON mc.py $HOME/Love2DWorld/region/r.0.0.mcr ../love2dworld/region.0.0 ../love2dworld/all_regions.txt &
$PYTHON mc.py $HOME/Love2DWorld/region/r.-1.-1.mcr ../love2dworld/region.-1.-1 ../love2dworld/all_regions.txt &
$PYTHON mc.py $HOME/Love2DWorld/region/r.0.-1.mcr ../love2dworld/region.0.-1 ../love2dworld/all_regions.txt &
$PYTHON mc.py $HOME/Love2DWorld/region/r.-1.0.mcr ../love2dworld/region.-1.0 ../love2dworld/all_regions.txt &

wait

cat ../love2dworld/region*.lights.vtx > ../love2dworld/global.lights.vtx

cat ../love2dworld/region*.dump > ../love2dworld/global.dump
$PYTHON intkeys.py ../love2dworld/global.dump | $HOME/nbperf/nbperf -n love2dworld_hash -I -a bpz -c 1.24 -m ../love2dworld/map.txt > ../love2dworld/inthash.c
