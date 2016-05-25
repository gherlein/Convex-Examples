/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*                        Copyright (c) James Pearman                          */
/*                                   2013                                      */
/*                            All Rights Reserved                              */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    Module:     vexdefault.c                                                 */
/*    Author:     James Pearman                                                */
/*    Created:    8 July 2013                                                  */
/*                                                                             */
/*    Revisions:                                                               */
/*                V1.00  04 July 2013 - Initial release                        */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
/*                                                                             */
/*    The author is supplying this software for use with the VEX cortex        */
/*    control system. This file can be freely distributed and teams are        */
/*    authorized to freely use this program , however, it is requested that    */
/*    improvements or additions be shared with the Vex community via the vex   */
/*    forum.  Please acknowledge the work of the authors when appropriate.     */
/*    Thanks.                                                                  */
/*                                                                             */
/*    Licensed under the Apache License, Version 2.0 (the "License");          */
/*    you may not use this file except in compliance with the License.         */
/*    You may obtain a copy of the License at                                  */
/*                                                                             */
/*      http://www.apache.org/licenses/LICENSE-2.0                             */
/*                                                                             */
/*    Unless required by applicable law or agreed to in writing, software      */
/*    distributed under the License is distributed on an "AS IS" BASIS,        */
/*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. */
/*    See the License for the specific language governing permissions and      */
/*    limitations under the License.                                           */
/*                                                                             */
/*    The author can be contacted on the vex forums as jpearman                */
/*    or electronic mail using jbpearman_at_mac_dot_com                        */
/*    Mentor for team 8888 RoboLancers, Pasadena CA.                           */
/*                                                                             */
/*-----------------------------------------------------------------------------*/
#include <stdlib.h>
#include <math.h>

#include "ch.h"         // needs for all ChibiOS programs
#include "hal.h"        // hardware abstraction layer header
#include "vex.h"        // vex library header


#define DEBUG_CONSOLE_PRINT
#define DEBUG_CONSOLE_COUNTER 100
#ifdef DEBUG_CONSOLE_PRINT
  static int count=0;
#endif


#define DEBOUNCE_VALUE 25


// Digi IO configuration
static  vexDigiCfg  dConfig[kVexDigital_Num] = {
    { kVexDigital_1,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_2,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_3,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_4,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_5,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_6,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_7,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_8,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_9,    kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_10,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_11,   kVexSensorDigitalInput,  kVexConfigInput,       0 },
    { kVexDigital_12,   kVexSensorDigitalInput,  kVexConfigInput,       0 }
};

static  vexMotorCfg mConfig[kVexMotorNum] = {
    { kVexMotor_1,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_2,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_3,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },

    { kVexMotor_4,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_5,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_6,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_7,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_8,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_9,      kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 },
    { kVexMotor_10,     kVexMotor393T,          kVexMotorNormal,       kVexSensorNone,        0 }
};

/*-----------------------------------------------------------------------------*/
/** @cond      name the motor ports                                            */
/*-----------------------------------------------------------------------------*/
#define LeftFront       kVexMotor_2
#define LeftBack        kVexMotor_3
#define RightFront      kVexMotor_4
#define RightBack       kVexMotor_5
/** @endcond */


/*-----------------------------------------------------------------------------*/
/** @brief      Cortex default code initialization                             */
/*-----------------------------------------------------------------------------*/
/** @details
 *  Setup motors and digital ports
 */

 void
 vexCortexDefaultSetup(void)
 {
    vexDigitalConfigure( dConfig, DIG_CONFIG_SIZE( dConfig ) );
    vexMotorConfigure( mConfig, MOT_CONFIG_SIZE( mConfig ) );
}


void
getJoystickVector(double* r, double* theta)
{
  int16_t joy_x  = 0;
  int16_t joy_y = 0;

  joy_y=vexControllerGet( Ch3 ); 
  joy_x=vexControllerGet( Ch4 ); 

  if(joy_x<DEBOUNCE_VALUE) joy_x=0;    
  if(joy_y<DEBOUNCE_VALUE) joy_y=0;    

  if(joy_x==0 && joy_x==0)
  {
    return;
  }

  double s = sqrt((joy_y*joy_y)+(joy_x*joy_x));
  double a = atan2(joy_y,joy_x);

  *r=s;
  *theta=a;

#ifdef DEBUG_CONSOLE_PRINT
  count++;
  if(count%DEBUG_CONSOLE_COUNTER==0)
  {
    vex_chprintf((vexStream *)SD_CONSOLE, "x: %d y: %d s: %f a: %f\n",joy_x,joy_y,s,a);        
    count=0;
  }
#endif


  return;
}



void
vexCortexDefaultDriver(void)
{

  double r=0;
  double theta=0;
  double fl, fr, bl, br;

  vexMotorDirectionSet( LeftFront,  kVexMotorNormal );
  vexMotorDirectionSet( LeftBack,  kVexMotorNormal );
  vexMotorDirectionSet( RightFront,  kVexMotorNormal );
  vexMotorDirectionSet( RightBack,  kVexMotorNormal );
  vexMotorSet( LeftFront,   0  );
  vexMotorSet( LeftBack,    0  );
  vexMotorSet( RightFront,  0  );
  vexMotorSet( RightBack,   0  );

  
  while( !chThdShouldTerminate() )
  {


#ifdef RUN_MOTORS_AVG
		// Controller 1/2, Stick L/R, Axis X/Y
        int C1LX = GetJoystickAnalog(1, 4);
        int C1LY = GetJoystickAnalog(1, 3);
        int C1RX = GetJoystickAnalog(1, 1);
    
        // Y component, X component, Rotation
        SetMotor(LeftFront, -C1LX - C1RX); // Front
        SetMotor(LeftBack, -C1LY - C1RX); // Left
        SetMotor(RightFront,C1LY - C1RX); // Right
        SetMotor(RightBack,  C1LX - C1RX); // Back

        // Motor values can only be updated every 20ms
        Wait(20);

#endif    

#ifdef RUN_MOTORS_TRIG
    getJoystickVector(&r, &theta);

    fl = -127 * cos(M_PI/4-theta);
    fr = 127 * cos(M_PI/4+theta);
    bl = -127 * cos(M_PI/4+theta);
    br = -127 * cos(M_PI/4-theta);

    vexMotorSet( LeftFront,   (int)fl  );
    vexMotorSet( LeftBack,    (int)bl  );
    vexMotorSet( RightFront,  (int)fr  );
    vexMotorSet( RightBack,   (int)br  );
#endif

    // small delay
    vexSleep(10);
}
}
