#include "engine.h"
#include <algorithm>
#include <cassert>

namespace arg3
{

    namespace yacht
    {

        engine::engine(die::engine *engine) : players_(), engine_(engine), currentPlayer_(0)
        {
        }

        engine::engine(const engine &other) : players_(other.players_), engine_(other.engine_), currentPlayer_(other.currentPlayer_)
        {

        }

        engine::engine(engine &&other) : players_(std::move(other.players_)), engine_(std::move(other.engine_)), currentPlayer_(other.currentPlayer_)
        {

        }

        engine &engine::operator=(const engine &other)
        {

            if (this != &other)
            {
                players_ = other.players_;
                engine_ = other.engine_;
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }


        engine &engine::operator=(engine && other)
        {

            if (this != &other)
            {
                players_ = std::move(other.players_);
                engine_ = std::move(other.engine_);
                currentPlayer_ = other.currentPlayer_;
            }
            return *this;
        }

        void engine::add_player(const string &name)
        {
            players_.push_back(player(name, engine_));
        }

        void engine::remove_player(size_t index)
        {

            iterator pos = players_.begin() + index;

            if (pos >= players_.end())
            {
                return;
            }

            players_.erase(pos);

            if (index >= currentPlayer_)
                currentPlayer_--;
        }

        engine *engine::instance()
        {
            static engine instance;
            return &instance;
        }


        player *engine::current_player()
        {
            if (currentPlayer_ >= players_.size())
                return 0;

            return &(players_.at(currentPlayer_));
        }

        size_t engine::number_of_players() const
        {
            return players_.size();
        }

        player *engine::next_player()
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

        // iterator methods
        engine::iterator engine::begin()
        {
            return players_.begin();
        }

        engine::const_iterator engine::begin() const
        {
            return players_.begin();
        }

        // const iterator methods
        const engine::const_iterator engine::cbegin() const
        {
            return players_.cbegin();
        }

        engine::iterator engine::end()
        {
            return players_.end();
        }

        engine::const_iterator engine::end() const
        {
            return players_.end();
        }

        const engine::const_iterator engine::cend() const
        {
            return players_.cend();
        }

        player *engine::operator[] ( size_t index )
        {
            return &(players_.at(index));
        }

        const player *engine::operator[] ( size_t index ) const
        {
            return &(players_[index]);
        }

        void engine::set_random_engine(die::engine *value)
        {
            engine_ = value;
        }

    }

}

