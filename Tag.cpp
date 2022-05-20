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
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) /* TODO(student): initialize */ {
  if (tagName.length() < 2 ) {
    throw std::invalid_argument("Invalid tag: Tag too small");
  }
  else if (tagName[0] != '#') {
    throw std::invalid_argument("Invalid tag: no hash");
  }
  else {
    for (size_t i = 1; i < tagName.size(); i++) {
      if (islower(tagName[i]) == false) {
        throw std::invalid_argument("Invalid tag: not lowercase");
      }
    }
  }
  Tag::tagName = tagName; // TODO(student): implement constructor checks
}

string Tag::getTagName() {
  return tagName;// TODO(student): implement getter
}

vector<Post*>& Tag::getTagPosts() {
  return tagPosts;// TODO(student): implement getter
}

void Tag::addTagPost(Post* post) {
  if (post == nullptr) {
    throw std::invalid_argument("Invalid Post: Nullptr");
  }
  //std::cout << "adding post" << std::endl;
  tagPosts.push_back(post);
  vector <Post*> tagposts = this->getTagPosts();
  for (Post* p : tagposts) {
    //std::cout << p->getPostText() << std::endl;
  }// TODO(student): add post to tag posts
}
