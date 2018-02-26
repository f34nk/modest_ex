// // #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>
// #include "erl_interface.h"
// #include "ei.h"
// #include "Document.h"
// #include "Node.h"

#include "modest.h"

// static std::string& implode(const std::vector<std::string>& elems, char delim, std::string& s)
// {
//     for (std::vector<std::string>::const_iterator ii = elems.begin(); ii != elems.end(); ++ii)
//     {
//         s += (*ii);
//         if ( ii + 1 != elems.end() ) {
//             s += delim;
//         }
//     }

//     return s;
// }

// static std::string implode(const std::vector<std::string>& elems, char delim)
// {
//     std::string s;
//     return implode(elems, delim, s);
// }

// const std::string gumbo_query::find(const std::string html, const std::string selector){
//   std::string page(html);
//   CDocument doc;
//   doc.parse(page.c_str());

//   CSelection c = doc.find(selector);

//   // std::vector<std::string> result;
//   // for(int i = 0; i < c.nodeNum(); i++){
//   //   CNode node = c.nodeAt(i);
//   //   //result.push_back(node.parent().ownText());
//   //   //result.push_back(page.substr(node.startPos(), node.endPos() - node.startPos()));
//   //   result.push_back(page.substr(node.startPosOuter(), node.endPosOuter() - node.startPosOuter()));
//   // }
//   // return implode(result, ',');

//   std::stringstream result;
//   for(int i = 0; i < c.nodeNum(); i++){
//     CNode node = c.nodeAt(i);
//     // result << page.substr(node.startPos(), node.endPos() - node.startPos());
//     result << page.substr(node.startPosOuter(), node.endPosOuter() - node.startPosOuter());
//   }
//   return result.str();
// }
