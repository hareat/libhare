#include "test.h"

#include <hare/mac_sz.h>

struct TestHareMacSz {
	static void test_mac_to_sz() {
		uint8_t mac[MAC_ADDR_LENGTH] = {0xAB, 0xCD, 0x15, 0xF9, 0xDA, 0xBC};
		const char achMac[MAC_ADDR_LENGTH * 3] = "AB:CD:15:F9:DA:BC";
		EQUAL_S(achMac, hare::mac_to_sz(mac));
	}

	static void test_mac_from_sz() {
		uint8_t mac[MAC_ADDR_LENGTH] = {0};
		const char achMac[MAC_ADDR_LENGTH * 3] = "AB:CD:15:F9:DA:BC";
		EQUAL_D(MAC_ADDR_LENGTH, hare::mac_from_sz(mac, achMac));
		EQUAL_S(achMac, hare::mac_to_sz(mac));
		EQUAL_D(0, hare::mac_from_sz(mac, "invalid"));
		EQUAL_D(1, hare::mac_from_sz(mac, "ABC:AB:first is valid"));
		EQUAL_D(2, hare::mac_from_sz(mac, "A:AB:one char is also valid"));
	}

	static void test() {
		test_mac_to_sz();
		test_mac_from_sz();
	}
};
