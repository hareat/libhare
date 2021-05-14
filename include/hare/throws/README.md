# hare/throws/ header files

Instead of cluttering code with error processing these functions throw an
exception to centralize the error processing.

If the return value of the original function is on necessary to indicate an
error the wrapper function does not return anything.

Example

    void fancy_stuff() {
        // automatically closes an open file pointer also in case of an error
        const hare::wrap::FILE fp(fopen(<your path>, "r"));
        // this will fail because the file is open read only
        hare::throws::fputs("fancy content", fp);
        hare::throws::fputs("more fancy content", fp);
    }

    int main(int argc, const char* argv[]) {
        try {
           fancy_stuff();
           hare::throws::chown(<another path>, 0);
           return EXIT_SUCCESS;
        } catch (const std::exception& ex) {
           puts(ex.what());
           return EXIT_FAILURE;
        }
    }
