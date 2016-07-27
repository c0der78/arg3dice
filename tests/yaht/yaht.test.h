#ifndef RJ_YAHT_TEST_H_
#define RJ_YAHT_TEST_H_

#include "../../src/yaht/player.h"

class player : public rj::yaht::player
{
   public:
    string name;
    int id;

    player(const string &name, die::engine *engine = die::default_engine) : rj::yaht::player(engine), name(name), id(++next_id)
    {
    }

   private:
    static int next_id;
};


#endif
