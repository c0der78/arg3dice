
#include <random>
#include <functional>
#include "dice.h"
#include <cassert>

namespace arg3
{
    // #######################################################################################################
    // die
    // #######################################################################################################

    // randomness for dice rolls
    static detail::default_engine default_die_engine = detail::default_engine();

    const die::value_type die::DEFAULT_SIDES;

    die::engine *const die::default_engine = &default_die_engine;

    die::value_type detail::default_engine::generate(die::value_type from, die::value_type to)
    {

        static std::default_random_engine random_engine(time(0));

        uniform_int_distribution<die::value_type> distribution(from, to);

        return distribution(random_engine);
    }

    die::die(const unsigned int sides, die::engine *const engine) : engine_(engine), value_(0), keep_(false)
    {
        if (sides == 0)
        {
            throw new invalid_argument("dice must have one or more sides.");
        }

        sides_ = sides;
    }

    die::die(const die &other) : engine_(other.engine_), sides_(other.sides_), value_(other.value_), keep_(other.keep_)
    {
    }

    die::die(die &&other) : engine_(std::move(other.engine_)), sides_(other.sides_), value_(other.value_), keep_(other.keep_)
    {}

    die &die::operator= (const die &other)
    {
        engine_ = other.engine_;
        sides_ = other.sides_;
        value_ = other.value_;
        keep_ = other.keep_;

        return *this;
    }

    die &die::operator= (die && other)
    {
        engine_ = std::move(other.engine_);
        sides_ = other.sides_;
        value_ = other.value_;
        keep_ = other.keep_;

        return *this;
    }

    die::~die()
    {
        // nothing to do
    }

    bool die::operator== (const die &rhs) const
    {
        return value_ == rhs.value_;
    }

    bool die::operator!= (const die &rhs) const
    {
        return !operator==(rhs);
    }

    die::operator value_type() const
    {
        return value_;
    }

    /*
     * returns the number of sides on the die
     */
    unsigned int die::sides() const
    {
        return sides_;
    }

    /*
     * sets the number of sides on the die
     */
    void die::sides(const unsigned int value)
    {
        sides_ = value;
    }

    die::value_type die::value() const
    {
        return value_;
    }

    // returns one of the sides on the die (random)
    die::value_type die::roll()
    {
        assert(engine_ != 0);

        value_ = engine_->generate(1, sides_);

        return value_;
    }

    void die::keep(bool value)
    {
        keep_ = value;
    }

    bool die::keep() const
    {
        return keep_;
    }

    // #######################################################################################################
    // dice
    // #######################################################################################################

    // creates x dice with y sides
    dice::dice(const unsigned int count, const unsigned int sides, die::engine *const engine) : bonus_(0), dice_(), lastRoll_()
    {
        for (int i = 0; i < count; i++)
            dice_.push_back(die(sides, engine));
    }

    // copy constructor
    dice::dice(const dice &other) : bonus_(other.bonus_), dice_(other.dice_), lastRoll_(other.lastRoll_)
    {
    }

    // move constructor
    dice::dice(dice &&other) : bonus_(other.bonus_), dice_(std::move(other.dice_)), lastRoll_(std::move(other.lastRoll_))
    {
    }

    dice &dice::operator=(const dice &other)
    {
        bonus_ = other.bonus_;
        dice_ = other.dice_;
        lastRoll_ = other.lastRoll_;

        return *this;
    }

    dice &dice::operator=(dice && other)
    {
        bonus_ = other.bonus_;
        dice_ = std::move(other.dice_);
        lastRoll_ = std::move(other.lastRoll_);

        return *this;
    }

    bool dice::operator==(const dice &other) const
    {
        return bonus_ == other.bonus_ && dice_ == other.dice_ && lastRoll_ == other.lastRoll_;
    }

    bool dice::operator!=(const dice &other) const
    {
        return !operator==(other);
    }

    // deconstructor
    dice::~dice()
    {

    }

    // iterator methods
    dice::iterator dice::begin()
    {
        return dice_.begin();
    }

    dice::const_iterator dice::begin() const
    {
        return dice_.begin();
    }

    // const iterator methods
    const dice::const_iterator dice::cbegin() const
    {
        return dice_.cbegin();
    }

    dice::iterator dice::end()
    {
        return dice_.end();
    }

    dice::const_iterator dice::end() const
    {
        return dice_.end();
    }

    const dice::const_iterator dice::cend() const
    {
        return dice_.cend();
    }

    unsigned int dice::size() const
    {
        return dice_.size();
    }

    /*
     * returns the bonus value
     */
    int dice::bonus() const
    {
        return bonus_;
    }

    /*
     * sets the bonus value
     */
    void dice::bonus(const int value)
    {
        bonus_ = value;
    }

    // a string representation of the dice ex. 5d20
    const string dice::to_string() const
    {
        stringstream buf;

        size_t size = dice_.size();

        buf << size;

        if (size > 0)
        {
            buf << "d" << dice_.begin()->sides();
        }

        if (bonus_ > 0)
        {
            buf << "+" << bonus_;
        }
        return buf.str();
    }

    // returns the values for each die in the last roll
    const vector<die::value_type> &dice::values() const
    {
        return lastRoll_;
    }

    // return the total of rolling all dice
    const unsigned int dice::roll()
    {
        die::value_type value = 0;

        lastRoll_.clear(); // reset the last roll values

        for (die & d : dice_)
        {
            auto roll = d.keep() ? d.value() : d.roll(); // roll the die
            value += roll; // sum the total
            // save each value for use later
            lastRoll_.push_back(roll);
        }
        return value + bonus(); // add the bonus
    }

    die &dice::operator[] ( size_t n )
    {
        return dice_[n];
    }

    const die &dice::operator[] ( size_t n ) const
    {
        return dice_[n];
    }

    ostream &operator<< (ostream &out, const dice &dice)
    {
        out << dice.to_string();
        return out;
    }

}
