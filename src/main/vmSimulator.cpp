/**
 *  Implementation of Memory Virtualization
 *
 *  vmSimulator and subsequent subclasses needed for Page Table lookup, address
 *  translation, and dynamic memory relocation.
 *  Aside from this file containing main(), function documentation will be in
 *  header files, with `.cpp` comments present as inline comments as necessary
 *
 *  @author: Dylan (Cole) Morgen
 *  @email: morgendc203@potsdam.edu
 *  @course: CIS 310 Operating Systems
 *  @due: 11/22/2021
 */

#include <unistd.h>

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "pageTable.h"
#include "ram.h"
#include "string_util.h"
#include "virtualMemoryTypes.h"

using namespace std;
using namespace str_util;

constexpr int framesInRAM = 8;
constexpr int pagesInProcess = 16;
const string commentMarker = "#";

/**
 * Print string to stdout iff stdin is connected to a keyboard.
 *
 * Uses istty() to detect whether stdin is redirected to a file.
 * Displays given string if it is not redirected.
 *
 * @param displayString the string to print to stdout if input is not redirected
 * @return true
 */
bool showOnlyOnScreen(const string& displayString) {
  if (isatty(fileno(stdin))) cout << displayString;
  return true;
}

/**
 * Command-processor for simulating a virtual memory system.
 *
 * Read standard input for commands: READ, WRITE, PAGES, FRAMES, TIME,
 * REF, CLEAR
 */
int main(int argc, char* argv[]) {
  RAM ram(framesInRAM);
  PageTable pageTable(pagesInProcess);
  int eventClock = 0;
  bool useTimeStamp = true;
  bool trace = false;
  vector<string> qWords{"quit", "Quit", "QUIT", "exit", "Exit", "EXIT"};

  string prompt = "> ";

  for (string line; showOnlyOnScreen(prompt), getline(cin, line);) {
    // strip eoln-comments
    string::size_type commentStart = line.find(commentMarker);
    if (commentStart != string::npos) line = line.substr(0, commentStart);

    // trim opening/closing whitespace
    line = trim_left(trim_right(line));

    // ignore blank lines
    if (line.empty()) continue;

    // take apart the read line
    stringstream readLine(line);
    string cmd;

    PageNumber page;
    FrameNumber frame;
    Offset offset;
    VirtualAddress vaddress;

    readLine >> cmd;
    if ((cmd == "READ") || (cmd == "WRITE")) {
      // Did this access cause a page fault interrupt?
      bool pageFault = false;  // not yet
      string vaddressString;
      readLine >> vaddressString;

      vaddress = stoi(vaddressString, 0, 16);
      ++eventClock;

      page = getPage(vaddress);
      if (trace)
        cout << "Page is: " << page << "; Original string: " << vaddressString
             << endl;

      offset = getOffset(vaddress);
      frame = pageTable.lookup(page);
      if (frame == noSuchFrame) {
        // page is not loaded in a frame (page fault interrupt)
        frame = ram.load(page, pageTable, useTimeStamp);
        pageFault = true;
      }

      // frame is frame of this address
      ram[frame].timestamp(eventClock);
      pageTable[page].referenced(true);
      cout << hex << setw(5) << setfill('0') << frame << '|' << hex << setw(3)
           << setfill('0') << offset << (pageFault ? "*" : " ") << dec << " "
           << ram[frame].timestamp() << endl;

    } else if (cmd == "PAGES") {
      cout << "PageTable------" << endl;
      cout << pageTable;
      cout << "----------------" << endl;
    } else if (cmd == "FRAMES") {
      cout << "RAM--------------" << endl;
      cout << ram;
      cout << "----------------" << endl;

    } else if (cmd == "TIME") {
      useTimeStamp = true;

    } else if (cmd == "REF") {
      useTimeStamp = false;

    } else if (cmd == "CLEAR") {
      pageTable.clearReferenced();

    } else if (std::find(qWords.begin(), qWords.end(), cmd) != qWords.end())
      return 0;
    else {
      cout << "Unknown command \"" << cmd << "\"" << endl;
    }
  }
  return 0;
}
