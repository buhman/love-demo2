set -eux

PYTHONPATH=~/d3d10 python -m collada.main \
                   ~/love-demo/scene/noodle/noodle.DAE \
                   data/scenes/noodle/noodle.cpp \
                   data/scenes/noodle/noodle.vtx \
                   data/scenes/noodle/noodle.vjw \
                   data/scenes/noodle/noodle.idx

PYTHONPATH=~/d3d10 python -m collada.main \
                   include/data/scenes/noodle.h

# shadow_test

PYTHONPATH=~/d3d10 python -m collada.main \
                   ~/love-demo/scene/shadow_test/shadow_test.DAE \
                   data/scenes/shadow_test/shadow_test.cpp \
                   data/scenes/shadow_test/shadow_test.vtx \
                   data/scenes/shadow_test/shadow_test.vjw \
                   data/scenes/shadow_test/shadow_test.idx

PYTHONPATH=~/d3d10 python -m collada.main \
                   include/data/scenes/shadow_test.h

# book

PYTHONPATH=~/d3d10 python -m collada.main \
                   ~/Downloads/book.DAE \
                   data/scenes/book/book.cpp \
                   data/scenes/book/book.vtx \
                   data/scenes/book/book.vjw \
                   data/scenes/book/book.idx

PYTHONPATH=~/d3d10 python -m collada.main \
                   include/data/scenes/book.h
