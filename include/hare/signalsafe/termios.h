#ifndef HARE_SIGNALSAFE_TERMIOS_H
#define HARE_SIGNALSAFE_TERMIOS_H

#include <termios.h>

/***************************************************************
 * hare/signalsafe/termios.h async-signal-safe functions of termios.h.
 * Only functions of the list in man signal-safety are allowed.
 *
 * @author Hannes Reisinger github@HaRe.at
 ***************************************************************/

namespace hare {
	namespace signalsafe {
		using ::cfgetispeed;
		using ::cfgetospeed;
		using ::cfsetispeed;
		using ::cfsetospeed;
		using ::tcdrain;
		using ::tcflow;
		using ::tcflush;
		using ::tcgetattr;
		using ::tcgetpgrp;
		using ::tcsendbreak;
		using ::tcsetattr;
		using ::tcsetpgrp;
	}	// namespace signalsafe
}	// namespace hare

#endif	// HARE_SIGNALSAFE_TERMIOS_H
