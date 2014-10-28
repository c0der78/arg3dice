/*!
 * @header Yacht Constants
 * Constant values
 */
#ifndef ARG3_YACHT_CONSTANTS_H
#define ARG3_YACHT_CONSTANTS_H

namespace arg3
{

    namespace yaht
    {


        typedef struct consts
        {

            /*! @var ROLL_COUNT the number of times to roll the dice per turn */
            static const unsigned short ROLL_COUNT = 3;

            /*! @var NUM_DICE the number of dice in a cup */
            static const unsigned short NUM_DICE = 5;

            static const unsigned short YAHT_SCORE_VALUE = 50;
            static const unsigned short FULL_HOUSE_VALUE = 25;

            static const unsigned short UPPER_BONUS_LEVEL = 63;

            static const unsigned short UPPER_BONUS = 35;

        } Constants;

    }

}

#endif
