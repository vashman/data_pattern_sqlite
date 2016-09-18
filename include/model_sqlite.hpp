//

#include <data_pattern/data_model.hpp>
#include <data_pattern/raw.hpp>
#include <string>
#include <vector>
#include "sqlite.cpp"

namespace data_pattern_sqlite {

namespace bits {

struct mdl_sql {

sqlite_statement stmt;

operator ()(data_pattern::model<sqlite> & _mdl)
return typesystems::make_type_map<>();
};

} /* bits */

auto make_sqlite_model (
  char const * const _db_name
){
return data_pattern::make_data_model(
  sqlite (_db_name)
, 
);
}

auto
make_sqlite_statement_model (
  char const * const _db_name
, char const * const _query
, bool input_statement
, std::size_t 
)
-> decltype ()
{
sqlite sq(_name);
auto i = begin(_queries);
auto e = std::next(i,pre_run);

while (i != e){
sqlite_statement (i.c_str()).step();
++i;
}

return make_data_model (
  std::make_tuple(std::move(sq), std::vector<std::string>(e, end(_queries)), sqlite_statement)
, [](data_pattern::model<std::tuple<sqlite, std::vector<string>>> & _mdl){
  std::get<2>(_mdl.device) = sqlite_statement (std::get<1>(_mdl.device));
  return typesystems::make_type_map
  <int, double, std::string, data_pattern::raw>
  ( sqlite_iterator<int>(std::get<2>(_mdl.device))
  , sqlite_iterator<double>(std::get<2>(_mdl.device))
  , sqlite_iterator<std::string>(std::get<2>(_mdl.device))
  , sqlite_iterator<data_pattern::raw>(std::get<2>(_mdl.device))
  );
  }
);
}

} /**/
#endif

