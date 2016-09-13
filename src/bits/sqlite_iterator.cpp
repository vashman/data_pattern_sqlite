sqlite_statement
sqlite_statement::operator ++ (int){
*this->row_on_def = true;
auto temp (*this);
++(index);
return temp;
}

sqlite_statement &
sqlite_statement::operator ++ (){
++(index);
this->row_step();
return *this;
}

sqlite_statement &
sqlite_statement::operator * (){
  if (*this->row_on_def){
  this->row_step();
  *this->row_on_def = false;
  }
return *this;
}

sqlite_statement *
sqlite_statement::operator -> (){
  if (*this->row_on_def){
  this->row_step();
  *this->row_on_def = false;
  }
return this;
}

sqlite_statement &
sqlite_statement::operator = (
  int _var
){
std::cerr << " BIND: " << this->index;
this->bind(this->index, _var);
return *this;
}

sqlite_statement &
sqlite_statement::operator = (
  std::string _var
){
std::cerr << " BIND: " << this->index;

this->bind(this->index, _var.c_str());
return *this;
}

sqlite_statement &
sqlite_statement::operator = (
  data_pattern::raw _var
){
std::cerr << " Bind: " << this->index;

this->bind (
  this->index
, _var.ptr()
, static_cast<int>(_var.size()) );
return *this;
}

sqlite_statement &
sqlite_statement::operator = (
  double _var 
){
std::cerr << " BIND: " << this->index;

this->bind(this->index, _var);
return *this;
}

bool
sqlite_statement::operator == (
  sqlite_statement const & _rhs
) const {
  /* no statement */
  if (this->state == nullptr)
  return true;
std::cerr << "\n  ==: state: " << *this->state;
  /*
   * Output statement or un-stepped
   * input statement.
   */
  if (!*this->input_type){
  std::cerr << " for an OUTPUT iter";
  return *this->stepped;
  }
/* stepped input statement. */
std::cerr << " for an INPUT iter S: index > " <<this->index << " max " << *this->max_col << " state: " <<*this->state;
  if (this->index >= *this->max_col)
  return true;
return false;
}

bool
operator != (
  sqlite_statement const & _lhs
, sqlite_statement const & _rhs
) {
return !(_lhs == _rhs);
}

