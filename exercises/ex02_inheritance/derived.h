#ifndef DERIVED_H_
#define DERIVED_H_

#include "object.h"

using std::cout;
using std::endl;

class DerivedClass : public ObjectClass {
public:
  DerivedClass() : var_a_(0), var_b_(0) {}
  DerivedClass(int a, int b) : var_a_(a), var_b_(b) {}
  void Print() {
    cout << "in derivedClass... "<<endl;
    cout << "var_a_ " << var_a_ << endl;
    cout << "var_b_ " << var_b_ << endl;
    cout << "object var_a_ " << ObjectClass::var_a_ << endl;
    cout << "object var_b_ " << ObjectClass::var_b_ << endl;
    ObjectClass::Print();
  }
private:

  int var_a_;
  int var_b_;

};

#endif
