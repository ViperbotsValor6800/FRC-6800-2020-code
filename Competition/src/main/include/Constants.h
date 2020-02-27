#pragma once

#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>

#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace OIConstants {

    constexpr static int GAMEPAD_BASE_LOCATION = 1;
    constexpr static int GAMEPAD_OPERATOR_LOCATION = 0;

}

namespace DriveConstants {

// 1/2/3, 4/5/6 from pdp increasing towards intake
    constexpr static int CAN_ID_LEFT_LEAD = 1;
    constexpr static int CAN_ID_LEFT_FOLLOW_A = 2;
    constexpr static int CAN_ID_LEFT_FOLLOW_B = 3;
    constexpr static int CAN_ID_RIGHT_LEAD = 4;
    constexpr static int CAN_ID_RIGHT_FOLLOW_A = 5;
    constexpr static int CAN_ID_RIGHT_FOLLOW_B = 6;

    constexpr auto kTrackwidth = 0.68_m;

    constexpr double kWheelDiameterInches = 6;
    constexpr double kGearRatio = 8.8;

    constexpr static double kP = 0.01f;
    constexpr static double kI = 0.0;
    constexpr static double kD = 0.0;
    constexpr static double kIz = 0.0;
    constexpr static double kFF = 0.0001754;
    constexpr static double MaxRPM = 5700;
    constexpr static double kMaxOutput = 1.0;
    constexpr static double kMinOutput = -1.0;
    constexpr static double kMaxVel = 1000;
    constexpr static double kMinVel = 0;
    constexpr static double kMaxAccel = 1500;
    constexpr static double kAllError = 0;
    constexpr static double kDeadband = 0.05;
    constexpr static double kDeadbandY = 0.02;
    constexpr static double kDeadbandX = 0.02;
    constexpr static double kDriveMultiplierX = 0.5;
    constexpr static double kDriveMultiplierY = 1;
    constexpr static double kDriveOffset = 1;
}

namespace RamseteConstants {

    constexpr auto kMaxSpeed = 4.4_mps; // 4_mps
    constexpr auto kMaxAcceleration = 4_mps_sq; //4_mps_sq;

    constexpr double kRamseteB = 2;
    constexpr double kRamseteZeta = 0.7;

    // Convert rotations to meters using gear ratio and wheel diameter (converted to meters)
    constexpr double kPositionConversionFactor = DriveConstants::kWheelDiameterInches * 0.0254 / DriveConstants::kGearRatio * M_PI;
    // Convert rotations per minute to meters per second 
    constexpr double kVelocityConversionFactor = kPositionConversionFactor / 60;

    constexpr bool kGyroReversed = true;

    constexpr auto kS = 0.146_V;
    constexpr auto kV = 2.25 * 1_V * 1_s / 1_m;
    constexpr auto kA = 0.315 * 1_V * 1_s * 1_s / 1_m;

    constexpr double kPDriveVel = 3.09;

    constexpr units::length::meter_t  kStartPos = 4.9_m;
    constexpr units::length::meter_t  kCenterline = 0.94_m;

}

namespace ArmConstants {

    constexpr static int CAN_ID_LEFT_ARM = 9;
    constexpr static int CAN_ID_RIGHT_ARM = 10;

}

namespace ShooterConstants {

    constexpr static int CAN_ID_SHOOTER_LEAD = 7;
    constexpr static int CAN_ID_SHOOTER_FOLLOW = 8;
    constexpr static int PWM_ID_THROAT = 0;
    constexpr static int PWM_ID_HOOD = 6;

}

namespace IntakeConstants {

    constexpr static int PWM_ID_INTAKE = 1;

}

namespace HopperConstants {

    constexpr static int PWM_ID_HOPPER = 2;

}

namespace LiftConstants {

    constexpr static int PWM_ID_LIFT_A = 3;
    constexpr static int PWM_ID_LIFT_B = 5;
    constexpr static int PWM_ID_LEFT_A_SERVO_LOCK = 7;
    constexpr static int PWM_ID_LEFT_B_SERVO_LOCK = 7;

}

namespace MuncherConstants {

    constexpr static int PWM_ID_MUNCHER = 4;

}

#endif