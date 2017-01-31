//

//          Copyright Sundeep S. Sangha 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <data_pattern/raw.hpp>
#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::open_database;
using data_pattern_sqlite::sqlite_statement;

int main () {
sqlite db = open_database("testdata");

/* Create the table if it does not exist yet. */
sqlite_statement s1 (
  db
, "CREATE TABLE IF NOT EXISTS test3"
  "(Value INT, str TEXT, dec REAL, raw Blob);"
);

sqlite_statement query1 (
  db
, "CREATE TABLE IF NOT EXISTS test"
  "(ID INT PRIMARY KEY NOT NULL, Value INT);"
);

auto query2 = sqlite_statement (
  db
, "INSERT INTO test3 "
  "(Value, str, dec, raw) Values (?,?,?,?);"
);

bind(query2, 45);
bind(query2, std::string("test string"));
bind(query2, 12.04);
bind(query2, data_pattern::raw<>("0101", 4));
  if (is_bind_done(query2)) step(query2);

auto query3 ( sqlite_statement (
  db, "INSERT INTO test (ID, Value) Values (?, ?);" ));

bind(query3, 2);
bind(query3, 28);
  if (is_bind_done(query3)) step(query3);

// Retrive data
auto select1 (
  sqlite_statement (db, "SELECT ID, Value FROM test;"));

int tmp_int (column_int(select1));
int temp_int = column_int(select1);
assert (tmp_int == 2);
assert (temp_int == 28);

auto select2 ( sqlite_statement (
  db
, "SELECT Value, dec, str, raw FROM test3;"
));

temp_int = column_int(select2);
double temp_dbl (column_double(select2));
auto temp_str = column_string(select2);
data_pattern::raw<> temp_raw = column_raw(select2);

assert (temp_int == 45);
assert (temp_str == sqlite_statement::string_t(reinterpret_cast<const unsigned char*>("test string")));
assert (temp_dbl == 12.04);
assert (temp_raw == data_pattern::raw<>("0101", 4));

return 0;
}
