// data_model sqlite implementation

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_STATEMENT_CPP
#define DATA_PATTERN_SQLITE_STATEMENT_CPP

namespace data_pattern_sqlite {

/* ctor */
sqlite_statement::sqlite_statement (
  sqlite _db
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
, db (_db)
, max_col (0)
, stepped(false)
, var_count (0)
// set to 1 for bind / output statements
, index (0) {

sqlite_check_error( sqlite3_prepare_v2 (
  _db.get()
, _query
, -1 /* Query is null terminated. */
, & (this->stmt)
/* 
 * There is never an unused portion of
 * the statement.
 */
, 0
));
  if (this->stmt == NULL)
  throw std::string("null stmt stepped.");

this->var_count = sqlite3_bind_parameter_count(this->stmt);
  /*
   * If the statement has no parameters to bind, then step right away.* 
   * if step finds a result, the statement will be treated like a input statement. otherwise complete.
   */
  if (0 == var_count) this->step();
}

sqlite_statement::~sqlite_statement (){
sqlite3_finalize((this->stmt));
}

/* sqlite step */
void
sqlite_statement::step (){
this->stepped = true;

this->state = sqlite_check_error(sqlite3_step (this->stmt));
this->max_col = sqlite3_column_count (this->stmt);

  if (this->max_col > 0) this->index = 0;
}

void
sqlite_statement::step_if (){
  if (0 == --this->var_count) this->step();
}

void
sqlite_statement::step_if_input (){
  if (
     (this->state == SQLITE_ROW)
  && (this->index >= this->max_col)
  ){
  this->step();
  }
}

/* sqlite_statement bind_int */
void
sqlite_statement::bind (
  int _index
, int _var
){
this->state = sqlite_check_error ( sqlite3_bind_int (
  this->stmt, _index, _var ) );
}

void
sqlite_statement::bind (
  int _var
){
this->bind (++this->index, _var);
this->step_if();
}

/* */
void
sqlite_dtor_data (void *);

void
sqlite_dtor_data (void * _data){/* do nothing */}

/* sqlite_statement bind_blob */
void
sqlite_statement::bind (
  int _index
, void const * _blob
, int _size
){
this->state = sqlite_check_error ( sqlite3_bind_blob (
  this->stmt, _index, _blob, _size, sqlite_dtor_data ) );
}

void
sqlite_statement::bind (
  void const * _blob
, int _size
){
this->bind(++this->index, _blob, _size);
this->step_if();
}

/* sqlite_statement bind string */
void
sqlite_statement::bind (
  int _index
, char const * _str
){
  if (_str == nullptr){
  this->state = sqlite_check_error ( sqlite3_bind_null (
    this->stmt, _index ) );
  return;
  }
// else bind string
this->state = sqlite_check_error ( sqlite3_bind_text (
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
this->step_if();
}

/* sqlite_statement bind double */
void
sqlite_statement::bind (
  int _index
, double _var
){
this->state = sqlite_check_error ( sqlite3_bind_double (
  this->stmt, _index, _var ) );
}

void
sqlite_statement::bind (
  double _var
){
this->bind(++this->index, _var);
this->step_if();
}

void
sqlite_statement::bind (){
this->bind(++this->index, nullptr);
this->step_if();
}

bool
sqlite_statement::is_stepped () const {
return this->stepped;
}

namespace helper {

/* sqlite_statement column_int */
template <>
int
column <int> (
  int _index
, sqlite3_stmt * _stmt
){
return sqlite3_column_int
  (_stmt, _index);
}

/* sqlite_statement column_double */
template <>
double
column <double> (
  int _index
, sqlite3_stmt * _stmt
){
return sqlite3_column_double
  (_stmt, _index);
}

/* sqlite_statement column_blob */
template <>
const void *
column <const void*> (
  int _index
, sqlite3_stmt * _stmt
){
return sqlite3_column_blob (_stmt, _index);
}

/* column text */
template <>
const unsigned char *
column <const unsigned char *> (
  int _index
, sqlite3_stmt * _stmt
){
return sqlite3_column_text (_stmt, _index);
}

/* column bytes 16 */
template <>
const char16_t *
column <const char16_t *> (
  int _index
, sqlite3_stmt * _stmt
){
return reinterpret_cast<const char16_t*>
( sqlite3_column_text16(_stmt, _index));
}

} /* helper */

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

int
sqlite_statement::get_var_count () const {
return this->var_count;
}

bool
sqlite_statement::is_done () const {
  if (! this->stepped) return false;

  if (
    (  (this->state != SQLITE_DONE)
    && (this->state != SQLITE_OK)
    )
  && (this->index < this->max_col)
  ){
  return false;
  }
return true;
}

} /* data pattern_sqlite */
#endif

