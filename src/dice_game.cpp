#include "dice_game.h"

namespace arg3
{
    dice_game::dice_game(unsigned int count, unsigned int sides, die::engine *const engine) : dice_(count, sides, engine)
    {

    }

    dice_game::dice_game(const dice_game &other) : dice_(other.dice_)
    {

    }

    dice_game::dice_game(dice_game &&other) : dice_(std::move(other.dice_))
    {}

    dice_game::~dice_game()
    {

    }

    dice_game &dice_game::operator=(const dice_game &other)
    {
        dice_ = other.dice_;

        return *this;
    }

    dice_game &dice_game::operator=(dice_game && other)
    {

        dice_ = std::move(other.dice_);

        return *this;
    }

    void dice_game::roll()
    {
        dice_.roll();

        on_roll();
    }

    const vector<die::value_type> &dice_game::values() const
    {
        return dice_.values();
    }

    const dice &dice_game::d1ce() const
    {
        return dice_;
    }

    bool dice_game::operator==(const dice_game &other) const
    {
        return dice_ == other.dice_;
    }

    bool dice_game::operator!=(const dice_game &other) const
    {
        return !operator==(other);
    }
}
