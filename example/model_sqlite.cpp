//

//          Copyright Sundeep S. Sangha 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <iostream>
#include <data_pattern/data_model.hpp>
#include <data_pattern/raw.hpp>
#include "../src/sqlite.cpp"

using std::vector;
using data_pattern_sqlite::sqlite;
using data_pattern::raw;
using data_pattern_sqlite::sqlite_statement;
using data_pattern::make_data_model;
using data_pattern::model_state;

vector <std::string> query = {
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
  "SELECT Value, dec, raw FROM "
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
_db.step (_db.create(query[0].c_str()));
_db.step (_db.create(query[1].c_str()));
return _db;
}

int main () {
std::shared_ptr<sqlite_statement> stmt;
bool istmt_active = false, ostmt_active = false;
unsigned int stage = 2;
auto io ( make_data_model ( 
  create_db(sqlite ("testdata"))
// input iterator
, [&](sqlite & _db)
  -> sqlite_statement & {
   if (istmt_active == false){
   stmt.reset ( new sqlite_statement (
     _db.create(query[stage].c_str()))
   );
   istmt_active = true;
  _db.step(*stmt);
   }
  return *stmt;
  }
// output iterator
, [&](sqlite & _db)
  -> sqlite_statement & {
   if (ostmt_active == false){
   stmt.reset ( new sqlite_statement (
     _db.create(query[stage].c_str()))
   );
   ostmt_active = true;
   }
  return *stmt;
  }
// sync
, [&](sqlite& _db, model_state& _state){
    if (istmt_active == false){
    _db.step(*stmt);
    }
  ++stage;
  ostmt_active = false;
  istmt_active = false;
  }
) );

io
<< 45
<< std::string("test string")
<< 12.04
<< raw("0101", 4);
sync(io);

/* bind data into data_model */
io << 1 << 4;
sync(io);

int temp_int;
std::string temp_str;
raw temp_raw;
double temp_dbl;

int temp;
sync(io);
io >> temp >> temp;

sync(io);
io >> temp_int >> temp_dbl;

return 0;
}
