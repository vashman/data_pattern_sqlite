//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_SQLITE_STATEMENT_TCC
#define DATA_PATTERN_SQLITE_SQLITE_STATEMENT_TCC

namespace data_pattern_sqlite {

template <typename T>
T
sqlite_statement::column (
){
this->step_if_more_input();
return this->column<T> (this->index++);
}

template <typename T>
T
sqlite_statement::column (
  int _index
){
return helper::column<T>(_index, this->stmt);
}

} /* data pattern sqlite */
#endif

