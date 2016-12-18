#include <iostream>
#include <stack>          // std::stack
#include <vector>         // std::vector
#include <deque>          // std::deque
#include <memory>
#include <iterator>
#include <algorithm>

# include "tree.hpp"


std::string depthFirstSearch(std::unique_ptr<Tree<int>> root)
{
	std::stack<std::unique_ptr<Tree<int>>> Q;
	std::vector<std::unique_ptr<Tree<int>>> children;
	std::string path = "";

	Q.push(std::move(root));

	while(!Q.empty())
	{
		int v = const_cast<Tree<int>>
		auto t = makeTree( ( Q.top().value() );
		path += t.value();

		Q.pop();

		children = t.getChildren();
		std::reverse(children.begin(),children.end());

		for (int i = 0; i < children.size(); ++i){
			Q.push(children[i]);
		}
	}
	return path;
}

int main () {
	auto Root = makeTree (1);
	Root->add_child( makeTree (2) );
	Root->add_child( makeTree (3) );
	std::cout << Root -> size()<<std::endl;

	return 0;
}
