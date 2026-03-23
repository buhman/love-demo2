set -eux
#cd ./minecraft/gen
PYTHON=pypy3.11

CROP=-255,-255:382,382
ALL_REGIONS=../midnightmeadow/all_regions.txt

cat <<EOF > $ALL_REGIONS
$HOME/sunnyhill/region/r.0.0.mcr
$HOME/sunnyhill/region/r.-1.-1.mcr
$HOME/sunnyhill/region/r.0.-1.mcr
$HOME/sunnyhill/region/r.-1.0.mcr
EOF
$PYTHON mc.py $HOME/sunnyhill/region/r.0.0.mcr   ../midnightmeadow/region.0.0 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/sunnyhill/region/r.-1.-1.mcr ../midnightmeadow/region.-1.-1 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/sunnyhill/region/r.0.-1.mcr  ../midnightmeadow/region.0.-1 $ALL_REGIONS $CROP &
$PYTHON mc.py $HOME/sunnyhill/region/r.-1.0.mcr  ../midnightmeadow/region.-1.0 $ALL_REGIONS $CROP &

wait

cat ../midnightmeadow/region*.lights.vtx > ../midnightmeadow/global.lights.vtx

cat ../midnightmeadow/region*.dump > ../midnightmeadow/global.dump
$PYTHON intkeys.py ../midnightmeadow/global.dump | $HOME/nbperf/nbperf -n midnightmeadow_hash -I -a bpz -c 1.24 -m ../love2dworld/map.txt > ../midnightmeadow/inthash.c
