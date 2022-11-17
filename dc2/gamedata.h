#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 001937C0 - 00196130


enum class ECommonItemDataType : u8
{
  Invalid = 0,
  Melee_Max = 1,
  Ranged_Max = 2,
  Melee_Monica = 3,
  Ranged_Monica = 4,
  Torso_Max = 5,
  Hat_Max = 6,
  Shoes_Max = 7,
  Torso_Monica = 8,
  Hat_Monica = 9,
  Shoes_Monica = 10,
  Ridepod_Core = 11,
  Ridepod_Body = 12,
  Ridepod_Arm = 13,
  Ridepod_Leg = 14,
  Ridepod_Battery = 15,
  Crystal = 16,
  _17 = 17,
  Gem = 18,
  Coin = 19,
  Crafting_Material = 20,
  Badge_Box = 21,
  Food = 22,
  Throwable = 23,
  Powder = 24,
  Amulet = 25,
  Dungeon_Key = 26,
  Story_Item = 27,
  Gift_Capsule = 28,
  Aquarium = 29,
  Fish = 30,
  _31 = 31,
  Lure = 32,
  Dungeon_Item_Or_Bait = 33,
  _34 = 34,
  _35 = 35,
  _36 = 36,
};


enum class ECommonItemData
{
  Invalid = 0,
  Battle_Wrench = 1,
  Drill_Wrench = 2,
  Smash_Wrench = 3,
  Stinger_Wrench = 4,
  Posion_Wrench = 5,
  Cubic_Hammer = 6,
  Digi_Hammer = 7,
  Heavy_Hammer = 8,
  Handy_Stick = 9,
  Turkey = 10,
  Swan = 11,
  Flamingo = 12,
  Falcon = 13,
  Albatross = 14,
  Turtle_Shell_Hammer = 15,
  Big_Bucks_Hammer = 16,
  Frozen_Tuna = 17,
  Kuberas_Hand = 18,
  Sigma_Breaker = 19,
  Grade_Zero = 20,
  LEGEND = 21,
  Classic_Gun = 22,
  Dryer_Gun = 23,
  Trumpet_Gun = 24,
  Bell_Trigger = 25,
  Magic_Gun = 26,
  Soul_Breaker = 27,
  Grenade_Launcher = 28,
  Dark_Viper = 29,
  Twin_Buster = 30,
  Jurak_Gun = 31,
  Question_Shooter = 32,
  Steal_Gun = 33,
  Supernova = 34,
  Star_Breaker = 35,
  Wild_Cat = 36,
  Sexy_Panther = 37,
  Desperado = 38,
  Sigma_Bazooka = 39,
  Last_Resort = 40,
  Long_Sword = 41,
  Broad_Sword = 42,
  Baselard = 43,
  Gladius = 44,
  Wise_Owl_Sword = 45,
  Cliff_Knife = 46,
  Antique_Sword = 47,
  Bastard_Sword = 48,
  Kitchen_Knife = 49,
  Tsukikage = 50,
  Sun_Sword = 51,
  Serpent_Slicer = 52,
  Macho_Sword = 53,
  Shamshir = 54,
  Ama_No_Murakumo = 55,
  Lambs_Sword = 56,
  Dark_Cloud = 57,
  Brave_Ark = 58,
  Big_Bang = 59,
  Atlamilla_Sword = 60,
  Mardan_Sword = 61,
  Garayan_Sword = 62,
  Mardan_Garayan_Weapon = 63,
  Rulers_Sword = 64,
  Evilcise = 65,
  Small_Sword = 66,
  Sand_Breaker = 67,
  Drain_Seeker = 68,
  Chopper = 69,
  Choora = 70,
  Claymore = 71,
  Maneater = 72,
  Bone_Rapier = 73,
  Sax = 74,
  Seven_Branch_Sword = 75,
  Dusack = 76,
  Cross_Heinder = 77,
  Seventh_Heaven = 78,
  Sword_Of_Zeus = 79,
  Chronicle_Sword = 80,
  Chronicle_2 = 81,
  Holy_Daedalus_Blade = 82,
  Muramasa = 83,
  Dark_Excaliber = 84,
  Sargatanas = 85,
  Halloween_Blade = 86,
  Shining_Bravado = 87,
  Island_King = 88,
  Griffon_Fork = 89,
  True_Battle_Wrench = 90,
  Magic_Brassard = 91,
  Gold_Brassard = 92,
  Bandit_Brassard = 93,
  Crystal_Brassard = 94,
  Platinum_Brassard = 95,
  Goddess_Brassard = 96,
  Spirit_Brassard = 97,
  Destruction_Brassard = 98,
  Satan_Brassard = 99,
  Athenas_Armlet = 100,
  Mobius_Bangle = 101,
  Angel_Shooter = 102,
  Pocklekul = 103,
  Thorn_Armlet = 104,
  Star_Armlet = 105,
  Moon_Armlet = 106,
  Sun_Armlet = 107,
  Five_Star_Armlet = 108,
  Love = 109,
  Royal_Sword = 110,
  Hunting_Cap = 111,
  Fashionable_Cap = 112,
  Two_Tone_Beret = 113,
  Maintenance_Cap = 114,
  Explorers_Helmet = 115,
  Clown_Hat = 116,
  Leather_Shoes = 117,
  Wing_Shoes = 118,
  Work_Shoes = 119,
  Dragon_Shoes = 120,
  Clown_Shoes = 121,
  Explorers_Shoes = 122,
  Yellow_Ribbon = 123,
  Stripe_Ribbon = 124,
  Zipangu_Comb = 125,
  Shallowtail = 126,
  Princess_Orb = 127,
  Kitty_Bell = 128,
  Knight_Boots = 129,
  Metal_Boots = 130,
  Wing_Boots = 131,
  Spike_Boots = 132,
  Princess_Boots = 133,
  Panther_Boots = 134,
  Drum_Can_Body = 135,
  Milk_Can_Body = 136,
  Refrigerator_Body = 137,
  Wooden_Box_Body = 138,
  Clown_Body = 139,
  Samurai_Body = 140,
  Super_Alloy_Body = 141,
  Sun_And_Moon_Armor = 142,
  Cannonball_Arm = 145,
  Barrel_Cannon = 146,
  Drill_Arm = 147,
  Missile_Pod_Arm = 148,
  Hammer_Arm = 149,
  Machine_Gun_Arm = 150,
  Clown_Hand = 151,
  Samurai_Arm = 152,
  Laser_Arm = 153,
  Nova_Cannon = 154,
  Iron_Leg = 155,
  Caterpillar = 156,
  Bucket_Leg = 157,
  Roller_Foot = 158,
  Buggy = 159,
  Propeller_Leg = 160,
  Multi_Feet = 161,
  Jet_Hover = 162,
  Clown_Foot = 163,
  Energy_Pack = 165,
  Energy_Pack_Barrel = 166,
  Bucket_Pack = 167,
  Cleaner_Pack = 168,
  Energy_Pack_Urn = 169,
  Triple_Urn_Pack = 170,
  Monster_Notes = 172,
  Dynamite = 173,
  Seal_Breaking_Scroll = 174,
  Flame_Crystal = 175,
  Chill_Crystal = 176,
  Lightning_Crystal = 177,
  Hunter_Crystal = 178,
  Holy_Crystal = 179,
  Destruction_Crystal = 180,
  Wind_Crystal = 181,
  Sea_Dragon_Crystal = 182,
  Power_Crystal = 183,
  Protector_Crystal = 184,
  Unknown185 = 185,
  Garnet = 186,
  Amethyst = 187,
  Aquamarine = 188,
  Diamond = 189,
  Emerald = 190,
  Pearl = 191,
  Ruby = 192,
  Peridot = 193,
  Sapphire = 194,
  Opal = 195,
  Topaz = 196,
  Turquoise = 197,
  Sun_Stone = 198,
  Moon_Stone = 199,
  Wealth_Coin = 200,
  Dark_Coin = 201,
  Indestructible_Coin = 202,
  Poison_Coin = 203,
  Time_Coin = 204,
  Bandit_Coin = 205,
  Absorption_Coin = 206,
  Healing_Coin = 207,
  Bulls_Eye_Coin = 208,
  Experience_Coin = 209,
  Rolling_Log = 210,
  Sturdy_Rock = 211,
  Rough_Rock = 212,
  Bundle_Of_Hay = 213,
  Sturdy_Cloth = 214,
  Gunpowder = 215,
  Glass_Material = 216,
  Unknown_Bone = 217,
  Sticky_Clay = 218,
  Flour = 219,
  Sugar_Cane = 220,
  Super_Hot_Pepper = 221,
  Posion = 222,
  Forest_Dew = 223,
  Scrap_Of_Metal = 224,
  Gold_Bar = 225,
  Silver_Ball = 226,
  Hunk_Of_Copper = 227,
  Light_Element = 228,
  Holy_Element = 229,
  Earth_Element = 230,
  Water_Element = 231,
  Chill_Element = 232,
  Thunder_Element = 233,
  Wind_Element = 234,
  Fire_Element = 235,
  Life_Element = 236,
  Paint_Red = 237,
  Paint_Blue = 238,
  Paint_Black = 239,
  Paint_Green = 240,
  Paint_Orange = 241,
  Paint_Yellow = 242,
  Paint_Purple = 243,
  Paint_Pink = 244,
  Thick_Hide = 245,
  Core = 246,
  Improved_Core = 247,
  Core_II = 248,
  Core_III = 249,
  Super_Core = 250,
  Hyper_Core = 251,
  Master_Grade_Core = 252,
  Anti_Petrify_Amulet = 253,
  Non_Stop_Amulet = 254,
  Anti_Curse_Amulet = 255,
  Anti_Goo_Amulet = 256,
  Antidote_Amulet = 257,
  Green_Overalls = 258,
  Red_Vest = 259,
  Denim_Overalls = 260,
  Explorers_Outfit = 261,
  Clown_Suit = 262,
  Pumpkin_Shorts = 263,
  Striped_Dress = 264,
  Star_Leotard = 265,
  Princess_Dress = 266,
  Panther_Ensemble = 267,
  Bread = 268,
  Cheese = 269,
  Premium_Chicken = 270,
  Double_Pudding = 271,
  Plum_Rice_Ball = 272,
  Resurrection_Powder = 273,
  Stamina_Drink = 274,
  Antidote_Drink = 275,
  Holy_Water = 276,
  Soap = 277,
  Medusas_Tear = 278,
  Mighty_Healing = 279,
  Bomb = 280,
  Stone = 281,
  Flame_Stone = 282,
  Chill_Stone = 283,
  Lightning_Stone = 284,
  Wind_Stone = 285,
  Holy_Stone = 286,
  Heart_Throb_Cherry = 287,
  Stone_Berry = 288,
  Gooey_Peach = 289,
  Bomb_Nut = 290,
  Poison_Apple = 291,
  Mellow_Banana = 292,
  Escape_Powder = 293,
  Repair_Powder = 294,
  Level_Up_Powder = 295,
  Fruit_Of_Eden = 296,
  Treasure_Chest_Key = 297,
  Gun_Repair_Powder = 298,
  Crunchy_Bread = 299,
  Crunchy_Bread2 = 300,
  Roasted_Chestnut = 301,
  Fishing_Rod = 302,
  Lure_Rod = 303,
  Gift_Capsule = 304,
  Map = 305,
  Magic_Crystal = 306,
  Lightspeed = 307,
  Badge_Box = 308,
  Aquarium = 309,
  Priscleen = 310,
  Medal_Holder = 311,
  Prickly = 312,
  Mimi = 313,
  Evy = 314,
  Carrot = 315,
  Potato_Cake = 316,
  Minon = 317,
  Battan = 318,
  Petite_Fish = 319,
  Bobo = 320,
  Gobbler = 321,
  Nonky = 322,
  Kaji = 323,
  Baku_Baku = 324,
  Mardan_Garayan_Fish = 325,
  Gummy = 326,
  Niler = 327,
  Umadakara = 328,
  Tarton = 329,
  Piccoly = 330,
  Bon = 331,
  Hama_Hama = 332,
  Negie = 333,
  Den = 334,
  Heela = 335,
  Baron_Garayan = 336,
  Key_Handle = 337,
  Channel_Key = 338,
  Fairy_Saw = 339,
  Slash_Branch = 340,
  Giant_Meat = 341,
  Luna_Stone = 342,
  Luna_Stone_Piece = 343,
  Magma_Rock = 344,
  Rope = 345,
  Stone_T = 346,
  White_Wind_Vase = 347,
  Queens_Watering_Pot = 348,
  Moon_Clock_Hand = 349,
  Trolley_Oil = 350,
  Rusted_Key = 351,
  Armband_Repair_Powder = 352,
  Circus_Ticket = 353,
  Fire_Horn = 354,
  Inside_Scoop_Memo = 355,
  Sundrop = 356,
  Photo_Album = 357,
  Cooking_Stove = 358,
  Help_Receiver = 359,
  Electric_Worm = 360,
  Lafrescia_Seed = 361,
  Star_Key = 362,
  White_Windflower = 363,
  Miracle_Dumplings = 364,
  Earth_Gem = 365,
  Water_Gem = 366,
  Wind_Gem = 367,
  Fire_Gem = 368,
  Camera = 369,
  Grape_Juice = 370,
  Starglass = 371,
  Time_Bomb = 372,
  Shell_Talkie = 373,
  Flower_Of_The_Sun = 374,
  Secret_Dragon_Remedy = 375,
  Gold_Paint = 376,
  Spinner = 377,
  Frog = 378,
  Minnow = 379,
  Fork = 380,
  Ridepod_Fuel = 381,
  Wrench = 382,
  Monster_Drop = 383,
  Name_Change_Ticket = 384,
  Teal_Envelope = 385,
  Notebook = 386,
  Wrench2 = 387,
  Potato_Pie = 388,
  Witch_Parfait = 389,
  Improved_Bomb = 390,
  Final_Bomb = 391,
  Cannonball_Arm_II = 392,
  Cannonball_Arm_III = 393,
  Cannonball_Arm_IV = 394,
  Barrel_Cannon_II = 395,
  Barrel_Cannon_III = 396,
  Barrel_Cannon_IV = 397,
  Drill_Arm_II = 398,
  Drill_Arm_III = 399,
  Drill_Arm_IV = 400,
  Missile_Pod_Arm_II = 401,
  Missile_Pod_Arm_III = 402,
  Missile_Pod_Arm_IV = 403,
  Hammer_Arm_II = 404,
  Hammer_Arm_III = 405,
  Hammer_Arm_IV = 406,
  Machine_Gun_Arm_II = 407,
  Machine_Gun_Arm_III = 408,
  Machine_Gun_Arm_IV = 409,
  Clown_Hand_II = 410,
  Clown_Hand_III = 411,
  Clown_Hand_IV = 412,
  Samurai_Arm_II = 413,
  Samurai_Arm_III = 414,
  Samurai_Arm_IV = 415,
  Laser_Arm_II = 416,
  Laser_Arm_III = 417,
  Laser_Arm_IV = 418,
  Nova_Cannon_II = 419,
  Nova_Cannon_III = 420,
  Nova_Cannon_IV = 421,
  Voice_Unit = 422,
  Shield_Kit = 423,
  Himarra_Badge = 424,
  Tasty_Water = 425,
  Sun_Badge = 427,
  Moon_Badge = 428,
};

enum class EUsedItemType
{
  Invalid = 0,
  Item_Misc = 1,
  Attach = 2,
  Weapon = 3,
  Clothing = 4,
  Robopart = 5,
  Fish = 6,
  Item_Gift = 7,
  Item_8 = 8,
};

struct ATTACH_USED
{
  
};

struct SDataItemCommon
{
  // 0
  ECommonItemDataType m_type{ ECommonItemDataType::Invalid };
  // 2
  ECommonItemData m_common_id{ ECommonItemData::Invalid };
  // 4
  s16 m_unk_field_4{ 0 };
  // 6
  s16 m_unk_field_6{ 0 };
  // 8
  s16 m_unk_field_8{ 0 };
  // A
  s16 m_unk_field_A{ 0 };
  // C
  std::array<char, 0x10> m_sprite_name{};
  // 1C
  s8 m_unk_field_1C{ 0 };
  // 1E
  s16 m_unk_field_1E{ 0 };
  // 20
  s8 m_unk_field_20{ 0 };
  // 24
  s32 m_unk_field_24{ 0 };
  // 28
  std::string m_name{};
  // SIZE 0x2C
};

class CDataItem
{
  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  _DWORD m_unk_field_4{ 0 };
  // 8
  // ?
  // A
  _WORD m_unk_field_A{ 0 };
  // C
  _WORD m_unk_field_C{ 0 };
  // E
  _WORD m_unk_field_E{ 0 };
};

class CDataAttach
{
  // memset all to 0
  // SIZE 0x18
};

class CDataWeapon
{
public:
  // memset all to 0 (except field 0 and 2)
  // 0
  s16 m_unk_field_0{ 20 };
  // 2
  s16 m_unk_field_2{ 20 };
  // 4
  s16 m_unk_field_4{ 0 };
  // 6
  s16 m_unk_field_6{ 0 };
  // 8
  s16 m_unk_field_8{ 0 };
  // A
  s16 m_unk_field_A{ 0 };
  // C
  std::array<s16, 8> m_unk_field_C{ 0 };
  // 1C
  std::array<s16, 8> m_unk_field_1C{ 0 };
  
  // ?

  // 2C
  s32 m_unk_field_2C{ 0 };

  // ?

  // 38
  u8 m_unk_field_38{ 0 };
  // 39
  s8 m_unk_field_39{ 0 };
  // 3A
  s16 m_unk_field_3A{ 0 };
  // 3C
  s16 m_unk_field_3C{ 0 };
  // 3E
  s16 m_unk_field_3E{ 0 };
  // 40
  s16 m_unk_field_40{ 0 };
  // 42
  s16 m_unk_field_42{ 0 };
  // 44
  s16 m_unk_field_44{ 0 };
  // 46
  s8 m_unk_field_46{ 0 };
  // 47
  s8 m_unk_field_47{ 0 };
  // 48
  s8 m_unk_field_48{ 0 };
  // 49
  s8 m_unk_field_49{ 0 };

  // SIZE 0x4C
};

class CDataRoboPart
{
  // SIZE 0x24
};

class CDataBreedFish
{
  // SIZE 0x14
};

class CDataGuard
{
  // SIZE 0x4
};

class CGameData
{
public:
  // 001946D0
  CGameData();

  // probably no copying this (saving might? will have to check)
  CGameData(CGameData& other) = delete;
  void operator=(const CGameData&) = delete;

  // 00195540
  s32 LoadData();
  // 00195770
  SDataItemCommon* GetCommonData(ECommonItemData index);
  // 001957E0
  CDataWeapon* GetWeaponData(ECommonItemData index);
  // 00195890
  CDataItem* GetItemData(ECommonItemData index);
  // 00195940
  CDataAttach* GetAttachData(ECommonItemData index);
  // 001959F0
  CDataRoboPart* GetRoboData(ECommonItemData index);
  // 00195A60
  CDataBreedFish* GetFishData(ECommonItemData index);
  // 00195B10
  CDataGuard* GetGuardData(ECommonItemData index);
  // 00195B80
  ECommonItemDataType GetDataType(ECommonItemData index);
  // 00195BB0
  ECommonItemData GetDataStartListNo(ECommonItemDataType type);

  // 0
  _DWORD m_unk_field_0{ 0 };
  // 4
  SDataItemCommon* m_com_itemdata;
  // 8
  CDataItem* m_itemdata;
  // C
  CDataWeapon* m_weapondata;
  // 10
  CDataGuard* m_guarddata;
  // 14
  CDataAttach* m_attachdata;
  // 18
  CDataRoboPart* m_robodata;
  // 1C
  CDataBreedFish* m_fishdata;
  // 20
  _WORD m_unk_field_20{ 0 };
  // 22
  _WORD m_unk_field_22{ 0 };
  // 24
  _WORD m_unk_field_24{ 0 };
  // 26
  s16 m_n_weapondata{ 0 };
  // 28
  _WORD m_unk_field_28{ 0 };
  // 2A
  _WORD m_unk_field_2A{ 0 };
  // 2C
  _WORD m_unk_field_2C{ 0 };
  // 2E
  _WORD m_unk_field_2E{ 0 };
};

// 00195470
bool LoadGameDataAnalyze(const char* config_file_name);

// 00195F10
EUsedItemType ConvertUsedItemType(ECommonItemDataType type);

// 00195C20
SDataItemCommon* GetCommonItemData(ECommonItemData index);

// 00195C30
CDataItem* GetItemInfoData(ECommonItemData index);

// 00195C40
CDataWeapon* GetWeaponInfoData(ECommonItemData index);

// 00195C50
CDataRoboPart* GetRoboPartInfoData(ECommonItemData index);

// 00195C60
CDataBreedFish* GetBreedFishInfoData(ECommonItemData index);

// 00196040
std::string GetItemMessage(ECommonItemData index);