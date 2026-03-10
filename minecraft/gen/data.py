from dataclasses import dataclass

class BlockID:
    AIR = 0
    STONE = 1
    GRASS = 2
    DIRT = 3
    STONEBRICK = 4
    WOOD = 5
    SAPLING = 6
    BEDROCK = 7
    WATER = 8
    WATER_CALM = 9
    LAVA = 10
    LAVA_CALM = 11
    SAND = 12
    GRAVEL = 13
    ORE_GOLD = 14
    ORE_IRON = 15
    ORE_COAL = 16
    TREE_TRUNK = 17
    LEAVES = 18
    SPONGE = 19
    GLASS = 20
    ORE_LAPIS = 21
    BLOCK_LAPIS = 22
    DISPENSER = 23
    SANDSTONE = 24
    NOTE_BLOCK = 25
    BED = 26
    RAIL_POWERED = 27
    RAIL_ACTIVATOR = 28
    PISTON_STICKY = 29
    COBWEB = 30
    TALL_GRASS = 31
    DEAD_BUSH = 32
    PISTON = 33
    PISTON_HEAD = 34
    CLOTH = 35
    PISTON_MOVING = 36
    FLOWER = 37
    ROSE = 38
    MUSHROOM_1 = 39
    MUSHROOM_2 = 40
    BLOCK_GOLD = 41
    BLOCK_IRON = 42
    STONESLAB_FULL = 43
    STONESLAB_HALF = 44
    BRICKS = 45
    TNT = 46
    BOOKSHELF = 47
    MOSS_STONE = 48
    OBSIDIAN = 49
    TORCH = 50
    FIRE = 51
    SPAWNER = 52
    STAIRS_WOOD = 53
    CHEST = 54
    WIRE = 55
    ORE_EMERALD = 56
    BLOCK_EMERALD = 57
    WORKBENCH = 58
    WHEAT = 59
    FARMLAND = 60
    FURNACE = 61
    FURNACE_LIT = 62
    SIGN = 63
    DOOR_WOOD = 64
    LADDER = 65
    RAIL = 66
    STAIRS_STONE = 67
    SIGN_WALL = 68
    LEVER = 69
    PLATE_STONE = 70
    DOOR_IRON = 71
    PLATE_WOOD = 72
    ORE_REDSTONE = 73
    ORE_REDSTONE_LIT = 74
    NOT_GATE_OFF = 75
    NOT_GATE_ON = 76
    BUTTON_STONE = 77
    TOPSNOW = 78
    ICE = 79
    SNOW = 80
    CACTUS = 81
    CLAY = 82
    REEDS = 83
    JUKEBOX = 84
    FENCE = 85
    PUMPKIN = 86
    NETHERRACK = 87
    SOUL_SAND = 88
    GLOWSTONE = 89
    PORTAL = 90
    PUMPKIN_LIT = 91
    CAKE = 92
    REPEATER_OFF = 93
    REPEATER_ON = 94
    INVISIBLE = 95
    TRAPDOOR = 96
    STONE_MONSTER_EGG = 97
    STONE_BRICKS = 98
    MUSHROOM1_BLOCK = 99
    MUSHROOM2_BLOCK = 100
    CLOTH_00 = 101
    CLOTH_10 = 102
    CLOTH_20 = 103
    CLOTH_30 = 104
    CLOTH_40 = 105
    CLOTH_50 = 106
    CLOTH_60 = 107
    CLOTH_70 = 108
    CLOTH_01 = 109
    CLOTH_11 = 110
    CLOTH_21 = 111
    CLOTH_31 = 112
    CLOTH_41 = 113
    CLOTH_51 = 114
    CLOTH_61 = 115

    # modded
    YELLOW_COBBLE = 128
    MARBLE_YELLOW = 248

class Texture:
    GRASS_TOP = 0
    STONE = 1
    DIRT = 2
    GRASS_SIDE = 3
    PLANKS = 4
    STONE_SLAB_SIDE = 5
    STONE_SLAB_TOP = 6
    BRICKS = 7
    TNT_SIDE = 8
    TNT_TOP = 9
    TNT_BOTTOM = 10
    COBWEB = 11
    ROSE = 12
    FLOWER = 13
    WATER_STATIC = 14
    SAPLING = 15
    STONEBRICK = 16
    BEDROCK = 17
    SAND = 18
    GRAVEL = 19
    LOG_SIDE = 20
    LOG_TOP = 21
    IRON = 22
    GOLD = 23
    EMERALD = 24
    CHEST_ONE_TOP = 25
    CHEST_ONE_SIDE = 26
    CHEST_ONE_FRONT = 27
    MUSHROOM_RED = 28
    MUSHROOM_BROWN = 29
    OBSIDIAN_CRYING = 30
    FIRE1 = 31
    ORE_GOLD = 32
    ORE_IRON = 33
    ORE_COAL = 34
    BOOKSHELF = 35
    MOSSY_STONE = 36
    OBSIDIAN = 37
    GRASS_SIDE_OVERLAY = 38
    TALL_GRASS = 39
    NONE40 = 40
    CHEST_TWO_FRONT_LEFT = 41
    CHEST_TWO_FRONT_RIGHT = 42
    WORKBENCH_TOP = 43
    FURNACE_FRONT = 44
    FURNACE_SIDE = 45
    DISPENSER_SIDE = 46
    FIRE2 = 47
    SPONGE = 48
    GLASS = 49
    ORE_EMERALD = 50
    ORE_RED_STONE = 51
    LEAVES_TRANSPARENT = 52
    LEAVES_OPAQUE = 53
    NONE54 = 54
    DEAD_BUSH = 55
    NONE56 = 56
    CHEST_TWO_BACK_LEFT = 57
    CHEST_TWO_BACK_RIGHT = 58
    WORKBENCH_SIDE_1 = 59
    WORKBENCH_SIDE_2 = 60
    FURNACE_LIT = 61
    FURNACE_TOP = 62
    NONE63 = 63
    CLOTH_64 = 64
    SPAWNER = 65
    SNOW = 66
    ICE = 67
    GRASS_SIDE_SNOW = 68
    CACTUS_TOP = 69
    CACTUS_SIDE = 70
    CACTUS_BOTTOM = 71
    CLAY = 72
    REEDS = 73
    JUKEBOX_SIDE = 74
    JUKEBOX_TOP = 75
    NONE76 = 76
    NONE77 = 77
    NONE78 = 78
    NONE79 = 79
    TORCH_LIT = 80
    DOOR_TOP = 81
    DOOR_IRON_TOP = 82
    LADDER = 83
    TRAPDOOR = 84
    NONE85 = 85
    FARMLAND = 86
    FARMLAND_DRY = 87
    WHEAT_0 = 88
    WHEAT_1 = 89
    WHEAT_2 = 90
    WHEAT_3 = 91
    WHEAT_4 = 92
    WHEAT_5 = 93
    WHEAT_6 = 94
    WHEAT_7 = 95
    LEVER = 96
    DOOR_BOTTOM = 97
    DOOR_IRON_BOTTOM = 98
    TORCH_RED_STONE = 99
    NONE100 = 100
    NONE101 = 101
    PUMPKIN_TOP = 102
    BLOODSTONE = 103
    SOULSAND = 104
    GLOWSTONE = 105
    STICKY_PISTON = 106
    PISTON = 107
    NONE108 = 108
    NONE109 = 109
    NONE110 = 110
    NONE111 = 111
    RAIL_CURVED = 112
    CLOTH_112 = 113
    CLOTH_113 = 114
    TORCH_RED_STONE_OFF = 115
    LOG_SPRUCE = 116
    LOG_BIRCH = 117
    PUMPKIN_SIDE = 118
    PUMPKIN_FACE = 119
    PUMPKIN_FACE_LIT = 120
    CAKE_TOP = 121
    CAKE_SIDE = 122
    CAKE_SIDE_BIT = 123
    CAKE_BOTTOM = 124
    NONE125 = 125
    NONE126 = 126
    NONE127 = 127
    RAIL = 128

    LAPIS = 144
    ORE_LAPIS = 160
    POWERED_RAIL = 163
    REDSTONE_DUST = 164
    REDSTONE_DUST_LINE = 165

    DETECTOR_RAIL = 195

    SANDSTONE_TOP = 176
    SANDSTONE_SIDE = 192
    WATER = 205
    SANDSTONE_BOTTOM = 208

    LAVA = 237

    INFO_UPDATEGAME1 = 252
    INFO_UPDATEGAME2 = 253

    LAVA_PLACEHOLDER = 255

    # modded
    YELLOW_COBBLE = 213
    MARBLE_YELLOW = 214

@dataclass
class Tile:
    block_id: BlockID
    texture: Texture

tiles = [
    Tile(BlockID.STONE, Texture.STONE),
    Tile(BlockID.GRASS, Texture.GRASS_TOP), # fixme
    Tile(BlockID.DIRT, Texture.DIRT),
    Tile(BlockID.STONEBRICK, Texture.STONEBRICK),
    Tile(BlockID.WOOD, Texture.PLANKS),
    Tile(BlockID.BEDROCK, Texture.BEDROCK),
    Tile(BlockID.WATER, Texture.WATER), # fixme
    Tile(BlockID.WATER_CALM, Texture.WATER), # fixme
    Tile(BlockID.LAVA, Texture.LAVA), # fixme
    Tile(BlockID.LAVA_CALM, Texture.LAVA), # fixme
    Tile(BlockID.SAND, Texture.SAND),
    Tile(BlockID.GRAVEL, Texture.GRAVEL),
    Tile(BlockID.ORE_GOLD, Texture.ORE_GOLD),
    Tile(BlockID.ORE_IRON, Texture.ORE_IRON),
    Tile(BlockID.ORE_COAL, Texture.ORE_COAL),
    Tile(BlockID.TREE_TRUNK, Texture.LOG_SIDE), # fixme
    Tile(BlockID.LEAVES, Texture.LEAVES_TRANSPARENT), # fixme
    Tile(BlockID.GLASS, Texture.GLASS),
    Tile(BlockID.ORE_LAPIS, Texture.ORE_LAPIS),
    Tile(BlockID.BLOCK_LAPIS, Texture.LAPIS),
    Tile(BlockID.SANDSTONE, Texture.SANDSTONE_SIDE),
    Tile(BlockID.CLOTH, Texture.CLOTH_64), # wool, colored
    Tile(BlockID.FLOWER, Texture.FLOWER),
    Tile(BlockID.ROSE, Texture.ROSE),
    Tile(BlockID.MUSHROOM_1, Texture.MUSHROOM_BROWN),
    Tile(BlockID.MUSHROOM_2, Texture.MUSHROOM_RED),
    Tile(BlockID.BLOCK_GOLD, Texture.GOLD),
    Tile(BlockID.BLOCK_IRON, Texture.IRON),
    Tile(BlockID.STONESLAB_FULL, Texture.STONE_SLAB_SIDE), # fixme
    Tile(BlockID.STONESLAB_HALF, Texture.STONE_SLAB_SIDE), # fixme
    Tile(BlockID.BRICKS, Texture.BRICKS),
    Tile(BlockID.TNT, Texture.TNT_SIDE),
    Tile(BlockID.BOOKSHELF, Texture.BOOKSHELF),
    Tile(BlockID.MOSS_STONE, Texture.MOSSY_STONE),
    Tile(BlockID.OBSIDIAN, Texture.OBSIDIAN),
    Tile(BlockID.TORCH, Texture.TORCH_LIT),
    Tile(BlockID.STAIRS_WOOD, Texture.PLANKS), # fixme
    Tile(BlockID.WIRE, Texture.REDSTONE_DUST),
    Tile(BlockID.ORE_EMERALD, Texture.ORE_EMERALD),
    Tile(BlockID.BLOCK_EMERALD, Texture.EMERALD),
    Tile(BlockID.FARMLAND, Texture.FARMLAND), # fixme
    Tile(BlockID.DOOR_WOOD, Texture.DOOR_TOP), # fixme
    Tile(BlockID.LADDER, Texture.LADDER),
    Tile(BlockID.STAIRS_STONE, Texture.STONEBRICK),
    Tile(BlockID.DOOR_IRON, Texture.DOOR_IRON_TOP), # fixme
    Tile(BlockID.ORE_REDSTONE, Texture.ORE_RED_STONE), # fixme
    Tile(BlockID.ORE_REDSTONE_LIT, Texture.ORE_RED_STONE), # fixme
    Tile(BlockID.TOPSNOW, Texture.SNOW),
    Tile(BlockID.ICE, Texture.ICE),
    Tile(BlockID.SNOW, Texture.SNOW),
    Tile(BlockID.CACTUS, Texture.CACTUS_SIDE),
    Tile(BlockID.CLAY, Texture.CLAY),
    Tile(BlockID.REEDS, Texture.REEDS),
    Tile(BlockID.FENCE, Texture.PLANKS),
    Tile(BlockID.INVISIBLE, Texture.STONE),
    Tile(BlockID.WOOD, Texture.PLANKS),
    #Tile(BlockID.LEAVES_CARRIED, Texture.LEAVES_TRANSPARENT), # fixme
    Tile(BlockID.FIRE, Texture.FIRE1),
    Tile(BlockID.SAPLING, Texture.SAPLING),
    Tile(BlockID.SPONGE, Texture.SPONGE),
    Tile(BlockID.TALL_GRASS, Texture.TALL_GRASS),
    Tile(BlockID.DEAD_BUSH, Texture.DEAD_BUSH),
    Tile(BlockID.PUMPKIN, Texture.PUMPKIN_FACE), # fixme
    Tile(BlockID.PUMPKIN_LIT, Texture.PUMPKIN_FACE_LIT), # fixme
    Tile(BlockID.NETHERRACK, Texture.BLOODSTONE),
    Tile(BlockID.SOUL_SAND, Texture.SOULSAND),
    Tile(BlockID.GLOWSTONE, Texture.GLOWSTONE),
    Tile(BlockID.COBWEB, Texture.COBWEB),
    Tile(BlockID.WORKBENCH, Texture.WORKBENCH_TOP), # fixme
    Tile(BlockID.WHEAT, Texture.WHEAT_0),

    # modded blocks
    Tile(BlockID.YELLOW_COBBLE, Texture.YELLOW_COBBLE),
    Tile(BlockID.MARBLE_YELLOW, Texture.MARBLE_YELLOW),
]

tiles_by_id = {
    tile.block_id: tile for tile in tiles
}
