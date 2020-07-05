#ifndef JUGGERNAUT_UTILITY_CONSOLE_OUTPUT_HPP
#define JUGGERNAUT_UTILITY_CONSOLE_OUTPUT_HPP

#include <string_view>

namespace jnt
{
    /**
     * Colored console output helper
     */
    class ConsoleOutput
    {
    public:
        /**
         * Log an informational message to the console
         * @param   message     Message to print
         */
        static void Info(std::string_view message);

        /**
         * Log a success message to the console
		 * @param   message     Message to print
		 */
        static void Success(std::string_view message);

        /**
         * Log a warning message to the console
		 * @param   message     Message to print
		 */
        static void Warning(std::string_view message);

        /**
         * Log an error message to the console
		 * @param   message     Message to print
		 */
        static void Error(std::string_view message);

        /**
         * Reset the console colors to the standard console colors
         */
        static void Reset();

    private:
        /**
         * Color to set the console to, internal use only
         */
        enum class Color
        {
            White,
            Green,
            Yellow,
            Red
        };

        /**
         * Change the console color
         * @param   color   Color to set the console output to
         */
        static void SetConsoleColor(Color color);
    };
}

#endif //! JUGGERNAUT_UTILITY_CONSOLE_OUTPUT_HPP
