// Copyright (c) 2021 -	Stefan de Bruijn
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "Generator.h"
#include "Parser.h"

namespace Configuration {
    class HandlerBase;
    class Validator;

    class Configurable {
        Configurable(const Configurable&) = delete;
        Configurable(Configurable&&)      = default;

        Configurable& operator=(const Configurable&) = delete;
        Configurable& operator=(Configurable&&) = default;

    public:
        Configurable() = default;

        virtual void group(HandlerBase& handler) = 0;
        virtual void validate(Validator& handler);
        virtual void afterParse(HandlerBase& handler);

        virtual const char* name() const = 0;

        virtual ~Configurable();
    };
}
