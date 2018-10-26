/**
 * @file SplayTree.hpp
 * @author George Fotopoulos
 */

#pragma once

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <queue>
#include <utility>

namespace forest {
	template <typename Key, typename Value>
	class SplayTree {
	private:
		class SplayTreeNode {
			friend class SplayTree;

		private:
			SplayTreeNode * parent{ nullptr };
			SplayTreeNode * left{ nullptr };
			SplayTreeNode * right{ nullptr };

		public:
			Key key;
			Value value;

		public:
			SplayTreeNode() = default;
			SplayTreeNode(const Key & KEY, const Value & VALUE) : key(KEY), value(VALUE) { }
			SplayTreeNode(const SplayTreeNode &) = delete;
			SplayTreeNode(SplayTreeNode &&) = delete;
			SplayTreeNode& operator=(const SplayTreeNode &) = delete;
			SplayTreeNode& operator=(SplayTreeNode &&) = delete;
			~SplayTreeNode() = default;
		};

	private:
		SplayTreeNode * tree_root{ nullptr };

	private:
		void pre_order_traversal(const SplayTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			handler(root->key, root->value);
			pre_order_traversal(root->left, handler);
			pre_order_traversal(root->right, handler);
		}
		void in_order_traversal(const SplayTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			in_order_traversal(root->left, handler);
			handler(root->key, root->value);
			in_order_traversal(root->right, handler);
		}
		void post_order_traversal(const SplayTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			post_order_traversal(root->left, handler);
			post_order_traversal(root->right, handler);
			handler(root->key, root->value);
		}
		void breadth_first_traversal(const SplayTreeNode * root, void handler(const Key & key, const Value & value)) noexcept {
			if (!root) return;
			std::queue <const SplayTreeNode *> queue;
			queue.push(root);
			while (!queue.empty()) {
				SplayTreeNode * root{ queue.front() };
				handler(root->key, root->value);
				queue.pop();
				if (root->left) queue.push(root->left);
				if (root->right) queue.push(root->right);
			}
		}

	private:
		SplayTreeNode * minimum(SplayTreeNode * root) noexcept {
			if (!root) return nullptr;
			while (root->left) root = root->left;
			return root;
		}
		SplayTreeNode * maximum(SplayTreeNode * root) noexcept {
			if (!root) return nullptr;
			while (root->right) root = root->right;
			return root;
		}

	private:
		int height(const SplayTreeNode * root) noexcept {
			if (!root) return 0;
			return std::max(height(root->left), height(root->right)) + 1;
		}
		int size(const SplayTreeNode * root) noexcept {
			if (!root) return 0;
			return size(root->left) + size(root->right) + 1;
		}

	private:
		void rotate_right(SplayTreeNode * rotation_root) noexcept {
			SplayTreeNode * new_root{ rotation_root->left };
			SplayTreeNode * orphan_subtree{ new_root->right };
			rotation_root->left = orphan_subtree;
			if (orphan_subtree) {
				orphan_subtree->parent = rotation_root;
			}
			new_root->right = rotation_root;
			if (!rotation_root->parent) {
				tree_root = new_root;
			}
			else if (rotation_root == rotation_root->parent->left) {
				rotation_root->parent->left = new_root;
			}
			else if (rotation_root == rotation_root->parent->right) {
				rotation_root->parent->right = new_root;
			}
			new_root->parent = rotation_root->parent;
			rotation_root->parent = new_root;
		}
		void rotate_left(SplayTreeNode * rotation_root) noexcept {
			SplayTreeNode * new_root{ rotation_root->right };
			SplayTreeNode * orphan_subtree{ new_root->left };
			rotation_root->right = orphan_subtree;
			if (orphan_subtree) {
				orphan_subtree->parent = rotation_root;
			}
			new_root->left = rotation_root;
			if (!rotation_root->parent) {
				tree_root = new_root;
			}
			else if (rotation_root == rotation_root->parent->left) {
				rotation_root->parent->left = new_root;
			}
			else {
				rotation_root->parent->right = new_root;
			}
			new_root->parent = rotation_root->parent;
			rotation_root->parent = new_root;
		}

	private:
		void fix(SplayTreeNode * root) noexcept {
			while (root->parent) {
				if (!root->parent->parent) {
					if (root->parent->left == root) {
						rotate_right(root->parent);
					}
					else if (root->parent->right == root) {
						rotate_left(root->parent);
					}
				}
				else if (root->parent->left == root && root->parent->parent->left == root->parent) {
					rotate_right(root->parent->parent);
					rotate_right(root->parent);
				}
				else if (root->parent->right == root && root->parent->parent->right == root->parent) {
					rotate_left(root->parent->parent);
					rotate_left(root->parent);
				}
				else if (root->parent->left == root && root->parent->parent->right == root->parent) {
					rotate_right(root->parent);
					rotate_left(root->parent);
				}
				else if (root->parent->right == root && root->parent->parent->left == root->parent) {
					rotate_left(root->parent);
					rotate_right(root->parent);
				}
			}
		}

	private:
		void destroy(SplayTreeNode * root) {
			if (!root) return;
			if (root->left != nullptr) destroy(root->left);
			if (root->right != nullptr) destroy(root->right);
			delete root;
			root = nullptr;
		}

	public:
		SplayTree() = default;
		explicit SplayTree(std::initializer_list <std::pair <Key, Value> > list) {
			for (auto element : list) {
				insert(element.first, element.second);
			}
		}
		SplayTree(const SplayTree &) = delete;
		SplayTree(SplayTree &&) = delete;
		SplayTree& operator=(const SplayTree &) = delete;
		SplayTree& operator=(SplayTree &&) = delete;
		~SplayTree() {
			destroy(tree_root);
		}

	public:
		void pre_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			pre_order_traversal(tree_root, handler);
		}
		void in_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			in_order_traversal(tree_root, handler);
		}
		void post_order_traversal(void handler(const Key & key, const Value & value)) noexcept {
			post_order_traversal(tree_root, handler);
		}
		void breadth_first_traversal(void handler(const Key & key, const Value & value)) noexcept {
			breadth_first_traversal(tree_root, handler);
		}

	public:
		SplayTreeNode * minimum() noexcept {
			return minimum(tree_root);
		}
		SplayTreeNode * maximum() noexcept {
			return maximum(tree_root);
		}

	public:
		int height() noexcept {
			return height(tree_root);
		}
		int size() noexcept {
			return size(tree_root);
		}

	public:
		void insert(const Key & key, const Value & value) noexcept {
			SplayTreeNode * current{ tree_root };
			SplayTreeNode * parent{ nullptr };
			while (current) {
				parent = current;
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
				else if (key == current->key) {
					current->value = value;
					return;
				}
			}
			current = new SplayTreeNode(key, value);
			current->parent = parent;
			if (!parent) {
				tree_root = current;
			}
			else if (current->key > parent->key) {
				parent->right = current;
			}
			else if (current->key < parent->key) {
				parent->left = current;
			}
			fix(current);
		}
		SplayTreeNode * search(const Key & key) noexcept {
			SplayTreeNode * current{ tree_root };
			while (current) {
				if (key > current->key) {
					current = current->right;
				}
				else if (key < current->key) {
					current = current->left;
				}
				else {
					return current;
				}
			}
			return nullptr;
		}
	};
}
