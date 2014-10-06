#include <bandit/bandit.h>

#include "../src/yaht/engine.h"

#include "../dice.test.h"

using namespace bandit;

using namespace arg3;

using namespace arg3::yacht;

go_bandit([]()
{

    describe("a game of yaht(zee)", []()
    {
        engine *yacht = engine::instance();

        dice_test_engine randengine;

        before_each([&]()
        {
            yacht->set_random_engine(&randengine);

            yacht->add_player("testPlayer");

            int size = yacht->number_of_players();

            while (size >= 1)
            {
                yacht->remove_player(size--);
            }
        });

        it("has a current player", [&]()
        {
            yacht->current_player()->roll();

            yacht->add_player("newPlayerB");

            yacht->next_player();

            Assert::That(yacht->current_player()->name(), Equals("newPlayerB"));

            yacht->remove_player(1);

            Assert::That(yacht->current_player()->name(), !Equals("newPlayerB"));
        });

        it("has a number of players", [&]()
        {
            Assert::That(yacht->number_of_players(), Equals(1));
        });

    });

});


