#pragma once
#include <fmt/format.h>

#include "common/macros.h"

#include "data/iso/types.h"

namespace data
{
  #pragma pack(push, 1)
  struct iso_datetime_short
  {
    // number of years since 1900
    iso711_t years_since_1900;
    // month 1-12
    iso711_t months;
    // day 1-31
    iso711_t days;
    // hour 0-23
    iso711_t hours;
    // minute 0-59
    iso711_t minutes;
    // second 059
    iso711_t seconds;
    //-48 to +52
    iso712_t gmt_offset;
  };

  struct iso_datetime_long
  {
    iso711_t year[4];
    iso711_t month[2];
    iso711_t day[2];
    iso711_t hour[2];
    iso711_t minute[2];
    iso711_t seconds[2];
    iso711_t hecta_seconds[2];
    iso712_t gmt_offset;
  };

  assert_type_size_static(iso_datetime_short, 7);
  assert_type_size_static(iso_datetime_long, 17);
  #pragma pack(pop)
}

// short datetime
template<>
struct fmt::formatter<data::iso_datetime_short> : formatter<std::string_view>
{
  auto format(const data::iso_datetime_short& dt, format_context& ctx)
  {
    const auto year = dt.years_since_1900 + 1900;

    static constexpr std::string_view tpl =
    {
      "iso9660 datetime(year: {}, month: {}, day: {}, hour: {}, minute: {}, second: {}, gmt offset: {})"
    };

    return fmt::format_to(ctx.out(), tpl, year, dt.months, dt.days, dt.hours, dt.minutes, dt.seconds, dt.gmt_offset);
  }
};

// long datetime
template<>
struct fmt::formatter<data::iso_datetime_long> : formatter<std::string_view>
{
  auto format(const data::iso_datetime_long& dt, format_context& ctx)
  {
    // yes, it's really encoded this way
    const auto full_year = (dt.year[3] * 1000) + (dt.year[2] * 100) + (dt.year[1] * 10) + dt.year[0];
    const auto full_month = (dt.month[1] * 10) + dt.month[0];
    const auto full_day = (dt.day[1] * 10) + dt.day[0];
    const auto full_hour = (dt.hour[1] * 10) + dt.hour[0];
    const auto full_min = (dt.minute[1] * 10) + dt.minute[0];
    const auto full_sec = (dt.seconds[1] * 10) + dt.seconds[0];

    static constexpr std::string_view tpl =
    {
      "iso9660 datetime(year: {}, month: {}, day: {}, hour: {}, minute: {}, second: {}, gmt offset: {})"
    };

    return fmt::format_to(ctx.out(), tpl, full_year, full_month, full_day , full_hour, full_min, full_sec, dt.gmt_offset);
  }
};