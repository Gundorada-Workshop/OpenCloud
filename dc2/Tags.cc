#include "Tags.h"

static bool amapIMG(SPI_STACK* stack, int)
{
  return true;
}

static bool amapPCP(SPI_STACK* stack, int)
{
  return true;
}

// 00334a80
const std::array<SPI_TAG_PARAM, 3> add_mapinfo_tag =
{
  "IMG", amapIMG,
  "PCP", amapPCP,
  NULL, nullptr
};
