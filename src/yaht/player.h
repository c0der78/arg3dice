/*!
     @header Yacht player
     The Yacht player provides a functional interface to a player in a game of
   Yacht. Use the functions declared here to handle gameplay.
     @updated 2012-09-09
 */
#ifndef CODA_YACHT_PLAYER_H
#define CODA_YACHT_PLAYER_H

#include "../dice.h"
#include "scoresheet.h"
#include <map>

namespace coda {
  namespace yaht {
    /*!
     * @class player
     * A player in a game of yaht(zee)
     */
    class player {
      friend std::ostream &operator<<(std::ostream &stm, const player &);

      public:
      /*!
       * number of sides in a die
       */
      unsigned int die_sides() const;

      /*!
       * number of die
       */
      unsigned int die_count() const;

      /*!
       * default constructor
       */
      player(die::engine *const = die::default_engine);

      /*!
       * copy constructor
       */
      player(const player &);

      player(player &&);

      /*!
       * assignment operator
       */
      player &operator=(const player &);

      player &operator=(player &&);

      /*!
       * destructor
       */
      virtual ~player();

      /*!
       * keeps a die
       */
      void keep_die(size_t index, bool value);

      bool is_kept(size_t index) const;

      bool is_finished() const;

      /*!
       * calculate a value on the lower part of scoresheet
       * @param type
       * the type of lower score
       */
      scoresheet::value_type calculate_lower_score(scoresheet::type) const;

      /*!
       * calcualte a value on the upper part of scoresheet
       * @param type
       * the type of upper score
       */
      scoresheet::value_type calculate_upper_score(die::value_type) const;

      scoresheet::value_type calculate_total_upper_score() const;

      /*!
       * calculates the best score available in hand
       */
      scoresheet::value_type calculate_best_score() const;

      pair<scoresheet::type, scoresheet::value_type>
      calculate_best_lower_score() const;

      pair<die::value_type, scoresheet::value_type>
      calculate_best_upper_score() const;

      scoresheet &score();

      const dice &d1ce() const;

      const die &d1e(size_t index) const;

      unsigned short roll_count() const;

      void reset();

      void roll();

      private:
      dice dice_;

      scoresheet::value_type calculate_number_of_a_kind(int) const;
      scoresheet::value_type calculate_full_house() const;
      scoresheet::value_type calculate_straight(int) const;
      scoresheet::value_type calculate_chance() const;
      scoresheet::value_type calculate_yaht() const;

      scoresheet score_;         // the score sheet
      unsigned short rollCount_; // number of die rolls
      map<size_t, int> kept_;    // kept die values
    };
  } // namespace yaht
} // namespace coda

#endif
