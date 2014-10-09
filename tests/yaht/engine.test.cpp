#include <bandit/bandit.h>

#include "../src/yaht/engine.h"

#include "../dice.test.h"

using namespace bandit;

using namespace arg3;

using namespace arg3::yaht;

go_bandit([]()
{

    describe("a game of yaht(zee)", []()
    {
        engine *yaht = engine::instance();

        dice_test_engine randengine;

        before_each([&]()
        {
            yaht->set_random_engine(&randengine);

            yaht->add_player("testPlayer");

            int size = yaht->number_of_players();

            while (size >= 1)
            {
                yaht->remove_player(size--);
            }
        });

        it("has a current player", [&]()
        {
            yaht->current_player()->roll();

            yaht->add_player("newPlayerB");

            yaht->next_player();

            Assert::That(yaht->current_player()->name(), Equals("newPlayerB"));

            yaht->remove_player(1);

            Assert::That(yaht->current_player()->name(), !Equals("newPlayerB"));
        });

        it("has a number of players", [&]()
        {
            Assert::That(yaht->number_of_players(), Equals(1));
        });

    });

});


