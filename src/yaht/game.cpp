#include "game.h"
#include <algorithm>
#include <cassert>

namespace arg3
{

    namespace yaht
    {

        game::game(die::engine *engine) : players_(), engine_(engine), currentPlayer_(0)
        {
        }

        game::game(const game &other) : players_(other.players_), engine_(other.engine_), currentPlayer_(other.currentPlayer_)
        {

        }

        game::game(game &&other) : players_(std::move(other.players_)), engine_(std::move(other.engine_)), currentPlayer_(other.currentPlayer_)
        {

        }

        game &game::operator=(const game &other)
        {

            if (this != &other)
            {
                players_ = other.players_;
                engine_ = other.engine_;
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }


        game &game::operator=(game && other)
        {

            if (this != &other)
            {
                players_ = std::move(other.players_);
                engine_ = std::move(other.engine_);
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }

        void game::add_player(const string &name)
        {
            players_.emplace_back(name, engine_);
        }

        void game::remove_player(const string &name)
        {
            for (iterator p = begin(); p != end(); p++)
            {
                if (p->name() == name)
                {
                    players_.erase(p);
                    return;
                }
            }
        }

        void game::remove_player(size_t index)
        {
            iterator pos = players_.begin() + index;

            if (pos >= players_.end())
            {
                return;
            }

            players_.erase(pos);

            if (index <= currentPlayer_)
                currentPlayer_--;
        }


        player *game::current_player()
        {
            if (currentPlayer_ < 0 || currentPlayer_ >= static_cast<int>(players_.size()))
                return 0;

            return &(players_.at(currentPlayer_));
        }

        size_t game::number_of_players() const
        {
            return players_.size();
        }

        player *game::next_player()
        {
            if (players_.size() == 0)
                return 0;

            currentPlayer_++;

            if (currentPlayer_ >= players_.size())
            {
                currentPlayer_ = 0;
            }

            return &(players_.at(currentPlayer_));
        }

        void game::reset()
        {
            players_.clear();
            currentPlayer_ = 0;
        }

        // iterator methods
        game::iterator game::begin()
        {
            return players_.begin();
        }

        game::const_iterator game::begin() const
        {
            return players_.begin();
        }

        // const iterator methods
        const game::const_iterator game::cbegin() const
        {
            return players_.cbegin();
        }

        game::iterator game::end()
        {
            return players_.end();
        }

        game::const_iterator game::end() const
        {
            return players_.end();
        }

        const game::const_iterator game::cend() const
        {
            return players_.cend();
        }

        player *game::operator[] ( size_t index )
        {
            if (index >= players_.size())
                return NULL;

            return &(players_.at(index));
        }

        const player *game::operator[] ( size_t index ) const
        {
            return &(players_[index]);
        }

        player *game::operator[] (const string &name )
        {
            for (iterator p = begin(); p != end(); p++)
            {
                if (p->name() == name)
                    return &(*p);
            }
            return NULL;
        }

        const player *game::operator[] (const string &name) const
        {
            for (const_iterator p = begin(); p != end(); p++)
            {
                if (p->name() == name)
                    return &(*p);
            }
            return NULL;
        }

        void game::set_random_engine(die::engine *value)
        {
            engine_ = value;
        }

    }

}

