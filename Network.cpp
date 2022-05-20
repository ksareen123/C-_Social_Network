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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;
using std::exception;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  std::ifstream file(fileName);
  if (!file.is_open()) {
    throw std::invalid_argument("Invalid File: File could not be opened");
  }
  string type = "";
  unsigned int ID = 0;
  string name = "";
  string text = "";
  string garbage = "";
  while (!file.eof()) {
    file >> type;
    //std::cout << "checking type " << type << std::endl;
    if (type == "Post") {
      file >> ID >> name;
      getline(file, text);
      //std::cout << ID << " " << name << " " << text << std::endl;
      try {
        //std::cout << "Creating Post (ID: " << ID << ")" << std::endl;
        addPost(ID, name, text);
      }
      catch (exception& ex) {
        throw std::runtime_error("Invalid Post");
      }
    }
    else if (type == "User") {
      file >> name;
      getline(file, garbage);
      //std::cout << "Attempting to create User " << name << std::endl;
      try {
        addUser(name);
      }
      catch (exception& ex) {
        throw std::runtime_error("Invalid User");
      }
    }
    else if (!file.fail()){
      throw std::runtime_error("Invalid FIle: Incorrect format");
    }
    type = "";
    ID = 0;
    name = "";
    text = "";
    garbage = "";
  }
  // TODO(student): load user and post information from file
}

void Network::addUser(string userName) {
  for (size_t j = 0; j < userName.length(); j++) {
    userName[j] = tolower(userName[j]);
  }
  //std::cout << userName << std::endl;
  for (size_t i = 0; i < users.size(); i++) {
    string checkname = users.at(i)->getUserName();
    if (checkname == userName) {
      throw std::invalid_argument("User Already Exists");
    }
  }

  User* my_user = new User(userName);
  users.push_back(my_user);
  std::cout << "Added User " << userName << std::endl;
  // TODO(student): create user and add it to network
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  for (size_t i = 0; i < posts.size(); i++) {
    unsigned int check = posts.at(i)->getPostId();
    //std::cout << "Checking " << postId << " against ID " << check << std::endl;
    if (check == postId) {
      throw std::invalid_argument("Invalid Post: Post ID already in system");
    }
  }
  //std::cout << "Valid post ID " << postId << std::endl;
  bool user_exists = false;
  size_t j = 0;
  for (j = 0; j < users.size(); j++) {
    if (users[j]->getUserName() == userName) {
      user_exists = true;
      break;
    }
  }
  if (!user_exists) {
    throw std::invalid_argument("Invalid Post: User doesn't exist");
  }
  //std::cout << "Valid Username: " << userName << std::endl;

  Post* mypost = new Post(postId, userName, postText);
  posts.push_back(mypost);
  users.at(j)->addUserPost(mypost);

  vector<string> mytags;
  mytags = mypost->findTags();

  for (size_t k = 0; k < mytags.size(); k++) {
    try {
      string current_tag = mytags.at(k);
      //std::cout << "Checking tag: " << current_tag << std::endl;
      bool unique_t = true;
      for (size_t n = 0; n < tags.size(); n++) {
        if (tags.at(n)->getTagName() == current_tag) {
          unique_t = false;
          tags.at(n)->addTagPost(mypost);
          break;
        }
      }
      if (unique_t) {
        //std::cout << "Tag is Unique" << std::endl;
        Tag* mytag;
        mytag = new Tag(current_tag);
        mytag->addTagPost(mypost);
        tags.push_back(mytag);
      }
      //std::cout << "Adding post to tag" << std::endl;
    }
    catch(exception& ex) {
      //std::cout << "Bad tag. Continuing..." << std::endl;
      continue;
    }
  }
  std::cout << "Added Post " << postId << " by " << userName << std::endl;
  // TODO(student): create post and add it to network
}

vector<Post*> Network::getPostsByUser(string userName) {
  vector<Post*> filtered;

  for (size_t i = 0; i < posts.size(); i++) {
    if (posts.at(i)->getPostUser() == userName) {
      filtered.push_back(posts.at(i));
    }
  }
  
  return filtered;// TODO(student): return posts created by the given user
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  vector<Post*> filtered;
  if (tagName == "") {
    throw std::invalid_argument("Invalid hashtag");
  }
  bool exists = false;
  for (Tag* t : tags) {
    if (t->getTagName() == tagName) {
      //std::cout << tagName << " is in database." << std::endl;
      //std::cout << t->getTagPosts().size() << std::endl;
      exists = true;
      for (Post* p : t->getTagPosts()) {
        //std::cout << p->getPostText() << std::endl;
        filtered.push_back(p);
      }
    }
  }
  if (exists == false) {
    filtered = {};
  }

  return filtered;// TODO(student): return posts containing the given tag
}

vector<string> Network::getMostPopularHashtag() {
  vector<string> pop_tags;
  vector<size_t> tag_data;
  if (tags.size() == 0) {
    pop_tags = {};
  }
  else {
    for (size_t i = 0; i < tags.size(); i++) {
      string name = tags.at(i)->getTagName();
      size_t popularity = getPostsWithTag(name).size();
      //std::cout << name << " is used by " << popularity << " posts." << std::endl;
      tag_data.push_back(popularity);
    }
    size_t max = tag_data.at(0);
    for (size_t i = 0; i < tag_data.size(); i++) {
      if (tag_data.at(i) > max) {
        max = tag_data.at(i);
        //std::cout << "max =" << max << std::endl;
      }
    }
    //std::cout << "Tags with " << max << "occurences will be used: " << std::endl;
    for (size_t n = 0; n < tag_data.size(); n++) {
      if (tag_data.at(n) == max) {
        pop_tags.push_back(tags.at(n)->getTagName());
        //std::cout << tags.at(n)->getTagName() << std::endl;
      }
    }
  }
  return pop_tags;
  // TODO(student): return the tag occurring in most posts
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
