//


#include <data_pattern/data_model.hpp>
#include <data_pattern/raw.hpp>
#include "sqlite.cpp"

namespace {

auto
make_sqlite_model (
  char const * const _name
, {}
, std::size_t pre_run = 0
)
->
{
auto mdl = make_data_model (
  sqlite (_name)
, 
, 
);
return mdl;
}

} /**/
#endif

