#include <algorithm>
#include "player.h"

namespace arg3
{

    namespace yaht
    {

        bool sortDice(const die &d1, const die &d2)
        {
            return d1.value() < d2.value();
        }

        player::player(die::engine *const engine) : dice_(die_count(), die_sides(), engine), score_(), rollCount_(0)
        {}

        player::player(const player &other) : dice_(other.dice_), score_(other.score_), rollCount_(other.rollCount_),
            kept_(other.kept_)
        {

        }

        player::player(player &&other) : dice_(std::move(other.dice_)), score_(std::move(other.score_)), rollCount_(other.rollCount_),
            kept_(std::move(other.kept_))
        {

        }

        player::~player()
        {

        }

        player &player::operator=(const player &other)
        {
            dice_ = other.dice_;
            score_ = other.score_;
            rollCount_ = other.rollCount_;
            kept_ = other.kept_;

            return *this;
        }

        player &player::operator=(player && other)
        {
            dice_ = std::move(other.dice_);
            score_ = std::move(other.score_);
            rollCount_ = other.rollCount_;
            kept_ = std::move(other.kept_);

            return *this;
        }

        unsigned int player::die_sides() const
        {
            return die::DEFAULT_SIDES;
        }

        unsigned int player::die_count() const
        {
            return Constants::NUM_DICE;
        }

        unsigned short player::roll_count() const
        {
            return rollCount_;
        }

        void player::roll()
        {
            dice_.roll([&](size_t index, const die & d)
            {
                return !is_kept(index);
            });

            rollCount_++;
        }

        void player::reset()
        {
            rollCount_ = 0;
            kept_.clear();
        }

        const dice &player::d1ce() const
        {
            return dice_;
        }

        void player::keep_die(size_t index, bool value)
        {
            if (value)
                kept_[index] = dice_[index].value();
            else
                kept_.erase(index);
        }

        bool player::is_kept(size_t index)
        {
            return kept_.find(index) != kept_.end();
        }

        const die &player::d1e(size_t index) const
        {
            return dice_[index];
        }

        scoresheet &player::score()
        {
            return score_;
        }

        scoresheet::value_type player::calculate_upper_score(die::value_type value) const
        {
            scoresheet::value_type score = 0;
            for (auto &d : dice_)
            {
                if (d.value() == value)
                    score += value;
            }
            return score;
        }

        scoresheet::value_type player::calculate_number_of_a_kind(int length) const
        {
            auto values = dice_;

            sort(values.begin(), values.end(), sortDice);

            int count = 0;

            die::value_type lastValue = 0;

            for (auto &d : values)
            {
                if (lastValue != d)
                {
                    count = 0;
                    lastValue = d;
                }
                else
                {
                    if (++count == length - 1)
                    {
                        return calculate_chance();
                    }
                }
            }
            return 0;
        }

        scoresheet::value_type player::calculate_full_house() const
        {
            auto values = dice_;

            if (values.size() < Constants::NUM_DICE)
                return 0;

            sort(values.begin(), values.end(), sortDice);

            if (
                (
                    (values[0] == values[1]) &&
                    (values[1] == values[2]) &&
                    (values[3] == values[4]) &&
                    (values[2] != values[3])
                ) ||
                (
                    (values[0] == values[1]) &&
                    (values[1] != values[2]) &&
                    (values[2] == values[3]) &&
                    (values[3] == values[4])
                )
            )
            {
                return Constants::FULL_HOUSE_VALUE;
            }

            return 0;
        }

        scoresheet::value_type player::calculate_straight(int length) const
        {
            auto values = dice_;

            sort(values.begin(), values.end(), sortDice);

            die::value_type test = 0;

            int count = 0;

            for (auto &d : values)
            {
                if (test == 0)
                {

                    test = d;
                    continue;
                }
                if (test + 1 == d)
                {
                    if (++count == length)
                    {
                        return length * 10;
                    }
                }

                test = d;
            }
            return 0;
        }

        scoresheet::value_type player::calculate_chance() const
        {
            scoresheet::value_type value = 0;
            for (auto &d : dice_)
            {
                value += d.value();
            }
            return value;
        }

        pair<scoresheet::type, scoresheet::value_type> player::calculate_best_lower_score() const
        {
            scoresheet::value_type value = 0;
            scoresheet::type type = scoresheet::MAX_TYPE;

            for (int i = scoresheet::FIRST_TYPE; i < scoresheet::MAX_TYPE; i++)
            {
                scoresheet::type t = (scoresheet::type) i;

                if (score_.lower_score(t) != 0) continue;

                auto score = calculate_lower_score(t);
                if (score > value)
                {
                    type = t;
                    value = score;
                }
            }
            return make_pair(type, value);
        }

        pair<die::value_type, scoresheet::value_type> player::calculate_best_upper_score() const
        {
            die::value_type type = 0;
            scoresheet::value_type value = 0;

            for (die::value_type d = 1; d <= die::DEFAULT_SIDES; d++)
            {
                if (score_.upper_score(d) != 0) continue;

                auto score = calculate_upper_score(d);

                if (score > value)
                {
                    type = d;
                    value = score;
                }
            }

            return make_pair(type, value);
        }

        scoresheet::value_type player::calculate_best_score() const
        {
            auto lower = calculate_best_lower_score();

            auto higher = calculate_best_upper_score();

            return max(lower.second, higher.second);
        }

        scoresheet::value_type player::calculate_yaht() const
        {
            auto values = dice_;

            sort(values.begin(), values.end(), sortDice);

            if (values[0] == values[values.size() - 1])
                return Constants::YAHT_SCORE_VALUE;

            return 0;
        }


        scoresheet::value_type player::calculate_total_upper_score() const
        {
            scoresheet::value_type total_score = 0;

            for (int i = 0; i <= Constants::NUM_DICE; i++)
            {
                auto value = score_.upper_score(i + 1);

                total_score += value;
            }

            auto lower_score_total = total_score;

            if (total_score > Constants::UPPER_BONUS_LEVEL)
                lower_score_total += Constants::UPPER_BONUS;

            return lower_score_total;
        }


        scoresheet::value_type player::calculate_lower_score(scoresheet::type type) const
        {
            switch (type)
            {
            case scoresheet::KIND_THREE:
                return calculate_number_of_a_kind(Constants::NUM_DICE - 2);
            case scoresheet::KIND_FOUR:
                return calculate_number_of_a_kind(Constants::NUM_DICE - 1);
            case scoresheet::FULL_HOUSE:
                return calculate_full_house();
            case scoresheet::STRAIGHT_SMALL:
                return calculate_straight(Constants::NUM_DICE - 2);
            case scoresheet::STRAIGHT_BIG:
                return calculate_straight(Constants::NUM_DICE - 1);
            case scoresheet::YACHT:
                return calculate_yaht();
            case scoresheet::CHANCE:
                return calculate_chance();
            default:
                return 0;
            }
        }

    }

}
