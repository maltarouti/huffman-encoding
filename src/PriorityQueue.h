

typedef struct queue{
	node *head;
	node *tail;
	int size;
}queue;


queue* create_queue(){
	queue *q = malloc(sizeof(queue));
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}


int get_size(queue *q){
	return(q->size);
}


int is_empty(queue *q){
	return(q->size == 0);
}


int enqueue(queue *q, 
			char data, 
			int frequency)
{
	node *new_node = create_node();
	new_node->data = data;
	new_node->frequency = frequency;
	new_node->next = NULL;

	if(q->head == NULL){
		q->head = new_node;
		q->tail = q->head;
	}
	else if(new_node->frequency > q->head->frequency){
		new_node->next = q->head;
		q->head = new_node;
	}
	else{
		node *current = create_node();
		current = q->head;
		
		while(current != NULL){
			if(current->next == NULL || current->next->frequency < frequency){	
				new_node->next = current->next;
				current->next = new_node;
				
				if(new_node->next == NULL){
					q->tail = new_node;
				}
				break;	
			}
			current = current->next;
		}
		current = NULL;
		free(current);
	}
	
	q->size++;
	return 1;
}


int enqueue_node(queue *q, node* new_node){
	if(q->head == NULL){
		q->head = new_node;
		q->tail = q->head;
	}
	else if(new_node->frequency > q->head->frequency){
		new_node->next = q->head;
		q->head = new_node;
	}
	else{
		node *current = create_node();
		current = q->head;
		
		while(current != NULL){
			if(current->next == NULL || current->next->frequency < new_node->frequency){	
				new_node->next = current->next;
				current->next = new_node;
				
				if(new_node->next == NULL){
					q->tail = new_node;
				}
				break;	
			}
			current = current->next;
		}
		current = NULL;
		free(current);
	}
	
	q->size++;
	return 1;
}

node* dequeue(queue *q){
	if(is_empty(q) == 1){
		return NULL;
	}
	else if(q->head == q->tail){
		node *new_node = create_node();
		new_node = q->head;
		q->head = NULL;
		q->size--;
		return(new_node);
	}
	else{
		node *current = create_node();
		
		current = q->head;
		
		while(current->next != q->tail){
			current = current->next;
		}
		
		node *new_node = create_node();
		new_node = current->next;
		q->tail = current;
		q->tail->next = NULL;
		
		current = NULL;
		free(current);
		q->size--;
		return new_node;	
	}
}


node* search(queue *q, char character){
	if(is_empty(q) == 0){
		node *needed_node = create_node();
		needed_node = q->head;
		while(needed_node->next != NULL){
			needed_node = needed_node->next;
			if(needed_node->data == character){
				return(needed_node);
			}
		}
	}
	return NULL;
}


void print_queue(queue *q){	
	if(is_empty(q) == 1){
		printf("The queue is empty");
		return;
	}
	
	node *temp = q->head;
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
