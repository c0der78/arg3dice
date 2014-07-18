#include <igloo/igloo.h>
#include "../../src/yacht/player.h"
#include "../../src/yacht/engine.h"
#include "../dice.test.h"

using namespace igloo;

using namespace arg3::yacht;

Context(yacht_player_test)
{
    static dice_test_engine rand_engine;

    static player player;

    /*void SetUp()
    {
        //player = new Player("testA", &rand_engine);
    }

    void TearDown()
    {
        delete player;
        player = 0;
    }*/

    Spec(calculate_four_of_a_kind_positive)
    {
        rand_engine.set_next_roll( {4, 4, 4, 1, 4} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::KIND_FOUR);

        Assert::That(score, Equals(17));
    }

    Spec(calculate_four_of_a_kind_negative)
    {
        rand_engine.set_next_roll( {4, 4, 1, 2, 3} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::KIND_FOUR);

        Assert::That(score, Equals(0));
    }


    Spec(calculate_three_of_a_kind_positive)
    {
        rand_engine.set_next_roll( {4, 4, 4, 1, 2} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::KIND_THREE);

        Assert::That(score, Equals(15));
    }

    Spec(calculate_three_of_a_kind_negative)
    {
        rand_engine.set_next_roll( {4, 3, 2, 1, 5} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::KIND_THREE);

        Assert::That(score, Equals(0));
    }

    Spec(calculate_upper_score_positive)
    {
        for (die::value_type i = 1; i <= Constants::NUM_DICE; i++)
        {
            rand_engine.set_next_roll( { i });

            player.roll();

            auto score = player.calculate_upper_score(i);

            Assert::That(score, Equals(i * Constants::NUM_DICE));
        }
    }

    Spec(calculate_upper_score_negative)
    {
        for (die::value_type i = 1; i <= Constants::NUM_DICE; i++)
        {
            rand_engine.set_next_roll( {i > 1 ? 1 : i + 1});

            player.roll();

            auto score = player.calculate_upper_score(i);

            Assert::That(score, Equals(0));
        }
    }

    Spec(calculate_full_house_positive)
    {
        rand_engine.set_next_roll( { 1, 1, 1, 4, 4 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::FULL_HOUSE);

        Assert::That(score, Equals(25));
    }

    Spec(calculate_full_house_negative)
    {
        rand_engine.set_next_roll( { 2, 2, 3, 5, 4 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::FULL_HOUSE);

        Assert::That(score, Equals(0));
    }



    Spec(calculate_small_straight_positive)
    {
        rand_engine.set_next_roll( { 1, 1, 2, 3, 4} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::STRAIGHT_SMALL);

        Assert::That(score, Equals(30));
    }

    Spec(calculate_small_straight_negative)
    {
        rand_engine.set_next_roll( { 2, 5, 3, 5, 6 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::STRAIGHT_SMALL);

        Assert::That(score, Equals(0));
    }


    Spec(calculate_big_straight_positive)
    {
        rand_engine.set_next_roll( { 1, 2, 3, 4, 5 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::STRAIGHT_BIG);

        Assert::That(score, Equals(40));
    }

    Spec(calculate_big_straight_negative)
    {
        rand_engine.set_next_roll( { 2, 2, 3, 5, 3 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::STRAIGHT_BIG);

        Assert::That(score, Equals(0));
    }


    Spec(calculate_yacht_positive)
    {
        rand_engine.set_next_roll( { 1, 1, 1, 1, 1} );

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::YACHT);

        Assert::That(score, Equals(50));
    }

    Spec(calculate_yacht_negative)
    {
        rand_engine.set_next_roll( { 2, 2, 3, 5, 4 });

        player.roll();

        auto score = player.calculate_lower_score(scoresheet::YACHT);

        Assert::That(score, Equals(0));
    }

    Spec(keep_die)
    {

        rand_engine.set_next_roll( { 4, 3, 6, 1, 3});

        player.roll();

        player.keep_die(1);

        rand_engine.set_next_roll( {1, 2, 4, 3});

        player.roll();

        auto values = player.values();

        Assert::That(values[0], !Equals(4));

        Assert::That(values[1], Equals(3));

        player.keep_die(4);

        rand_engine.set_next_roll( {6, 6, 4});

        player.roll();

        values = player.values();

        Assert::That(values[0], !Equals(1));

        Assert::That(values[4], Equals(3));
    }

    Spec(calculate_best_lower_score)
    {
        rand_engine.set_next_roll( { 5, 5, 4, 4, 4 } );

        player.roll();

        auto lower = player.calculate_best_lower_score();

        Assert::That(lower.first, Equals(scoresheet::type::FULL_HOUSE));

        Assert::That(lower.second, Equals(25));

    }

    Spec(calculate_best_upper_score)
    {
        rand_engine.set_next_roll( { 2, 2, 3, 3, 4 } );

        player.roll();

        auto upper = player.calculate_best_upper_score();

        Assert::That(upper.first, Equals(3));

        Assert::That(upper.second, Equals(6));
    }

    Spec(calculate_best_score)
    {
        rand_engine.set_next_roll( {3, 6, 1, 6, 1});

        player.roll();

        auto score = player.calculate_best_score();

        Assert::That(score, Equals(17));

        player.score().lower_score(scoresheet::CHANCE, score);

        score = player.calculate_best_score();

        Assert::That(score, Equals(12));
    }
};

dice_test_engine yacht_player_test::rand_engine;

player yacht_player_test::player("testA", &yacht_player_test::rand_engine);
