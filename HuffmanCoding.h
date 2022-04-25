

FILE* read_file(char path[]){
	FILE* ptr;
	ptr = fopen(path, "r");
	
	if(ptr == NULL){
		printf("File could not be opened\n");
	}
	return ptr;	
}


queue* count_frequency(FILE *ptr){	
	queue *q = create_queue();
	char current;
	
	array* characters = create_array();
	
	current = fgetc(ptr);
	while(current != EOF){
		int character_index = find_index(characters, current);
		
		if(character_index != -1){
			int frequency = get_frequency(characters, current) + 1;
			update_frequency(characters, character_index, frequency);
		}
		else{
			append(characters, current);
		}				
		
		current = fgetc(ptr);
	}

	while(characters->size != 0){
		element* e = pop(characters, 0);
		enqueue(q, e->data, e->frequency);
		e = NULL;
		free(e);
	}
	
	fclose(ptr);
	characters = NULL;
	free(characters);
	return q;	
}


node* build_tree(queue* q){	
	while(q->size != 1){
		node* left_node = dequeue(q);
		left_node->is_leaf = 1;
		
		node* right_node = dequeue(q);
		right_node->is_leaf = 1;
		
		int frequency = left_node->frequency + right_node->frequency;
		
		node* shared_node = create_node();
		shared_node->frequency = frequency;
		shared_node->left = left_node;
		shared_node->right = right_node;
		enqueue_node(q, shared_node);
	}
	node* root = dequeue(q);
	return root;
}


void print_tree(node* root, int level){
	if(root != NULL){
		print_tree(root->left, level+1);
		// TODO: do the print(" "*level*4 + root.data);
		print_tree(root->right, level+1);
	}
}

int encode(char path[]){
	FILE* ptr = read_file(path);
	queue* q = count_frequency(ptr);
	node* root = build_tree(q);
	print_tree(root, 0);
	return 0;
}
	







