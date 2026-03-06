import struct

def id_to_px(i):
    x = i % 16
    y = i // 16
    return x * 16, y * 16

def px_to_id(px, py):
    x = px // 16
    y = py // 16
    i = y * 16 + x
    return i

unk = 185

mapping = [
    (1, 1, "stone"),
    (2, 0, "grass"),
    (31, 0, "grass"), # fixme actually tallgrass
    (3, 2, "dirt"),
    (4, 16, "stonebrick"),
    (5, 4, "wood"),
    (6, 15, "sapling"),
    (7, 17, "bedrock"),
    (8, 205, "water"), # flowing
    (9, 205, "water"), # still
    (10, 237, "lava"), # flowing
    (11, 237, "lava"), # still
    (12, 18, "sand"),
    (13, 19, "gravel"),
    (14, 32, "oreGold"),
    (15, 33, "oreIron"),
    (16, 34, "oreCoal"),
    (17, 20, "log"),
    (18, 52, "leaves"),
    (19, 48, "sponge"),
    (20, 49, "glass"),
    (35, 64, "cloth"),
    (37, 13, "flower"),
    (38, 12, "rose"),
    (39, 29, "mushroom"),
    (40, 28, "mushroom"),
    (41, 39, "blockGold"),
    (42, 38, "blockIron"),
    (43, 5, "stoneSlab"), # double
    (44, 5, "stoneSlab"), # single
    (45, 7, "brick"),
    (46, 8, "tnt"),
    (47, 35, "bookshelf"),
    (48, 36, "stoneMoss"),
    (49, 37, "obsidian"),
    (50, 80, "torch"),
    (51, 31, "fire"),
    (52, 65, "mobSpawner"),
    (53, 4, "stairsWood"),
    (54, 27, "chest"),
    (55, 84, "redstoneDust"),
    (56, 50, "oreDiamond"),
    (57, 40, "blockDiamond"),
    (58, 43, "workbench"),
    (59, 88, "crops"),
    (60, 87, "farmland"),
    (61, 44, "furnace"), # off
    (62, 61, "furnace"), # burning
    (63, unk, "sign"),
    (64, 81, "doorWood"),
    (65, 83, "ladder"),
    (66, 128, "rail"),
    (67, 16, "stairsStone"),
    (68, unk, "sign"),
    (69, 96, "lever"),
    (70, 6, "pressurePlate"),
    (71, 82, "doorIron"),
    (72, 6, "pressurePlate"),
    (73, 51, "oreRedstone"),
    (74, 51, "oreRedstone"),
    (75, 115, "notGate"),
    (76, 99, "notGate"),
    (77, unk, "button"),
    (78, 66, "snow"),
    (79, 67, "ice"),
    (80, 66, "snow"),
    (81, 70, "cactus"),
    (82, 72, "clay"),
    (83, 73, "reeds"),
    (84, 74, "jukebox"),
    (85, 4, "fence"),
    (86, 102, "pumpkin"),
    (87, 103, "hellrock"),
    (88, 104, "hellsand"),
    (89, 105, "lightgem"),
    (90, 14, "portal"),
    (91, 102, "pumpkin"),
]

lookup = {
    k: v for k, v, _ in mapping
}

with open("block_id_to_texture_id.data", "wb") as f:
    for i in range(256):
        value = lookup.get(i, unk)
        f.write(struct.pack("<i", value))
        print(str(value)+',')
