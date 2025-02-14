add_library(application-bell-main STATIC)
add_library(bell::app-main ALIAS application-bell-main)

target_sources(application-bell-main
    PRIVATE
        ApplicationBellMain.cpp
        widgets/BellBattery.cpp
        widgets/ProgressTimerWithSnoozeTimer.cpp
        widgets/SnoozeTimer.cpp
        windows/BellBatteryShutdownWindow.cpp
        windows/BellHomeScreenWindow.cpp
        windows/BellMainMenuWindow.cpp
        windows/BellBatteryStatusWindow.cpp

        models/BatteryModel.cpp
        models/TemperatureModel.cpp

        presenters/HomeScreenPresenter.cpp
        presenters/StateController.cpp

        widgets/BellBattery.hpp
        widgets/ProgressTimerWithSnoozeTimer.hpp
        widgets/SnoozeTimer.hpp

        windows/BellBatteryShutdownWindow.hpp
        windows/BellHomeScreenWindow.hpp
        windows/BellMainMenuWindow.hpp
        windows/BellBatteryStatusWindow.hpp
        data/BatteryUtils.hpp

        models/BatteryModel.cpp
        models/TemperatureModel.hpp

        presenters/HomeScreenPresenter.hpp
        presenters/StateController.hpp
        presenters/StateControllerLogger.hpp

    PUBLIC
        include/application-bell-main/ApplicationBellMain.hpp
)

target_include_directories(application-bell-main
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(application-bell-main
    PRIVATE
        app
        apps-common
        bellgui
        i18n
        module-gui
        service-gui
        utils-time
        bell::db
        bell::evtmgr
        bell::app-alarm
        bell::app-onboarding
        bell::app-background-sounds
        bell::app-bedtime
        bell::app-meditation-timer
        bell::app-settings
        bell::app-powernap
        bell::keymap
        ${TARGET_LIBRARIES}
    PUBLIC
        bell::app-common
)
