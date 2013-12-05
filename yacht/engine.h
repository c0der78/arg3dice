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

namespace arg3
{

    namespace yacht
    {


        /*!
         * @class engine
         * A class that represents a game of Yacht
         */
        class engine
        {
        public:

            /*!
             * Gets the instance of the yacht engine
             */
            static engine *instance();

            /*! iterator type for players */
            typedef typename vector<player>::iterator iterator;
            /*! const iterator type for players */
            typedef typename vector<player>::const_iterator const_iterator;

            /*!
             * Adds a player with given name to the game
             * @param name
             * the name to give the added player
             */
            void add_player(const string &name);

            /*!
             * Removes a player from the game
             * @param index
             * which player to remove
             */
            void remove_player(size_t index);

            /*!
             * @result the player whose turn it is
             */
            player *current_player();

            /*!
             * Advances to the next player in the game
             * @result the next player in the game
             */
            player *next_player();

            /*!
             * @result the number of players in the game
             */
            size_t number_of_players() const;

            // iterator methods
            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;

            // const iterator methods
            const const_iterator cbegin() const;
            const const_iterator cend() const;

            // index operators
            player *operator[] ( size_t );
            const player *operator[] ( size_t ) const;

            /*!
             * Sets the random engine to use when adding players
             * @param engine
             * The engine to use
             */
            void set_random_engine(die::engine *engine);

            engine(const engine &other);
            engine(engine  &&other);
            engine &operator=(const engine &);
            engine &operator=(engine && );

        private:
            vector<player> players_;

            die::engine *engine_;

            // private singleton constructors
            engine(die::engine * = die::default_engine);


            size_t currentPlayer_;
        };

    }

}
#endif

