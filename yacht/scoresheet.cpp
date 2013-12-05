#include "engine.h"

namespace arg3
{

    namespace yacht
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
            if (this != &other)
            {
                upperValues_ = other.upperValues_;
                lowerValues_ = other.lowerValues_;
            }
            return *this;
        }

        scoresheet &scoresheet::operator=(scoresheet && other)
        {
            if (this != &other)
            {
                upperValues_ = std::move(other.upperValues_);
                lowerValues_ = std::move(other.lowerValues_);
            }
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
        }

        void scoresheet::upper_score(die::value_type index, scoresheet::value_type value)
        {
            upperValues_[index] = value;
        }

        scoresheet::value_type scoresheet::lower_score(type index) const
        {
            return lowerValues_[index];
        }

        scoresheet::value_type scoresheet::upper_score(die::value_type index) const
        {
            return upperValues_[index];
        }

    }

}
