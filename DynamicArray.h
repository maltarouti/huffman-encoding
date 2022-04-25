

typedef struct element{
	char data;
	int frequency;
	struct element* next;
}element;


typedef struct array{
	element* head;
	element* tail;
	int size;
}array;


array* create_array(){
	array* new_array = malloc(sizeof(array));
	new_array->head = NULL;
	new_array->tail = NULL;
	new_array->size = 0;
}

element* create_element(){
	element* new_element = malloc(sizeof(element));
	new_element->data = 0;
	new_element->frequency=1;
	new_element->next = NULL;
}

void append(array* a, char data){
	element* new_element = create_element();
	new_element->data = data;
	
	if(a->size == 0){
		a->head = a->tail = new_element;
	}
	else{
		a->tail->next = new_element;
		a->tail = a->tail->next;	
	}
	a->size++;
}

int insert(array* a, 
			char data, 
			int index)
{
	if(index > (a->size-1) || index < 0){
		return 0;
	}
	
	element* new_element = create_element();
	new_element->data = data;
			
	if(index == 0){
		new_element->next = a->head;
		a->head=new_element;
	}
	else{
		int count = 0;
		element* current = create_element();
		current = a->head;
		while(count != index-1){
			current = current->next;
			count++;
		}
	
		new_element->next = current->next;
		current->next = new_element;
		current = NULL;
		free(current);
	}
	a->size++;
	return 1;
}


element* pop(array* a, int index){
	if(index > a->size-1 || index < 0){
		return 0;
	}
	
	element* current = create_element();
	element* found = create_element();
	current = a->head;
	
	if(index == 0){
		current = a->head;
		a->head = a->head->next;
		found = current;
	}
	else if(index == a->size-1){
		while(current->next != a->tail){
			current = current->next;
		}	
		element* found = create_element();
		found = current->next;
		current->next = NULL;
	}
	else{
		int count = 0;
		while(count+1 != index){
			current = current->next;
		}
		element* found =  create_element();
		found = current;
		current->next = current->next->next;		
	}
	current = NULL;
	free(current);
	a->size--;	
	return found;
}

int len(array *a){
	return a->size;
}


int find_index(array *a, char data){	
	element* current = create_element();
	current = a->head;
	
	int index = 0;
	while(current != NULL){
		if(current->data == data){
			current = NULL;
			free(current);
			return index;
		}
		current = current->next;
		index++;
	}
	current = NULL;
	free(current);
	return -1;
}

int get_frequency(array *a, char data){	
	element* current = create_element();
	current = a->head;
	
	while(current != NULL){
		if(current->data == data){
			int frequency = current->frequency;
			current = NULL;
			free(current);
			return frequency;
		}
		current = current->next;
	}
	current = NULL;
	free(current);
	return -1;
}


int update_frequency(array *a, 
					int index,
					int frequency){
	
	element* current = create_element();
	current = a->head;
	
	int count = 0;
	while(index != count && current != NULL){
		current = current->next;
		count += 1;	
	}
	
	if(current == NULL){
		current = NULL;
		free(current);
		return 0;
	}
	else{
		current->frequency = frequency;	
		current = NULL;
		free(current);
		return 1;
	}
}

void print_array(array* a){
	if(len(a) == 0){
		printf("The array is empty");
		return;
	}
	
	element* temp = a->head;
	while(temp != NULL){
		if(temp->next != NULL){
			printf("%c [%d] -> ", temp->data, temp->frequency);
		}
		else{
			printf("%c [%d] -> NULL\n", temp->data, temp->frequency);	
		}
		temp = temp->next;
	}
	temp = NULL;
	free(temp);
}




