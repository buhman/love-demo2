set -eux
cd ./minecraft/gen
PYTHON=pypy3.11
$PYTHON blocks.py ../block_id_to_texture_id.data
