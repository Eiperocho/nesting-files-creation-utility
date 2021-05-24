/*
 Intention Repeater Nesting Utility created by Anthro Teacher aka Thomas
 Sweet. May 23, 2021. Version 4.0
 Format code with: clang-format-9
 Style = Mozilla format.
 Compile code with: clang++-9 -O3 -Wall -static
 ./Repeater_Nesting_Utility_4.0.cpp -o ./Repeater_Nesting_Utility_4.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const std::string WHITESPACE = " \n\r\t\f\v";

std::string
ltrim(const std::string& s)
{
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

std::string
rtrim(const std::string& s)
{
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string
trim(const std::string& s)
{
  return rtrim(ltrim(s));
}

void
RestoreKeyboardBlocking(struct termios* initial_settings)
{
  tcsetattr(0, TCSANOW, initial_settings);
}

void
SetKeyboardNonBlock(struct termios* initial_settings)
{
  struct termios new_settings;
  tcgetattr(0, initial_settings);

  new_settings = *initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  new_settings.c_lflag &= ~ISIG;
  new_settings.c_cc[VMIN] = 0;
  new_settings.c_cc[VTIME] = 0;

  tcsetattr(0, TCSANOW, &new_settings);
}

void
print_help()
{
  cout << "Intention Repeater Nesting File Creation Utility v4.0." << endl;
  cout << "Created by Anthro Teacher aka Thomas Sweet (5/23/2021)." << endl
       << endl;
  cout << "https://www.intentionrepeater.com" << endl;
  cout << "https://forums.intentionrepeater.com" << endl << endl;

  cout << "Optional Flags:" << endl;
  cout << " a) -z or --zip, example: --zip" << endl;
  cout << " b) -n or --numfiles, example: --numfiles 10" << endl;
  cout << " c) -r or --numreps, example: --numreps 100" << endl;
  cout << " d) -h or --help, example: --help" << endl << endl;

  cout << "--zip = When provided, will create a NESTFILES.ZIP archive on the "
          "fly, and remove temporary N# files."
       << endl;
  cout << "--numfiles = Specify how many Nesting Files (N#) to create." << endl;
  cout << "--numreps = Specify how many times to reference each Nesting File "
       << endl;
  cout << "--help = Print this help." << endl << endl << std::flush;
}

int
main(int argc, char** argv)
{
  std::string num_files, num_repetitions, archive_7zip, build_string,
    create_filename, create_filename_1, command;

  std::string param_archive_7zip, param_num_files, param_num_repetitions;

  struct termios term_settings;

  long long int CHUNK_SIZE = 10;

  char c = 0;

  std::string prefix_7zip = "7z a -mmt2 -mx=9 NESTFILES.ZIP";
  std::fstream myfile;

  param_archive_7zip = "";
  param_num_files = "";
  param_num_repetitions = "";

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "-z") || !strcmp(argv[i], "--zip")) {
      param_archive_7zip = "Y";
    } else if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--numfiles")) {
      param_num_files = argv[i + 1];
    } else if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--numreps")) {
      param_num_repetitions = argv[i + 1];
    } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
      print_help();
      exit(EXIT_SUCCESS);
    }
  }

  cout << "Intention Repeater Nesting File Creation Utility v4.0." << endl;
  cout << "Created by Anthro Teacher (5/23/2021)." << endl;
  cout << "Note: 10 reps per file X 100 files = 1 Googol Repetitions per "
          "iteration!"
       << endl;
  cout << "Number of total Reps = (# reps per file) ^ (# files)." << endl
       << endl;
  cout << "Press 'q' key to quit when running." << endl << endl << std::flush;

  if (param_archive_7zip == "") {
    cout << "Archive into Zip? (y/N): ";
    std::getline(std::cin, archive_7zip);
    cout << endl;

  } else {
    archive_7zip = param_archive_7zip;
  }

  std::transform(
    archive_7zip.begin(), archive_7zip.end(), archive_7zip.begin(), ::toupper);

  if (param_num_files == "") {
    cout << "# of Nesting Files to create: ";
    std::getline(std::cin, num_files);
    cout << endl;
  } else {
    num_files = param_num_files;
  }

  if (param_num_repetitions == "") {
    cout << "# of Repetitions in each Nesting File: ";
    std::getline(std::cin, num_repetitions);
    cout << endl;
  } else {
    num_repetitions = param_num_repetitions;
  }

  SetKeyboardNonBlock(&term_settings);

  myfile.open("P0", ios::out);

  if (myfile.is_open()) {
    for (long long int repnum = 1; repnum <= stoll(num_repetitions); repnum++) {
      build_string = build_string + "INTENTIONS.TXT ";
    }

    try {
      myfile << build_string;
    } catch (...) {
      cout << "Error Writing to " << "P0" << endl << std::flush;
      RestoreKeyboardBlocking(&term_settings);
      exit(EXIT_FAILURE);
    }

  myfile.close();
  }

  for (long long int filenum = 0; filenum <= stoll(num_files); filenum++) {
    if (archive_7zip == "Y") {
      c = getchar();

      cout << "Adding File # " << trim(std::to_string(filenum)) << " / "
           << num_files << endl;

      if (c == 'q' || c == 'Q') {
        cout << "Program Terminated by Keypress." << endl << std::flush;
        RestoreKeyboardBlocking(&term_settings);
        exit(EXIT_SUCCESS);
      }

      create_filename = "P" + trim(std::to_string(filenum));
      create_filename_1 = "P" + trim(std::to_string(filenum - 1));

      try {
        myfile.open(create_filename, ios::out);
      } catch (...) {
        cout << "Error creating " << create_filename << endl << std::flush;
        RestoreKeyboardBlocking(&term_settings);
        exit(EXIT_FAILURE);
      }

      build_string = "";
      for (long long int repnum = 1; repnum <= stoll(num_repetitions);
           repnum++) {
        build_string += create_filename_1 + " ";
      }

      try {
        myfile << build_string;
      } catch (...) {
        cout << "Error Writing to " << create_filename << endl << std::flush;
        RestoreKeyboardBlocking(&term_settings);
        exit(EXIT_FAILURE);
      }

      myfile.close();

      if (filenum % CHUNK_SIZE == 0) {
        try {
          command = prefix_7zip + " P* >> logfile.txt";
          system(command.c_str());
        } catch (...) {
          cout << "Error updating NESTFILES.ZIP" << endl << std::flush;
          RestoreKeyboardBlocking(&term_settings);
          exit(EXIT_FAILURE);
        }

#ifdef _WIN32
        command = "del P* >nul 2>&1";
#else
        command = "rm -f P* >> logfile.txt";
#endif

        try {
          system(command.c_str());
        } catch (...) {
          cout << "Error removing temporary N# files" << endl << std::flush;
          RestoreKeyboardBlocking(&term_settings);
          exit(EXIT_FAILURE);
        }

        command = prefix_7zip + " P* >> logfile.txt";

        cout << "Updating NESTFILES.ZIP Archive" << endl;

        try {
          system(command.c_str());
        } catch (...) {
          cout << "Error adding files to NESTFILES.ZIP" << endl << std::flush;
          RestoreKeyboardBlocking(&term_settings);
          exit(EXIT_FAILURE);
        }

#ifdef _WIN32
        command = "del P* >nul 2>&1";
#else
        command = "rm -f P* >> logfile.txt";
#endif

        try {
          system(command.c_str());
        } catch (...) {
          cout << "Error removing N# files: " << endl << std::flush;
          RestoreKeyboardBlocking(&term_settings);
          exit(EXIT_FAILURE);
        }
      }
    } else {
      create_filename = "P" + trim(std::to_string(filenum));
      create_filename_1 = "P" + trim(std::to_string(filenum - 1));
      build_string = "";
      for (long long int repnum = 1; repnum <= stoll(num_repetitions);
           repnum++) {
        build_string += create_filename_1;
      }

      command = prefix_7zip + " P* >> logfile.txt";

      try {
        system(command.c_str());
      } catch (...) {
        cout << "Error adding files to NESTFILES.ZIP" << endl << std::flush;
        RestoreKeyboardBlocking(&term_settings);
        exit(EXIT_FAILURE);
      }

#ifdef _WIN32
      command = "del P* >nul 2>&1";
#else
      command = "rm -f P* >> logfile.txt";
#endif

      try {
        system(command.c_str());
      } catch (...) {
        cout << "Error removing P# files: " << endl << std::flush;
        RestoreKeyboardBlocking(&term_settings);
        exit(EXIT_FAILURE);
      }
    }
  }

  cout << "Intention Repeater Nesting Files Written." << endl << endl;
  cout << "Be sure to have your intentions in the INTENTIONS.TXT file." << endl
       << endl;

  if (archive_7zip == "N") {
    cout << "And use " << create_filename
         << " whatever nesting level you prefer, i.e. P25 for "
            "25 levels deep."
         << endl
         << endl;

  } else {
    cout << "And use NESTFILES.ZIP"
         << " in the Intention Repeater to utilize the full NEST stack." << endl
         << endl;
  }
  cout << std::flush;
  RestoreKeyboardBlocking(&term_settings);
  return 0;
}
