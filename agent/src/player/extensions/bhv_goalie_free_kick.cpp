// -*-c++-*-

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bhv_goalie_free_kick.h"

#include "bhv_goalie_basic_move.h"

#include "bhv_basic_offensive_kick.h"

#include "basic_actions/body_clear_ball.h"

#include "basic_actions/basic_actions.h"
#include "basic_actions/body_kick_one_step.h"
#include "basic_actions/neck_scan_field.h"

#include <rcsc/player/player_agent.h>
#include <rcsc/player/debug_client.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/geom/rect_2d.h>

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!
  execute action
*/
bool
Bhv_GoalieFreeKick::execute( PlayerAgent * agent )
{
    static bool s_first_move = false;
    static bool s_second_move = false;
    static int s_second_wait_count = 0;

    dlog.addText( Logger::TEAM,
                  __FILE__": Bhf_GoalieFreeKick" );
    if ( agent->world().gameMode().type() != GameMode::GoalieCatch_
         || agent->world().gameMode().side() != agent->world().ourSide()
         || ! agent->world().self().isKickable() )
    {
        dlog.addText( Logger::TEAM,
                      __FILE__": Bhv_GoalieFreeKick. Not a goalie catch mode" );

        Bhv_GoalieBasicMove().execute( agent );
        return true;
    }


    const long time_diff
        = agent->world().time().cycle()
        - agent->effector().getCatchTime().cycle();
    //- M_catch_time.cycle();

    // reset flags & wait
    if ( time_diff <= 2 )
    {
        s_first_move = false;
        s_second_move = false;
        s_second_wait_count = 0;

        doWait( agent );
        return true;
    }

    // first move
    if ( ! s_first_move )
    {
        //Vector2D move_target( ServerParam::i().ourPenaltyAreaLine() - 0.8, 0.0 );
        Vector2D move_target( ServerParam::i().ourPenaltyAreaLineX() - 1.5,
                              agent->world().ball().pos().y > 0.0 ? -13.0 : 13.0 );
        //Vector2D move_target( -45.0, 0.0 );
        s_first_move = true;
        s_second_move = false;
        s_second_wait_count = 0;
        agent->doMove( move_target.x, move_target.y );
        agent->setNeckAction( new Neck_ScanField );
        return true;
    }

    // after first move
    // check stamina recovery or wait teammate
    Rect2D our_pen( Vector2D( -52.5, -40.0 ),
                    Vector2D( -36.0, 40.0 ) );
    if ( time_diff < 50
         || agent->world().getSetPlayCount() < 3
         || ( time_diff < ServerParam::i().dropBallTime() - 15
              && ( agent->world().self().stamina() < ServerParam::i().staminaMax() * 0.9
                   || agent->world().existTeammateIn( our_pen, 20, true )
                   )
              )
         )
    {
        doWait( agent );
        return true;
    }

    // second move
    if ( ! s_second_move )
    {
        Vector2D kick_point = getKickPoint( agent );
        agent->doMove( kick_point.x, kick_point.y );
        agent->setNeckAction( new Neck_ScanField );
        s_second_move = true;
        s_second_wait_count = 0;
        return true;
    }

    s_second_wait_count++;

    // after second move
    // wait see info
    if ( s_second_wait_count < 5
         || agent->world().seeTime() != agent->world().time() )
    {
        doWait( agent );
        return true;
    }

    s_first_move = false;
    s_second_move = false;
    s_second_wait_count = 0;

    // register kick intention
    doKick( agent );

    return true;
}

/*-------------------------------------------------------------------*/
/*!

 */
Vector2D
Bhv_GoalieFreeKick::getKickPoint( const PlayerAgent * agent )
{
    static const double base_x = -43.0;
    static const double base_y = 10.0;

    std::vector< std::pair< Vector2D, double > > candidates;
    candidates.reserve( 4 );
    candidates.push_back( std::make_pair( Vector2D( base_x, base_y ), 0.0 ) );
    candidates.push_back( std::make_pair( Vector2D( base_x, -base_y ), 0.0 ) );
    candidates.push_back( std::make_pair( Vector2D( base_x, 0.0 ), 0.0 ) );

    for ( PlayerObject::Cont::const_iterator o = agent->world().opponentsFromSelf().begin(),
              end = agent->world().opponentsFromSelf().end();
          o != end;
          ++o )
    {
        for ( std::vector< std::pair< Vector2D, double > >::iterator it = candidates.begin();
              it != candidates.end();
              ++it )
        {
            it->second += 1.0 / (*o)->pos().dist2( it->first );
        }
    }

    Vector2D best_pos = candidates.front().first;
    double min_cong = 10000.0;
    for ( std::vector< std::pair< Vector2D, double > >::iterator it = candidates.begin();
          it != candidates.end();
          ++it )
    {
        if ( it->second < min_cong )
        {
            best_pos = it->first;
            min_cong = it->second;
        }
    }

    return best_pos;
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Bhv_GoalieFreeKick::doKick( PlayerAgent * agent )
{
    Vector2D target_point;
    if (Bhv_BasicOffensiveKick().pass(agent, 1)){
            dlog.addText( Logger::TEAM,
                          __FILE__": bhv_basic_offensive_kick pass");    
    }

    Body_ClearBall().execute( agent );
    agent->setNeckAction( new Neck_ScanField() );
}

/*-------------------------------------------------------------------*/
/*!

 */
void
Bhv_GoalieFreeKick::doWait( PlayerAgent * agent )
{
    const WorldModel & wm = agent->world();
    Vector2D face_target( 0.0, 0.0 );

    if ( wm.self().pos().x > ServerParam::i().ourPenaltyAreaLineX()
         - ServerParam::i().ballSize()
         - wm.self().playerType().playerSize()
         - 0.5 )
    {
        face_target.assign( ServerParam::i().ourPenaltyAreaLineX() - 1.0,
                            0.0 );
    }

    Body_TurnToPoint( face_target ).execute( agent );
    agent->setNeckAction( new Neck_ScanField() );
}
