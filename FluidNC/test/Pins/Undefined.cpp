#include "../TestFramework.h"

#include <src/Pin.h>
#include <esp32-hal-gpio.h>  // CHANGE

namespace Pins {
    Test(Undefined, Pins) {
        // Unassigned pins are not doing much...

        Pin unassigned;
        Assert(Pin() == unassigned, "Undefined has wrong pin id");

        {
            unassigned.write(true);
            auto result = unassigned.read();
            Assert(0 == result, "Result value incorrect");
        }

        {
            unassigned.write(false);
            auto result = unassigned.read();
            Assert(0 == result, "Result value incorrect");
        }

        AssertThrow(unassigned.attachInterrupt([](void* arg) {}, CHANGE));
        AssertThrow(unassigned.detachInterrupt());

        Assert(unassigned.capabilities().has(Pin::Capabilities::Void));
        auto name = unassigned.name();
        Assert(unassigned.name().equals("NO_PIN"));

        // Can't change undefined-pin attributes:
        Assert(unassigned.getAttr() == Pin::Attr::Undefined);
        unassigned.setAttr(Pin::Attr::Input);
        Assert(unassigned.getAttr() == Pin::Attr::Undefined);
    }

    Test(Undefined, MultipleInstances) {
        {
            Pin unassigned;
            Pin unassigned2;

            Assert(unassigned == unassigned2, "Should evaluate to true.");
        }

        {
            Pin unassigned = Pin();
            Pin unassigned2;

            Assert(unassigned == unassigned2, "Should evaluate to true.");
        }

        {
            Pin unassigned = Pin::create("void.2");
            Pin unassigned2;

            Assert(unassigned != unassigned2, "Second void pin should match first.");
        }

        {
            Pin unassigned  = Pin::create("void.2");
            Pin unassigned2 = Pin::create("void.2");

            Assert(unassigned != unassigned2, "Second void pin should not match first.");
        }
    }
}
