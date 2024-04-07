// -*-c++-*-

/*!
  \file strategy.cpp
  \brief team strategh Source File
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "strategy.h"

#include <rcsc/player/intercept_table.h>
#include <rcsc/player/world_model.h>

#include <rcsc/common/logger.h>
#include <rcsc/common/server_param.h>
#include <rcsc/param/cmd_line_parser.h>
#include <rcsc/param/param_map.h>
#include <rcsc/game_mode.h>
#include <rcsc/player/intercept_table.h>

#include <iostream>

using namespace rcsc;

/*-------------------------------------------------------------------*/
/*!

 */
Strategy::Strategy()
{
}

/*-------------------------------------------------------------------*/
/*!

 */
Strategy &
Strategy::instance()
{
    static Strategy s_instance;
    return s_instance;
}

/*-------------------------------------------------------------------*/
/*!

 */

Vector2D Strategy::getHomePosition(const rcsc::WorldModel &wm, int self_unum)
{
    if ( wm.gameMode().type() == GameMode::BeforeKickOff
         || wm.gameMode().type() == GameMode::AfterGoal_ )
    {
        std::vector<Vector2D> KickOffPosition(4);
        KickOffPosition[1] = Vector2D(-10.0,0);
        KickOffPosition[2] = Vector2D(-10,-10);
        KickOffPosition[3] = Vector2D(-10,10);
        Vector2D move_point =  KickOffPosition.at( self_unum );
        return move_point;
    }

    int ball_step = 0;
    if ( wm.gameMode().type() == GameMode::PlayOn
         || wm.gameMode().type() == GameMode::GoalKick_ )
    {
        ball_step = std::min( 1000, wm.interceptTable().teammateStep() );
        ball_step = std::min( ball_step, wm.interceptTable().opponentStep() );
        ball_step = std::min( ball_step, wm.interceptTable().selfStep() );
    }

    Vector2D ball_pos = wm.ball().inertiaPoint( ball_step );

    dlog.addText( Logger::TEAM,
                  __FILE__": HOME POSITION: ball pos=(%.1f %.1f) step=%d",
                  ball_pos.x, ball_pos.y,
                  ball_step );

    std::vector<Vector2D> positions(4);
    double min_x_rectengle[4]={0,-20,-22.5,-22.5};
    double max_x_rectengle[4]={0,-10.0,18,18};
    double min_y_rectengle[4]={0,-2,-13,-2};
    double max_y_rectengle[4]={0,+2, 2, 13};

    for(int i=1; i<=3; i++){
          double xx_rectengle = max_x_rectengle[i] - min_x_rectengle[i];
          double yy_rectengle = max_y_rectengle[i] - min_y_rectengle[i];
          double x_ball = ball_pos.x + 22.5;
          x_ball /= 45.0;
          double y_ball = ball_pos.y + 14.0;
          y_ball /= 28.0;
          double x_pos = xx_rectengle * x_ball + min_x_rectengle[i];
          double y_pos = yy_rectengle * y_ball + min_y_rectengle[i];
          positions[i] = Vector2D(x_pos,y_pos);
    }

    if ( ServerParam::i().useOffside() )
    {
        double max_x = wm.offsideLineX();
        if ( ServerParam::i().kickoffOffside()
             && ( wm.gameMode().type() == GameMode::BeforeKickOff
                  || wm.gameMode().type() == GameMode::AfterGoal_ ) )
        {
            max_x = 0.0;
        }
        else
        {
            int mate_step = wm.interceptTable().teammateStep();
            if ( mate_step < 50 )
            {
                Vector2D trap_pos = wm.ball().inertiaPoint( mate_step );
                if ( trap_pos.x > max_x ) max_x = trap_pos.x;
            }

            max_x -= 1.0;
        }

        for ( int unum = 1; unum <= 4; ++unum )
        {
            if ( positions[unum].x > max_x )
            {
                dlog.addText( Logger::TEAM,
                              "____ %d offside. home_pos_x %.2f -> %.2f",
                              unum,
                              positions[unum].x, max_x );
                positions[unum].x = max_x;
            }
        }
    }
    return positions.at(self_unum);
}

/*-------------------------------------------------------------------*/
/*!

 */
double
Strategy::get_normal_dash_power( const WorldModel & wm )
{
    static bool s_recover_mode = false;

    if ( wm.self().staminaModel().capacityIsEmpty() )
    {
        return std::min( ServerParam::i().maxDashPower(),
                         wm.self().stamina() + wm.self().playerType().extraStamina() );
    }

    const int self_min = wm.interceptTable().selfStep();
    const int mate_min = wm.interceptTable().teammateStep();
    const int opp_min = wm.interceptTable().opponentStep();

    // check recover
    if ( wm.self().staminaModel().capacityIsEmpty() )
    {
        s_recover_mode = false;
    }
    else if ( wm.self().stamina() < ServerParam::i().staminaMax() * 0.5 )
    {
        s_recover_mode = true;
    }
    else if ( wm.self().stamina() > ServerParam::i().staminaMax() * 0.7 )
    {
        s_recover_mode = false;
    }

    /*--------------------------------------------------------*/
    double dash_power = ServerParam::i().maxDashPower();
    const double my_inc
        = wm.self().playerType().staminaIncMax()
        * wm.self().recovery();

    if ( wm.ourDefenseLineX() > wm.self().pos().x
         && wm.ball().pos().x < wm.ourDefenseLineX() + 20.0 )
    {
        dlog.addText( Logger::TEAM,
                      __FILE__": (get_normal_dash_power) correct DF line. keep max power" );
        // keep max power
        dash_power = ServerParam::i().maxDashPower();
    }
    else if ( s_recover_mode )
    {
        dash_power = my_inc - 25.0; // preffered recover value
        if ( dash_power < 0.0 ) dash_power = 0.0;

        dlog.addText( Logger::TEAM,
                      __FILE__": (get_normal_dash_power) recovering" );
    }
    // exist kickable teammate
    else if ( wm.kickableTeammate()
              && wm.ball().distFromSelf() < 20.0 )
    {
        dash_power = std::min( my_inc * 1.1,
                               ServerParam::i().maxDashPower() );
        dlog.addText( Logger::TEAM,
                      __FILE__": (get_normal_dash_power) exist kickable teammate. dash_power=%.1f",
                      dash_power );
    }
    // in offside area
    else if ( wm.self().pos().x > wm.offsideLineX() )
    {
        dash_power = ServerParam::i().maxDashPower();
        dlog.addText( Logger::TEAM,
                      __FILE__": in offside area. dash_power=%.1f",
                      dash_power );
    }
    else if ( wm.ball().pos().x > 25.0
              && wm.ball().pos().x > wm.self().pos().x + 10.0
              && self_min < opp_min - 6
              && mate_min < opp_min - 6 )
    {
        dash_power = bound( ServerParam::i().maxDashPower() * 0.1,
                            my_inc * 0.5,
                            ServerParam::i().maxDashPower() );
        dlog.addText( Logger::TEAM,
                      __FILE__": (get_normal_dash_power) opponent ball dash_power=%.1f",
                      dash_power );
    }
    // normal
    else
    {
        dash_power = std::min( my_inc * 1.7,
                               ServerParam::i().maxDashPower() );
        dlog.addText( Logger::TEAM,
                      __FILE__": (get_normal_dash_power) normal mode dash_power=%.1f",
                      dash_power );
    }

    return dash_power;
}
