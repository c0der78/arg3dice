#include <igloo/igloo.h>

#include "engine.h"

#include "../dice.test.h"

using namespace igloo;

using namespace arg3;

using namespace arg3::yacht;

Context(yacht_test)
{
    static engine *yacht;

    static dice_test_engine randengine;

    static void SetUpContext()
    {
        yacht = engine::instance();

        yacht->set_random_engine(&randengine);

        yacht->add_player("testPlayer");
    }

    void SetUp()
    {
        int size = yacht->number_of_players();

        while (size >= 1)
        {
            yacht->remove_player(size--);
        }
    }

    Spec(current_player)
    {
        yacht->current_player()->roll();

        yacht->add_player("newPlayerB");

        yacht->next_player();

        Assert::That(yacht->current_player()->name(), Equals("newPlayerB"));

        yacht->remove_player(1);

        Assert::That(yacht->current_player()->name(), !Equals("newPlayerB"));
    }

    Spec(number_of_players)
    {
        Assert::That(yacht->number_of_players(), Equals(1));
    }

};


engine *yacht_test::yacht;
dice_test_engine yacht_test::randengine;

