set -eux
#cd ./minecraft/gen
PYTHON=pypy3.11

CROP=-200,-150:300,200
ALL_REGIONS=../grandlecturn/all_regions.txt

cat <<EOF > $ALL_REGIONS
$HOME/GrandLecturn/region/r.0.0.mcr
$HOME/GrandLecturn/region/r.-1.-1.mcr
$HOME/GrandLecturn/region/r.0.-1.mcr
$HOME/GrandLecturn/region/r.-1.0.mcr
EOF
$PYTHON mc.py $HOME/GrandLecturn/region/r.0.0.mcr   ../grandlecturn/region.0.0 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/GrandLecturn/region/r.-1.-1.mcr ../grandlecturn/region.-1.-1 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/GrandLecturn/region/r.0.-1.mcr  ../grandlecturn/region.0.-1 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/GrandLecturn/region/r.-1.0.mcr  ../grandlecturn/region.-1.0 $ALL_REGIONS $CROP &

wait

cat ../grandlecturn/region*.lights.vtx > ../grandlecturn/global.lights.vtx

cat ../grandlecturn/region*.dump > ../grandlecturn/global.dump
$PYTHON intkeys.py ../grandlecturn/global.dump | $HOME/nbperf/nbperf -n grandlecturn_hash -I -a bpz -c 1.24 -m ../love2dworld/map.txt > ../grandlecturn/inthash.c
