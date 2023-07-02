// SPDX-License-Identifier: MIT

#pragma once
#include <utility> // std::pair
#include <algorithm> // std::find_if
#include <array>

#include "common/types.h"
#include "common/debug.h"

namespace common
{
  // a key->value map with constexpr support
  //
  // Nothing too fancy here, entire thing is backed by an array
  // A size must be provided though there is probably a way to work around this
  template<typename k, typename v, usize s>
  class dictionary
  {
  public:
    using key_type   = k;
    using value_type = v;
    using size_type  = usize;

    using storage_type      = std::pair<key_type, value_type>;
    using storage_ref_type  = storage_type&;
    using storage_cref_type = const storage_type&;

    using list_type      = std::array<storage_type, s>;
    using result_type    = std::optional<value_type>;

    // initialize the dictionary with key value pairs
    constexpr dictionary(std::initializer_list<storage_type> data);

    // array access
    // calls find_or_panic
    constexpr value_type operator[](const key_type& k) const;

    // find a value given a key
    // returns nullopt if not found
    constexpr result_type find(const key_type& k) const;

    // find a value given a key
    // panics if not found
    constexpr value_type find_or_panic(const key_type& k) const;

    // returns the number of key value pairs
    constexpr size_type size() const;

  private:
    static constexpr size_type size_{ s };

    std::array<storage_type, size_> data_{};
  };

  template<typename k, typename v, usize s>
  constexpr dictionary<k, v, s>::dictionary(std::initializer_list<dictionary::storage_type> data)
  {
    const auto d = std::data(data);

    for (usize i = 0; i < data.size(); ++i)
    {
      data_[i] = d[i];
    }
  }

  template<typename k, typename v, usize s>
  constexpr auto dictionary<k, v, s>::operator[](const key_type& k) const -> value_type
  {
    return find_or_panic(k);
  }

  template<typename k, typename v, usize s>
  constexpr auto dictionary<k, v, s>::find(const key_type& k) const -> result_type
  {
    const auto res = std::find_if(data_.cbegin(), data_.cend(), [&](const storage_type& item) {
      return item.first == k;
    });

    if (res == std::end(data_))
    {
      return std::nullopt;
    }

    return res->second;
  }

  template<typename k, typename v, usize s>
  constexpr auto dictionary<k, v, s>::find_or_panic(const key_type& k) const -> value_type
  {
    const auto res = find(k);

    assert_panic(res);

    return *res;
  }

  template<typename k, typename v, usize s>
  constexpr auto dictionary<k, v, s>::size() const -> size_type
  {
    return size_;
  }
}