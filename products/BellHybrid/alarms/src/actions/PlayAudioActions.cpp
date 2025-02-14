// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#include "AlarmSoundPaths.hpp"
#include "PlayAudioActions.hpp"

#include <audio/AudioMessage.hpp>
#include <db/SystemSettings.hpp>
#include <Timers/TimerFactory.hpp>

namespace alarms
{
    PlayAudioAction::PlayAudioAction(sys::Service &service,
                                     const std::filesystem::path &tonesDirPath,
                                     std::string_view toneSetting,
                                     std::string_view durationSetting,
                                     audio::PlaybackType playbackType)
        : service{service}, soundsRepository{tonesDirPath}, toneSetting{toneSetting}, durationSetting{durationSetting},
          playbackType{playbackType}, settings{service::ServiceProxy{service.weak_from_this()}}
    {}

    bool PlayAudioAction::play(const std::filesystem::path &path, std::chrono::minutes duration)
    {
        if (duration != InfiniteDuration && duration != NoDuration) {
            spawnTimer(duration);
        }
        return service.bus.sendUnicast(std::make_shared<service::AudioStartPlaybackRequest>(path, playbackType),
                                       service::audioServiceName);
    }

    bool PlayAudioAction::turnOff()
    {
        detachTimer();
        auto stopPlaybackVec = std::vector<audio::PlaybackType>({playbackType});
        const auto msg       = std::make_shared<service::AudioStopRequest>(stopPlaybackVec);
        return service.bus.sendUnicast(msg, service::audioServiceName);
    }
    bool PlayAudioAction::execute()
    {
        const auto tone        = settings.getValue(toneSetting, settings::SettingsScope::Global);
        const auto durationStr = settings.getValue(durationSetting, settings::SettingsScope::Global);
        const auto durationVal = utils::getNumericValue<int>(durationStr);
        return play(soundsRepository.titleToPath(tone).value_or(""), std::chrono::minutes{durationVal});
    }

    void PlayAudioAction::detachTimer()
    {
        if (timer.isValid()) {
            timer.stop();
            timer.reset();
        }
    }
    void PlayAudioAction::spawnTimer(std::chrono::minutes timeout)
    {
        constexpr auto timerName = "playDurationTimer";
        if (not timer.isValid()) {
            auto callback = [this](sys::Timer &) { turnOff(); };
            timer         = sys::TimerFactory::createSingleShotTimer(&service, timerName, timeout, callback);
        }
        timer.stop();
        timer.start();
    }
    namespace factory
    {
        std::unique_ptr<PlayAudioAction> createPreWakeUpChimeAction(sys::Service &service)
        {
            return std::make_unique<PlayAudioAction>(service,
                                                     paths::getPreWakeUpChimesDir(),
                                                     bell::settings::PrewakeUp::tone,
                                                     NoPlaybackTimeout,
                                                     audio::PlaybackType::PreWakeUp);
        }

        std::unique_ptr<PlayAudioAction> createSnoozeChimeAction(sys::Service &service)
        {
            return std::make_unique<PlayAudioAction>(service,
                                                     paths::getSnoozeChimesDir(),
                                                     bell::settings::Snooze::tone,
                                                     bell::settings::Snooze::length,
                                                     audio::PlaybackType::Snooze);
        }
        std::unique_ptr<PlayAudioAction> createAlarmToneAction(sys::Service &service)
        {
            return std::make_unique<PlayAudioAction>(
                service, paths::getAlarmDir(), bell::settings::Alarm::tone, bell::settings::Alarm::duration);
        }
        std::unique_ptr<PlayAudioAction> createBedtimeChimeAction(sys::Service &service)
        {
            return std::make_unique<PlayAudioAction>(service,
                                                     paths::getBedtimeReminderChimesDir(),
                                                     bell::settings::Bedtime::tone,
                                                     bell::settings::Bedtime::duration,
                                                     audio::PlaybackType::Bedtime);
        }
    } // namespace factory
} // namespace alarms
