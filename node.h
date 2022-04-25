

typedef struct node{
	char data;
	int frequency;
	struct node *next;
	struct node *left;
	struct node *right;
	int is_leaf;
}node;


node* create_node(){
	node *new_node = malloc(sizeof(node));
	new_node->data = 0;
	new_node->frequency = 0;
	new_node->next = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->is_leaf = 0;
}


