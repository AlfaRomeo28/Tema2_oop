#include <gtest/gtest.h>
#include "EfectEcou.h"
#include "EfectAudio.h"

TEST(AudioTest, CreareEfect) {
    EfectEcou ecou("EcouTest", true, 5, 0.4f);
    EXPECT_EQ(ecou.getNume(), "EcouTest");
    EXPECT_TRUE(ecou.esteActiv());
}
