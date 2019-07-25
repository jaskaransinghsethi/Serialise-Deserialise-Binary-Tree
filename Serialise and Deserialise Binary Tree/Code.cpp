//////////////////////////////////////////////////////////////////////////////////
// Code.cpp       : Provides functions to serialise and deserialise binary Tree //
// ver 1.0																		//
//																				//
// Application    : Serialise/Deserialise Binary Tree                           //
// Platform       : Visual Studio 2019 Community Edition                        //
//                  Windows 10 Professional 64-bit, Acer Aspire R5-571TG        //
// Author         : Jaskaran Singh, EECS Department, Syracuse University        //
//                  315-925-9941, jsingh09@syr.edu							    //
//////////////////////////////////////////////////////////////////////////////////

/*
* Design an algorithm to serialize and deserialize a binary tree. There is no restriction 
* on how your serialization/deserialization algorithm should work. You just need to ensure 
* that a binary tree can be serialized to a string and this string can be deserialized to 
* the original tree structure.
*
*/

#include <iostream>
#include <list>
#include <string>

using namespace std;

//Definition of Binary Tree
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v) : val(v), left(NULL), right(NULL) { }
};

//Helper function to serialise binary tree by converting preorder tree traversal to string
void serialiseHelperFn(TreeNode* node, string& str)
{
	if (!node)
	{
		str += "null,";
		return;
	}
	else {
		str += to_string(node->val) + ",";
		serialiseHelperFn(node->left, str);
		serialiseHelperFn(node->right, str);
	}
}

//Helper function to split a string into list of string, given a delimiter
list<string> split(string& str, char delimiter)
{
	if (str == "")
		return list<string>();
	list<string> strings;
	string temp;
	for (auto& ch : str)
	{
		if (ch == delimiter)
		{
			strings.push_back(temp);
			temp = "";
		}
		else
			temp += ch;
	}
	if (temp.size() > 0)
		strings.push_back(temp);
	return strings;
}

//Serialise binary tree to string using preorder traversal
string serialiseBinaryTree(TreeNode* root)
{
	if (!root)
		return "null";
	string str = "";
	serialiseHelperFn(root, str);
	return str;
}

//Helper function to deserialise the list of strings into binary tree
TreeNode* deserialiseHelperFn(list<string> &strings)
{
	if (strings.size() == 0)
		return nullptr;

	if (strings.front() == "null")
	{
		strings.pop_front();
		return nullptr;
	}

	TreeNode* node = new TreeNode(stoi(strings.front()));
	strings.pop_front();
	node->left = deserialiseHelperFn(strings);
	node->right = deserialiseHelperFn(strings);
	return node;
}

//Deserialise string into binary tree
TreeNode* deserialiseBinaryTree(string data)
{
	if (data == "")
		return nullptr;
	list<string> strings = split(data, ',');
	return deserialiseHelperFn(strings);
}

//Preorder traversal of binary Tree
void preorder(TreeNode* root)
{
	if (root == nullptr)
		return;
	cout << root->val << "\n";
	preorder(root->left);
	preorder(root->right);
}

//Main function to demonstrate the functionality
int main() {
	TreeNode root(1), l1(2), r1(3), l2(4), r2(5);
	root.left = &l1;
	root.right = &r1;
	r1.left = &l2;
	r1.right = &r2;
	string str = serialiseBinaryTree(&root);
	TreeNode* node = deserialiseBinaryTree(str);
	preorder(node);
	getchar();
}