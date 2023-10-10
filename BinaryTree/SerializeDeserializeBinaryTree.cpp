#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

string serialize(TreeNode* root) {
    if (root == nullptr) {
        return "null";
    }

    string result = to_string(root->val);
    result += "," + serialize(root->left);
    result += "," + serialize(root->right);

    return result;
}

TreeNode* deserialize(string data) {
    stringstream ss(data);
    string token;
    queue<string> tokens;

    while (getline(ss, token, ',')) {
        tokens.push(token);
    }

    function<TreeNode*()> buildTree = [&]() -> TreeNode* {
        string val = tokens.front();
        tokens.pop();

        if (val == "null") {
            return nullptr;
        }

        TreeNode* node = new TreeNode(stoi(val));
        node->left = buildTree();
        node->right = buildTree();

        return node;
    };

    return buildTree();
}

void inorderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    string serializedTree = serialize(root);
    cout << "Serialized Tree: " << serializedTree << endl;

    TreeNode* deserializedRoot = deserialize(serializedTree);

    cout << "Inorder Traversal of Deserialized Tree: ";
    inorderTraversal(deserializedRoot);

    return 0;
}
