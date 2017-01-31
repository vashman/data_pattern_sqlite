// data_model sqlite implementation

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_SQLITE_STATEMENT_CPP
#define DATA_PATTERN_SQLITE_SQLITE_STATEMENT_CPP

namespace data_pattern_sqlite {

/* ctor */
sqlite_statement::sqlite_statement (
  sqlite _database
, char const * _query
)
/*
 * index starts at 1 and then
 * increments.
 */
: stmt (NULL)
  /*
   * The following state cannot be set only thrown, and
   * signifies a new un-stepped statement.
   */
, state (SQLITE_MISUSE)
, db (_database)
, column_count (0)
, stepped(false)
, bind_parameter_count (0)
// will be set to 1 for when auto binding.
, index (0) {

sqlite_check_error ( sqlite3_prepare_v2 (
  _database.get()
, _query
, -1 /* Query must be alawys null terminated. */
, & (this->stmt)
, 0 /* There is never an unused portion of the statement. */
));
  if (this->stmt == NULL)
  throw sqlite_exception("Null statement", SQLITE_MISUSE);

this->bind_parameter_count
  = sqlite3_bind_parameter_count(this->stmt);
  /*
   * If the statement has no parameters to bind, then step
   * right away.
   * if step finds a result, the statement will be treated
   * like a input statement. otherwise complete.
   */
  if (0 == bind_parameter_count) this->step();
}

sqlite_statement::~sqlite_statement (
){
sqlite3_finalize(this->stmt);
}

/* sqlite step */
void
sqlite_statement::step (
){
  if (this->stepped) return;
this->stepped = true;
this->state = sqlite_check_error(sqlite3_step (this->stmt));
this->column_count = sqlite3_column_count (this->stmt);

  if (this->column_count > 0) this->index = 0;
}

int
sqlite_statement::get_state (
) const {
return this->state;
}

/* column bytes */
int
sqlite_statement::column_bytes (
  int _index
){
return sqlite3_column_bytes (this->stmt, _index);
}

/* column bytes 16 */
int
sqlite_statement::column_bytes16 (
  int _index
){
return sqlite3_column_bytes16 (this->stmt, _index);
}

sqlite3_value *
sqlite_statement::column_value (
  int _index
){
return sqlite3_column_value (this->stmt, _index);
}

int
sqlite_statement::column_type (
  int _index
){
return sqlite3_column_type (this->stmt, _index);
}

int
sqlite_statement::get_column_count () const {
return this->column_count;
}

int
sqlite_statement::get_bind_parameter_count () const {
return this->bind_parameter_count;
}

bool
sqlite_statement::is_stepped (
) const {
return this->stepped;
}

bool
sqlite_statement::is_done (
) const {
  if (! this->stepped) return false;

  if (((this->state != SQLITE_DONE)
    && (this->state != SQLITE_OK)
    )
  && (this->index < this->column_count)
  ){
  return false;
  }
return true;
}

/* sqlite_statement bind_int */
void
sqlite_statement::bind (
  int _index
, int _var
){
this->state = sqlite_check_error (
  sqlite3_bind_int (this->stmt, _index, _var) );
}

/* sqlite_statement bind_blob */
void
sqlite_statement::bind (
  int _index
, void const * _blob
, int _size
){
this->state = sqlite_check_error ( sqlite3_bind_blob (
  this->stmt
, _index
, _blob
, _size
, reinterpret_cast<sqlite3_destructor_type>(-1)
));
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
, static_cast<int> (std::char_traits<char>::length(_str))
, reinterpret_cast<sqlite3_destructor_type>(-1)
));
}

/* sqlite_statement bind double */
void
sqlite_statement::bind (
  int _index
, double _var
){
this->state = sqlite_check_error (
  sqlite3_bind_double(this->stmt, _index, _var ) );
}

/* sqlite_statement column_int */
int
sqlite_statement::column_int (
  int _index
){
return sqlite3_column_int(this->stmt, _index);
}

/* sqlite_statement column_double */
double
sqlite_statement::column_double (
  int _index
){
return sqlite3_column_double(this->stmt, _index);
}

/* sqlite_statement column_blob */
const void *
sqlite_statement::column_const_void_ptr (
  int _index
){
return sqlite3_column_blob (this->stmt, _index);
}

/* column text */
const unsigned char *
sqlite_statement::column_const_unsigned_char_ptr (
  int _index
){
return sqlite3_column_text (this->stmt, _index);
}

/* column bytes 16 */
const char16_t *
sqlite_statement::column_const_char16_t_ptr (
  int _index
){
return reinterpret_cast<const char16_t*>
(sqlite3_column_text16(this->stmt, _index));
}

sqlite3_int64
sqlite_statement::column_sqlite3_int64(
  int _index
){
return sqlite3_column_int64(this->stmt, _index);
}

void
step (
  sqlite_statement & _stmt
){
_stmt.step();
}

bool
is_bind_done (
  sqlite_statement const & _stmt
){
return is_bind_done(_stmt, _stmt.index);
  //if (0 == --this->bind_parameter_count) this->step();
}

bool
is_bind_done (
  sqlite_statement const & _stmt
, int _index
){
return _index >= _stmt.get_bind_parameter_count();
}

bool
has_another_row (
  sqlite_statement const & _stmt
){
return _stmt.get_state() == SQLITE_ROW;
//  && (_stmt.index >= _stmt.get_column_count()));
}

void
bind (
  sqlite_statement & _stmt
, int _var
){
_stmt.bind (++_stmt.index, _var);
}

void
bind (
  sqlite_statement & _stmt
, double _var
){
_stmt.bind(++_stmt.index, _var);
}

void
bind (
  sqlite_statement & _stmt
){
_stmt.bind(++_stmt.index, nullptr);
}

void
sqlite_statement::bind (
  int _index
, data_pattern::raw_view _blob
){
this->bind(_index, _blob.data(), _blob.size());
}

void
bind (
  sqlite_statement & _stmt
, data_pattern::raw_view _blob
){
_stmt.bind(++_stmt.index, _blob);
}

/* column_int */
int
column_int (
  sqlite_statement & _stmt
){
return _stmt.column_int(_stmt.index++);
}

sqlite3_int64
column_sqlite3_int64 (
  sqlite_statement & _stmt
){
return _stmt.column_sqlite3_int64(_stmt.index++);
}

/* column_double */
double
column_double (
  sqlite_statement & _stmt
){
return _stmt.column_double(_stmt.index++);
}

data_pattern::raw<>
column_raw (
  sqlite_statement & _stmt
){
return _stmt.column_raw(_stmt.index++);
}

data_pattern::raw<>
sqlite_statement::column_raw (
  int _index
){
return data_pattern::raw<> (
  *static_cast<const data_pattern::raw<>::data_type *> (
    this->column_const_void_ptr(_index))
, static_cast<std::size_t>(this->column_bytes(_index))
);
}

} /* data pattern_sqlite */
#endif

