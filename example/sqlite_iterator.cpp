//

//          Copyright Sundeep S. Sangha 2015 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cassert>
#include <data_pattern/raw.hpp>
//#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::open_database;
using data_pattern_sqlite::sqlite_statement;
using data_pattern_sqlite::sqlite_iterator;
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

auto iter_i = sqlite_iterator<int>(query2);
auto iter_d = sqlite_iterator<double>(query2);
auto iter_r = sqlite_iterator<raw<>>(query2);
auto iter_s = sqlite_iterator<string>(query2);

// Bind values
*iter_i++ = 45;
*iter_s++ = std::string("test string");
*iter_d++ = 12.04;
*iter_r++ = raw<>("0101", 4);

auto query3 = sqlite_statement (
  db, "INSERT INTO test (ID, Value) Values (?, ?);" );

iter_i = sqlite_iterator<int>(query2);
*iter_i = 2;
++iter_i;
*iter_i++ = 28;

// Retrive data
auto sel1 ( sqlite_statement (
  db, "SELECT ID, Value FROM test;" ) );

iter_i = sqlite_iterator<int>(sel1);

int temp_int (*iter_i++);
assert (temp_int == 2);
temp_int = *iter_i++;
assert (temp_int == 28);

auto sel2 ( sqlite_statement (
  db, "SELECT Value, dec, str, raw FROM test3;" ));

iter_i = sqlite_iterator<int>(del2);
temp_int = *iter_i++;
double temp_dbl (*sqlite_iterator<double>(sel2)++);
std::string temp_str
  (reinterpret_cast<const char*>(sel2.column <const unsigned char*>()));
data_pattern::raw temp_raw
 (sel2.column <const void*>(), sel2.column_bytes(static_cast<std::size_t>(sel2.index-1)));
assert (temp_int == 45);
assert (temp_str == std::string("test string"));
assert (temp_dbl == 12.04);

return 0;
}
