// Intention Repeater Nesting Utility created by Anthro Teacher aka Thomas
// Sweet. May 22, 2021. Version 3.0

#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
  std::string num_files, num_repetitions, archive_7zip, build_string,
      chunk_size, create_filename, build_chunk, build_chunk_2;
  int repnum, filenum;
  std::fstream myfile;

  cout << "Intention Repeater Nesting File Creation Utility v3.0." << endl;
  cout << "Created by Anthro Teacher (5/22/2021)." << endl;
  cout << "Note: 10 reps per file X 100 files = 1 Googol Repetitions per "
          "iteration!"
       << endl;
  cout << "Number of total Reps = (# reps per file) ^ (# files)." << endl
       << endl;

  cout << "Archive into 7zip? (y/N): ";
  std::getline(std::cin, archive_7zip);

  if (archive_7zip != "Y" && archive_7zip != "y") {
    cout << "Filename you would like to use in the Repeater for Nesting (Not "
            "INTENTIONS.TXT): ";
    std::getline(std::cin, create_filename);
    archive_7zip = "N";

  } else {
    archive_7zip = "Y";
  }

  cout << endl;

  cout << "How many nesting files to create: ";
  std::getline(std::cin, num_files);

  cout << endl;

  cout << "How many repetitions in each file: ";
  std::getline(std::cin, num_repetitions);

  cout << endl;

  cout << "How many files to write at a time: ";
  std::getline(std::cin, chunk_size);

  cout << endl;

  myfile.open("NEST-0.TXT", ios::out);

  build_string = "";

  if (myfile.is_open()) {
    for (repnum = 1; repnum <= stoi(num_repetitions); repnum++) {
      build_string += "INTENTIONS.TXT\r\n";
    }
    myfile << build_string;
  }

  myfile.close();

  if (archive_7zip == "Y") {
    cout << "Adding File # 0 / " << num_files << endl;
    system("7z a -mmt2 -mx=9 NESTFILES.ZIP NEST-0.TXT >> logfile.txt");
    system("rm NEST-0.TXT >> logfile.txt");
  }

  for (filenum = 1; filenum <= stoi(num_files); filenum++) {
      create_filename = "NEST-" + std::to_string(filenum) + ".TXT";
      myfile.open(create_filename, ios::out);

      build_string = "";
      for (repnum = 1; repnum <= stoi(num_repetitions); repnum++) {
        build_string += "NEST-" + std::to_string(filenum - 1) + ".TXT\r\n";
      }
      myfile << build_string;
      myfile.close();
      build_chunk += " NEST-" + std::to_string(filenum) + ".TXT";
      build_chunk_2 += " NEST-" + std::to_string(filenum) + ".TXT";

      if (archive_7zip == "Y") {
        if (filenum % stoi(chunk_size) == 0) {
          build_chunk_2 = "7z a -mmt2 -mx=9 NESTFILES.ZIP" + build_chunk +
                          " >> logfile.txt";

          system(build_chunk_2.c_str());

          build_chunk_2 = "rm" + build_chunk + " >> logfile.txt";

          system(build_chunk_2.c_str());

          build_chunk = "";
          build_chunk_2 = "";
        }

        cout << "Adding File # " << std::to_string(filenum) << " / "
             << num_files << endl;
      }

    build_chunk_2 = "7z a -mmt2 -mx=9 NESTFILES.ZIP" + build_chunk +
                " >> logfile.txt";

    system(build_chunk_2.c_str());

    build_chunk_2 = "rm" + build_chunk + " >> logfile.txt";

    system(build_chunk_2.c_str());

    build_chunk = "";
    build_chunk_2 = "";
  }

  cout << "Intention Repeater Nesting Files Written." << endl << endl;

  cout << "Be sure to have your intentions in the INTENTIONS.TXT file." << endl
       << endl;

  if (archive_7zip == "N") {

    cout << "And use " << create_filename
         << " in the Intention Repeater to utilize the full NEST stack." << endl
         << endl;

  } else {
    cout << "And use NESTFILES.ZIP in the Intention Repeater to utilize the "
            "full "
            "NEST stack."
         << endl
         << endl;
  }

  return 0;
}
