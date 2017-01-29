//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_SQLITE_STATEMENT_TCC
#define DATA_PATTERN_SQLITE_SQLITE_STATEMENT_TCC

namespace data_pattern_sqlite {

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement & _stmt
, std::basic_string<char, Traits, Allocator> && _str
){
_stmt.bind(++_stmt.index, _str.c_str());
}

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement & _stmt
, std::basic_string<char, Traits, Allocator> & _str
){
_stmt.bind(++_stmt.index, _str.c_str());
}

template <typename Traits, typename Allocator>
void
bind (
  sqlite_statement & _stmt
, std::basic_string<char, Traits, Allocator> const & _str
){
_stmt.bind(++_stmt.index, _str.c_str());
}

template <typename Traits, typename Allocator>
std::basic_string<unsigned char, Traits, Allocator>
sqlite_statement::column_string (
  int _index
){
return std::basic_string<unsigned char, Traits, Allocator> (
  this->column_const_unsigned_char_ptr(_index) );
}

template <typename Traits, typename Allocator>
std::basic_string<unsigned char, Traits, Allocator>
column_string (
  sqlite_statement & _stmt
){
return std::basic_string<unsigned char, Traits, Allocator> (
  _stmt.column_const_unsigned_char_ptr(_stmt.index++) );
}

template <typename Allocator>
void
bind (
  sqlite_statement & _stmt
, data_pattern::raw<Allocator> && _raw
){
data_pattern_sqlite::bind(_stmt, _raw);
}

template <typename Allocator>
void
sqlite_statement::bind (
  int _index
, data_pattern::raw<Allocator> && _raw
){
this->bind(_index, _raw);
}

template <typename Traits, typename Allocator>
void
sqlite_statement::bind (
  int _index
, std::basic_string<char, Traits, Allocator> const & _str
){
this->bind(_index, _str.c_str());
}

} /* data pattern sqlite */
#endif

