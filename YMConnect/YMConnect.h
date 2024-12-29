//Copyright 2024 Yaskawa America Inc.
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http ://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#pragma once

#ifdef YMCONNECT_EXPORTS
#define YMCONNECT_API __declspec(dllexport)
#elif __linux__
#define YMCONNECT_API
#include <math.h>//this is where std::double_t is
#include <float.h>//this is where std::float_t is
#include <ctime>
#include <cstdint>
#include <bitset>
#else
#define YMCONNECT_API __declspec(dllimport)
#endif
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <optional>
#include <bitset>


#define YMConnect_Header_Version "1.1.0"

//============================================================================================================================================================================

using CHAR8 = char;
using UCHAR = unsigned char;

using UINT8 = std::uint8_t;
using UINT16 = std::uint16_t;
using UINT32 = std::uint32_t;
using UINT64 = std::uint64_t;

using INT8 = std::int8_t;
using INT16 = std::int16_t;
using INT32 = std::int32_t;
using INT64 = std::int64_t;

using DOUBLE64 = std::double_t;
using FLOAT32 = std::float_t;


//============================================================================================================================================================================

const INT32 max_alarms = 4;
const INT32 alarm_history_size = 100;
const INT32 max_supported_axis = 8;
const INT32 OK = 0x00;
using CoordinateArray = std::array<DOUBLE64, max_supported_axis>;
using AxisConfigurationData = std::array<CHAR8, max_supported_axis>;
using RegisterData = UINT16;
using IOByteData = std::bitset<8>;
using IOWordData = std::bitset<16>;

//============================================================================================================================================================================

#pragma region Enums

/// <summary>
/// Selection of control groups. Encompasses robots, bases and stations.
/// </summary>
enum class ControlGroupId 
{
	R1 = 1, R2 = 2, R3 = 3, R4 = 4, R5 = 5, R6 = 6, R7 = 7, R8 = 8,
	B1 = 11, B2 = 12, B3 = 13, B4 = 14, B5 = 15, B6 = 16, B7 = 17, B8 = 18,
	S1 = 21, S2 = 22, S3 = 23, S4 = 24, S5 = 25, S6 = 26, S7 = 27, S8 = 28, 
	S9 = 29, S10 = 30, S11 = 31, S12 = 32, S13 = 33, S14 = 34, S15 = 35, S16 = 36, 
	S17 = 37, S18 = 38, S19 = 39, S20 = 40, S21 = 41, S22 = 42, S23 = 43, S24 = 44
};

/// <summary>
/// The type of information to be requested from the controller by the GetSystemInfo function.
/// This includes robots, stations and application number.
/// </summary>
enum class SystemInfoId 
{
	R1 = 11, R2 = 12, R3 = 13, R4 = 14, R5 = 15, R6 = 16, R7 = 17, R8 = 18, // Robot number
	S1 = 21, S2 = 22, S3 = 23, S4 = 24, S5 = 25, S6 = 26, S7 = 27, S8 = 28, 
	S9 = 29, S10 = 30, S11 = 31, S12 = 32, S13 = 33, S14 = 34, S15 = 35, S16 = 36, 
	S17 = 37, S18 = 38, S19 = 39, S20 = 40, S21 = 41, S22 = 42, S23 = 43, S24 = 44, // Station number
	A1 = 101, A2 = 102, A3 = 103, A4 = 104, A5 = 105, A6 = 106, A7 = 107, A8 = 108 //Application number.
};

/// <summary>
/// Used to specify the type of system parameter to be retrieved by the GetSystemParameter function.
/// </summary>
enum class SystemParameterType
{
	S1CG = 0,      /* S1CxG requires group number.*/
	S2C = 1,      /* S2C   */
	S3C = 2,      /* S3C   */
	S4C = 3,      /* S4C   */
	RS = 4,      /* RS    */
	AP = 5,      /* AxP   requires group number*/
	SE = 6,      /* SxE   requires group number*/
};

/// <summary>
/// Type of alarm to retrieve. Used by the GetActiveAlarms and GetAlarmHistory functions.
/// </summary>
enum class AlarmCategory { Major = 0, Minor = 1000, UserSystem = 2000, User = 3000, Offline = 4000 };

/// <summary>
/// Activate or deactivate Hold, Servo.
/// </summary>
enum class SignalStatus : INT32 { ON = 1, OFF = 2 };

/// <summary>
/// Category of I/O signal. All signal categories are readable. Writing is limited to NetworkInput. 
/// Additionally, GeneralOutput can be written on YRC1000 or newer controllers.
/// </summary>
enum class IOType 
{
	GeneralInput, GeneralOutput, ExternalInput, NetworkInput, ExternalOutput, NetworkOutput,
	SpecificInput, SpecificOutput, InterfacePanelInput, AuxiliaryRelay, RobotControlStatus, PsuedoInput
};

/// <summary>
/// Specifies the task to reference when getting the executing job information and Job stack.
/// </summary>
enum class InformTaskNumber {
	Master, Subtask1, Subtask2, Subtask3, Subtask4, Subtask5, Subtask6,
	Subtask7, Subtask8, Subtask9, Subtask10, Subtask11, Subtask12, Subtask13, Subtask14, Subtask15
};

enum class CoordinateType : INT32 { Pulse = 0, BaseCoordinate = 16, RobotCoordinate = 17, ToolCoordinate = 18, UserCoordinate = 19, MasterTool = 20, Undefined = 55, JointDegrees = 56 };

enum class MoveInterpolationType { NoneSelected, MoveJoint, MoveLinear, MoveCircular };

enum class CycleMode { Step = 0, Cycle, Automatic };

enum class FileType { Job_JBI, Data_DAT, Condition_CND, Parameter_PRM, System_SYS, Ladder_LST, Log_LOG };

/// <summary> The location of the B axis rotation when viewed from the right side of the robot. 
/// <para> Front: center of the B-axis is to the right of the S-axis rotation center. </para> 
/// Back: center of the B-axis is to the left of the S-axis rotation center. </summary>
enum class FrontOrBack { Front, Back };

/// <summary>
/// When viewed by the right side, the angle of the elbow (L and U axis). Upper is less than 180 degrees, lower is greater than 180 degrees.
/// </summary>
enum class UpperOrLower { Uppper, Lower };

/// <summary>
/// <para> Flip:  B axis is in positive direction (Theta B &gt; = 0 degrees). </para>
/// <para> NoFlip = B axis is in negative direction (Theta B &lt; 0 degrees). </para>
/// </summary>
enum class FlipOrNoFlip { Flip, NoFlip };

/// <summary>
/// Specify if an angle is less than or greater than 180 degrees.
/// </summary>
enum class AxisAngle { LessThan180, GreaterThanOrEqual180 };

/// <summary>
/// Type of time to request when calling GetOperatingTime.
/// </summary>
enum class TimeType
{
	ControllerOnTime = 1,
	ServoPowerOnTimeTotal = 10,
	ServoPowerOnTimeRobot = 11,
	ServoPowerOnTimeStation = 20,
	PlayBackTimeTotal = 110,
	PlayBackTimeRobot = 111,
	PlayBackTimeStation = 120,
	MovingTimeTotal = 210,
	MovingTimeRobot = 211,
	MovingTimeStation = 221,
	ApplicationOperationTime = 300

};

//Application ex. Arc Welding, Spot Welding, Painting, General Purpose.
//On standard pendant, assignments can be found from the main menu under
//[System Information]>[Controller Information] under the APPLICATION section.
enum class ApplicationNumber
{
	ApplicationOne = 1,
	ApplicationTwo,
	ApplicationThree,
	ApplicationFour,
	ApplicationFive,
	ApplicationSix,
	ApplicationSeven,
	ApplicationEight
};

namespace AxisIndex
{
	enum PulseAxis { S = 0, L, U, R, B, T, E, W };
	enum CartesianAxis { X = 0, Y, Z, Rx, Ry, Rz, Re, Rw };
};

/// <summary>
/// When converting between coordinate types using the KinematicsInterface,  specifies the conversion to use.
/// </summary>
enum class KinematicConversions
{
	JointAngleToCartesianPos,	// Convert Joint Angles(in degrees) To Cartesian Position. 
	PulseToJointAngle,	// Convert Pulse position To Joint Angles(in degrees). 
	JointAngleToPulse,	// Convert Joint Angles(in degrees) To Pulse. 
	PulseToCartesianPos,	// Convert Pulse position To Cartesian Position. 
	CartesianPosToJointAngle,
	CartesianPosToPulse
};

/// <summary>
/// Specifies how to solve inverse kinematics when converting from cartesian position. Used when calling ConvertPosition in the Kinematics interface.
/// </summary>
enum class KinematicType
{
	Default,// Calculate using parameter S2C430 value. 2:Delta, 1:Figure
	Delta,// Calculate by prevAngle. If this type is selected, prevAngle must be provided.
	Figure //Calculate by the figure set in the position to convert.
};

#pragma endregion

//=============================================================================================================================================================================

#pragma region Data Objects

/// <summary>
/// The StatusInfo class provides a numerical error code and a human readable error message.
/// </summary>
class StatusInfo
{
public:

	INT32 StatusCode{};// The error code returned from the function call. 0 indicates no error.
	std::string Message{};// The error message associated with the error code.

	constexpr bool IsOk() const { return StatusCode == OK; }
	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const StatusInfo& status);

	/// <summary>
	/// A convenience function to return the StatusCode and Message as a string.
	/// </summary>
	/// <returns>StatusInfo represented as a string.</returns>
	std::string ToString() const
	{
		return "Code (" + std::to_string(StatusCode) + "): " + Message;
	}
};

/// <summary>
/// <para> Representation of the robot's figure. Includes front/back, upper/lower, and flip/no flip in addition to the axis angles. </para>
/// Axis Angles are represented as either less than or equal to 180 degrees or greater than 180 degrees.
/// </summary>
struct Figure
{
	FrontOrBack frontOrBack{};
	UpperOrLower upperOrLower{};
	FlipOrNoFlip flipOrNoFlip{};
	std::array<AxisAngle, max_supported_axis> axisAngles{}; // An array of entries for each axis.

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const Figure& fig);

};

/// <summary>
/// Information about a position. Includes the coordinate type, figure, tool number, user coordinate number, and the position values of the axes.
/// </summary>
struct PositionData
{
	CoordinateType coordinateType{};
	Figure figure{};//Used to represent a robot configuration when the coordinate system is cartesian.
	UINT32 toolNumber{};//|0 if the coordinate type is anything other than ToolCoordinate.
	UINT32 userCoordinateNumber{};//Only used when coordinateType is UserCoordinate. Otherwise it is 0. Only used with robot position variables.
	CoordinateArray axisData{};//Pulse counts for coordinate type pulse, millimeters and joint angles otherwise.

	PositionData() = default;

	PositionData(CoordinateType coordType, const Figure& fig, UINT32 toolNum, UINT32 userCoordNumber, const CoordinateArray& coordinates) :
		coordinateType(coordType)
		, figure(fig)
		, toolNumber(toolNum)
		, userCoordinateNumber(userCoordNumber)
		, axisData(coordinates)
	{}

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const PositionData& pos);
};

/// <summary>
/// Type of position vector.
/// </summary>
struct XyzVector
{
	DOUBLE64	X{};
	DOUBLE64	Y{};
	DOUBLE64	Z{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const XyzVector& xyz);
};

/// <summary>
/// Representation of the pose in 3D space. Includes the position and orientation. Orientation is represented as ZYX-intrinsic (roll, pitch, yaw).
/// </summary>
struct EulerMatrix
{
	DOUBLE64 nx{};
	DOUBLE64 ny{};
	DOUBLE64 nz{};
	DOUBLE64 ox{};
	DOUBLE64 oy{};
	DOUBLE64 oz{};
	DOUBLE64 ax{};
	DOUBLE64 ay{};
	DOUBLE64 az{};
	DOUBLE64 px{};
	DOUBLE64 py{};
	DOUBLE64 pz{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const EulerMatrix& em);
};

/// <summary>
/// Servo error data. The difference between the command position and the feedback position of each axis.
/// </summary>
struct PositionErrorData
{
	std::array<INT32, max_supported_axis> axisData{};
	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const PositionErrorData& posErr);
};

/// <summary>
/// Torque data of a control group. Includes the control group ID and the axis torques. Expressed as a percentage.
/// </summary>
struct TorqueData
{
	ControlGroupId controlGroupId{ ControlGroupId::R1 };
	std::array<INT32, max_supported_axis> axisData{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const TorqueData& torque);
};

/// <summary>
/// Used in TimeData structure. Represents the elapsed time in seconds, minutes and hours.
/// </summary>
struct ElapsedTime
{
	UINT32 Seconds{};
	UINT32 Minutes{};
	UINT32 Hours{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const ElapsedTime& time);
};

/// <summary>
/// Time data. Includes the start time and elapsed. Since this structure is used in  GetOperatingTime, the elapsed time corresponds to the TimeType Selected.
/// </summary>
struct TimeData
{
	std::time_t startTime{};
	ElapsedTime elapsedTime{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const TimeData& time);
};

/// <summary>
/// The software version running on the controller. Also includes the model of the system
///  requested by ReadSystemInformation.
/// </summary>
struct SystemInfoData
{
	std::string softwareVersion{};
	std::string modelName{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const SystemInfoData& sysInfo);
};

/// <summary>
/// All of the information about the controller's state. Includes the running mode, control mode, and hold status.
/// </summary>
struct ControllerStateData
{
	enum class ControlMode { Teach, Play, Remote };
	CycleMode cycleMode;
	bool isRunning;
	ControlMode  controlMode;
	bool isInHold;
	bool isAlarming;
	bool isErroring;
	bool isServoOn;

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const ControllerStateData& state);
};

/// <summary>
/// The name, line, step number, and speed override of a job. Line corresponds to the line number of the job. Step number corresponds to the motion step in the job. 
/// SpeedOverride is expressed as a percentage. 100% is programmed speed. Ranges from 10% to 150%.
/// </summary>
struct JobData
{
	std::string name;
	UINT32 line;
	UINT32 stepNumber;
	DOUBLE64 speedOverride;

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const JobData& job);
};

/// <summary>
/// The code, subcode, alarm type, time, and name of an alarm.
/// </summary>
struct AlarmData
{
	UINT32 code;
	UINT32 subcode;
	std::string time;
	std::string name;

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const AlarmData& alarm);
};

/// <summary>
/// A structure containing all of the active alarms on the controller. There can be four alarms at a time.
/// </summary>
struct ActiveAlarms
{
	std::array<AlarmData, max_alarms> alarms;
	UINT32 numberOfActiveAlarms;

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const ActiveAlarms& activeAlarms);
};

/// <summary>
/// The previous n alarms of the controller. n = numberOfAlarmsFetched. Also includes any active alarms.
/// </summary>
struct AlarmHistory
{
	std::array<AlarmData, alarm_history_size> alarm{};
	UINT32 numberOfAlarmsFetched{};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const AlarmHistory& alarmHistory);
};

#pragma region Variable Data Objects
/// <summary>
/// Byte (B) variable data. Includes the value and the variable index.
/// </summary>
struct ByteVariableData
{
	UINT8 value{};
	UINT16 variableIndex{};

	ByteVariableData() = default;

	ByteVariableData(UINT8 value, UINT16 variableIndex) : 
		value(value), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const ByteVariableData& byteVariableData);
};

/// <summary>
/// Integer (I) variable data. Includes the value and the variable index.
/// </summary>
struct IntegerVariableData
{
	INT16 value{};
	UINT16 variableIndex{};

	IntegerVariableData() = default;

	IntegerVariableData(INT16 value, UINT16 variableIndex) :
		value(value), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const IntegerVariableData& integerVariableData);
};

/// <summary>
/// Double integer (D) variable data. Includes the value and the variable index.
/// </summary>
struct DoubleIntVariableData
{
	INT32 value{};
	UINT16 variableIndex{};

	DoubleIntVariableData() = default;

	DoubleIntVariableData(INT32 value, UINT16 variableIndex) :
		value(value), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const DoubleIntVariableData& doubleIntVariableData);
};

/// <summary>
/// Real variable (R) variable data. Includes the value and the variable index.
/// </summary>
struct RealVariableData
{
	FLOAT32 value{};
	UINT16 variableIndex{};
	
	RealVariableData() = default;

	RealVariableData(FLOAT32 value, UINT16 variableIndex) :
		value(value), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const RealVariableData& realVariableData);
};

/// <summary>
/// String variable (S) variable data. Includes the value and the variable index. Max length is 32 characters.
/// </summary>
struct StringVariableData
{
	std::string stringVariableData{};
	UINT16 variableIndex{};
	
	StringVariableData() = default;

	StringVariableData(const std::string& stringVariableData, UINT16 variableIndex) :
		stringVariableData(stringVariableData), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const StringVariableData& stringVariableData);
};

/// <summary>
/// Robot position variable (P) data. Includes the position data and the variable index.
/// </summary>
struct RobotPositionVariableData
{
	PositionData positionData{};
	UINT16 variableIndex{};

	RobotPositionVariableData() = default;

	RobotPositionVariableData(const PositionData& positionData, UINT16 variableIndex) :
		positionData(positionData), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const RobotPositionVariableData& robotPositionVariableData);
};

/// <summary>
/// Base axis position variable (P) data. Includes the position data and the variable index. If the coordinate type is pulse, the pulse counts will be in X.
/// </summary>
struct BaseAxisPositionVariableData
{
	PositionData positionData{};
	UINT16 variableIndex{};

	BaseAxisPositionVariableData() = default;

	BaseAxisPositionVariableData(const PositionData& positionData, UINT16 variableIndex) :
		positionData(positionData), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const BaseAxisPositionVariableData& robotPositionVariableData);
};

/// <summary>
/// Station position variable (P) data. Includes the position data and the variable index.
/// </summary>
struct StationPositionVariableData
{
	PositionData positionData{};
	UINT16 variableIndex{};

	StationPositionVariableData() = default;

	StationPositionVariableData(const PositionData& positionData, UINT16 variableIndex) :
		positionData(positionData), variableIndex(variableIndex) {};

	YMCONNECT_API friend std::ostream& operator<<(std::ostream& os, const StationPositionVariableData& stationPositionVariableData);
};
#pragma endregion

/// <summary>
/// Contains the acceleration and deceleration ratios for a motion. These ratios reduce the amount of acceleration and/or deceleration that occurs during a motion.
/// For example, if the acceleration ratio is set to 50%, the robot will accelerate at half of the programmed acceleration rate.
/// If the deceleration ratio is set to 50%, the robot will decelerate at half of the programmed deceleration rate.
/// </summary>
struct MotionAccelDecel
{
	//Will change the acceleration ratio of subsequent motions until changed again. Valid range is 20.00%-100.00%. 
	DOUBLE64 accelRatio{ DBL_MAX };
	//Will change the deceleration ratio of subsequent motions until changed again. Valid range is 20.0%-100.00%
	DOUBLE64 decelRatio{ DBL_MAX }; 
};

/// <summary>
/// The base struct for the Motion targets.
/// </summary>
struct Motion
{
	ControlGroupId groupId{};
	DOUBLE64 speed{}; //Speed of the motion.  This value is a percentage (0.00 - 100.00) for JointMotion. For LinearMotion and CircularMotion, the value is in mm/sec (0.0 - 1500.0)
	MotionAccelDecel attributes{}; //The acceleration and deceleration ratios for the motion.
	MoveInterpolationType interpolationType{ MoveInterpolationType::NoneSelected }; //The interpolation type of the motion. Note that changing this instead of using the proper derived class can cause undefined behavior.
	PositionData position{}; //The position data of the motion.
	
	Motion() = default;

	Motion(ControlGroupId groupId, const PositionData& destinationCoords, DOUBLE64 speed, const MotionAccelDecel& attributes = MotionAccelDecel())
		: groupId(groupId),
		speed(speed),
		attributes(attributes),
		position(destinationCoords)
	{}
};

struct LinearMotion : Motion
{
	LinearMotion() = default;
	/// <summary>
	/// Constructor for a linear motion target.
	/// </summary>
	/// <param name="groupId">ControlGroupId for the motion.</param>
	/// <param name="destinationCoords">Data for the target position.</param>
	/// <param name="speed">Speed for this motion target.</param>
	/// <param name="attributes">Optional Motion attributes.</param>
	LinearMotion(ControlGroupId groupId, const PositionData& destinationCoords, DOUBLE64 speed, const MotionAccelDecel& attributes = MotionAccelDecel())
		: Motion(groupId, destinationCoords, speed, attributes)
	{
		interpolationType = MoveInterpolationType::MoveLinear;
	}
};

/// <summary>
/// Use this struct to create a joint motion target.
/// </summary>
struct JointMotion : Motion
{

	JointMotion() = default;

	/// <summary>
	/// Constructor for a joint motion target.
	/// </summary>
	/// <param name="groupId">ControlGroupId for the motion.</param>
	/// <param name="destinationCoords">Data for the target position</param>
	/// <param name="speed">Speed for this motion target.</param>
	/// <param name="attributes">Optional Motion attributes.</param>
	JointMotion(ControlGroupId groupId, const PositionData& destinationCoords, DOUBLE64 speed, const MotionAccelDecel& attributes = MotionAccelDecel())
		: Motion(groupId, destinationCoords, speed, attributes)
	{
		interpolationType = MoveInterpolationType::MoveJoint;
	}
};

struct CircularMotion : Motion
{
	CoordinateArray auxCoords{}; // Passing point.

	CircularMotion() = default;

	/// <summary>
	/// Constructor for a circular motion target.
	/// </summary>
	/// <param name="groupId">ControlGroupId for the motion.</param>
	/// <param name="destinationCoords">Data for the target position.</param>
	/// <param name="auxCoords">Pass in pulse counts for coordinate type pulse, millimeters and joint angles otherwise. Used as a passing point.
	/// e.g if you want to move from point A to point C, but you want to pass through point B, then point B would be the auxCoords.
	/// </param>
	/// <param name="speed"></param>
	/// <param name="attributes"></param>
	CircularMotion(ControlGroupId groupId, const PositionData& destinationCoords, const CoordinateArray& auxCoords, DOUBLE64 speed, const MotionAccelDecel& attributes = MotionAccelDecel())
		: Motion(groupId, destinationCoords, speed, attributes),
		auxCoords(auxCoords)
	{
		interpolationType = MoveInterpolationType::MoveCircular;
	}
};

#pragma endregion

//===========================================================================================================================================================================

#pragma region Interfaces

/// <summary>
/// The main interface for fault and error management.
/// </summary>
class FaultInterface
{

public:
	virtual ~FaultInterface() = default;
	/// <summary>
	/// Retrieves the current fault status of the robot.
	/// </summary>
	/// <param name="activeAlarmsData">OUT Current active alarms.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo GetActiveAlarms(ActiveAlarms& activeAlarmsData) = 0;

	/// <summary>
	/// Retrieves the number of previous alarms specified by the quantity parameter.
	/// </summary>
	/// <param name="category">IN Requested category of alarm.</param>
	/// <param name="quantity">IN Requested number of alarms to retrieve. Maximum is 100.</param>
	/// <param name="alarmHistoryData">OUT Alarm history. Number of alarms coorespond to quantity.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo GetAlarmHistory(AlarmCategory category, UINT32 quantity, AlarmHistory& alarmHistoryData) = 0;

	/// <summary>
	/// Clear all errors and alarms. Please note that this will not clear Major alarms.
	/// </summary>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ClearAllFaults() = 0;
};

class ControlGroupInterface
{
public:
	virtual ~ControlGroupInterface() = default;
	/// <summary>
	/// Retrieves the current position data for the specified control group. If using a controller generation before YRC1000, the only allowed coordinate type will be pulse and base.
	/// In addition, the base position returned will be in relation to the active tool.
	/// </summary>
	/// <param name="controlGroupId">IN Control group ID for the Position Data.</param>
	/// <param name="coordinateType">IN Coordinate type of the Position Data requested.</param>
	/// <param name="userFrameNumber">IN User frame number of the Position Data requested. Set to 0 if coordinateType is anything but UserCoordinate.</param>
	/// <param name="toolNumber">IN Tool number of the Position Data requested.</param>
	/// <param name="robotPositionData">OUT Position data of the control group.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadPositionData(ControlGroupId controlGroupId, CoordinateType coordinateType, UINT8 userFrameNumber, UINT8 toolNumber,
		PositionData& robotPositionData) = 0;

	/// <summary>
	/// Retrieves the current axis configuration for the specified control group. Example: [S,L, U, R, B, T, E, W].
	/// </summary>
	/// <param name="controlGroupId">IN Control group for axis configuration.</param>
	/// <param name="axisConfigData">OUT Describes axis config. For example [S,L,U,R,B,T]. For an external axis or base it will retrieve the axis number.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadAxisConfiguration(ControlGroupId controlGroupId, AxisConfigurationData& axisConfigData) = 0;

	/// <summary>
	/// Robot servo error data.
	/// </summary>
	/// <param name="controlGroupId">IN Control group id to retrieve the position error data for.</param>
	/// <param name="positionErrorData">OUT Position error data returned from the controller according to the controlGroupId.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadPositionError(ControlGroupId controlGroupId, PositionErrorData& positionErrorData) = 0;

	/// <summary>
	/// Get torque data for the specified control group.
	/// </summary>
	/// <param name="controlGroupId">IN Control group id to retrieve torque data for.</param>
	/// <param name="torqueData">OUT Torque data for the control group specified. A percentage value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadTorqueData(ControlGroupId controlGroupId, TorqueData& torqueData) = 0;
};

class ByteVariableInterface
{
public:
	virtual ~ByteVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="byteVariableDataObject">OUT Data at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, ByteVariableData& byteVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="byteVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const ByteVariableData& byteVariableDataObject) = 0;
};

class IntegerVariableInterface
{
public:
	virtual ~IntegerVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="integerVariableDataObject">OUT Data at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, IntegerVariableData& integerVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="integerVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const IntegerVariableData& integerVariableDataObject) = 0;
};

class DoubleIntVariableInterface
{
public:
	virtual ~DoubleIntVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="doubleVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, DoubleIntVariableData& doubleVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="doubleVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const DoubleIntVariableData& doubleVariableDataObject) = 0;
};

class RealVariableInterface
{
public:
	virtual ~RealVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="realVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, RealVariableData& realVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="realVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const RealVariableData& realVariableDataObject) = 0;
};

class StringVariableInterface
{
public:
	virtual ~StringVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="stringVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, StringVariableData& stringVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// Max length is 32 characters.
	/// </summary>
	/// <param name="stringVariableDataObject">Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const StringVariableData& stringVariableDataObject) = 0;
};

class RobotPositionVariableInterface
{
public:
	virtual ~RobotPositionVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="robotPositionVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, RobotPositionVariableData& robotPositionVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="robotPositionVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const RobotPositionVariableData& robotPositionVariableDataObject) = 0;
};

class BaseAxisPositionVariableInterface
{
public:
	virtual ~BaseAxisPositionVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="basePositionVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, BaseAxisPositionVariableData& basePositionVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="basePositionVariableDataObject">IN Data to set.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const BaseAxisPositionVariableData& basePositionVariableDataObject) = 0;
};

class StationPositionVariableInterface
{
public:
	virtual ~StationPositionVariableInterface() = default;
	/// <summary>
	/// Get variable data at the specified variable index.
	/// </summary>
	/// <param name="variableIndex">IN Index that contains the variable data.</param>
	/// <param name="stationPositionVariableDataObject">OUT Data at the index. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Read(UINT16 variableIndex, StationPositionVariableData& stationPositionVariableDataObject) = 0;

	/// <summary>
	/// Set variable data at the specified variable index. System Parameter at RS7 may need to be set to 2 to allow writing outside of REMOTE mode.
	/// </summary>
	/// <param name="stationPositionVariableDataObject">IN Data to set at the index.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo Write(const StationPositionVariableData& stationPositionVariableDataObject) = 0;
};

class VariablesInterface
{
public:
	virtual ~VariablesInterface() = default;
	ByteVariableInterface* ByteVariable;
	IntegerVariableInterface* IntegerVariable;	
	DoubleIntVariableInterface* DoubleIntVariable;
	RealVariableInterface* RealVariable;
	StringVariableInterface* StringVariable;
	RobotPositionVariableInterface* RobotPositionVariable;
	BaseAxisPositionVariableInterface* BasePositionVariable;
	StationPositionVariableInterface* StationPositionVariable;
};

class ControllerStateInterface
{
public:
	virtual ~ControllerStateInterface() = default;
	/// <summary>
	/// Get the current state of the controller. See the ControllerStateData structure for details. This includes the cycle mode, if the controller is running, the control mode,
	/// if it is in hold, alarming or erroring, and the servo state.
	/// </summary>
	/// <param name="statusDataObject">OUT The object containing data about the state of the controller. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadState(ControllerStateData& statusDataObject) = 0;

	/// <summary>
	/// Get System Information from the controller. 
	/// This includes the software version of the controller and the model of system requested. 
	/// Model name is truncated to 16 characters.
	/// If an application is selected as the system information, the "model name" will be the name of the
	/// application.
	/// Ex. R1 might return a value of 1-06VXH12-A0*(GP. 
	/// A1 might return a value of GENERAL.
	/// </summary>
	/// <param name="sysInfoId">IN The ID for which to retrieve the system information.</param>
	/// <param name="systemInfo">OUT The systems information corresponding to the ID.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadSystemInformation(SystemInfoId sysInfoId, SystemInfoData& systemInfo) = 0;

	/// <summary>
	/// Get times from the controller according to the specified time type.
	/// </summary>
	/// <param name="controlGroupId">IN The ID for which to retrieve the Operating Times. Specify for TimeTypes that are not totals or applications, otherwise pass R1.</param>
	/// <param name="timeType">IN The specific category of time data to retrieve.</param>
	/// <param name="timeData">OUT The structure containing the start and stop times of the time type.</param>
	/// <param name="appNumber">IN When ApplicationOperationTime is selected, this is where the application is selected. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadOperatingTimes(ControlGroupId controlGroupId, TimeType timeType, TimeData& timeData, ApplicationNumber appNumber = ApplicationNumber::ApplicationOne) = 0;

	/// <summary>
	/// Read out a system parameter from the controller. S1CxG, AxP and SxE parameters require a group to be specified. Use the other overload for these.
	/// </summary>
	/// <param name="parameterType">IN Type of the parameter requested.</param>
	/// <param name="parameterNumber">IN Index of the parameter.</param>
	/// <param name="parameterValue">OUT The retrieved parameter value from the controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadSystemParam(SystemParameterType parameterType, INT32 parameterNumber, INT32& parameterValue) = 0;

	/// <summary>
	/// Read out a system parameter from the controller with the ability to specify a group.
	/// </summary>
	/// <param name="parameterType">IN Type of the parameter requested.</param>
	/// <param name="parameterNumber">IN Index of the parameter.</param>
	/// <param name="parameterGroup">IN Specified group for the parameter. This is required for S1CxG, AxP and SxE parameters.</param>
	/// <param name="parameterValue">OUT The retrieved parameter value from the controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadSystemParam(SystemParameterType parameterType, INT32 parameterNumber, INT32 parameterGroup, INT32& parameterValue) = 0;
};

class JobInterface
{
public:
	virtual ~JobInterface() = default;
	/// <summary>
	/// Set the active job on the controller.
	/// </summary>
	/// <param name="jobName">IN Name to set as active. Not case sensitive. ".JBI" extension does not have to be included, but it can be if your program requires it.</param>
	/// <param name="lineNumber">IN Line number to set.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SetActiveJob(const std::string& jobName, UINT32 lineNumber) = 0;

	/// <summary>
	/// If the controller is currently executing a job, this function will return the name of the job.
	/// </summary>
	/// <param name="selection">IN Task number for which to get executing job.</param>
	/// <param name="job">OUT Job data for executing job.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo GetExecutingJobInformation(InformTaskNumber selection, JobData& job) = 0;

	/// <summary>
	/// Get the job stack from the controller.
	/// </summary>
	/// <param name="taskNumber">IN Task number of the job stack.</param>
	/// <param name="jobStack">OUT The job stack represented as a vector of strings. Top of stack is at index 0. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo GetJobStack(InformTaskNumber taskNumber, std::vector<std::string>& jobStack) = 0;
};

class FileInterface
{
public:
	virtual ~FileInterface() = default;
	/// <summary>
	/// Load a file to the controller from a string. Parameter RS7 must be set to 2 to allow this function outside of REMOTE mode. RS214 
	/// must be set to 2 to allow overwriting of existing files.
	/// </summary>
	/// <param name="fileName">IN The name of the file that you want to load.</param>
	/// <param name="contentsToLoad">IN The file contents.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo LoadToControllerFromString(const std::string& fileName, const std::string& contentsToLoad) = 0;

	/// <summary>
	/// Open a file from your system file path and load it onto the controller. Parameter RS7 must be set to 2 to allow writing outside of REMOTE mode.
	/// RS214 must be set to 2 to allow overwriting of existing files.
	/// </summary>
	/// <param name="filePath">IN The file path on your system to the file to load. </param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo LoadToControllerFromPath(const std::string& filePath) = 0;

	/// <summary>
	/// Save a file from the controller to your system file path. Parameter RS7 must be set to 2 to allow this function outside of REMOTE mode.
	/// </summary>
	/// <param name="fileName">IN File name to retrieve.</param>
	/// <param name="destinationFile">IN Name of the file to write to your system.</param>
	/// <param name="overwriteFlag">IN TRUE: Overwrite the file if it exists. FALSE: Return error if file already exists.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SaveFromControllerToFile(const std::string& fileName, const std::string& destinationFile, bool overwriteFlag = false) = 0;

	/// <summary>
	/// Save a file from the controller to a string. Parameter RS7 must be set to 2 to allow this function outside of REMOTE mode.
	/// </summary>
	/// <param name="fileName">IN File name to retrieve.</param>
	/// <param name="fileContents">OUT The file contents represented in a string.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SaveFromControllerToString(const std::string& fileName, std::string& fileContents) = 0;

	/// <summary>
	/// Delete a job file from the controller. Not case sensitive. ".JBI" extension does not have to be included, but it can be if your program requires it.
	/// </summary>
	/// <param name="fileName">IN Name of the file to be deleted.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo DeleteJobFile(const std::string& fileName) = 0;

	/// <summary>
	/// Get the amount of files with a specified file type. Parameter RS7 must be set to 2 to allow this function outside of REMOTE mode.
	/// </summary>
	/// <param name="fileType">IN File type to count.</param>
	/// <param name="fileCount">OUT Number of files with the specified type.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo GetFileCount(FileType fileType, INT32& fileCount) = 0;

	/// <summary>
	/// List all files of a specified file type. Parameter RS7 must be set to 2 to allow this function outside of REMOTE mode.
	/// </summary>
	/// <param name="fileType">IN file type for which to retrieve file names.</param>
	/// <param name="fileNames">OUT Names with specified file type.</param>
	/// <param name="sorted">IN TRUE: Sort alphabetically, FALSE: Dont sort.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ListFiles(FileType fileType, std::vector<std::string>& fileNames, bool sorted) = 0;
};

class IOInterface
{
public:
	virtual ~IOInterface() = default;
	/// <summary>
	/// Read a bit from the controller using the specified IO type, group, and bit position.
	/// </summary>
	/// <param name="type">IN IOType of bit to receive.</param>
	/// <param name="group">IN Group of bit to receive.</param>
	/// <param name="bitPosition">IN Position 0-7 to get. e.g for 0010010, bit position 5 would be 0.</param>
	/// <param name="ioBit">OUT bit value retrieved from controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadBit(IOType type, UINT16 group, UINT8 bitPosition, bool& ioBit) = 0;

	/// <summary>
	/// Read a bit from the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of bit to receive.<para>Example:</para>
	/// <para>Address 10010 will return the bit value of signal #10010 </para></param>
	/// <param name="ioBit">OUT Bit value retrieved from controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadBit(UINT32 address, bool& ioBit) = 0;

	/// <summary>
	/// Read a byte from the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of byte to receive.</param>
	/// <param name="group">IN Group of byte to receive.</param>
	/// <param name="io">OUT The corresponding byte value represented as a bitset.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadByte(IOType type, UINT16 group, IOByteData& io) = 0;

	/// <summary>
	/// Read a byte from the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of byte to receive. <para>Example:</para>
	/// <para>Address 10010 will return the byte value of signals #10010 - #10017</para></param>
	/// <param name="io">OUT The corresponding byte value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadByte(UINT32 address, IOByteData& io) = 0;

	/// <summary>
	/// Read a byte from the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of byte to receive.</param>
	/// <param name="group">IN Group of byte to receive.</param>
	/// <param name="io">OUT The corresponding byte value represented as a bitset.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadByte(IOType type, UINT16 group, UINT8& io) = 0;

	/// <summary>
	/// Read a byte from the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of byte to receive. <para>Example:</para>
	/// <para>Address 10010 will return the byte value of signals #10010 - #10017</para></param>
	/// <param name="io">OUT The corresponding byte value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadByte(UINT32 address, UINT8& io) = 0;

	/// <summary>
	/// Read a word from the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of word to receive.</param>
	/// <param name="group">IN Group of word to receive.</param>
	/// <param name="io">OUT The corresponding word value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadWord(IOType type, UINT16 group, IOWordData& io) = 0;

	/// <summary>
	/// Read a word from the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of word to receive.<para>Example:</para>
	/// <para>Address 10010 will return the word value of signals #10010 - #10027</para></param>
	/// <param name="io">OUT The corresponding word value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadWord(UINT32 address, IOWordData& io) = 0;

	/// <summary>
	/// Read a word from the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of word to receive.</param>
	/// <param name="group">IN Group of word to receive.</param>
	/// <param name="io">OUT The corresponding word value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadWord(IOType type, UINT16 group, UINT16& io) = 0;

	/// <summary>
	/// Read a word from the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of word to receive.<para>Example:</para>
	/// <para>Address 10010 will return the word value of signals #10010 - #10027</para></param>
	/// <param name="io">OUT The corresponding word value.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadWord(UINT32 address, UINT16& io) = 0;

	/// <summary>
	/// Write a bit to the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of bit to write.<para>Example:</para>
	/// <para>Address 10010 will write the bit value of signal #10010 </para></param>
	/// <param name="ioBit">IN The bit value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteBit(UINT32 address, bool ioBit) = 0;

	/// <summary>
	/// Write a bit to the controller using the specified IO type, group, and bit position.
	/// </summary>
	/// <param name="type">IN IOType of bit to write.</param>
	/// <param name="group">IN Group of bit to write.</param>
	/// <param name="bitPosition">IN Position 0-7 to write. e.g for 0010010, bit position 5 would be 0.</param>
	/// <param name="ioBit">IN bit value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteBit(IOType type, UINT16 group, UINT8 bitPosition, bool ioBit) = 0;

	/// <summary>
	/// Write a byte to the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of byte to write.</param>
	/// <param name="group">IN Group of byte to write.</param>
	/// <param name="io">IN Byte value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteByte(IOType type, UINT16 group, IOByteData& io) = 0;

	/// <summary>
	/// Write a byte to the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of byte to write.<para>Example:</para>
	/// <para>Address 10010 will write the byte value of signals #10010 - #10017</para></param>
	/// <param name="io">IN Byte value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteByte(UINT32 address, IOByteData& io) = 0;

	/// <summary>
	/// Write a byte to the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of byte to write.</param>
	/// <param name="group">IN Group of byte to write.</param>
	/// <param name="io">IN Byte value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteByte(IOType type, UINT16 group, UINT8& io) = 0;

	/// <summary>
	/// Write a byte to the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of byte to write.<para>Example:</para>
	/// <para>Address 10010 will write the byte value of signals #10010 - #10017</para></param>
	/// <param name="io">IN Byte value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteByte(UINT32 address, UINT8& io) = 0;

	/// <summary>
	/// Write a word to the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of word to write.</param>
	/// <param name="group">IN Group of word to write.</param>
	/// <param name="io">IN Word value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteWord(IOType type, UINT16 group, IOWordData& io) = 0;

	/// <summary>
	/// Write a word to the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of word to write.<para>Example:</para>
	/// <para>Address 10010 will write the word value of signals #10010 - #10027</para></param>
	/// <param name="io">IN Word value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteWord(UINT32 address, IOWordData& io) = 0;

	/// <summary>
	/// Write a word to the controller using the specified IO type and group.
	/// </summary>
	/// <param name="type">IN IOType of word to write.</param>
	/// <param name="group">IN Group of word to write.</param>
	/// <param name="io">IN Word value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteWord(IOType type, UINT16 group, UINT16& io) = 0;

	/// <summary>
	/// Write a word to the controller using the specified address.
	/// </summary>
	/// <param name="address">IN Address of word to write.<para>Example:</para>
	/// <para>Address 10010 will write the word value of signals #10010 - #10027</para></param>
	/// <param name="io">IN Word value to write.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteWord(UINT32 address, UINT16& io) = 0;

	/// <summary>
	/// Read from a register address on the controller.
	/// </summary>
	/// <param name="registerAddress"></param>
	/// <param name="registerData"></param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadRegister(UINT16 registerAddress, RegisterData& registerData) = 0;

	/// <summary>
	/// Write to a register address on the controller. Note that if the register value is controlled by the CIO ladder logic running on the controller, 
	/// the register value that you send will be overwritten by the application. This function will still return ok, but the register value will not be changed.
	/// </summary>
	/// <param name="registerAddress"></param>
	/// <param name="registerData"></param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo WriteRegister(UINT16 registerAddress, const RegisterData& registerData) = 0;

	/// <summary>
	/// Read from a register address on the controller.
	/// </summary>
	/// <param name="registerAddress"></param>
	/// <param name="registerData"></param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ReadRegister(UINT16 registerAddress, std::bitset<16>& registerData) = 0;

	/// <summary>	
	/// Write to a register address on the controller. Note that if the register value is controlled by the CIO ladder logic running on the controller, 
	/// the register value that you send will be overwritten by the application. This function will still return ok, but the register value will not be changed.
	/// </summary>
	/// <param name="registerAddress"></param>
	/// <param name="registerData"></param>
	/// <returns></returns>
	virtual StatusInfo WriteRegister(UINT16 registerAddress, const std::bitset<16>& registerData) = 0;


	/// <summary>
	/// Conversion of IOGroup to bit address. Useful for IO reading and writing. If a bit address is required, this function can be used to convert the IOType, Group and bit index to a bit address.
	/// </summary>
	/// <param name="type">IN IOType for conversion</param>
	/// <param name="group">IN Group for conversion.</param>
	/// <param name="bitIndex">IN Position 0-7 to write. e.g for 0010010, bit position 5 would be 0.</param>
	/// <param name="statusInfo">OUT Status info about whether or not the operation completed successfully.</param>
	/// <returns>The bit address corresponding to the IOGroup.</returns>
	virtual	UINT32 ConvertIOGroupToBitAddress(IOType type, UINT16 group, UINT8 bitIndex, StatusInfo& statusInfo) = 0;
};


class ControlCommandsInterface
{
public:
	virtual ~ControlCommandsInterface() = default;
	/// <summary>
	/// Set Servo On/Off. Must be in remote mode or play mode to turn on.
	/// </summary>
	/// <param name="signal">IN ON: Servo On, OFF: Servo Off.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SetServos(SignalStatus signal) = 0;

	/// <summary>
	/// Set Hold On/Off.
	/// </summary>
	/// <param name="signal">IN ON: Hold On, OFF: Hold Off.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SetHold(SignalStatus signal) = 0;


	/// <summary>
	/// Select the cycle mode.
	/// </summary>
	/// <param name="cycleSelect">IN Selection to set.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo SetCycleMode(CycleMode cycleSelect) = 0;

	/// <summary>
	/// Display a message string on the pendant.
	/// </summary>
	/// <param name="message">IN Message to display. Max size is 30 characters.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo DisplayStringToPendant(const std::string& message) = 0;

	/// <summary>
	/// Start the active job at the current job line.
	/// </summary>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo StartJob() = 0;
};

class MotionManagerInterface
{
public:
	virtual ~MotionManagerInterface() = default;
	/// <summary>
	/// Adds a Motion to the trajectory. Up to 4 groups can be added at a time. All of these groups will be in one motion. 
	/// NOTE: When using the motion manager, set parameter S2C430 to 1 and S2C425 to 0.
	/// </summary>
	/// <param name="firstGroupTarget">IN First control group.</param>
	/// <param name="secondGroupTarget">IN Optional: Second control group.</param>
	/// <param name="thirdGroupTarget">IN Optional: Third control group.</param>
	/// <param name="fourthGroupTarget">IN Optional: Fourth control group.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo AddPointToTrajectory(const Motion& firstGroupTarget, std::optional<Motion> secondGroupTarget = std::nullopt,
		std::optional<Motion> thirdGroupTarget = std::nullopt, std::optional<Motion> fourthGroupTarget = std::nullopt) = 0;

	/// <summary>
	/// Gets a percentage of the progress toward the next point in the trajectory. Range from 0-100 (0.00% to 100.00%).
	/// </summary>
	/// <param name="grp">IN Requested control group for which to get progress.</param>
	/// <param name="statusCode">OUT Status info about whether or not the operation completed successfully.</param>
	/// <returns>The progress toward the next point.</returns>
	virtual DOUBLE64 GetMotionTargetProgress(ControlGroupId grp, StatusInfo& statusCode) = 0;

	/// <summary>
	/// Start the motion at the first point in the trajectory or if it was paused mid-motion, continue motion.
	/// </summary>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo MotionStart() = 0;

	/// <summary>
	/// Stop the motion immediately. Note that this will not clear the trajectory.
	/// </summary>
	/// <param name="clearTrajectory">IN true: Clear the trajectory, false: Keep the trajectory.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo MotionStop(bool clearTrajectory = false) = 0;

	/// <summary>
	/// Clear out the trajectory for all groups.
	/// </summary>
	virtual StatusInfo ClearAllTrajectory() = 0;




};

class KinematicsInterface
{
public:
	virtual ~KinematicsInterface() = default;
	/// <summary>
	/// Converts the position data to the specified type. This function should not be used for conversions from cartesian.
	/// </summary>
	/// <param name="grp">IN Group with position to convert.</param>
	/// <param name="positionToConvert">IN Position can be pulse or joint angle.</param>
	/// <param name="conversionType">IN Type of conversion to perform. <para> Valid conversions are JointAngleToCartesianPos, PulseToJointAngle, JointAngleToPulse,	PulseToCartesianPos. </para> </param>
	/// <param name="convertedPosition">OUT The converted position received from the controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ConvertPosition(ControlGroupId grp, PositionData& positionToConvert,
		KinematicConversions conversionType, PositionData& convertedPosition) = 0;

	/// <summary>
	/// Converts the position data from the specified cartesian type.
	/// </summary>
	/// <param name="grp">IN Group with position to convert.</param>
	/// <param name="positionToConvert">IN Position must be cartesian.</param>
	/// <param name="conversionType">IN Type of conversion to perform. <para> Valid conversions are CartesianPosToJointAngle, CartesianPosToPulse </para> </param>
	/// <param name="type">IN optional parameter that specifies how to solve inverse kinematics. </param>
	/// <param name="prevAngle">IN required angle when conversions are done with with KinematicType::Delta. Otherwise ignored.</param>
	/// <param name="convertedPosition">OUT The converted position received from the controller.</param>
	/// <returns>0 if successful, otherwise a StatusInfo object with a description of error.</returns>
	virtual StatusInfo ConvertPositionFromCartesian(ControlGroupId grp, PositionData& positionToConvert,
		KinematicConversions conversionType, KinematicType type,
		const CoordinateArray& prevAngle, PositionData& convertedPosition) = 0;

};
/// <summary>
/// Interfaces for calling all functions.
/// </summary>
class MotomanController
{
public:
	virtual ~MotomanController() = default;

	ControlGroupInterface* ControlGroup{ nullptr };
	ControllerStateInterface* Status{ nullptr };
	VariablesInterface* Variables{ nullptr };
	FaultInterface* Faults{ nullptr };
	JobInterface* Job{ nullptr };
	FileInterface* Files{ nullptr };
	IOInterface* Io{ nullptr };
	ControlCommandsInterface* ControlCommands{ nullptr };
	MotionManagerInterface* MotionManager{ nullptr };
	KinematicsInterface* Kinematics{ nullptr };
};
#pragma endregion

//==========================================================================================================================================================================

#pragma region DLL Export Commands

#ifdef __cplusplus
extern "C" {
#endif

	namespace YMConnect
	{
		/// <summary>
		/// This is the main function to call to open a connection to the controller.
		/// </summary>
		/// <param name="ip">: IN The ip of the controller you are trying to connect to</param>
		/// <param name="receivePacketTimeout">: IN The amount of time to wait for a response packet</param>
		/// <param name="sendPacketRetries">: IN Number of times to retry the command</param>
		/// <param name="loggingEnabled">: IN Enable or disable logging. This will write motion errors to "YMConnectLog.txt" in the same folder as the DLL/SO.</param>
		/// <param name="version">: IN Used to ensure version of this header is the correct version for the YMConnect binary.</param>
		/// <returns>A pointer to the main object.</returns>
		YMCONNECT_API MotomanController* OpenConnection(const std::string& ip, StatusInfo& statusCode, UINT32 receivePacketTimeout_ms = 500,
			UINT32 sendPacketRetries = 3, bool loggingEnabled = true, const std::string_view& version = YMConnect_Header_Version);
		YMCONNECT_API void CloseConnection(MotomanController* controller);
	}

	namespace VectorMath
	{
		/// <summary>
		/// Calculate the inner product of two vectors.
		/// </summary>
		/// <param name="vector1">IN multiplicand</param>
		/// <param name="vector2">IN multiplier</param>
		/// <param name="product">OUT The product of the calculation.</param>
		YMCONNECT_API void InnerProduct(const XyzVector& vector1, const XyzVector& vector2, DOUBLE64& product);

		/// <summary>
		/// Calculate the cross product of two vectors.
		/// </summary>
		/// <param name="vector1">IN multiplicand</param>
		/// <param name="vector2">IN multiplier</param>
		/// <param name="product">OUT The product of the calculation.</param>
		YMCONNECT_API void CrossProduct(const XyzVector& vector1, const XyzVector& vector2, XyzVector& product);
	}
	namespace FrameMath
	{
		/// <summary>
		/// Calculate the inverse of a frame.
		/// </summary>
		/// <param name="frame">Frame to invert.</param>
		/// <param name="inverseFrame">OUT Inverse of input frame.</param>
		YMCONNECT_API void InvertFrame(const EulerMatrix& frame, EulerMatrix& inverseFrame);

		/// <summary>
		/// Rotate a frame about an axis by a specified angle.
		/// </summary>
		/// <param name="org_frame">Origin frame.</param>
		/// <param name="rotationVector">Vector to rotate about.</param>
		/// <param name="angle">Angle for which to rotate.</param>
		/// <param name="rotatedFrame">OUT Output of the operation.</param>
		YMCONNECT_API void RotateFrame(const EulerMatrix& org_frame, const XyzVector& rotationVector, DOUBLE64 angle, EulerMatrix& rotatedFrame);

		/// <summary>
		/// Convert a frame to ZYX Euler angles.
		/// </summary>
		/// <param name="frame">Frame to convert.</param>
		/// <param name="coord">OUT Converted angles.</param>
		YMCONNECT_API void FrameToZYXeuler(const EulerMatrix& frame, CoordinateArray& coord);
		/// <summary>
		/// Multiply two frames.
		/// </summary>
		/// <param name="f1">multiplicand</param>
		/// <param name="f2">multiplier</param>
		/// <param name="productFrame">Product of operation.</param>
		YMCONNECT_API void MultiplyFrames(const EulerMatrix& f1, const EulerMatrix& f2, EulerMatrix& productFrame);
		/// <summary>
		/// Convert ZYX Euler angles to a frame.
		/// </summary>
		/// <param name="coord">Angles to convert.</param>
		/// <param name="frame">Converted frame.</param>
		YMCONNECT_API void ZYXeulerToFrame(const CoordinateArray& coord, EulerMatrix& frame);
		/// <summary>
		/// Set a frame to an identity matrix.
		/// </summary>
		/// <param name="frame">Frame to set.</param>
		YMCONNECT_API void SetIdentityMatrixInFrame(EulerMatrix& frame);
	}
#ifdef __cplusplus
}
#endif


#pragma endregion
