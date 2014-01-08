/*!
     @header Yacht player
     The Yacht player provides a functional interface to a player in a game of Yacht.
     Use the functions declared here to handle gameplay.
     @copyright ryan jennings (arg3.com) 2012 LGPL
     @updated 2012-09-09
 */
#ifndef ARG3_YACHT_PLAYER_H
#define ARG3_YACHT_PLAYER_H

#include "../dice_game.h"
#include "scoresheet.h"

namespace arg3
{

    namespace yacht
    {

        /*!
         * @class player
         * A player in a game of yacht
         */
        class player : public dice_game
        {
            friend std::ostream &operator<<(std::ostream &stm, const player & );

        public:
            /*!
             * number of sides in a die
             */
            unsigned int die_sides() const;

            /*!
             * number of die
             */
            unsigned int die_count() const;

            /*!
             * default constructor takes a name
             * @param name
             * the name given to a player
             * @param engine
             * the die engine to use
             */
            player(const string &name, die::engine *const = die::default_engine);

            /*!
             * copy constructor
             */
            player(const player &);

            player(player &&);

            /*!
             * assignment operator
             */
            player &operator=(const player &);

            player &operator=(player && );

            /*!
             * destructor
             */
            virtual ~player();

            /*!
             * keeps a die
             */
            void keep_die(size_t index);

            /*!
             * calculate a value on the lower part of scoresheet
             * @param type
             * the type of lower score
             */
            scoresheet::value_type calculate_lower_score(scoresheet::type) const;

            /*!
             * calcualte a value on the upper part of scoresheet
             * @param type
             * the type of upper score
             */
            scoresheet::value_type calculate_upper_score(die::value_type) const;

            /*!
             * calculates the best score available in hand
             */
            scoresheet::value_type calculate_best_score() const;

            pair<scoresheet::type, scoresheet::value_type> calculate_best_lower_score() const;

            pair<die::value_type, scoresheet::value_type> calculate_best_upper_score() const;


            scoresheet &score();

            /*!
             * name of the player
             */
            const string &name() const;

            /*!
             * equality operator
             */
            bool operator==(const player &) const;

            /*!
             * equality operator
             */
            bool operator!=(const player &) const;

            unsigned short roll_count() const;

            void reset();

        private:

            void on_roll();

            scoresheet::value_type calculate_number_of_a_kind(int) const;
            scoresheet::value_type calculate_full_house() const;
            scoresheet::value_type calculate_straight(int) const;
            scoresheet::value_type calculate_chance() const;
            scoresheet::value_type calculate_yacht() const;

            scoresheet score_;  // the score sheet
            unsigned short rollCount_; // number of die rolls
            string name_;   // player name
        };

    }

}

#endif
