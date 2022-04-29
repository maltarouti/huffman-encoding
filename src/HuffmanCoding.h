

FILE* _open_file(char path[], char mode[]){
	FILE* ptr;
	ptr = fopen(path, mode);
	
	if(ptr == NULL){
		printf("File could not be opened\n");
		return NULL;
	}
	return ptr;	
}

queue* count_frequency(char path[]){
	FILE* ptr = _open_file(path, "rb");
	queue *q = create_queue();
	
	array* characters = create_array();
	
	char current = fgetc(ptr);
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


void get_path(char data,
			   node* root,
			   char path[],
			   char buffer[]){
	if(root->data == data && root->is_leaf == 1){
		strcpy(buffer, path);
	}

	if(root->left != NULL){
		char left[] = "";
		strcpy(left, path);
		strcat(left, "0");
		get_path(data, root->left, left, buffer);
	}

	if(root->right != NULL){
		char right[] = "";
		strcpy(right, path);
		strcat(right, "1");
		get_path(data, root->right, right, buffer);
	}
}


void compress(char source_path[],
			  char destination_path[],
			  node* root){
		
	// Reading the source
	FILE* source = _open_file(source_path, "rb");
	char current = fgetc(source);
	
	// Writing the header of the compressed file
	// TODO: ...
	// 4-bytes: total number of chars in the compressed file
	// 4-bytes: total number of chars in the header
	// 4-bytes: total number of chars in uncompressed file
	// 12-bytes: For the huffman tree
	// Writing the compressed file
	char byte = 0;
	int count = 0;
	while(current != EOF){
		char buffer[] = "";
		get_path(current, root, "", buffer);
		
		int i;
		int buffer_size = sizeof(buffer)/sizeof(char);
		for(i=0; i<buffer_size; i++){
			// if the byte is full
			if(count == 8){
				// Write the byte to the file
				FILE* destination = _open_file(destination_path, "ab");
				fwrite(&byte, sizeof(char*), 1, destination);
				fclose(destination);
				
				// Reset the byte
				count = 0;
				byte = 0;
			}
			
			// Add to the byte
			if(buffer[i] == '1'){
				byte |= 1;
				byte <<= 1;
				count++;
			}
			else{
				byte <<=1;
				count++;
			}
		}
		current = fgetc(source);
	}
	fclose(source);
}

void print_tree(node* root, int level){
	if(root != NULL){
		print_tree(root->right, level+1);
		int indent = level * 4;
		char prefix[] = " ";
		
		int i;
		for(i=0; i<indent; i++){
			strcat(prefix, " ");
		}
		if(root->data){
			strcat(prefix, "|-");
		}
		else{
			strcat(prefix, "---->");
		}
		
		printf("%s%c[%d]\n", prefix, root->data, root->frequency);	
		print_tree(root->left, level+1);
	}
}

int encode(char path[], char destination[]){
	queue* q = count_frequency(path);
	node* root = build_tree(q);
	compress(path, destination, root);
	return 0;
}
	







