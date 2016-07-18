//

//          Copyright Sundeep S. Sangha 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <cassert>
#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::sqlite_statement;

int main () {
sqlite db("testdata");

/* Create the table if it does not exist
  yet.
*/
step ( sqlite_statement (
  db
, "CREATE TABLE IF NOT EXISTS test3"
  "(Value INT, str TEXT, dec REAL, "
  "raw Blob);"
) );

sqlite_statement query1 (
  db
, "CREATE TABLE IF NOT EXISTS test"
  "(ID INT PRIMARY KEY NOT NULL"
  ", Value INT);"
);

/* Run the statement. */
step(query1);

auto query3 = sqlite_statement (
  db
, "INSERT INTO test3 "
  "(Value, str, dec, raw) Values"
  " (?,?,?,?);"
);

query3 = 45;
++query3;
query3 = std::string("test string");
++query3;
query3 = 12.04;
++query3;
query3 = data_pattern::raw("0101", 4);

step(query3);

auto query4 = sqlite_statement (
  db
, "INSERT INTO test "
  "(ID, Value) Values (?, ?);"
);

/* bind data into data_model */
query4 = 1;
++query4;
query4 = 14;
step(query4);

//
int temp_int;
std::string temp_str;
data_pattern::raw temp_raw;
double temp_dbl;

auto query5 ( sqlite_statement (
  db
, "SELECT ID, Value FROM test;"
) );
step(query5);

int temp;
temp = *query5++;
assert (1);
std::cout << "temp: " << temp;

temp = *query5++;
assert (14);
std::cout << " and " << temp
<< std::endl;

auto query6 ( sqlite_statement (
  db
, "SELECT Value, str, dec, raw FROM "
  "test3;"
));
step(query6);

temp_int = query6++;
temp_str
  = static_cast <std::string>(query6++);
temp_dbl = query6++;

std::cout << "value: " << temp_int
<< " str: " << temp_str << " dec: "
<< temp_dbl;

assert (temp_int == 45);
std::string ff("test string");
assert (temp_str == ff);
assert (temp_dbl == 12.04);


return 0;
}
