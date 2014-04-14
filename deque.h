#ifndef DEQUE_H
#define DEQUE_H 

template<class K>
class deque{
private:
	//friend class const_iterator;
	class nodo{
	public:
		K info;
		nodo* next;
		nodo* prev;
		nodo(nodo*);
		nodo();
		nodo(const K&, nodo* , nodo* );
	};
	nodo* inizio;
	nodo* fine;
	void deep_delete();
	void deep_copy(const deque&);
public:
	

	class const_iterator{
	protected:
		nodo* ptr;
	public:
		const_iterator(nodo*);
		const_iterator(const const_iterator&);
		void operator++(int);
		const_iterator& operator++();
		void operator--(int);
		const_iterator& operator--();
		const K& operator*() const;
		const K* operator->() const;
		bool operator==(const const_iterator&) const;
		bool operator!=(const const_iterator&) const;
		bool null() const;
	};
	
	

	class iterator: public const_iterator{
	public:
		iterator(nodo*);
		iterator(const const_iterator&);
		K& operator*() const;
		K* operator->() const;
	};



	deque();
	deque(const deque<K>&);
	~deque();
	deque& operator=(const deque&);
	bool empty() const;
	int size() const;
	void insertAt(int,K);
	K& operator[](int)const;
	void clear();
	//void erase(const_iterator,const_iterator);
	//bool operator<(const deque&)const; implementare se serve confrontare le dim.
	iterator begin() const;
	iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	//iterator erase (const_iterator);
	//iterator erase (const_iterator,const_iterator);
	void push_front(const K&);
	void push_back(const K&);
	K pop_front();
	K pop_back();
	//void delete(iterator);
	void deleteAt(int);
};

//----------------------------------------CLASSE NODO
template<class K>
deque<K>::nodo::nodo(): info(), prev(0), next(0) {}

template<class K>
deque<K>::nodo::nodo(nodo* p){this=p;}

template<class K>
deque<K>::nodo::nodo(const K& data, nodo* precedente, nodo* successivo): info(data), prev(precedente), next(successivo) {}
//----------------------------------------------------


//----------------------------------------CLASSE DEQUE
template<class K>
void deque<K>::deep_delete(){
	if(empty()) return;
	while(inizio){
		nodo* a=inizio;
		inizio=inizio->next;
		delete a;
	}
	fine=0;
}

template<class K>
void deque<K>::deep_copy(const deque& dl){
	if(dl.empty()) return;
	inizio=new nodo(dl.inizio->info,0,0);
	nodo* d=inizio;
	nodo* p=dl.inizio->next;
	while(p){
		d->next=new nodo(p->info,d,0);
		fine=d->next;
		d=d->next; p=p->next;
	}
}

template<class K>
deque<K>::deque(): inizio(0), fine(0){}

template<class K>
deque<K>::deque(const deque& dl): inizio(0), fine(0){
	deep_copy(dl);
}

template<class K>
deque<K>::~deque(){
	deep_delete();
}

template<class K>
typename deque<K>::deque& deque<K>::operator=(const deque& dl){
	if(this!=&dl){
		deep_delete();
		deep_copy(dl);
	}
	return *this;
}

template<class K>
bool deque<K>::empty() const{
	return ((!inizio) && (!fine));
}

template<class K>
int deque<K>::size() const{
	int aux=0; nodo* p=inizio;
	while(p){
		++aux;p=p->next;
	}
	return aux;
}

template<class K>
void deque<K>::insertAt(int pos,K inf){//revisionare
	nodo* a=inizio;
	for(int i=0; i<pos; ++i){
		a=a->next;
	}
	nodo* b=new nodo(inf,a->prev,a);
	if(a->prev)
		a->prev->next=b;
	if(a->next)
		a->next->prev=b;
}

template<class K>
K& deque<K>::operator[](int a)const{
	nodo* p=inizio;
	for(int i=0; i<a; ++i){
		p=p->next;
	}
	return p->info;
}

template<class K>
void deque<K>::clear(){
	deep_delete();
}

template<class K>
typename deque<K>::const_iterator deque<K>::cbegin() const{
	return inizio;
}

template<class K>
typename deque<K>::const_iterator deque<K>::cend() const{
	return 0;
}

template<class K>
typename deque<K>::iterator deque<K>::begin() const{
	return inizio;
}

template<class K>
typename deque<K>::iterator deque<K>::end() const{
	return 0;
}

template<class K>
void deque<K>::push_front(const K& inf){
	if(empty()){
		inizio=new nodo(inf,0,0); fine=inizio;
	}else{
		inizio=new nodo(inf,0,inizio); inizio->next->prev=inizio;
	}
}

template<class K>
void deque<K>::push_back(const K& inf){
	if(empty()){
		fine=new nodo(inf,0,0); inizio=fine;
	}else{
		fine=new nodo(inf,fine,0); fine->prev->next=fine;
	}
}
template<class K>
K deque<K>::pop_front(){
	K aux=inizio->info;
	nodo* p=inizio;
	inizio=inizio->next;
	delete p;
	inizio->prev=0;
	return aux;
}

template<class K>
K deque<K>::pop_back(){
	K aux=fine->info;
	nodo* p=fine;
	fine=fine->prev;
	delete p;
	fine->next=0;
	return aux;
}

template<class K>
void deque<K>::deleteAt(int i){
	if(i<0 || i>=size()) return;
	int x=0;
	nodo* a=inizio;
	while(x<i){
		a=a->next;
	}
	if(inizio==fine){
		inizio=0;
		fine=0;
		delete a;
		return;
	}
	if(a==inizio){
		inizio=inizio->next;
		a->next->prev=0;
		delete a;
		return;
	}
	if(a==fine){
		fine=fine->prev;
		a->prev->next=0;
		delete a;
		return;
	}
	
	a->prev->next=a->next;
	a->next->prev=a->prev;
	delete a;
	return;

}

//----------------------------------------------------

//----------------------------------------CLASSE CONSTITERATOR
template <class K>
deque<K>::const_iterator::const_iterator(nodo* p): ptr(p){}

template <class K>
deque<K>::const_iterator::const_iterator(const const_iterator& it): ptr(it.ptr) {}

template<class K>
void deque<K>::const_iterator::operator++(int){
	ptr=ptr->next;
}

template<class K>
typename deque<K>::const_iterator& deque<K>::const_iterator::operator++(){
	ptr=ptr->next;
	return *this;
}

template<class K>
void deque<K>::const_iterator::operator--(int){
	ptr=ptr->prev;
}

template<class K>
typename deque<K>::const_iterator& deque<K>::const_iterator::operator--(){
	ptr=ptr->prev;
	return *this;
}

template<class K>
const K& deque<K>::const_iterator::operator*() const{
	return ptr->info;
}
template<class K>
const K* deque<K>::const_iterator::operator->() const{
	return &ptr->info;
}

template<class K>
bool deque<K>::const_iterator::operator==(const const_iterator& it) const{
	return ptr==it.ptr;
}

template<class K>
bool deque<K>::const_iterator::operator!=(const const_iterator& it) const{
	return ptr!=it.ptr;
}

template<class K>
bool deque<K>::const_iterator::null() const{
	return !ptr;
}

template<class K>
deque<K>::iterator::iterator(nodo* p): const_iterator(p){}

template<class K>
deque<K>::iterator::iterator(const const_iterator& it): const_iterator(it.ptr){}

template<class K>
K& deque<K>::iterator::operator*() const{
	return const_iterator::ptr->info;
}

template<class K>
K* deque<K>::iterator::operator->() const{
	return &const_iterator::ptr->info;
}
//----------------------------------------------------
#endif