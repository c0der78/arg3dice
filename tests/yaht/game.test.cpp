#include <bandit/bandit.h>

#include "../src/yaht/game.h"

#include "../dice.test.h"

using namespace bandit;

using namespace arg3;

using namespace arg3::yaht;

go_bandit([]()
{

    dice_test_engine randengine;

    arg3::yaht::game yahtgame(&randengine);

    describe("a game of yaht(zee)", [&]()
    {
        before_each([&yahtgame]
        {
            yahtgame.add_player(make_shared<player>("testPlayer"));
        });

        after_each([&yahtgame]
        {
            yahtgame.reset();
        });

        it("has a current player", [&]()
        {
            Assert::That(yahtgame.number_of_players(), Equals(1));

            Assert::That(yahtgame.current_player() == nullptr, Equals(false));

            yahtgame.current_player()->roll();

            yahtgame.add_player(make_shared<player>("newPlayerB"));

            yahtgame.next_player();

            Assert::That(yahtgame.current_player()->name(), Equals("newPlayerB"));

            yahtgame.remove_player(1);

            Assert::That(yahtgame.current_player()->name(), !Equals("newPlayerB"));
        });

        it("has a number of players", [&]()
        {
            Assert::That(yahtgame.number_of_players(), Equals(1));
        });

    });

});


