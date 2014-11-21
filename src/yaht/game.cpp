#include "game.h"
#include <algorithm>

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

        game::game(game &&other) : players_(std::move(other.players_)), engine_(std::move(other.engine_)), currentPlayer_(std::move(other.currentPlayer_))
        {

        }

        game &game::operator=(const game &other)
        {

            players_ = other.players_;
            engine_ = other.engine_;
            currentPlayer_ = other.currentPlayer_;

            return *this;
        }


        game &game::operator=(game && other)
        {
            players_ = std::move(other.players_);
            engine_ = std::move(other.engine_);
            currentPlayer_ = std::move(other.currentPlayer_);

            return *this;
        }

        shared_ptr<player> game::operator[](size_t index)
        {
            if (index >= players_.size()) return nullptr;

            return players_[index];
        }

        void game::add_player(shared_ptr<player> player)
        {
            auto it = find(players_.begin(), players_.end(), player);

            if (it == players_.end())
                players_.push_back(player);
        }

        void game::remove_player(const shared_ptr<player> &player)
        {
            auto it = find(players_.begin(), players_.end(), player);

            if (it != players_.end())
            {

                size_t index = distance(players_.begin(), it);

                if (index < currentPlayer_ )
                    currentPlayer_--;

                players_.erase(it);
            }
        }

        void game::remove_player(size_t index)
        {
            auto pos = players_.begin() + index;

            if (pos >= players_.end())
            {
                return;
            }

            size_t iPos = distance(players_.begin(), pos);

            if (iPos < currentPlayer_)
                currentPlayer_--;

            players_.erase(pos);

        }


        shared_ptr<player> game::current_player()
        {
            size_t pSize = players_.size();

            if (players_.size() == 0)
                return nullptr;

            if (currentPlayer_ >= pSize)
            {
                currentPlayer_ = 0;
            }

            return players_[currentPlayer_];
        }

        size_t game::number_of_players() const
        {
            return players_.size();
        }

        shared_ptr<player> game::next_player()
        {
            size_t pSize = players_.size();

            if (pSize == 0)
                return 0;

            if (currentPlayer_ == pSize || ++currentPlayer_ == pSize)
            {
                currentPlayer_ = 0;
            }

            return players_[currentPlayer_];
        }

        void game::reset()
        {
            players_.clear();
            currentPlayer_ = 0;
        }

        void game::for_players(std::function<void(const shared_ptr<player> &player)> funk)
        {
            for (const auto & p : players_)
            {
                funk(p);
            }
        }

        void game::set_random_engine(die::engine *value)
        {
            engine_ = value;
        }

    }

}

