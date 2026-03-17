set -eux

PYTHONPATH=~/d3d10 python -m collada.main \
                   path/to/noodle.DAE \
                   data/scenes/noodle/noodle.cpp \
                   data/scenes/noodle/noodle.vtx \
                   data/scenes/noodle/noodle.vjw \
                   data/scenes/noodle/noodle.idx

PYTHONPATH=~/d3d10 python -m collada.main \
                   include/data/scenes/noodle.h
