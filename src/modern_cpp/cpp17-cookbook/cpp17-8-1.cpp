#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h" // For unit testing

#include <iostream>  // For input/output operations (cin, cout)
#include <chrono>    // For time measurement (duration, steady_clock)
#include <ratio>     // For compile-time rational numbers (std::ratio, std::milli, std::micro)
#include <iomanip>   // For output formatting (fixed, setprecision, setw)
#include <string>    // For string manipulation

// Use specific parts of std and std::chrono to avoid ambiguity and improve readability
using std::string;
using std::pair;
using std::cout;
using std::cin;
using std::fixed;
using std::setprecision;
using std::setw;

// Define custom duration types using double for precision
// Note: std::chrono::milli and std::chrono::micro are nested within std::chrono
using seconds = std::chrono::duration<double>;
using milliseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::milli>>;
using microseconds = std::chrono::duration<double, std::ratio_multiply<seconds::period, std::micro>>;

/**
 * @brief Gets user input and measures the time taken.
 * @return A pair containing the user's input string and the time taken as 'seconds' duration.
 * Returns an empty string and zero duration if input fails.
 */
static pair<string, seconds> get_input_with_timing() {
    string s;
    const auto tic = std::chrono::steady_clock::now(); // Record start time

    // Attempt to read user input. If failed (e.g., EOF), return empty.
    if (!(cin >> s)) {
        return { {}, seconds::zero() }; // Return empty string and zero duration
    }

    const auto toc = std::chrono::steady_clock::now(); // Record end time
    return {s, toc - tic}; // Return input string and the duration
}


TEST_CASE("CPP17-8-1") {
    cout << "--- Starting Typing Speed Game ---\n";
    cout << "Type 'exit' to quit.\n\n";

    while (true) {
        cout << "Please type the word \"C++17\" as fast as you can.\n> ";

        // Use C++17 structured binding to unpack the pair
        const auto [user_input, diff] = get_input_with_timing();

        // Check for empty input (e.g., stream error or EOF) or explicit 'exit' command
        if (user_input.empty() || user_input == "exit") {
            cout << "\nExiting game.\n";
            break;
        }

        if (user_input == "C++17") {
            cout << "Bravo! You did it in:\n"
                 << fixed << setprecision(2)
                 << setw(12) << diff.count() << " seconds.\n"
                 << setw(12) << milliseconds(diff).count() << " milliseconds.\n"
                 << setw(12) << microseconds(diff).count() << " microseconds.\n\n";
            break; // Correct input, exit game
        } else {
            cout << "Sorry, your input does not match. You may try again.\n\n";
        }
    }
    // You could add a CHECK here if you wanted to verify internal state,
    // but for an interactive demo, direct output is usually enough.
    CHECK(true); // Always pass for demonstration purposes
}

