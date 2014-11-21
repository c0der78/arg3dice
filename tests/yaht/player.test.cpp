#include <bandit/bandit.h>
#include "../../src/yaht/player.h"
#include "../../src/yaht/game.h"
#include "../dice.test.h"

using namespace bandit;

using namespace arg3::yaht;

go_bandit([]()
{

    describe("a yaht(zee) player", []()
    {
        dice_test_engine rand_engine;

        shared_ptr<player> player;

        before_each([&]()
        {
            player = make_shared<yaht::player>("testA", &rand_engine);
        });

        after_each([&]()
        {
            player = nullptr;
        });

        it("can positively determine four of a kind", [&]()
        {
            rand_engine.set_next_roll( {4, 4, 4, 1, 4} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::KIND_FOUR);

            Assert::That(score, Equals(17));
        });

        it("can negatively determine four of a kind", [&]()
        {
            rand_engine.set_next_roll( {4, 4, 1, 2, 3} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::KIND_FOUR);

            Assert::That(score, Equals(0));
        });

        it("can positively determine three of a kind", [&]()
        {
            rand_engine.set_next_roll( {4, 4, 4, 1, 2} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::KIND_THREE);

            Assert::That(score, Equals(15));
        });

        it("can negatively determine three of a kind", [&]()
        {
            rand_engine.set_next_roll( {4, 3, 2, 1, 5} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::KIND_THREE);

            Assert::That(score, Equals(0));
        });

        it("can positively determine upper score", [&]()
        {
            for (die::value_type i = 1; i <= Constants::NUM_DICE; i++)
            {
                rand_engine.set_next_roll( { i });

                player->roll();

                auto score = player->calculate_upper_score(i);

                Assert::That(score, Equals(i * Constants::NUM_DICE));
            }
        });

        it("can negatively determine upper score", [&]()
        {
            for (die::value_type i = 1; i <= Constants::NUM_DICE; i++)
            {
                rand_engine.set_next_roll( {i > 1 ? 1 : i + 1});

                player->roll();

                auto score = player->calculate_upper_score(i);

                Assert::That(score, Equals(0));
            }
        });

        it("can positively determine a full house", [&]()
        {
            rand_engine.set_next_roll( { 1, 1, 1, 4, 4 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::FULL_HOUSE);

            Assert::That(score, Equals(25));
        });

        it("can negatively determine a full house", [&]()
        {
            rand_engine.set_next_roll( { 2, 2, 3, 5, 4 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::FULL_HOUSE);

            Assert::That(score, Equals(0));
        });

        it("can positively determine a small straight", [&]()
        {
            rand_engine.set_next_roll( { 1, 1, 2, 3, 4} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::STRAIGHT_SMALL);

            Assert::That(score, Equals(30));
        });

        it("can negatively determine a small straight", [&]()
        {
            rand_engine.set_next_roll( { 2, 5, 3, 5, 6 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::STRAIGHT_SMALL);

            Assert::That(score, Equals(0));
        });

        it("can positively determine a large straight", [&]()
        {
            rand_engine.set_next_roll( { 1, 2, 3, 4, 5 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::STRAIGHT_BIG);

            Assert::That(score, Equals(40));
        });

        it("can negatively determine a large straight", [&]()
        {
            rand_engine.set_next_roll( { 2, 2, 3, 5, 3 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::STRAIGHT_BIG);

            Assert::That(score, Equals(0));
        });

        it("can positively determine a yaht(zee)", [&]()
        {
            rand_engine.set_next_roll( { 1, 1, 1, 1, 1} );

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::YACHT);

            Assert::That(score, Equals(50));
        });

        it("can negatively determine a yaht(zee)", [&]()
        {
            rand_engine.set_next_roll( { 2, 2, 3, 5, 4 });

            player->roll();

            auto score = player->calculate_lower_score(scoresheet::YACHT);

            Assert::That(score, Equals(0));
        });

        it("can keep a die or dice", [&]()
        {

            rand_engine.set_next_roll( { 4, 3, 6, 1, 3});

            player->roll();

            player->keep_die(1, true);

            rand_engine.set_next_roll( {1, 2, 4, 3});

            player->roll();

            Assert::That(player->d1e(0).value(), !Equals(4));

            Assert::That(player->d1e(1).value(), Equals(3));

            player->keep_die(4, true);

            rand_engine.set_next_roll( {6, 6, 4});

            player->roll();

            Assert::That(player->d1e(0).value(), !Equals(1));

            Assert::That(player->d1e(4).value(), Equals(3));
        });

        it("can determine best lower score", [&]()
        {
            rand_engine.set_next_roll( { 5, 5, 4, 4, 4 } );

            player->roll();

            auto lower = player->calculate_best_lower_score();

            Assert::That(lower.first, Equals(scoresheet::type::FULL_HOUSE));

            Assert::That(lower.second, Equals(25));

        });

        it("can determine best upper score", [&]()
        {
            rand_engine.set_next_roll( { 2, 2, 3, 3, 4 } );

            player->roll();

            auto upper = player->calculate_best_upper_score();

            Assert::That(upper.first, Equals(3));

            Assert::That(upper.second, Equals(6));
        });

        it("can determine the best score", [&]()
        {
            rand_engine.set_next_roll( {3, 6, 1, 6, 1});

            player->roll();

            auto score = player->calculate_best_score();

            Assert::That(score, Equals(17));

            player->score().lower_score(scoresheet::CHANCE, score);

            score = player->calculate_best_score();

            Assert::That(score, Equals(12));
        });
    });

});

