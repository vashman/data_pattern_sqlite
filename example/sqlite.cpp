//

//          Copyright Sundeep S. Sangha 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cassert>
#include <data_pattern/raw.hpp>
#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::sqlite_statement;

int main () {
sqlite db("testdata");

/* Create the table if it does not exist
  yet.
*/

sqlite_statement s1 (
  db
, "CREATE TABLE IF NOT EXISTS test3"
  "(Value INT, str TEXT, dec REAL, "
  "raw Blob);"
);

sqlite_statement query1 (
  db
, "CREATE TABLE IF NOT EXISTS test"
  "(ID INT PRIMARY KEY NOT NULL"
  ", Value INT);"
);

/* Run the statement. */
s1.step();
query1.step();

auto query2 = sqlite_statement (
  db
, "INSERT INTO test3 "
  "(Value, str, dec, raw) Values"
  " (?,?,?,?);"
);

query2.bind(45);
query2.bind("test string");
query2.bind(12.04);
query2.bind("0101", 4);
query2.step(); 

auto query3 = sqlite_statement (
  db
, "INSERT INTO test "
  "(ID, Value) Values (?, ?);"
);

query3.bind(2);
query3.bind(28);
query3.step();

// Retrive data

auto sel1 ( sqlite_statement (
  db
, "SELECT ID, Value FROM test;"
) );
sel1.step();

int temp_int (sel1.column <int>());
assert (temp_int == 2);
temp_int = sel1.column <int>();
assert (temp_int == 28);

auto sel2 ( sqlite_statement (
  db
, "SELECT Value, dec, str, raw FROM "
  "test3;"
));
sel2.step();

temp_int = sel2.column <int>();
double temp_dbl (sel2.column <double>());
std::string temp_str
  (reinterpret_cast<const char*>(sel2.column <const unsigned char*>()));
data_pattern::raw temp_raw
 (sel2.column <const void*>(), sel2.column_bytes(static_cast<std::size_t>(sel2.index-1)));
assert (temp_int == 45);
assert (temp_str == std::string("test string"));
assert (temp_dbl == 12.04);

return 0;
}
