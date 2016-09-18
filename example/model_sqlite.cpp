//

//          Copyright Sundeep S. Sangha 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <iostream>
#include <cassert>
#include <data_pattern/data_model.hpp>
#include <data_pattern/raw.hpp>
#include "../src/sqlite.cpp"

using data_pattern_sqlite::sqlite;
using data_pattern_sqlite::sqlite_statement;
using data_pattern::make_data_model;
using data_pattern::model_state;

std::vector <std::string> query = {
  "CREATE TABLE IF NOT EXISTS "
  "test3 (Value INT, str TEXT, dec REAL"
  ", raw Blob);"
,
  "CREATE TABLE IF NOT EXISTS test"
  "(ID INT PRIMARY KEY NOT NULL"
  ", Value INT);"
,
  "INSERT INTO test3 "
  "(Value, str, dec, raw) Values"
  " (?,?,?,?);"
,
  "INSERT INTO test "
  "(ID, Value) Values (?,?);"
,
  "SELECT ID, Value FROM test;"
,
  "SELECT Value, dec, str, raw FROM "
  "test3;"
};

sqlite
create_db (
  sqlite _db
);

sqlite
create_db (
  sqlite _db
){
step (sqlite_statement(_db, query[0].c_str()));
step (sqlite_statement(_db, query[1].c_str()));
return _db;
}

int main () {
std::cerr << std::boolalpha;
sqlite_statement istmt, ostmt;
bool inflag = false;
unsigned int stage = 2;

auto io ( make_data_model (
  create_db(sqlite ("testdata"))
// input iterator
, [&](sqlite & _db)
  -> sqlite_statement & {
   if (istmt == sqlite_statement()){
   inflag = true;
   std::cerr << "\nI: creating istmt: " << stage << " \"" << query[stage].c_str();
   istmt = sqlite_statement (
     _db, query[stage].c_str());
  step(istmt);
  }
  return istmt;
  }
// output iterator
, [&](sqlite & _db)
  -> sqlite_statement & {
   if (ostmt == sqlite_statement()){
   ostmt = sqlite_statement (
     _db, query[stage].c_str() );
   }
  return ostmt;
  }
// sync
, [&](sqlite & _db, model_state & _state){
std::cerr << " SYNC ";
    if (ostmt != sqlite_statement()){
    step(ostmt); ++stage;
    }
    if (istmt == sqlite_statement() && inflag){
    std::cerr << "\nI: input synced, stage: ";
//    _state = model_state::end;
    ++stage;
    inflag = false;
    std::cerr << stage;
    }
std::cerr << " END ";
  }
) );

io
<< 45
<< std::string("test string")
<< 12.04
<< data_pattern::raw("0101", 4);
sync(io);

/* bind data into data_model */
io << 1 << 4;
sync(io);

int temp_int;
std::string temp_str;
data_pattern::raw temp_raw;
double temp_dbl;

sync(io);
io >> temp_int;
assert (temp_int == 1);

io >> temp_int;
assert (temp_int == 4);

sync(io);
io
  >> temp_int
  >> temp_dbl
  >> temp_str
  >> temp_raw;

assert (temp_int == 45);
assert (temp_dbl == 12.04);
assert (
  temp_str == std::string("test string")
);

return 0;
}
