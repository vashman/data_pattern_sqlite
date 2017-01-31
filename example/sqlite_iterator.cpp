//

//          Copyright Sundeep S. Sangha 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::open_database;
using data_pattern_sqlite::sqlite_statement;
using data_pattern_sqlite::sqlite_iterator_input;
using data_pattern_sqlite::sqlite_iterator_output;
using data_pattern::raw;
using std::string;

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

auto iter_o = sqlite_iterator_output(query2);
// Bind values
*iter_o++ = 45;
*iter_o++ = std::string("test string");
*iter_o++ = 12.04;
*iter_o++ = raw<>("0101", 4);
  if (is_bind_done(query2)) step(query2);

auto query3 = sqlite_statement (
  db, "INSERT INTO test (ID, Value) Values (?, ?);" );

iter_o = sqlite_iterator_output(query3);
*iter_o = 2;
++iter_o;
*iter_o++ = 28;
  if (is_bind_done(query3)) step(query3);

// Retrive data
auto sel1 ( sqlite_statement (
  db, "SELECT ID, Value FROM test;" ) );

auto iter_i = sqlite_iterator_input<int>(sel1);

int tmp_int (*iter_i++);
int temp_int = *iter_i++;
assert (tmp_int == 2);
assert (temp_int == 28);

auto sel2 ( sqlite_statement (
  db, "SELECT Value, dec, str, raw FROM test3;" ));

temp_int = *sqlite_iterator_input<int>(sel2)++;
double temp_dbl (*sqlite_iterator_input<double>(sel2, 1)++);
auto temp_str
   = *sqlite_iterator_input<sqlite_statement::string_t>(sel2, 2)++;
auto temp_raw
   = *sqlite_iterator_input<data_pattern::raw<>>(sel2, 3)++;

assert (temp_int == 45);
assert (temp_str == sqlite_statement::string_t(reinterpret_cast<const unsigned char*>("test string")));
assert (temp_dbl == 12.04);
assert (temp_raw == raw<>("0101", 4));

return 0;
}
