/*!
 * @header dice
 * A representation of dice or a single die for use in games.
 */
#ifndef ARG3_DICE_H
#define ARG3_DICE_H

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>

using namespace std;

namespace arg3
{

    /*!
     * A die with a given number of sides
     */
    class die
    {
    public:
        /*!
         * type of the value of die sides
         */
        typedef unsigned value_type;

        /*!
         * Default number of sides on a die
         */
        static const value_type DEFAULT_SIDES = 6;

        /*!
         * Abstract class for the underlying random engine
         */
        class engine
        {
        public:
            /*!
             * the random generator method
             * @param from the start range
             * @param to the end range
             */
            virtual die::value_type generate(die::value_type from, die::value_type to) = 0;
        };

        /*!
         * An instanceof the default random engine
         */
        static engine *const default_engine;

        /*!
         * custom sides constructor
         * throws exception if sides <= 0
         * @param sides the number of sides on this die
         * @param engine the die engine to use
         */
        die(const unsigned int sides = DEFAULT_SIDES, engine *const engine = default_engine);

        /*!
         * copy constructor
         * @param other the object to copy from
         */
        die(const die &other);

        die(die &&other);

        /*!
         * assignment operator
         * @param rhs the right hand side of the operator
         */
        die &operator=(const die &rhs);

        die &operator=(die && rhs);

        /*!
         * deconstructor
         */
        virtual ~die();

        /*!
         * returns the number of sides on the die
         */
        unsigned int sides() const;

        /*!
         * equality operator
         * @param rhs the right hand side of the operator
         */
        bool operator==(const die &rhs) const;
        /*!
         * inequality operator
         * @param rhs the right hand side of the operator
         */
        bool operator!=(const die &rhs) const;

        // cast operator
        operator value_type () const;

        /*!
         * sets the number of sides on the die
         * @param value the valude to set
         */
        void sides(const unsigned int value);

        /*!
         * current value of the die, or the side facing up
         */
        value_type value() const;

        // returns one of the sides on the die (random)
        value_type roll();

    private:
        engine *engine_;     // engine to use for dice rolling
        unsigned sides_; // number of sides on die
        value_type value_;   // the current roll value
    };


    namespace detail
    {

        /*!
         * Default implementation of the underlying random engine
         */
        class default_engine : public die::engine
        {
        public:
            /*!
             * the random generator method
             * @param from the starting range
             * @param to the ending range
             */
            die::value_type generate(die::value_type from, die::value_type to);
        };

    }
    /*!
     * simple class to encapsulate a collection of dice which can be rolled
     * a bonus value can be given
     */
    class dice
    {
    private:
        short bonus_;
        vector<die> dice_;
    public:
        /*! iterator type for each die */
        typedef typename vector<die>::iterator iterator;
        /*! const iterator type for each die */
        typedef typename vector<die>::const_iterator const_iterator;

        /*!
         * create x dice with default number of sides
         * creates x dice with y sides
         * @param num the number of dice to create
         * @param sides the number of sides per die
         * @param engine the die engine to use
         */
        dice(const unsigned int num, const unsigned int sides = die::DEFAULT_SIDES, die::engine *const engine = die::default_engine);

        /*!
         * copy constructor
         * @param other the other dice to copy
         */
        dice(const dice &other);

        dice(dice &&other);

        /*!
         * assignment operator
         * @param rhs the right hand side of the assignment
         */
        dice &operator= (const dice &rhs);

        dice &operator= (dice && rhs);

        /*!
         * deconstructor
         */
        virtual ~dice();

        // iterator methods
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;

        // const iterator methods
        const const_iterator cbegin() const;
        const const_iterator cend() const;

        // returns how many die in this collection
        unsigned int size() const;

        /*!
         * index operator
         * @param index the index
         */
        die &operator[] ( size_t index);

        /*!
         * const index operator
         * @param index the index
         */
        const die &operator[] ( size_t index) const;

        /*!
         * returns the bonus value
         */
        int bonus() const;

        /*!
         * sets the bonus value
         * @param value the bonus value to set
         */
        void bonus(const int value);

        // a string representation of the dice ex. 5d20
        const string to_string() const;

        // return the total of rolling all dice
        die::value_type roll(std::function<bool(size_t index, const die &d)> selector = nullptr);
    };

    ostream &operator<< (ostream &, const dice &);

}

#endif
