/*!
     @header Yacht engine
     The Yacht engine provides a functional interface to a game of Yacht.
     Use the functions declared here to handle gameplay.
     @copyright ryan jennings (arg3.com) 2012 LGPL
     @updated 2012-09-09
 */
#ifndef ARG3_YACHT_H
#define ARG3_YACHT_H

#include "player.h"
#include <memory>
#include <vector>

namespace arg3
{

    namespace yaht
    {


        /*!
         * @class engine
         * A class that represents a game of Yacht
         */

        class game
        {
        public:
            /*!
             * Adds a player with given name to the game
             * @param name
             * the name to give the added player
             */
            void add_player(std::shared_ptr<player> player);

            /*!
             * Removes a player from the game
             * @param index
             * which player to remove
             */
            void remove_player(size_t index);

            void remove_player(const std::shared_ptr<player> &player);

            /*!
             * @result the player whose turn it is
             */
            std::shared_ptr<player> current_player();

            /*!
             * Advances to the next player in the game
             * @result the next player in the game
             */
            std::shared_ptr<player> next_player();

            std::shared_ptr<player> get_player(size_t index);

            void set_current_player(const std::shared_ptr<player> &player);

            const std::shared_ptr<player> get_player(size_t index) const;

            /*!
             * @result the number of players in the game
             */
            size_t number_of_players() const;

            void reset();

            void for_players(std::function<void(const std::shared_ptr<player> &)> funk);

            /*!
             * Sets the random engine to use when adding players
             * @param engine
             * The engine to use
             */
            void set_random_engine(die::engine *engine);

            game(const game &other);
            game(game  &&other);
            game &operator=(const game &);
            game &operator=(game && );

            // private singleton constructors
            game(die::engine * = die::default_engine);

            virtual ~game() {}

        private:
            std::vector<std::shared_ptr<player>> players_;

            die::engine *engine_;

            size_t currentPlayer_;
        };

    }

}
#endif

