#ifndef _ARG3_YAHT_TEST_H_
#define _ARG3_YAHT_TEST_H_

#include "../../src/yaht/player.h"

class player : public arg3::yaht::player
{
public:
    string name;
    int id;

    player(const string &name, die::engine *engine = die::default_engine) : arg3::yaht::player(engine), name(name), id(++next_id)
    {}
private:
    static int next_id;
};


#endif
