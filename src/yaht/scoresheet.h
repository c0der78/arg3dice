/*!
 * @header Yacht scoresheet
 * The Yacht scoresheet provides an interfaces to tracking scores in a game of Yacht
 */
#ifndef RJ_YACHT_SCORE_H
#define RJ_YACHT_SCORE_H

#include <array>
#include "../dice.h"
#include "constants.h"

using namespace std;

namespace rj
{
    namespace yaht
    {
        /*!
         * Class to track scores
         */
        class scoresheet
        {
           public:
            /*! Underlying type to store scores */
            typedef unsigned short value_type;

            /*! Types of scoring */
            typedef enum {
                /*! three of a kind */
                KIND_THREE,
                /*! four of a kind */
                KIND_FOUR,
                /*! full house */
                FULL_HOUSE,
                /*! straight of 4 */
                STRAIGHT_SMALL,
                /*! straight of 5 */
                STRAIGHT_BIG,
                /*! 5 of a kind */
                YACHT,
                /*! total of dice */
                CHANCE,
                /*! maximum type for looping */
                MAX_TYPE,
                /*! first type for looping */
                FIRST_TYPE = KIND_THREE
            } type;

            /*! default constructor */
            scoresheet();

            /*!
             * copy constructor
             * @param other the object to copy from
             */
            scoresheet(const scoresheet &other);

            scoresheet(scoresheet &&other);

            /*!
             * destructor
             */
            virtual ~scoresheet();

            /*!
             * assignment operator
             * @param rhs the right hand side of the operator
             */
            scoresheet &operator=(const scoresheet &rhs);

            scoresheet &operator=(scoresheet &&rhs);

            /*!
             * sets a score on the lower page
             * @param type the type of score
             * @param value the value to set
             */
            void lower_score(type type, scoresheet::value_type value, bool played = true);

            /*!
             * sets a score on the upper page
             * @param type the type of score
             * @param value the value to set
             */
            void upper_score(die::value_type type, scoresheet::value_type value, bool played = true);

            /*!
             * resets/clears the score
             */
            void reset();

            /*!
             * gets the upper score
             * @param type the type of score to get
             */
            scoresheet::value_type lower_score(type type) const;

            bool lower_played(type index) const;

            scoresheet::value_type total_score() const;

            /*!
             * gets the lower score
             * @param type the type of score to get
             */
            scoresheet::value_type upper_score(die::value_type type) const;

            bool upper_played(die::value_type index) const;

            size_t size() const;

            size_t number_played() const;

           private:
            unsigned short upperPlayed_, lowerPlayed_;
            array<value_type, die::DEFAULT_SIDES> upperValues_;
            array<value_type, MAX_TYPE> lowerValues_;
        };
    }
}

#endif
