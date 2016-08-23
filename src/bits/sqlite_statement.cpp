// data_model sqlite implementation

//          Copyright Sundeep S. Sangha 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_STATEMENT_CPP
#define DATA_PATTERN_SQLITE_STATEMENT_CPP

namespace data_pattern_sqlite {

/* ctor */
sqlite_statement::sqlite_statement (
  sqlite & _db
, char const * _query
)
/*
 * index starts at 1 and then
 * increments.
 */
: stmt (NULL)
  /*
   * The following state cannot be set
   * only thrown, and signifies a new
   * un-stepped statement.
   */
, state (SQLITE_MISUSE)
, max_col (0)
, input_type (false)
, stepped(false)
, row_on_def(false)
// set to 1 for bind / output statements
, index (0) {

  bits
::check_error( sqlite3_prepare_v2 (
  _db.db
, _query
, -1 /* Query is null terminated. */
, & (this->stmt)
/* 
 * There is never an unused portion of
 * the statement.
 */
, 0
));
}

sqlite_statement::~sqlite_statement (
){
sqlite3_finalize((this->stmt));
}

/* sqlite step */
void
sqlite_statement::step (
){
  if (this->stmt == NULL)
  throw
  std::string("null stmt stepped.");

this->stepped = true;

this->state = bits::check_error (
  sqlite3_step (this->stmt) );

this->max_col
  = sqlite3_column_count (this->stmt);

  if (this->max_col > 0){
  this->input_type = true;
  this->index = 0;
  }
}

/* sqlite_statement bind_int */
void
sqlite_statement::bind (
  int _index
, int _var
){
this->state =
  bits
::check_error ( sqlite3_bind_int (
  this->stmt, _index, _var ) );
}

void
sqlite_statement::bind (
  int _var
){
this->bind (++this->index, _var);
}

/* */
void
sqlite_dtor_data (
  void *
);

void
sqlite_dtor_data (
  void * _data
){
// do nothing
}

/* sqlite_statement bind_blob */
void
sqlite_statement::bind (
  int _index
, void const * _blob
, int _size
){
this->state =
  bits
::check_error ( sqlite3_bind_blob (
  this->stmt
, _index
, _blob
, _size
, sqlite_dtor_data ) );
}

void
sqlite_statement::bind (
  void const * _blob
, int _size
){
this->bind(++this->index, _blob, _size);
}

/* sqlite_statement bind string */
void
sqlite_statement::bind (
  int _index
, char const * _str
){
  if (_str == nullptr){
  this->state =
    bits
  ::check_error ( sqlite3_bind_null (
    this->stmt, _index ) );
  return;
  }
// else bind string
this->state =
  bits
::check_error ( sqlite3_bind_text (
  this->stmt
, _index
, _str
, static_cast<int> (
  std::char_traits<char>::length(_str) )
, sqlite_dtor_data ) );
}

void
sqlite_statement::bind (
  char const * _str
){
this->bind (++this->index, _str);
}

/* sqlite_statement bind double */
void
sqlite_statement::bind (
  int _index
, double _var
){
this->state =
  bits
::check_error ( sqlite3_bind_double (
  this->stmt, _index, _var ) );
}

void
sqlite_statement::bind (
  double _var
){
this->bind(++this->index, _var);
}

void
sqlite_statement::bind (){
this->bind(++this->index, nullptr);
}

/* sqlite_statement column_int */
int
sqlite_statement::column_int (
  int _index
){
return sqlite3_column_int (
  this->stmt, _index );
}

/* sqlite_statement column_double */
double
sqlite_statement::column_double(
  int _index
){
return sqlite3_column_double (
  this->stmt, _index );
}

/* sqlite_statement column_blob */
const void *
sqlite_statement::column_blob (
  int _index
){
return sqlite3_column_blob (
  this->stmt, _index );
}

/* column bytes */
int
sqlite_statement::column_bytes (
  int _index
){
return sqlite3_column_bytes (
  this->stmt, _index );
}

/* column bytes 16 */
int
sqlite_statement::column_bytes16 (
  int _index
){
return sqlite3_column_bytes16 (
  this->stmt, _index );
}

/* column text */
const unsigned char *
sqlite_statement::column_text (
  int _index
){
return sqlite3_column_text (
  this->stmt, _index );
}

/* column bytes 16 */
const void *
sqlite_statement::column_text16 (
  int _index
){
return sqlite3_column_text16 (
  this->stmt, _index );
}

sqlite3_value *
sqlite_statement::column_value (
  int _index
){
return sqlite3_column_value (
  this->stmt, _index );
}

int
sqlite_statement::column_type (
  int _index
){
return sqlite3_column_type (
  this->stmt, _index );
}

int
sqlite_statement::get_max_col () const {
return this->max_col;
}
/*
int
sqlite_statement::row_step(){
  if (*this->state == SQLITE_ROW){
    if (this->index >= *this->max_col){
    step(*this);
    }
  return false;
  }
return true;
}*/

/* sqlite_statement column_int */
int
sqlite_statement::column_int (){
return sqlite3_column_int (
  this->stmt, this->index++ );
}

/* sqlite_statement column_double */
double
sqlite_statement::column_double(){
return sqlite3_column_double (
  this->stmt, this->index++ );
}

/* sqlite_statement column_blob */
const void *
sqlite_statement::column_blob (){
return sqlite3_column_blob (
  this->stmt, this->index++ );
}

/* column bytes */
int
sqlite_statement::column_bytes (){
return sqlite3_column_bytes (
  this->stmt, this->index++ );
}

/* column bytes 16 */
int
sqlite_statement::column_bytes16 (){
return sqlite3_column_bytes16 (
  this->stmt, this->index++ );
}

/* column text */
const unsigned char *
sqlite_statement::column_text (){
return sqlite3_column_text (
  this->stmt, this->index++ );
}

/* column bytes 16 */
const void *
sqlite_statement::column_text16 (){
return sqlite3_column_text16 (
  this->stmt, this->index++ );
}

sqlite3_value *
sqlite_statement::column_value (){
return sqlite3_column_value (
  this->stmt, this->index++ );
}

int
sqlite_statement::column_type (){
return sqlite3_column_type (
  this->stmt, this->index++ );
}

} /* data pattern_sqlite */
#endif

