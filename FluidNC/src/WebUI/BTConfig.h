// Copyright (c) 2014 Luc Lebosse. All rights reserved.
// Copyright (c) 2021 Stefan de Bruijn
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

#ifdef ENABLE_BLUETOOTH
#    include "../Configuration/Configurable.h"
#    include "../Config.h"  // ENABLE_*

#    include <WString.h>
#    include <BluetoothSerial.h>

namespace WebUI {
    extern BluetoothSerial SerialBT;

    class BTConfig : public Configuration::Configurable {
    private:
        static BTConfig* instance;  // BT Callback does not support passing parameters. Sigh.

        String _btclient = "";
        String _btname   = "btfluidnc";
        char   _deviceAddrBuffer[18];

        static const int MAX_BTNAME_LENGTH = 32;
        static const int MIN_BTNAME_LENGTH = 1;

        static void my_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t* param);

        //boundaries
    public:
        BTConfig();

        void validate() const override {
            Assert(_btname.length() > 0, "Bluetooth must have a name if it's configured");
            Assert(_btname.length() >= MIN_BTNAME_LENGTH && _btname.length() <= MAX_BTNAME_LENGTH,
                   "Bluetooth name must be between %d and %d characters long",
                   MIN_BTNAME_LENGTH,
                   MAX_BTNAME_LENGTH);
        }
        void group(Configuration::HandlerBase& handler) override { handler.item("_name", _btname); }

        String        info();
        bool          isBTnameValid(const char* hostname);
        const String& BTname() const { return _btname; }
        const String& client_name() const { return _btclient; }
        const char*   device_address();
        bool          begin();
        void          end();
        void          handle();
        void          reset_settings();
        bool          Is_BT_on() const;

        ~BTConfig();
    };
}

#endif
