/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "Network.h"

using std::cout, std::cin, std::endl;
using std::string, std::vector;

void printMenu() {
  cout << "Welcome to CPPeers" << endl;
  cout << "The options are: " << endl;
  cout << "1. load data file and add information" << endl;
  cout << "2. show posts by user" << endl;
  cout << "3. show posts with hashtag" << endl;
  cout << "4. show most popular hashtag" << endl;
  cout << "9. quit" << endl;
  cout << "--------> Enter your option: ";
}

void processLoad(Network& cppeers) {
  string fileName = "";
  cout << "Enter filename: ";
  cin >> fileName;
  cppeers.loadFromFile(fileName);
}

void processPostsByUser(Network& cppeers) {
  string userName = "";
  cout << "Enter username:";
  cin >> userName;
  std::vector<Post*> myposts;
  myposts = cppeers.getPostsByUser(userName);
  for (size_t i = 0; i < myposts.size(); i++) {
    string text = myposts.at(i)->getPostText();
    //std::cout << i+1 << ":" << text << std::endl;
    std::cout << text << std::endl;
  }
  // TODO(student): implement

}

void processPostsWithHashtags(Network& cppeers) {
  string tag = "";
  cout << "Enter tagname:";
  cin >> tag;
  //std::cout << (cppeers.getPostsWithTag(tag)).size() << " posts found. " << std::endl;
  for (Post* p : cppeers.getPostsWithTag(tag)) {
    //std::cout << "turn" << std::endl;
    string text = p->getPostText();
    std::cout << text << std::endl;
  }
  // TODO(student): implement
}

void processMostPopularHashtag(Network& cppeers) {
  std::vector<string> mytags;
  mytags = cppeers.getMostPopularHashtag();
  for (size_t k = 0; k < mytags.size(); k++) {
    //std::cout << k + 1 << ":" << mytags.at(k) << std::endl;
    std::cout << mytags.at(k) << std::endl;
  }
  // TODO(student): implement
}

int main() {

  try {
    Network cppeers;

    int choice = 0;

    // present menu
    do {
      printMenu();
      cin >> choice;
      switch(choice) {
        case 1: {
          processLoad(cppeers);
          break;
        }
        case 2: {
          processPostsByUser(cppeers);
          break;
        }
        case 3: {
          processPostsWithHashtags(cppeers);
          break;
        }
        case 4: {
          processMostPopularHashtag(cppeers);
          break;
        }
      }
    } while (choice != 9);
  } catch (std::exception& exc) {
    std::cout << exc.what() << endl;
  }

  return 0;
}
