/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) : userPosts({})/* TODO(student): initialize */ {
  // TODO(student): implement constructor checks 
  if (userName == "") {
    throw std::invalid_argument("invalid username: empty");
  }
  else {
    for (size_t i = 0; i < userName.size(); i++) {
      if (islower(userName[i]) == false) {
        throw std::invalid_argument("invalid username: not lowercase");
      }
    }
  }
  User::userName = userName;
}

string User::getUserName() {
  return userName; // TODO(student): implement getter
}

vector<Post*>& User::getUserPosts() {
  return userPosts; // TODO(student): implement getter
}

void User::addUserPost(Post* post) {
  if (post == nullptr) {
    throw std::invalid_argument("Invalid Post: Nullptr");
  }
  userPosts.push_back(post); // TODO(student): add post to user posts
}
