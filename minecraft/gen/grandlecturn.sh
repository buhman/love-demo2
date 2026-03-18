set -eux
#cd ./minecraft/gen
PYTHON=pypy3.11
cat <<EOF > ../grandlecturn/all_regions.txt
$HOME/GrandLecturn/region/r.0.0.mcr
$HOME/GrandLecturn/region/r.-1.-1.mcr
$HOME/GrandLecturn/region/r.0.-1.mcr
$HOME/GrandLecturn/region/r.-1.0.mcr
EOF
$PYTHON mc.py $HOME/GrandLecturn/region/r.0.0.mcr   ../grandlecturn/region.0.0 ../grandlecturn/all_regions.txt &
$PYTHON mc.py $HOME/GrandLecturn/region/r.-1.-1.mcr ../grandlecturn/region.-1.-1 ../grandlecturn/all_regions.txt &
$PYTHON mc.py $HOME/GrandLecturn/region/r.0.-1.mcr  ../grandlecturn/region.0.-1 ../grandlecturn/all_regions.txt &
$PYTHON mc.py $HOME/GrandLecturn/region/r.-1.0.mcr  ../grandlecturn/region.-1.0 ../grandlecturn/all_regions.txt &

wait

cat ../grandlecturn/region*.lights.vtx > ../grandlecturn/global.lights.vtx

cat ../grandlecturn/region*.dump > ../grandlecturn/global.dump
$PYTHON intkeys.py ../grandlecturn/global.dump | $HOME/nbperf/nbperf -n grandlecturn_hash -I -a bpz -c 1.26 -m ../love2dworld/map.txt > ../grandlecturn/inthash.c
