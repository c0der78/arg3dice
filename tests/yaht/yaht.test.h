#ifndef CODA_YAHT_TEST_H
#define CODA_YAHT_TEST_H

#include "yaht/player.h"

class player : public coda::yaht::player {
  public:
  string name;
  int id;

  player(const string &name, die::engine *engine = die::default_engine)
      : coda::yaht::player(engine), name(name), id(++next_id) {}

  private:
  static int next_id;
};

#endif
