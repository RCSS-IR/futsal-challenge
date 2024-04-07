// -*-c++-*-

/*!
  \file strategy.h
  \brief team strategy manager Header File
*/

/*
 *Copyright:

 Copyright (C) Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef STRATEGY_H
#define STRATEGY_H

#include <rcsc/geom/vector_2d.h>

#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>
#include <string>

// # define USE_GENERIC_FACTORY 1

namespace rcsc {
class CmdLineParser;
class WorldModel;
}

class Strategy {
public:
    // private for singleton
    Strategy();

    // not used
    Strategy( const Strategy & );
    const Strategy & operator=( const Strategy & );

    static
    Strategy & instance();

    static
    const
    Strategy & i()
      {
          return instance();
      }

    static
    rcsc::Vector2D getHomePosition(const rcsc::WorldModel & wm, int self_unum);

    static
    double get_normal_dash_power( const rcsc::WorldModel & wm );
};

#endif
