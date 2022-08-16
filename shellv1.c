#include <stdio.h>
#include <stdlib.h>
#define LEN 1

//String modulo
//

struct string{
	int max;
	int len;
	char *str;
};

struct node{
	struct string *data;
	struct node *next;
};

struct queue{
	struct node *first, *last;
};

void initstr(struct string *str){
	str->len = 0;
	str->max = LEN;
	str->str = malloc(sizeof(char) * str->max);
	str->str[str->len] = '\0';
}

void copystr(struct string **to, const struct string in){
	struct string *buf = malloc(sizeof(struct string));
	buf->max = in.max;
	buf->len = in.len;
	buf->str = malloc(sizeof(char) * buf->max);

	int i = 0;
	for(; i < in.len; i++)
		buf->str[i] = in.str[i];
	buf->str[in.len] = '\0';
	free((*to)->str);
	free(*to);
	*to = buf;
}

void resizestr(struct string **str){
	struct string *buf = malloc(sizeof(struct string));
	buf->max = (*str)->max + LEN;
	buf->len = (*str)->len;
	buf->str = malloc(sizeof(char) * buf->max);
	
	int i = 0;
	for(; i < (*str)->len; i++)
		buf->str[i] = (*str)->str[i];
	buf->str[buf->len] = '\0';
	free((*str)->str);
	free((*str));
	*str = buf;
}

char getstr(struct string **str, const char sep){
	
	char c;
	for(int i = 0; (c = getchar()) != EOF; i++){
		if(c == sep){
			(*str)->str[(*str)->len] = '\0';
			return sep;
		}
		if((*str)->len >= (*str)->max)
			resizestr(str);
		(*str)->str[i] = c;
		(*str)->len++;
	}
	(*str)->str[(*str)->len] = '\0';
	return EOF;
}

void clearstr(struct string *str){
	str->max = LEN;
	str->len = 0;
	free(str->str);
	initstr(str);
}

void pushstr(struct string **str, const char c){
	if((*str)->len >= (*str)->max)
		resizestr(str);
	(*str)->str[(*str)->len++] = c;
}

void chartostr(struct string **str, const char *arr){
	for(int i = 0; arr[i] != '\0'; i++)
		pushstr(str, arr[i]);
	pushstr(str, '\0');
}

//Queue
void initq(struct queue *q){
	q->first = NULL;
	q->last = q->first;
}

void pushq(struct queue *q, struct string *data){
	struct node *tmp = malloc(sizeof(struct string));
	tmp->data = malloc(sizeof(struct string));
	initstr(tmp->data);
	copystr(&tmp->data, *data);

	tmp->next = NULL;
	if(q->first == NULL){
		q->first = tmp;
		q->last = tmp;
	}else{
		q->first->next = tmp;
		q->first = q->first->next;
	}
}

int popq(struct queue *q, struct string **str){
	
	if(q->last == NULL){
		return 0;
	}
	struct node *tmp = q->last;

	copystr(str, *tmp->data);

	q->last = q->last->next;
	clearstr(tmp->data);
	free(tmp->data->str);
	free(tmp->data);
	free(tmp);
	return 1;
}

void processing(){
	printf("Processing\n");
}

int main(){
	struct string *str = malloc(sizeof(struct string));
	struct string *tmp = malloc(sizeof(struct string));
	struct queue q;
	initstr(str);
	initstr(tmp);
	initq(&q);
	char c;
	
	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n'){
			pushq(&q, str);
			//copystr(&tmp, *str);
			clearstr(str);

			//clearstr(tmp);	
		}else{
			pushstr(&str, c);
		}
		if(c == '\n'){
			while(popq(&q, &str))
				printf("%s\n", str->str);
			initq(&q);
			clearstr(str);
		}
	}
	return 0;
}
