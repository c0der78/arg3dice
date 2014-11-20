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
            for (auto p = players_.begin(); p != players_.end(); ++p)
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
            auto pos = players_.begin() + index;

            if (pos >= players_.end())
            {
                return;
            }

            players_.erase(pos);

            if (static_cast<int>(index) <= currentPlayer_)
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

            if (currentPlayer_ >= static_cast<int>(players_.size()))
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

        const vector<player> &game::players() const
        {
            return players_;
        }

        void game::set_random_engine(die::engine *value)
        {
            engine_ = value;
        }

    }

}

