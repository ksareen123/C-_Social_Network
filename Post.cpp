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
#include <sstream>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  vector<string> tags;
  string text = this->getPostText(); 
  string test = "";
  //std::cout << "searching through: " << text << std::endl;
  std::istringstream wordinput(text);
  wordinput >> test;
  while(!wordinput.fail()) {
    //std::cout << test << std::endl;
    if (test[0] == '#') {
      //std::cout << "Found hashtag candidate: " << test << std::endl;
      size_t i = 0;
      string real = "";
      while(test[i] != '!' && test[i] != '?' && test[i] != '.' && test[i] != ',' && i < test.length()) {
        real += tolower(test[i]);
        i++;
      }
      bool is_unique = true;
      for (size_t i = 0; i < tags.size(); i++) {
        if (tags.at(i) == real) {
          is_unique = false;
        }
      }
      if (is_unique == true) {
        //std::cout << "unique hashtag found, inserting " << std::endl;
        tags.push_back(real);
      }
    }
    wordinput >> test;
  }
  
  return tags;// TODO(student): extracts candidate tags based on occurrences of # in the post
}
