#include "Tags.h"

static bool _DATACOMINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATACOM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEBNUM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_ST_L(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP2_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP2_ST_L(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_SPE(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAWEP_BUILDUP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAITEMINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAITEM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACHINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST2(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAATTACH_ST_SP(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAROBOINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAROBO_ANALYZE(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAGUARDNUM(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAGUARD(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAFISHINIT(SPI_STACK* stack, int)
{
  return true;
}

static bool _DATAFISH(SPI_STACK* stack, int)
{
  return true;
}

static bool _MES_SYS(SPI_STACK* stack, int)
{
  return true;
}

static bool _MES_SYS_SPECTOL(SPI_STACK* stack, int)
{
  return true;
}

static bool amapIMG(SPI_STACK* stack, int)
{
  return true;
}

static bool amapPCP(SPI_STACK* stack, int)
{
  return true;
}

// 003359a0
const std::array<SPI_TAG_PARAM, 25> gamedata_tag =
{
  "COMINIT",    _DATACOMINIT,
  "COM",        _DATACOM,
  "WEPNUM",     _DATAWEBNUM,
  "WEP",        _DATAWEP,
  "WEP_ST",     _DATAWEP_ST,
  "WEP_ST_L",   _DATAWEP_ST_L,
  "WEP_ST2",    _DATAWEP2_ST,
  "WEP_ST2_L",  _DATAWEP2_ST_L,
  "WEP_SPE",    _DATAWEP_SPE,
  "WEP_BUILD",  _DATAWEP_BUILDUP,
  "ITEMINIT",   _DATAITEMINIT,
  "ITEM",       _DATAITEM,
  "AT_INIT",    _DATAATTACHINIT,
  "AT_ST",      _DATAATTACH_ST,
  "AT_ST2",     _DATAATTACH_ST2,
  "AT_ST_SP",   _DATAATTACH_ST_SP,
  "ROBOTINIT",  _DATAROBOINIT,
  "RB_PARTS",   _DATAROBO_ANALYZE,
  "GRDNUM",     _DATAGUARDNUM,
  "GRD",        _DATAGUARD,
  "FISHINIT",   _DATAFISHINIT,
  "FISH",       _DATAFISH,
  "MES_SYS",    _MES_SYS,
  "MES_SYSSPE", _MES_SYS_SPECTOL,
  NULL, nullptr
};

// 00334a80
const std::array<SPI_TAG_PARAM, 3> add_mapinfo_tag =
{
  "IMG", amapIMG,
  "PCP", amapPCP,
  NULL, nullptr
};
