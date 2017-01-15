//

//          Copyright Sundeep S. Sangha 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cassert>
#include <data_pattern/raw.hpp>
#include "../include/model_sqlite.hpp"

using data_pattern_sqlite::make_sqlite_statement_model;
using data_pattern::raw;
using std::string;

int main () {
char const * const db = "testdata";

/* Create the table if it does not exist
  yet.
*/

auto s1 = make_sqlite_statement_model (
  db
, "CREATE TABLE IF NOT EXISTS test3"
  "(Value INT, str TEXT, dec REAL, "
  "raw Blob);"
);

auto query1 = make_sqlite_statement_model (
  db
, "CREATE TABLE IF NOT EXISTS test"
  "(ID INT PRIMARY KEY NOT NULL"
  ", Value INT);"
);

auto query2 = make_sqlite_statement_model (
  db
, "INSERT INTO test3 "
  "(Value, str, dec, raw) Values"
  " (?,?,?,?);"
);

query2 << 45 << "test string"
<< 12.04 << raw("0101", 4);

auto query3 = make_sqlite_statement_model (
  db
, "INSERT INTO test "
  "(ID, Value) Values (?, ?);"
);

query3 << 2 << 28;

// Retrive data

auto sel1 ( make_sqlite_statement_model (
  db
, "SELECT ID, Value FROM test;"
) );

int temp_int;
sel1 >> temp_int;
assert (temp_int == 2);
sel1 >> temp_int;
assert (temp_int == 28);

auto sel2 ( make_sqlite_statement_model (
  db
, "SELECT Value, dec, str, raw FROM "
  "test3;"
));

sel2 >> temp_int;
double temp_dbl;
sel2 >> temp_dbl;
std::string temp_str;
sel2 >> temp_str;
data_pattern::raw temp_raw;
sel2 >> temp_raw;
assert (temp_int == 45);
assert (temp_str == std::string("test string"));
assert (temp_dbl == 12.04);

return 0;
}
