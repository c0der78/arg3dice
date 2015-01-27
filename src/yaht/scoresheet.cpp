#include "scoresheet.h"
#include <algorithm>

namespace arg3
{

    namespace yaht
    {


        scoresheet::scoresheet()
        {
            lowerValues_.fill(0);
            upperValues_.fill(0);
        }

        scoresheet::scoresheet(const scoresheet &other) : upperValues_(other.upperValues_), lowerValues_(other.lowerValues_)
        {

        }

        scoresheet::scoresheet(scoresheet &&other) : upperValues_(std::move(other.upperValues_)), lowerValues_(std::move(other.lowerValues_))
        {

        }

        scoresheet::~scoresheet()
        {

        }

        scoresheet &scoresheet::operator=(const scoresheet &other)
        {
            upperValues_ = other.upperValues_;
            lowerValues_ = other.lowerValues_;

            return *this;
        }

        scoresheet &scoresheet::operator=(scoresheet && other)
        {
            upperValues_ = std::move(other.upperValues_);
            lowerValues_ = std::move(other.lowerValues_);

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
            return upperPlayed_ & (1 << index);
        }

        scoresheet::value_type scoresheet::upper_score(die::value_type index) const
        {
            auto i = std::max(0U, index - 1);

            if (i < upperValues_.size())
                return upperValues_[i];
            else
                return 0;
        }

        size_t scoresheet::number_of_values() const
        {
            return lowerValues_.size() + upperValues_.size();
        }

    }

}
