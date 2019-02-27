#include<iostream>
#include<cstring>
using namespace std;
struct DigitalBlock
{
	unsigned char block;
	DigitalBlock *last;
	DigitalBlock *next;

	DigitalBlock(char c){
		block = c;
		last = NULL;
		next = NULL;
	}
};
class LinkList{
	private: 
	DigitalBlock *head;
	DigitalBlock *tail;


	public:
	LinkList(char c){
		head = new DigitalBlock(c);
		tail = head;
	}
	void insert(char c){
		insert(new DigitalBlock(c));
	}
	void insert(int index, char c){
		insert(index, new DigitalBlock(c));
	}
	void insert(int index, DigitalBlock *d){
		DigitalBlock *p = head;
		for(int i = 0; i <index && p->next!=NULL; i++)
		{
			p = p->next;
		}
		if (p==tail) {
			insert(d);
		}
		else
		{
			d->next = p->next;
			d->last = p;
			d->next->last = d;
			p->next = d;
		}
	}
	void insert(DigitalBlock *d){
		tail->next = d;
		d->last = tail;
		tail = d;
	}
	DigitalBlock* get_head(){
		return head;
	}
	DigitalBlock* get_tail(){
		return tail;
	}
	void reverse(){
		DigitalBlock *p = head->next, *q = tail;
		while(p!=q && p->last!=q){
			char temp;
			temp = p->block;
			p->block = q->block;
			q->block = temp;
			p = p->next;
			q = q->last;
		}
	}

	LinkList* to_binary(){
		LinkList *res = new LinkList(head->block);
		LinkList *temp = new LinkList(head->block);
		for (DigitalBlock *p = head->next; p != NULL;p=p->next)
		{
			temp->insert(p->block - '0');
		}
			int d, sum = 1;
		while(sum){
			sum = 0;
			DigitalBlock *p ;
			for (p = temp->head->next; p!=temp->tail; p = p->next)
			{
				d = (p->block) / 2;
				sum += d;
				p->next->block += (p->block) % 2 * 10;
				p->block = d ;
			}
			d = (p->block) / 2;
			sum += d;
			res->insert(new DigitalBlock((p->block) % 2 + '0'));
			p->block = d ;
		}
		res->reverse();
		return res;
	}

	LinkList* to_decimal(){
		LinkList *res = new LinkList(head->block);
		LinkList *temp = new LinkList(head->block);
		res->insert(tail->block);
		temp->insert('1');
		for (DigitalBlock *p = tail->last; p != head && p!=NULL;p=p->last)
		{
			temp->decimal_add_self();
			if(p->block-'0')
			{
				res->decimal_add(temp);
			}
		}
		return res;
	}

	void decimal_add_self()
	{
		int temp = 0;
		for (DigitalBlock *p = tail; p != head;p=p->last)
		{
			p->block = (p->block - '0')*2 + temp;
			temp = p->block / 10;
			p->block = p->block % 10 + '0';
		}
		if(temp){
			insert(0, '0' + temp);
		}
	}

	void decimal_add(LinkList *l)
	{
		DigitalBlock *q = tail;
		for (DigitalBlock *p = l->get_tail(); p != l->get_head();p=p->last)
		{
			int res = p->block - '0' + q->block - '0';
			q->block = res % 10 + '0';
			if(q->last==head || q->last==NULL)
			{
				insert(0, '0');
			}
			q->last->block += res / 10;
			q = q->last;
		}
	}
};

int main(int argc, char const *argv[])
{
	for(int i = 1; i < argc; i++)
	{
		LinkList *digital = new LinkList(' ');
		for(int j = 0,len = strlen(argv[i]) ; j < len ; j++)
		{
			digital->insert(argv[i][j]);
		}
		LinkList *res = digital->to_binary();
		res->reverse();
		res = res->to_decimal();
		DigitalBlock *p = res->get_head();
		while(p!=NULL){
			cout << p->block;
			p = p->next;
		}
	}
	return 0;
}
