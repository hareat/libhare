# hare/signalsafe/ header files

[Linux manual page about signal-safety](https://man7.org/linux/man-pages/man7/signal-safety.7.html)
lists all the POSIX functions which are async-signal-safe.
But it is unconvenient and error prone to always remember which function is
allowed to use and which one is not allowed. So it is much more handy to use
this namespace to indicate if it is part of the list.

Example

    static void my_signal_handler() {
        const char *msg = "signal cought\n";
        hare::signalsafe::write(2, msg, hare::signalsafe::strlen(msg));
    }

    int main(int argc, const char* argv[]) {
        try {
           hare::throws::signal(SIGUSR1, my_signal_handler);
           hare::throws::raise(SIGUSR1);
           std::puts("exit success");
           return EXIT_SUCCESS;
        } catch (const std::exception& ex) {
           std::fprintf(stderr, "%s\n", ex.what());
           return EXIT_FAILURE;
        }
    }
