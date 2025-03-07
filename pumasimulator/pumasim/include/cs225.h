/*
* File:   cs225.h
*
* This file contains constants and types that are common across the servo and
* ui processes.
*/

/*
* modification history
*----------------------
*
* 04/13/07 : Jinsung: Last updated
* 03/06/03 : Andres Loi: Final Version (RTLinux) 
* 12/25/02: Weyn Ong: Version for RTLinux.
* 03/28/98: K.C. Chang: created.
*/

#ifndef _cs225_h
#define _cs225_h
#include "PrVector3.h"


// Messages sent from the UI to the servo via the ServoAgent class

enum UiToServoMessageType {
  GET_JPOS,      // Get the joint position (arg: DestinationUi)
  GET_JVEL,      // Get the joint velocity (arg: DestinationUi)
  GET_TORQ,      // Get the torque (arg: DestinationUi)
  GET_EMASS,     // Get the effective mass and its major directions (arg: DestinationUi)
  GET_ACCLIMITS, // Get the acceleration Limits (arg: DestinationUi)
  GET_SFORCELIMITS, // Get the static force Limits (arg: DestinationUi)
  GET_IPOS,      // Get the operational-space position (arg: DestinationUi)
  GET_WFORCE,    // Get the force-sensor measurement (arg: DestinationUi)
  GET_CURTIME,   // Get the current time (arg: DestinationUi)

  GET_KJ,        // Get the current potential gains (arg: DestinationUi)
  GET_KP,        // Get the current KP values (arg: DestinationUi)
  GET_KV,        // Get the current KV values (arg: DestinationUi)
  GET_CMODE,     // Get the current control mode (arg: DestinationUi)
  GET_DEBUG,     // Get user-defined debug info (arg: DestinationUi)

  START_GATHER,          // Start gathering MATLAB data (arg: filename)
  STOP_GATHER,           // Stop gathering MATLAB data (no args)
  SET_CONTACT_POINT,     // Set the contact point for mouse-dragging (args:
  // joint #, contact pt in base coords, joint pos)
  APPLY_CONTACT_FORCE,   // Apply contact force (args: dest pt in base coords)
  REMOVE_CONTACT_FORCE,  // Remove contact force (no args)
  GRIPPER,               // Send command to gripper (arg: DAC value to apply)
  CONTROL_MODE,          // Set the control mode (arg: ControlMode, followed
  // by mode-specific args)
  SET_CONSTANT,          // Set a constant (arg: ConstantType, folled by
  // constant-specific data)
  RESET,                 // Reset the encoder
  BREAK                  // Exit the program
};


// Messages sent from the servo to the UI via the UiAgent class

enum ServoToUiMessageType {
  JPOS_DATA,         // Response to GET_JPOS (args: joint position)
  JVEL_DATA,         // Response to GET_JVEL (args: joint velocity)
  TORQ_DATA,         // Response to GET_TORQ (args: current torque)
  EMASS_DATA,        // Response to GET_EMASS (args: effective mass at the end effector)
  ACCLIMITS_DATA,    // Response to GET_ACCLIMITS (args: acceleration limits at the end effector)
  SFORCELIMITS_DATA,    // Response to GET_SFORCELIMITS (args: static force limits at the end effector)
  IPOS_DATA,         // Response to GET_IPOS (args: op-space coords)
  WFORCE_DATA,       // Response to GET_WFORCE (args: force-sensor data)
  CURTIME_DATA,      // Response to GET_CURTIME (arg: current time)
  START_GATHER_DATA, // Response to START_GATHER (arg: filename)
  STOP_GATHER_DATA,  // Response to STOP_GATHER (no args)
  GATHER_DATA,       // Matlab data (args: data from gatherData variable)
  STRING_DATA,       // String generated by ui->Display() (arg: string)
  GAIN_DATA,         // New values of control gains (args: mode, kp, kv)
  CONST_DATA         // New values of constants (args: big list of constants)
};


// Used to control whether the data that is returned from the robot is
// displayed in the user console or GUI.  Sent as an int after
// UiToServoMessageType.

enum DestinationUi {
  CONSOLE=0,             // Display the data on the console
  GUI=1,                 // Return the data to the remote GUI
  LOCAL_GATHER_THREAD=2  // Return the data to the local UI
};


// Used in the CONTROL_MODE command to determine which control mode to
// enter.
enum ControlMode {
  NO_CONTROL,
  FLOATMODE,
  NJHOLD,
  JHOLD,
  NHOLD,
  HOLD,
  OPEN,
  NJMOVE,
  JMOVE,
  NJGOTO,
  JGOTO,
  NJTRACK,
  JTRACK,
  NXTRACK,
  XTRACK,
  NGOTO,
  GOTO,
  NTRACK,
  TRACK,
  PFMOVE,
  LINE,
  PROJ1,
  PROJ2,
  PROJ3,

  LAST_CONTROL_MODE = PROJ3
};

static const int NUM_CONTROL_MODES = LAST_CONTROL_MODE + 1;


// Used in the SET_CONSTANT command to determine which constant is
// being set.

enum ConstantType {
  SET_ROBOT_TYPE,
  SET_VMAX,
  SET_AMAX,
  SET_WMAX,
  SET_RHO0,
  SET_ETA,
  SET_SBOUND,
  SET_SPRINGK,
  SET_SIMSPEED,
  SET_JLIMIT,
  SET_FRICTION,
  SET_TORQLIM,
  SET_QMIN,
  SET_QMAX,
  SET_DQMAX,
  SET_DDQMAX,
  SET_Q0,
  SET_KJ,
  SET_OBSTACLE,
  DEL_OBSTACLE,
  SET_LINE,
  DEL_LINE,
  SET_PLANE,
  DEL_PLANE,
  SET_KP,
  SET_KV,
  SET_EMASS_POS
};


// Values of the SET_ROBOT_TYPE constant

enum RobotType {
  PUMA_1DOF,      // Puma in which only joint q2 moves
  PUMA_3DOF,      // Puma in which joints q1, q4, and q6 are frozen
  PUMA_4DOF,      // Puma in which joints q4 and q6 are frozen
  PUMA_6DOF_Q,    // 6-DOF PUMA, using quaternions to represent rotation
  PUMA_6DOF_EA,   // 6-DOF PUMA, using Euler angles to represent rotation
  PUMA_6DOF_EAY,  // 6-DOF PUMA, using Euler angles (y-convention)
  PUMA_6DOF_AA    // 6-DOF PUMA, using axis-angles to represent rotation
};
static const RobotType DEFAULT_ROBOT_TYPE = PUMA_6DOF_Q;


// MesgQueue ids used to transfer data from the RT modules to the User
// Interface and vice versa

enum Fifos { 
  RT_TO_UI_FIFO,
  UI_TO_RT_FIFO
};


// Sphere: This struct defines a spherical obstacle, used by the
// PFMOVE control mode.

struct Sphere {
  int id;           // Unique ID of the sphere
  PrVector3 coord;  // coord[0], coord[1], and coord[2] are the x,y,z coords
  Float radius;     // Radius of the sphere
};


// Line:  This class defines a line, used by the LINE control mode.
//
// In the GUI, it's easiest to create the line by specifying two
// points.  However, when you use the line, it's easier to view the
// line as a point and a unit vector.  This class allows you to use
// either notation.

class Line {
public:
  Line() : m_enabled( false ), m_unitVec( 1, 0, 0 ) {}

  // These methods allow you to treat the line as a point and a unit
  // vector.  line.center() is the point on the line nearest the
  // origin, and line.unitVec() is a unit vector that points along
  // the line.  (Note: A PrVector3 is a 3x1 vector.  You can get the
  // elements of a PrVector3 just like an array.  For example, the
  // first element -- the X coordinate -- of line.center() is
  // line.center()[0].)

  const PrVector3& center()      const { return m_center;    }
  const PrVector3& unitVec()     const { return m_unitVec;   }

  // This method allows you to treat the line as a line between two
  // points.  line.point(0) and line.point(1) are the two points you
  // specified in the GUI.

  const PrVector3& point(int ii) const { return m_point[ii]; }

  // These methods tell you whether the line is enabled or disabled

  bool enabled()     const { return m_enabled;   }
  bool disabled()    const { return !m_enabled;  }

  // These methods allow you to change the line.  They are normally
  // only called via the GUI.

  void setEnabled()                    { m_enabled = true;   }
  void setDisabled()                   { m_enabled = false;  }
  void set( Float x1, Float y1, Float z1,
    Float x2, Float y2, Float z2, bool enabled = true );

private:
  bool      m_enabled;    // Tells whether the line is enabled
  PrVector3 m_point[2];   // The line extends from m_point[0] to m_point[1]
  PrVector3 m_center;     // The point in the line nearest the origin
  PrVector3 m_unitVec;    // The unit vector that points along the line
};

// Line::set() lets you set the entire line at once.  x1-z1 are the
// coordinates of the 1st point, x2-z2 are the coordinates of the 2nd
// point, and enabled tells whether the line is enabled.  It was
// easier to define Line::set() as an inline function than it was to
// create a cs225.cpp file.  :-)

inline void Line::set(  Float x1, Float y1, Float z1,
                      Float x2, Float y2, Float z2, bool enabled )
{
  m_enabled = enabled;
  m_point[0].values( x1, y1, z1 );
  m_point[1].values( x2, y2, z2 );

  if( m_point[0] == m_point[1] )
  {
    m_unitVec.values( 1, 0, 0 );
    m_center.values( 0, y1, z1 );
  }
  else
  {
    m_unitVec = m_point[1] - m_point[0];
    m_unitVec.normalize();
    m_center = m_point[0] - m_unitVec * m_point[0].dot( m_unitVec );
  }
}


class TexturedPlane {
private:
  bool      m_enabled;    // Tells whether the plane is enabled
  PrVector3 m_center;	  // COM of the plane in the world frame
  PrVector3 m_euler;      // orientation of the plane in euler angles
public:
  TexturedPlane() : m_enabled( false ), m_center( 0, -1, 0 ), m_euler( 0, 0, -M_PI/2.0 ) {}

  const PrVector3& center()      const { return m_center;    }
  const PrVector3& euler()     const { return m_euler;   }

  bool enabled()     const { return m_enabled;   }
  bool disabled()    const { return !m_enabled;  }

  // These methods allow you to change the plane.  They are normally
  // only called via the GUI.

  void setEnabled()                    { m_enabled = true;   }
  void setDisabled()                   { m_enabled = false;  }
  void set( Float x, Float y, Float z,
    Float roll, Float pitch, Float yaw, bool enabled = true );
};

inline void TexturedPlane::set(  Float x, Float y, Float z,
                      Float roll, Float pitch, Float yaw, bool enabled )
{
  m_enabled = enabled;
  m_center.values( x, y, z );
  m_euler.values( roll, pitch, yaw );
}

#endif /* cs225.h */
