#include "scoresheet.h"
#include <algorithm>

namespace arg3
{

    namespace yaht
    {


        scoresheet::scoresheet() : upperPlayed_(0), lowerPlayed_(0)
        {
            lowerValues_.fill(0);
            upperValues_.fill(0);
        }

        scoresheet::scoresheet(const scoresheet &other) : upperPlayed_(other.upperPlayed_), lowerPlayed_(other.lowerPlayed_),
            upperValues_(other.upperValues_), lowerValues_(other.lowerValues_)
        {

        }

        scoresheet::scoresheet(scoresheet &&other) : upperPlayed_(std::move(other.upperPlayed_)), lowerPlayed_(std::move(other.lowerPlayed_)),
            upperValues_(std::move(other.upperValues_)), lowerValues_(std::move(other.lowerValues_))
        {

        }

        scoresheet::~scoresheet()
        {

        }

        scoresheet &scoresheet::operator=(const scoresheet &other)
        {
            upperValues_ = other.upperValues_;
            lowerValues_ = other.lowerValues_;
            upperPlayed_ = other.upperPlayed_;
            lowerPlayed_ = other.lowerPlayed_;

            return *this;
        }

        scoresheet &scoresheet::operator=(scoresheet && other)
        {
            upperValues_ = std::move(other.upperValues_);
            lowerValues_ = std::move(other.lowerValues_);
            upperPlayed_ = std::move(other.upperPlayed_);
            lowerPlayed_ = std::move(other.lowerPlayed_);

            return *this;
        }

        void scoresheet::reset()
        {
            lowerValues_.fill(0);
            upperValues_.fill(0);
        }

        void scoresheet::lower_score(type index, scoresheet::value_type value)
        {
            lowerValues_[index] = value;

            lowerPlayed_ |= (1 << (index));
        }

        void scoresheet::upper_score(die::value_type index, scoresheet::value_type value)
        {
            auto i = std::max(0U, index - 1);

            if (i < upperValues_.size())
            {
                upperValues_[i] = value;

                upperPlayed_ |= (1 << (i));
            }
        }

        bool scoresheet::lower_played(type index) const
        {
            return lowerPlayed_ & (1 << index);
        }

        scoresheet::value_type scoresheet::lower_score(type index) const
        {
            return lowerValues_[index];
        }

        bool scoresheet::upper_played(die::value_type index) const
        {
            auto i = std::max(0U, index - 1);

            return upperPlayed_ & (1 << i);
        }

        scoresheet::value_type scoresheet::upper_score(die::value_type index) const
        {
            auto i = std::max(0U, index - 1);

            if (i < upperValues_.size())
                return upperValues_[i];
            else
                return 0;
        }

        size_t scoresheet::size() const
        {
            return lowerValues_.size() + upperValues_.size();
        }


        scoresheet::value_type scoresheet::total_score() const
        {
            scoresheet::value_type total_score = 0;

            for (size_t i = 0; i < upperValues_.size(); i++)
            {
                total_score += upperValues_[i];
            }

            if (total_score > 63)
                total_score += 35;

            for (size_t i = 0; i < lowerValues_.size(); i++)
            {
                total_score += lowerValues_[i];
            }

            return total_score;
        }

        size_t scoresheet::number_played() const
        {
            scoresheet::value_type count = 0;

            for (size_t i = 0; i < upperValues_.size(); i++)
                if (upperPlayed_ & (1 << i))
                    count++;

            for (size_t i = 0; i < lowerValues_.size(); i++)
                if (lowerPlayed_ & (1 << i))
                    count++;

            return count;
        }
    }

}
