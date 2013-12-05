#include <igloo/igloo.h>
#include "scoresheet.h"
#include "constants.h"
#include "../dice.h"

using namespace igloo;
using namespace arg3;
using namespace arg3::yacht;

Context(scoresheet_test)
{
    scoresheet *score;

    void SetUp()
    {
        score = new scoresheet();
    }

    void TearDown()
    {
        delete score;
    }

    Spec(set_ones)
    {
        score->upper_score(1, 1 * Constants::NUM_DICE);

        Assert::That(score->upper_score(1), Equals(5));
    }

    Spec(upper_score)
    {

        for (int i = 1; i <= die::DEFAULT_SIDES; i++)
        {
            auto value = 2 * i;

            score->upper_score(2, value);

            Assert::That(score->upper_score(2), Equals(value));
        }
    }

    Spec(lower_score)
    {
        for (int i = scoresheet::FIRST_TYPE; i < scoresheet::MAX_TYPE; i++)
        {
            auto value = 2 * i;

            score->upper_score(2, value);

            Assert::That(score->upper_score(2), Equals(value));
        }
    }

    Spec(reset)
    {
        score->upper_score(2, 10);

        Assert::That(score->upper_score(2), Equals(10));

        score->reset();

        Assert::That(score->upper_score(2), !Equals(10));
    }
};
