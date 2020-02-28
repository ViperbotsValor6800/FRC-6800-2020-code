#include <commands/Auto/TenBallHomeAuto.h>

TenBallHomeAuto::TenBallHomeAuto() {
    trajectory1 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[0].trajectory;
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
    
    trajectory2 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[1].trajectory;
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


    trajectory3 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[2].trajectory;
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


    trajectory4 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[3].trajectory;
    frc2::RamseteCommand ramseteCommand4(trajectory4,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    trajectory5 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[4].trajectory;
    frc2::RamseteCommand ramseteCommand5(trajectory5,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    trajectory6 = m_trajectories.GetAutosMap().at("TenBallHomeAuto")[5].trajectory;
    frc2::RamseteCommand ramseteCommand6(trajectory6,
                                        [&] () { return m_drivetrain.GetPose(); },
                                        frc::RamseteController(RamseteConstants::kRamseteB, RamseteConstants::kRamseteZeta),
                                        m_drivetrain.kSimpleMotorFeedforward,
                                        m_drivetrain.kDriveKinematics,
                                        [&] { return m_drivetrain.GetWheelSpeeds(); },
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        frc2::PIDController(RamseteConstants::kPDriveVel, 0, 0),
                                        [&] (auto left, auto right) { m_drivetrain.TankDriveVolts(left, right); },
                                        {&Drivetrain::GetInstance()});

    AddCommands(frc2::InstantCommand([&] {m_arm.SetArmPower(-0.25); }).WithInterrupt([&] { return m_arm.GetRestLimitSwitches(); }),
                frc2::ParallelRaceGroup(std::move(ramseteCommand1), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})), 
                frc2::ParallelRaceGroup(std::move(ramseteCommand2), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})), 
                ShootStart(m_shooter).WithTimeout(1.5_s),
                frc2::ParallelRaceGroup(std::move(ramseteCommand3), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})), 
                frc2::ParallelRaceGroup(std::move(ramseteCommand4), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})), 
                frc2::ParallelRaceGroup(std::move(ramseteCommand5), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})), 
                frc2::ParallelRaceGroup(std::move(ramseteCommand6), frc2::InstantCommand([&] { m_intake.SetIntakePower(0.5); }, {&m_intake})),
                ShootStart(m_shooter).WithTimeout(1.5_s));
}