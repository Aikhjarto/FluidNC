// Copyright (c) 2021 -  Stefan de Bruijn
// Copyright (c) 2021 -  Mitch Bradley
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#include "../Configuration/Configurable.h"
#include "../WebUI/InputBuffer.h"  // WebUI::inputBuffer

namespace Machine {
    class Macros : public Configuration::Configurable {
    public:
        static const int n_startup_lines = 2;
        static const int n_macros        = 4;

    private:
        String _startup_line[n_startup_lines];
        String _macro[n_macros];

    public:
        Macros() = default;

        void run_macro(size_t index) {
            if (index >= n_macros) {
                return;
            }
            String macro = _macro[index];
            if (macro == "") {
                return;
            }

            // & is a proxy for newlines in macros, because you cannot
            // enter a newline directly in a config file string value.
            macro.replace('&', '\n');
            macro += "\n";

            WebUI::inputBuffer.push(macro.c_str());
        }

        String startup_line(size_t index) {
            if (index >= n_startup_lines) {
                return "";
            }
            String s = _startup_line[index];
            if (s == "") {
                return s;
            }
            // & is a proxy for newlines in startup lines, because you cannot
            // enter a newline directly in a config file string value.
            s.replace('&', '\n');
            return s + "\n";
        }

        // Configuration helpers:

        // TODO: We could validate the startup lines

        void group(Configuration::HandlerBase& handler) override {
            handler.item("n0", _startup_line[0]);
            handler.item("n1", _startup_line[1]);
            handler.item("macro0", _macro[0]);
            handler.item("macro1", _macro[1]);
            handler.item("macro2", _macro[2]);
            handler.item("macro3", _macro[3]);
        }

        ~Macros() {}
    };
}
