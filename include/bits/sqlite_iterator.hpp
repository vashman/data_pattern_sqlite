//

//          Copyright Sundeep S. Sangha 2013 - 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef DATA_PATTERN_SQLITE_BITS_SQLITE_ITERATOR_HPP
#define DATA_PATTERN_SQLITE_BITS_SQLITE_ITERATOR_HPP

#include <iterator>
#include <memory>

namespace data_pattern_sqlite {

template <typename T>
class sqlite_iterator {

public:

struct proxy {

T temp;
int index;
std::weak_ptr<sqlite_statement> stmt;

proxy (
  T const & _var
, int _index
, std::shared_ptr<sqlite_statement> _stmt
)
: temp (_var)
, index (_index)
, stmt (_stmt)
{}

explicit
proxy (
  std::shared_ptr<sqlite_statement> _stmt
)
: temp ()
, index()
, stmt (_stmt)
{}

~proxy() = default;
proxy (proxy const &) = default;
proxy (proxy &&) = default;
proxy & operator = (proxy const &) = delete;
proxy & operator = (proxy &&) = default;

operator T(){
auto st = this->stmt.lock();
this->temp = st-> template column<T>(this->index);
return this->temp;
}

T *
operator -> (){
return &this->temp;
}

proxy &
operator = (
  T const & _var
){
auto st = this->stmt.lock();
st->bind(this->index, _var);
return *this;
}

}; /* proxy */

private:

std::shared_ptr<sqlite_statement> stmt;
proxy temp;

public:

typedef std::input_iterator_tag iterator_catagory;
typedef proxy value_type;
typedef std::size_t difference_type;
typedef proxy * pointer;
typedef proxy & reference;

explicit
sqlite_iterator (sqlite_statement & _stmt);
sqlite_iterator ();
~sqlite_iterator() = default;
sqlite_iterator (sqlite_iterator const &) = default;
sqlite_iterator (sqlite_iterator &&) = default;

sqlite_iterator &
operator = (sqlite_iterator const &) = default;

sqlite_iterator &
operator = (sqlite_iterator &&) = default;

sqlite_iterator
operator ++ (int) {
auto temp_iter (*this);
++this->temp.index;
return temp_iter;
}

sqlite_iterator &
operator ++ (){
++this->temp.index;
return *this;
}

bool
operator == (
  sqlite_iterator const & _rhs
) const {
  if (_rhs.stmt == nullptr && this->stmt == nullptr)
  return true;
  else if (_rhs.stmt == nullptr)
  return this->stmt->is_done();
  else if (this->stmt == nullptr) return _rhs.is_done();

return (this->stmt->is_done() && _rhs.stmt->is_done());
}

bool
operator != (
  sqlite_iterator const & _rhs
) const {
return !(*this == _rhs);
}

proxy &
operator * (){
return this->temp;
}

proxy *
operator -> (){
return &this->temp;
}
}; /* sqlite iterator */

} /* data_pattern_sqlite */
#endif
#include "sqlite_iterator.tcc"

