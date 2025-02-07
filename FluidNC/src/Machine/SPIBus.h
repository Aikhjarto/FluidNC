// Copyright (c) 2021 -  Stefan de Bruijn
// Copyright (c) 2021 -  Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "../Configuration/Configurable.h"

namespace Machine {
    class SPIBus : public Configuration::Configurable {
    public:
        SPIBus() = default;

        Pin _cs;
        Pin _miso;
        Pin _mosi;
        Pin _sck;

        void validate() const override;
        void group(Configuration::HandlerBase& handler) override;
        void afterParse() override;

        void init();

        ~SPIBus() = default;
    };
}
