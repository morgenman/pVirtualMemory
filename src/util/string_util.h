/**
 * Purpose of this document is to provide a set of string related functions to
 * deal with hex <=> dec <=> strings
 */

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>

// A small collection of free-functions for manipulating std::string
// objects.
namespace str_util {

/**
 * Return a copy of the original string with left-side whitespace trimmed.
 *
 * @param orig original string to copy, except for left-side whitespace
 * @return copy of orig without left-side whitespace (" \t\n\r"); result
 *         will be empty if there are no non-whitespace characters.
 * @note NOT locale aware
 */
std::string trim_left(const std::string& orig);

/**
 * Return a copy of the original string with right-side whitespace trimmed.
 *
 * @param orig original string to copy, except for right-side whitespace
 * @return copy of orig without right-side whitespace (" \t\n\r"); result
 *         will be empty if there are no non-whitespace characters.
 * @note NOT locale aware
 */
std::string trim_right(const std::string& orig);

/**
 * Globally replace instances of to_be_replaced with the replacement string.
 * No recursive replacement (the inserted text is not scanned). Returns a
 * copy with the text replaced.
 *
 * @param orig the original string to be copied with replacements made
 * @param to_be_replaced the string to be replaced in orig; should not be empty
 * @param replacement string to put in place of to_be_replaced
 * @cite https://stackoverflow.com/questions/27617903
 * Note: the escape-handling code on that page is broken.
 * @return copy of orig with all instances of to_be_replaced overwritten with
 *         replacement
 */
std::string string_globally_replace(const std::string& orig,
                                    const std::string& to_be_replaced,
                                    const std::string& replacement);

/**
 * Internalize a C/C++ slash-escaped string. Convert character combinations like
 * '\n' into a new line character. Returns an internalized copy of the string.
 *
 * @param orig original, slash-escaped (possibly) string to internalize
 * @return a copy of orig with \ escape sequences replaced with their internal
 *         representations.
 * @note DOES NOT handle octal, hex, or Unicode character encodings
 */
std::string intern_escaped_string(const std::string& orig);

/**
 * Does the string consist of a valid hex encoding? "Ox" or "0X" at
 * the beginning and a sequence of hex digits after that.
 *
 * @param str string to check
 * @return true if string is non-empty with only hex digits; false otherwise
 * @cite see https://stackoverflow.com/questions/8899069/
 * how-to-find-if-a-given-string-conforms-to-hex-notation-eg-0x34ff-without-regex
 * for discussion and original version of this code; code extended for
 * 0X/0x.
 */
bool is_hex_digit_string(std::string const& str);

/**
 * Copy a string of the form "0xdeadbeef" into the internal
 * representation of the eight-bit characters represented by the pairs
 * of hex digits, returning the internalized version.
 *
 * @param hex_str a string containing a hex-encoded string: must begin
 *        with 0x or 0X, must be a valid hex encoding of even length
 *        after that.
 * @return returns a string containing the characters described by the hex
 *         sequence is hex_str; if hex_str is not of the right form, the
 *         return string is empty
 * @cite seen somewhere on the 'Net while looking at hex conversion; cannot
 * find matching original as modified to use char[]. strtol was in original
 */
std::string intern_hex_encoded_string(std::string const& hex_str);

/**
 * Extract characters from is (after initial whitespace), interpreting
 * contiguous pairs as hex encodings of 8-bit characters. The encoded
 * characters are converted into the string they represent.
 *
 * @param is the stream to read from
 * @param str the string to put the hex into
 * @return the stream
 */
std::istream& get_hex_string(std::istream& is, std::string& str);

/**
 * Extract characters from is, expecting that the first non-whitespace
 * character will be a double quote; extracted characters are stored
 * into str until a matching (unescaped) double quote or delim
 * character is reached. As with std::getline, the terminating
 * character is consumed; unlike getline, the terminating character
 * must come _after_ the starting character (the double quote).
 *
 * @param is the input stream to read
 * @param str where the characters in the quoted string are stored;
 *        the string is unchanged if there is no quoted string to read
 * @param openQ the opening quote character; defaults to double quote
 * @param closeQ the closing quote character; defaults to double quote.
 *        closeQ is escaped by being preceded with a \ and should not,
 *        itself, be the \ character
 * @param delim the delimiter to end on if there is no ending quote
 * @return the input stream
 */
std::istream& get_quoted_string(std::istream& is, std::string& str,
                                char openQ = '\"', char closeQ = '\"',
                                char delim = '\n');

}  // namespace str_util

#endif /* STRING_UTIL_H */
