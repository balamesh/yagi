/**
 * @file   YAGIInterpreter.h
 * @author Christopher Maier (cmaier@student.tugraz.at)
 * @date   January 2015
 *
 * YAGIInterpreter main functions
 */

/*
 This file is part of YAGI.

 YAGI is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 3.0 of the License, or (at your option) any later version.

 YAGI is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with YAGI.
*/


#include <string>

/**
 * @brief The YAGIInterpreter class offering all functions to write a YAGI interpreter
 */
class YAGIInterpreter
{
private:
    /**
     * Checks if a string is prefix of another string
     * @param potentialPrefix The potential prefix
     * @param text The text to check
     * @return True If prefix, false otherwise
     */
    static bool isPrefixOf(const std::string& potentialPrefix, const std::string& text);

    /**
     * Checks if a string is a suffix of another string
     * @param potentialSuffix Potential suffix string
     * @param text Text to be checked
     * @return true If suffix, false otherwise
     */
    static bool isSuffixOf(const std::string& potentialSuffix, const std::string& text);
public:

    /**
     * Parses command line args using TCLAP.
     * @param argc Number of args
     * @param argv Arguments
     */
    static void parseCommandLineArgs(int argc, char* argv[]);

    /**
     * Executes a YAGI program.
     * @param line The program to execute
     * @param isFileName Flag that indicates whether or not it line is a filename
     * @return True if execution successful, false otherwise
     */
    static bool execute(const std::string&, bool);

    /**
     * Parses the filename from an import command
     * @param importCmd The import command string
     * @return The filename
     */
    static std::string parseFileName(const std::string&);

    /**
     * Checks if the input command is a 'load from file' command
     * @param line Input command to check
     * @return true If it is 'import' command, false otherwise
     */
    static bool isFromFile(const std::string&);

    /**
     * Checks if an exit command has been entered
     * @param line The line that should be checked
     * @return true If exit, else otherwise
     */
    static bool isExit(const std::string&);

    /**
     * Displays the YAGI welcome message.
     */
    static void displayWelcome();

    /**
     * Callback method for readline that handles multine YAGI code.
     * @return success
     */
    static int addMultilineCommand(int, int);
};
