// Copyright (c) 2017-2021, Mudita Sp. z.o.o. All rights reserved.
// For licensing, see https://github.com/mudita/MuditaOS/LICENSE.md

#pragma once

#include <hal/key_input/AbstractKeyInput.hpp>

namespace hal::key_input
{
    class KeyInput : public AbstractKeyInput
    {
      public:
        void init(xQueueHandle) final;
        void deinit() final;
        std::vector<bsp::KeyEvent> getKeyEvents(KeyNotificationSource) final;

        BaseType_t wakeupIRQHandler();
    };
} // namespace hal::key_input
