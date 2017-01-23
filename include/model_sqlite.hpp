//

#ifndef DATA_PATTERN_SQLITE_LOCALE_HPP
#define DATA_PATTERN_SQLITE_LOCALE_HPP

#include <data_pattern/model.hpp>
#include <data_pattern/raw.hpp>
#include <typesystems/type_map.hpp>
#include <tuple>
#include <string>
#include <vector>
#include "sqlite.hpp"

namespace data_pattern_sqlite {

using sqlite_locale = typesystems::type_map <
  std::tuple <>
, int, data_pattern::end_iterator_tag<int>, data_pattern::sync_iterator_tag<int>
, double
, std::string
, data_pattern::raw
>;

auto ilam = [](data_pattern::model<std::tuple<sqlite, sqlite_statement>> & _mdl){
return typesystems::make_type_map
<int, double, std::string, data_pattern::raw>
( std::make_tuple (
  sqlite_iterator<int>(std::get<1>(_mdl.device))
, sqlite_iterator<double>(std::get<1>(_mdl.device))
, sqlite_iterator<std::string>(std::get<1>(_mdl.device))
, sqlite_iterator<data_pattern::raw>(std::get<1>(_mdl.device))
));
};

auto olam = [](data_pattern::model<std::tuple<sqlite, sqlite_statement>> & _mdl){
return typesystems::make_type_map
<int, double, std::string, data_pattern::raw>
( std::make_tuple (
  sqlite_iterator<int>(std::get<1>(_mdl.device))
, sqlite_iterator<double>(std::get<1>(_mdl.device))
, sqlite_iterator<std::string>(std::get<1>(_mdl.device))
, sqlite_iterator<data_pattern::raw>(std::get<1>(_mdl.device))
));
};

typedef data_pattern::data_model <
  std::tuple<sqlite, sqlite_statement>, decltype(ilam), decltype(olam) >
model_type;

model_type
make_sqlite_statement_model (
  char const * const
, char const * const
);

model_type
make_sqlite_statement_model (
  char const * const _db_name
, char const * const _query
){
sqlite sq(_db_name);
sqlite_statement st(sq, _query);

return data_pattern::make_data_model (
  std::make_tuple(std::move(sq), std::move(st))
, ilam
, olam
);
}

} /**/
#endif

