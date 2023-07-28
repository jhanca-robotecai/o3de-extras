/*
 * Copyright (c) Contributors to the Open 3D Engine Project.
 * For complete copyright and license terms please see the LICENSE at the root of this distribution.
 *
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

#include <QApplication>

#include <AzCore/Component/Entity.h>
#include <AzCore/RTTI/RTTIMacros.h>
#include <AzCore/UserSettings/UserSettingsComponent.h>
#include <AzQtComponents/Utilities/QtPluginPaths.h>
#include <AzTest/GemTestEnvironment.h>
#include <AzToolsFramework/ToolsComponents/TransformComponent.h>
#include <AzToolsFramework/UnitTest/ToolsTestApplication.h>

#include <Camera/ROS2CameraSensorEditorComponent.h>
#include <GNSS/ROS2GNSSSensorComponent.h>
#include <Imu/ROS2ImuSensorComponent.h>
#include <Lidar/ROS2Lidar2DSensorComponent.h>
#include <Lidar/ROS2LidarSensorComponent.h>

namespace UnitTest
{
    class SDFormatImporterTestEnvironment : public AZ::Test::GemTestEnvironment
    {
        // AZ::Test::GemTestEnvironment overrides ...
        AZ::ComponentApplication* CreateApplicationInstance() override;
        void PostSystemEntityActivate() override;

    public:
        SDFormatImporterTestEnvironment() = default;
        ~SDFormatImporterTestEnvironment() override = default;
    };

    AZ::ComponentApplication* SDFormatImporterTestEnvironment::CreateApplicationInstance()
    {
        // Using ToolsTestApplication to have AzFramework and AzToolsFramework components.
        return aznew UnitTest::ToolsTestApplication("SDFormatImporter");
    }

    void SDFormatImporterTestEnvironment::PostSystemEntityActivate()
    {
        AZ::UserSettingsComponentRequestBus::Broadcast(&AZ::UserSettingsComponentRequests::DisableSaveOnFinalize);
    }

    class SDFormatImportFixture : public ::testing::Test
    {
    };

    TEST_F(SDFormatImportFixture, CreateComponents)
    {
        AZ::Entity entity;
        entity.CreateComponent<AzToolsFramework::Components::TransformComponent>();
        entity.Init();

        ROS2::SensorConfiguration sensorConfiguration;
        sensorConfiguration.m_frequency = 11;

        ROS2::CameraSensorConfiguration cameraConfiguration;
        cameraConfiguration.m_height = 111;
        entity.CreateComponent<ROS2::ROS2CameraSensorEditorComponent>(sensorConfiguration, cameraConfiguration);

        ROS2::GNSSSensorConfiguration gnssConfiguration;
        gnssConfiguration.m_originAltitude = 111.0f;
        entity.CreateComponent<ROS2::ROS2GNSSSensorComponent>(sensorConfiguration, gnssConfiguration);

        ROS2::ImuSensorConfiguration imuConfiguration;
        imuConfiguration.m_filterSize = 111;
        entity.CreateComponent<ROS2::ROS2ImuSensorComponent>(sensorConfiguration, imuConfiguration);

        ROS2::Lidar2DSensorConfiguration lidar2DConfiguration;
        lidar2DConfiguration.m_addPointsAtMax = true;
        entity.CreateComponent<ROS2::ROS2Lidar2DSensorComponent>(sensorConfiguration, lidar2DConfiguration);

        ROS2::LidarSensorConfiguration lidarConfiguration;
        lidarConfiguration.m_addPointsAtMax = true;
        entity.CreateComponent<ROS2::ROS2LidarSensorComponent>(sensorConfiguration, lidarConfiguration);

        const auto& components = entity.GetComponents();
        EXPECT_EQ(components.size(), 6U);
        EXPECT_EQ(azrtti_typeid<ROS2::ROS2CameraSensorEditorComponent>(), components[1]->GetUnderlyingComponentType());
        const auto* cameraEditorComponent = azrtti_cast<ROS2::ROS2CameraSensorEditorComponent*>(components[1]);
        ASSERT_TRUE(cameraEditorComponent);
        EXPECT_EQ(cameraEditorComponent->GetHeight(), 111);

        EXPECT_EQ(azrtti_typeid<ROS2::ROS2GNSSSensorComponent>(), components[2]->GetUnderlyingComponentType());
        EXPECT_EQ(azrtti_typeid<ROS2::ROS2ImuSensorComponent>(), components[3]->GetUnderlyingComponentType());
        EXPECT_EQ(azrtti_typeid<ROS2::ROS2Lidar2DSensorComponent>(), components[4]->GetUnderlyingComponentType());
        EXPECT_EQ(azrtti_typeid<ROS2::ROS2LidarSensorComponent>(), components[5]->GetUnderlyingComponentType());
    }

} // namespace UnitTest

// required to support running integration tests with Qt and PhysX
AZTEST_EXPORT int AZ_UNIT_TEST_HOOK_NAME(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    AzQtComponents::PrepareQtPaths();
    QApplication app(argc, argv);
    AZ::Test::printUnusedParametersWarning(argc, argv);
    AZ::Test::addTestEnvironments({ new UnitTest::SDFormatImporterTestEnvironment() });
    int result = RUN_ALL_TESTS();
    return result;
}

IMPLEMENT_TEST_EXECUTABLE_MAIN();
