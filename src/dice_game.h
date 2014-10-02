/*!
 * @header Dice Game
 * Abstract class for a game of dice
 */
#ifndef ARG3_DICE_GAME_H
#define ARG3_DICE_GAME_H

#include "dice.h"

namespace arg3
{

    /*!
     * class representing a game of dice
     */
    class dice_game
    {
    protected:
        dice dice_;

        dice_game(unsigned int, unsigned int, die::engine * = die::default_engine);
        dice_game(const dice_game &other);
        dice_game(dice_game  &&other);
        dice_game &operator=(const dice_game &);
        dice_game &operator=(dice_game && );
        virtual ~dice_game();
        virtual void on_roll() {};
    public:
        // rolls the dice for the game
        void roll();
        // returns the values of the dice for the game
        const vector<die::value_type> &values() const;
        const dice &d1ce() const;

        // equality operator
        bool operator==(const dice_game &) const;
        // inequality operator
        bool operator!=(const dice_game &) const;
    };

}

#endif
