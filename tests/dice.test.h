#ifndef CODA_DICE_TEST_H
#define CODA_DICE_TEST_H

#include "dice.h"

using namespace coda;

class dice_test_engine : public die::engine {
  public:
  dice_test_engine();

  dice_test_engine(initializer_list<die::value_type> items);

  dice_test_engine(const dice_test_engine &copy);

  virtual ~dice_test_engine();

  dice_test_engine &operator=(const dice_test_engine &rhs);

  die::value_type generate(die::value_type from, die::value_type to);

  void set_next_roll(initializer_list<die::value_type> items);

  private:
  vector<die::value_type> values_;
  size_t currentValue_;
};

#endif
