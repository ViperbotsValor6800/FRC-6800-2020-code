#include <commands/Auto/SixBallAuto.h>

SixBallAuto::SixBallAuto() {
    trajectory1 = m_trajectories.GetAutosMap().at("SixBallAuto")[0].trajectory;
    frc2::RamseteCommand ramseteCommand1(trajectory1,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    trajectory2 = m_trajectories.GetAutosMap().at("SixBallAuto")[1].trajectory;
    frc2::RamseteCommand ramseteCommand2(trajectory2,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    trajectory3 = m_trajectories.GetAutosMap().at("SixBallAuto")[2].trajectory;
    frc2::RamseteCommand ramseteCommand3(trajectory3,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    AddCommands(
        frc2::SequentialCommandGroup(
            frc2::InstantCommand( [&] { m_shooter.SetHoodTarget(0.715); } ), 
            std::move(ramseteCommand1),
            frc2::RunCommand( [&] {m_shooter.SetShooterPower(0.7); } ).WithTimeout(2_s),
            frc2::InstantCommand( [&] {m_shooter.SetShooterPower(0.7); m_hopper.SetHopperPower(0.8); m_intake.SetIntakePower(1); } ),
            frc2::WaitCommand(3_s),
            frc2::InstantCommand( [&] {m_shooter.SetShooterPower(0); m_hopper.SetHopperPower(0); m_intake.SetIntakePower(0); } ),
            frc2::InstantCommand( [&] { m_shooter.SetHoodTarget(0.8); } ),
            frc2::ParallelCommandGroup( frc2::RunCommand([&] { m_intake.SetIntakePower(1); }).WithTimeout(2_s), std::move(ramseteCommand2)),
            std::move(ramseteCommand3),
            frc2::InstantCommand( [&] { m_shooter.SetHoodTarget(0.715); } ), 
            frc2::RunCommand( [&] {m_shooter.SetShooterPower(0.7); } ).WithTimeout(2_s),
            frc2::InstantCommand( [&] {m_shooter.SetShooterPower(0.7); m_hopper.SetHopperPower(0.8); m_intake.SetIntakePower(1); } ),
            frc2::WaitCommand(3_s),
            frc2::InstantCommand( [&] {m_shooter.SetShooterPower(0); m_hopper.SetHopperPower(0); m_intake.SetIntakePower(0); } )//,
        )
    );
}