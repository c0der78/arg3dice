#include "engine.h"

namespace arg3
{

    namespace yacht
    {

        std::ostream &operator<<(std::ostream &stm, const player &p)
        {
            stm << p.name();
            return stm;
        }

        player::player(const string &name, die::engine *const engine) : dice_game(die_count(), die_sides(), engine),
            score_(), rollCount_(0), name_(name)
        {

        }
        player::player(const player &other) : dice_game(other), score_(other.score_), rollCount_(other.rollCount_),
            name_(other.name_)
        {

        }

        player::player(player &&other) : dice_game(std::move(other)), score_(std::move(other.score_)), rollCount_(other.rollCount_),
            name_(std::move(other.name_))
        {

        }

        player::~player()
        {

        }

        player &player::operator=(const player &other)
        {

            dice_game::operator=(other);

            if (this != &other)
            {
                score_ = other.score_;
                rollCount_ = other.rollCount_;
                name_ = other.name_;
            }
            return *this;
        }

        player &player::operator=(player && other)
        {
            dice_game::operator=(std::move(other));

            if (this != &other)
            {
                score_ = std::move(other.score_);
                rollCount_ = other.rollCount_;
                name_ = std::move(other.name_);
            }
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

        void player::on_roll()
        {
            rollCount_++;
        }

        unsigned short player::roll_count() const
        {
            return rollCount_;
        }

        void player::reset()
        {
            rollCount_ = 0;

            for (auto & die : dice_)
            {
                die.keep(false);
            }
        }

        void player::keep_die(size_t index)
        {
            dice_[index].keep(true);
        }

        const string &player::name() const
        {
            return name_;
        }

        scoresheet &player::score()
        {
            return score_;
        }

        bool player::operator==(const player &other) const
        {
            return name_ == other.name_;
        }

        bool player::operator!=(const player &other) const
        {
            return !operator==(other);
        }

        scoresheet::value_type player::calculate_upper_score(die::value_type value) const
        {
            scoresheet::value_type score = 0;
            for (auto & d : dice_)
            {
                if (d.value() == value)
                    score += value;
            }
            return score;
        }



        scoresheet::value_type player::calculate_number_of_a_kind(int length) const
        {
            auto values = dice_.values();

            sort(values.begin(), values.end());

            int count = 0;
            die::value_type lastValue = 0;

            for (auto & d : values)
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
            auto values = dice_.values();

            if (values.size() < 5)
                return 0;

            sort(values.begin(), values.end());

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
                return 25;
            }

            return 0;
        }

        scoresheet::value_type player::calculate_straight(int length) const
        {
            auto values = dice_.values();

            sort(values.begin(), values.end());

            die::value_type test = 0;

            int count = 0;

            for (auto & d : values)
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
            for (auto & d : dice_.values())
            {
                value += d;
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

        scoresheet::value_type player::calculate_yacht() const
        {
            auto values = dice_.values();

            sort(values.begin(), values.end());

            if (values.front() == values.back())
                return 50;

            return 0;
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
                return calculate_yacht();
            case scoresheet::CHANCE:
                return calculate_chance();
            default:
                return 0;
            }
        }

    }

}
